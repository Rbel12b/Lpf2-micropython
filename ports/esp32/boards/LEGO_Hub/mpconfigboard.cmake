set(IDF_TARGET esp32s3)

set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/sdkconfig.ble
    boards/LEGO_Hub/sdkconfig.board
    boards/sdkconfig.240mhz
    boards/sdkconfig.spiram
    boards/sdkconfig.spiram_oct
)

list(APPEND MICROPY_DEF_BOARD
    MICROPY_HW_BOARD_NAME="ESP32S3 LEGO Hub"
)