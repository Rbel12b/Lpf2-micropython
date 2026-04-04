# Hardware

This directory contains the hardware design files for the custom LEGO lpf2 hub. The design is still in progress, and the current version is v2. The design files are available (or will be available) in the [hardware/v2](hardware/v2) directory. The design was created using EasyEDA.

## Overview

The board has a 4-pin conector for a battery pack, with the following pinout (top view):

| Pin | Function |
| --- | --- |
| 1 | 5v suply from the board (to charge the battery when the board is powered from usb) |
| 2 | 9v from the battery (or directly the positive terminal of a 2S lipo - max ~8.4V) |
| 3 | GND |
| 4 | Vbatt - battery voltage measurement pin, max 8.4V |

### LPF2 ports

For the port pinout, visit Philippe Hurbain's website: [https://www.philohome.com/lpf2/lpf2.htm](https://www.philohome.com/wedo2reverse/connect.htm)

Currently the ID1 and ID2 pins are directly connected to the mcu, with a 47k pull-up to 3v3.
The motor pwm pins are connected to a H-bridge, which is controlled by the mcu. The H-bridge is powered by a separate 9v supply, for a battery pack.
Each port requires an UART pheripherial, but the esp32s3 has 3 of them, so one one of the ports is connected to a SC16IS750 I2C to UART bridge, which is controlled by the mcu through I2C. This allows to have 4 ports with only 3 UARTs on the mcu.

I bought the connectors from aliexpress, and they are compatible with the official ones, but their quality is not the best.

### I2C port

The i2c port is a standard 4-pin header, with the following pinout:

| Pin | Function |
| --- | --- |
| 1 | SCL |
| 2 | SDA |
| 3 | 3v3 |
| 4 | GND |

## Copyright and License

Copyright (C) 2026 Rbel12b

The contents of this directory are licensed under CC-BY-NC-SA 4.0. See the [LICENSE](LICENSE) file for more details.
