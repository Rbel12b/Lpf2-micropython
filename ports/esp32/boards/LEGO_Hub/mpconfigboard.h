#ifndef MICROPY_HW_BOARD_NAME
// Can be set by mpconfigboard.cmake.
#define MICROPY_HW_BOARD_NAME               "ESP32S3 LEGO Hub"
#endif
#define MICROPY_HW_MCU_NAME                 "ESP32S3"

// Use native USB
#define MICROPY_HW_ENABLE_UART_REPL         (1)
// #define MICROPY_HW_USB_CDC                  (0)
// #define MICROPY_HW_ESP_USB_SERIAL_JTAG      (1)

#define MICROPY_HW_I2C0_SCL                 (42)
#define MICROPY_HW_I2C0_SDA                 (8)
