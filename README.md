# Lpf2-micropython

A micropython port for a custom LEGO lpf2 hub with an esp32s3, with some extra modules (like the Lpf2 library)

> **Note:** This project is still a work in progress (WIP). Features and documentation may change significantly as development continues.

I'm planning it to support the following "features":

- 4x lpf2 ports
- hub emulation (so it can be used with the official app)
- controlling other lpf2 hubs
- an i2c port for connecting sensors and other devices
- all this usable from microPython

all this from micropython, with some code running in the background to handle the communication with the ports and the app.

## Hardware

See the [hardware/README.md](hardware/README.md) file for more details about the hardware design and implementation.

## Software

The software is still in the early stages of development, currently local ports are messed up, only hub emulation is working, and the i2c port is not implemented yet. Micropython integration is missing entirely.

## Copyright and License

Copyright (C) 2026 Rbel12b

The project (excluding the [hardware/](hardware/README.md) directory) is licensed uder the AGPL-3.0 License. See the [LICENSE](LICENSE) file for more details.
