/**
 *  Copyright (C) 2026 - Rbel12b
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  */

#pragma once
#include "Lpf2/config.hpp"
#include "Lpf2/Local/IO/UART.hpp"
#include "Lpf2/Local/IO/IO.hpp"

#include <Arduino.h>
#include <HardwareSerial.h>

class Esp32s3Uart;
class Esp32s3MotorPWM;

using Lpf2UartPort = Esp32s3Uart;
using Lpf2PwmPort = Esp32s3MotorPWM;

#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_err.h"

class Esp32s3Uart : public Lpf2::Local::Uart
{
public:
    explicit Esp32s3Uart(uart_port_t uart_num)
        : uart_num_(uart_num)
    {
    }

    bool begin(uint32_t baudrate,
               uint32_t config = SERIAL_8N1,
               int id1_pin = -1,
               int id2_pin = -1)
    {
        baud_ = baudrate;
        config_ = config;
        id1_pin_ = id1_pin; // TX
        id2_pin_ = id2_pin; // RX

        // ADC mode by default
        setPinsToAnalog();

        m_uartActive = false;
        return true;
    }

    void end() override
    {
        if (m_uartActive)
        {
            uart_driver_delete(uart_num_);
            m_uartActive = false;
        }
        setPinsToAnalog();
    }

    void setBaudrate(uint32_t baudrate) override
    {
        baud_ = baudrate;

        if (!m_uartActive)
        {
            LPF2_LOG_W("Baudrate set to %u (UART not active, will take effect when UART is enabled)", baudrate);
            return;
        }

        uart_wait_tx_done(uart_num_, pdMS_TO_TICKS(100));
        uart_flush(uart_num_);
        uart_set_baudrate(uart_num_, baudrate);
        uart_flush(uart_num_);

        vTaskDelay(pdMS_TO_TICKS(10));

        LPF2_LOG_D("Baudrate set to %u", baudrate);
    }

    size_t write(const uint8_t *data, size_t length) override
    {
        if (!m_uartActive || !data || length == 0)
        {
            LPF2_LOG_W("Attempted to write to UART while inactive or with invalid data/length");
            return 0;
        }

        int written = uart_write_bytes(uart_num_, (const char *)data, length);
        return written < 0 ? 0 : written;
    }

    int read() override
    {
        if (!m_uartActive)
            return -1;

        uint8_t byte;
        int len = uart_read_bytes(uart_num_, &byte, 1, 0);
        return (len == 1) ? byte : -1;
    }

    size_t read(uint8_t *data, size_t length) override
    {
        if (!m_uartActive || !data || length == 0)
            return 0;

        int len = uart_read_bytes(uart_num_, (void *)data, length, 0);
        return len < 0 ? 0 : len;
    }

    int available() override
    {
        if (!m_uartActive)
            return 0;

        size_t buffered = 0;
        uart_get_buffered_data_len(uart_num_, &buffered);
        return buffered;
    }

    void flush() override
    {
        if (!m_uartActive)
            return;

        uart_flush(uart_num_);
    }

    void setUartPinsState(bool highZ) override
    {
        LPF2_LOG_D("Setting uart pins state: highZ=%s", highZ ? "true" : "false");
        if (highZ)
        {
            // Switch to ADC mode
            if (m_uartActive)
            {
                uart_flush(uart_num_);
                uart_wait_tx_done(uart_num_, pdMS_TO_TICKS(100));
                uart_driver_delete(uart_num_);
                m_uartActive = false;
            }

            setPinsToAnalog();
        }
        else
        {
            // Switch to UART mode
            initUart();
            m_uartActive = true;
        }
    }

    float readCh(uint8_t ch) override
    {
        int pin = (ch == 0) ? id1_pin_ : id2_pin_;

        if (pin < 0)
        {
            return 0.0f;
        }

        // ESP32 ADC: 12-bit by default (0–4095), reference ~3.3V
        constexpr float VREF = 3.3f;
        int raw = analogRead(pin);
        return (raw / 4095.0f) * VREF;
    }

private:
    void initUart()
    {
        gpio_set_direction((gpio_num_t)id1_pin_, GPIO_MODE_OUTPUT);
        gpio_set_drive_capability((gpio_num_t)id1_pin_, GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_level((gpio_num_t)id1_pin_, 1);
        ets_delay_us(50);

        uart_config_t uart_config = {};
        uart_config.baud_rate = baud_;
        uart_config.data_bits = UART_DATA_8_BITS;
        uart_config.parity = UART_PARITY_DISABLE;
        uart_config.stop_bits = UART_STOP_BITS_1;
        uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
        uart_config.source_clk = UART_SCLK_DEFAULT;

        uart_param_config(uart_num_, &uart_config);

        uart_driver_install(uart_num_, 1024, 0, 0, NULL, 0);

        uart_set_pin(uart_num_,
                     id1_pin_,
                     id2_pin_,
                     UART_PIN_NO_CHANGE,
                     UART_PIN_NO_CHANGE);

        uart_flush(uart_num_);

        vTaskDelay(pdMS_TO_TICKS(20));
    }

    void setPinsToAnalog()
    {
        if (id1_pin_ >= 0)
        {
            pinMode(id1_pin_, INPUT);
            gpio_reset_pin((gpio_num_t)id2_pin_);
        }

        if (id2_pin_ >= 0)
        {
            pinMode(id2_pin_, INPUT);
            gpio_reset_pin((gpio_num_t)id2_pin_);
        }
    }

private:
    uart_port_t uart_num_;

    int id1_pin_ = -1; // TX
    int id2_pin_ = -1; // RX

    uint32_t baud_ = 115200;
    uint32_t config_ = SERIAL_8N1;

    bool m_uartActive = false;
};

#include "driver/mcpwm.h"

class Esp32s3MotorPWM : public Lpf2::Local::PWM
{
public:
    explicit Esp32s3MotorPWM() = default;

