/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Patrick Van Oosterwijck
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/runtime.h"
#include "py/mphal.h"
#include "usb_serial_jtag.h"

#if MICROPY_HW_ESP_USB_SERIAL_JTAG

#include "driver/usb_serial_jtag.h"
#include "driver/usb_serial_jtag_select.h"
#include "esp_intr_alloc.h"
#include "soc/periph_defs.h"
#include "freertos/portmacro.h"

// Number of bytes in the input buffer, and number of bytes for output chunking.
#define USB_SERIAL_JTAG_PACKET_SZ_BYTES (64)

static DRAM_ATTR portMUX_TYPE rx_mux = portMUX_INITIALIZER_UNLOCKED;
static uint8_t rx_buf[USB_SERIAL_JTAG_PACKET_SZ_BYTES];

static void usb_serial_jtag_handle_rx(void) {
    if (xPortInIsrContext()) {
        portENTER_CRITICAL_ISR(&rx_mux);
    } else {
        portENTER_CRITICAL(&rx_mux);
    }
    size_t req_len = ringbuf_free(&stdin_ringbuf);
    if (req_len > USB_SERIAL_JTAG_PACKET_SZ_BYTES) {
        req_len = USB_SERIAL_JTAG_PACKET_SZ_BYTES;
    }
    size_t len = usb_serial_jtag_read_bytes(rx_buf, req_len, 0);
    for (size_t i = 0; i < len; ++i) {
        if (rx_buf[i] == mp_interrupt_char) {
            mp_sched_keyboard_interrupt();
        } else {
            ringbuf_put(&stdin_ringbuf, rx_buf[i]);
        }
    }
    if (xPortInIsrContext()) {
        portEXIT_CRITICAL_ISR(&rx_mux);
    } else {
        portEXIT_CRITICAL(&rx_mux);
    }
}

static usb_serial_jtag_driver_config_t usb_serial_jtag_confing = USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT();

void usb_serial_jtag_notif_callback(usj_select_notif_t notif, BaseType_t *task_woken)
{
    if (notif == USJ_SELECT_READ_NOTIF) {
        usb_serial_jtag_handle_rx();
        mp_hal_wake_main_task_from_isr();
    }
};

void usb_serial_jtag_init(void) {
    usb_serial_jtag_driver_install(&usb_serial_jtag_confing);
    usb_serial_jtag_set_select_notif_callback(usb_serial_jtag_notif_callback);
}

void usb_serial_jtag_poll_rx(void) {
    if (usb_serial_jtag_read_ready()) {
        usb_serial_jtag_handle_rx();
    }
}

void usb_serial_jtag_tx_strn(const char *str, size_t len) {
    if (len == 0 || !usb_serial_jtag_is_connected()) {
        return;
    }
    usb_serial_jtag_write_bytes(str, len, pdMS_TO_TICKS(10));
}

#endif // MICROPY_HW_ESP_USB_SERIAL_JTAG
