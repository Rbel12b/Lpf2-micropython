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

#include "Ports.h"
#include "Board.h"
#include "Lpf2/Devices/DistanceSensor.hpp"
#include "Lpf2/Devices/ColorSensor.hpp"
#include "Lpf2/Devices/BasicMotor.hpp"
#include "Lpf2/Devices/EncoderMotor.hpp"
#include "Utils.h"
#include "ExtSerialGPIO.h"

class Lpf2ExtSerialIO: public Lpf2::Local::IO
{
public:
    Lpf2ExtSerialIO() {}

    Lpf2::Local::PWM *getPWM() override
    {
        return &m_pwm;
    }

    Lpf2::Local::Uart *getUart() override
    {
        return m_uart;
    }

    /**
     * @brief Initialize the IO ports.
     * @param pwm_pin1 The first PWM output pin. Use -1 for no PWM.
     * @param pwm_pin2 The second PWM output pin. Use -1 for no PWM.
     * @param freq The PWM frequency in Hz.
     * @param resolution The PWM resolution in bits.
     * @param channel1 The PWM channel for the first pin.
     * @param channel2 The PWM channel for the second pin.
     * @return 0 if initialization was successful, -1 otherwise.
     * @note Must be called before any IO operations. (Before calling init on Lpf2Port or update on Lpf2DeviceManager)
     */
    int init(Lpf2ExtSerial *uart, int pwm_pin1 = -1, int pwm_pin2 = -1, mcpwm_unit_t unit = mcpwm_unit_t(0), mcpwm_timer_t timer = mcpwm_timer_t(0), uint32_t freq = 1000)
    {
        m_uart = uart;
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
    Lpf2ExtSerial *m_uart;
    Esp32s3MotorPWM m_pwm;
    bool m_inited = false;
};

Esp32s3IO portA_IO(PORT_A_HWS);
Esp32s3IO portB_IO(PORT_B_HWS);
Esp32s3IO portC_IO(PORT_C_HWS);
Lpf2ExtSerialIO portD_IO;

Lpf2::Local::Port portA(portA_IO);
Lpf2::Local::Port portB(portB_IO);
Lpf2::Local::Port portC(portC_IO);
Lpf2::Local::Port portD(portD_IO);

ExtSerialGPIO extSerialGPIO(I2C_HW, 3686400);
Lpf2ExtSerial *extSerial;

#define initIOForPort(_port)                                        \
    port##_port##_IO.init(PORT_##_port##_ID_1, PORT_##_port##_ID_2, \
                          PORT_##_port##_PWM_1, PORT_##_port##_PWM_2, PORT_##_port##_PWM_UNIT, PORT_##_port##_PWM_TIMER, 1000);
void Ports_init()
{
    initIOForPort(A);
    initIOForPort(B);
    initIOForPort(C);
    
    extSerialGPIO.begin();
    extSerial = new Lpf2ExtSerial(&extSerialGPIO);
    extSerial->init(PORT_D_ID_1, PORT_D_ID_2, PORT_D_TX_DISABLE);
    
    portD_IO.init(extSerial, PORT_D_PWM_1, PORT_D_PWM_2);

    portA.init();
    portB.init();
    portC.init();
    portD.init();
}

void Ports_update()
{
    portA.update();
    portB.update();
    portC.update();
    portD.update();
}