    int init(int pin1,
             int pin2,
             mcpwm_unit_t unit,
             mcpwm_timer_t timer,
             uint32_t freq = 1000)
    {
        pin1_ = pin1;
        pin2_ = pin2;
        unit_ = unit;
        timer_ = timer;
        freq_ = freq;

        gpio_reset_pin((gpio_num_t)pin1_);
        gpio_reset_pin((gpio_num_t)pin2_);
        gpio_set_direction((gpio_num_t)pin1_, GPIO_MODE_INPUT);
        gpio_set_direction((gpio_num_t)pin2_, GPIO_MODE_INPUT);

        // Attach GPIOs
        mcpwm_gpio_init(unit_, mcpwm_io_signals_t(MCPWM0A + timer_ * 2), pin1_);
        mcpwm_gpio_init(unit_, mcpwm_io_signals_t(MCPWM0B + timer_ * 2), pin2_);

        mcpwm_config_t cfg = {};
        cfg.frequency = freq_;
        cfg.cmpr_a = 0;
        cfg.cmpr_b = 0;
        cfg.counter_mode = MCPWM_UP_COUNTER;
        cfg.duty_mode = MCPWM_DUTY_MODE_0;

        mcpwm_init(unit_, timer_, &cfg);

        LPF2_LOG_D("Initialized PWM on pins %d (ch1) and %d (ch2) with frequency %u Hz, mcpwm unit: %i, timer: %i", pin1_, pin2_, freq_, unit_, timer_);

        return 0;
    }

    void out(uint8_t ch1, uint8_t ch2) override
    {
        // Convert 0–255 → percentage
        float dutyA = (ch1 * 100.0f) / 255.0f;
        float dutyB = (ch2 * 100.0f) / 255.0f;

        mcpwm_set_duty(unit_, timer_, MCPWM_OPR_A, dutyA);
        mcpwm_set_duty(unit_, timer_, MCPWM_OPR_B, dutyB);

        mcpwm_set_duty_type(unit_, timer_, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty_type(unit_, timer_, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

        LPF2_LOG_D("PWM output set: ch1=%u (%.1f%%) -> pin: %i, ch2=%u (%.1f%%) -> pin: %i", ch1, dutyA, pin1_, ch2, dutyB, pin2_);
    }

private:
    int pin1_ = -1;
    int pin2_ = -1;
    mcpwm_unit_t unit_;
    mcpwm_timer_t timer_;
    uint32_t freq_ = 1000;
};

class Esp32s3IO : public Lpf2::Local::IO
{
public:
    Esp32s3IO(int uartNum) : m_uart((uart_port_t)uartNum) {}

    Lpf2::Local::PWM *getPWM() override
    {
        return &m_pwm;
    }

    Lpf2::Local::Uart *getUart() override
    {
        return &m_uart;
    }

    /**
     * @brief Initialize the IO ports.
     * @param id1_pin The analog input connected to the TX pin, external 47k pull-up is required.
     * @param id2_pin The analog input connected to the RX pin, external 47k pull-up is required.
     * @param pwm_pin1 The first PWM output pin. Use -1 for no PWM.
     * @param pwm_pin2 The second PWM output pin. Use -1 for no PWM.
     * @param freq The PWM frequency in Hz.
     * @param resolution The PWM resolution in bits.
     * @param channel1 The PWM channel for the first pin.
     * @param channel2 The PWM channel for the second pin.
     * @return 0 if initialization was successful, -1 otherwise.
     * @note Must be called before any IO operations. (Before calling init on Lpf2Port or update on Lpf2DeviceManager)
     */
    int init(int id1_pin = -1, int id2_pin = -1, int pwm_pin1 = -1, int pwm_pin2 = -1, mcpwm_unit_t unit = mcpwm_unit_t(0), mcpwm_timer_t timer = mcpwm_timer_t(0), uint32_t freq = 1000)
    {
        if (!m_uart.begin(115200, SERIAL_8N1, id1_pin, id2_pin))
        {
            return -1;
        }
        if (m_pwm.init(pwm_pin1, pwm_pin2, unit, timer, freq) != 0)
        {
            return -1;
        }
        m_inited = true;
        return 0;
    }

    bool ready() const override
    {
        return m_inited;
    }

private:
    Esp32s3Uart m_uart;
    Esp32s3MotorPWM m_pwm;
    bool m_inited = false;
};
