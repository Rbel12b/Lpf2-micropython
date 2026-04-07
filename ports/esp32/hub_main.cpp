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

#include <Arduino.h>

#include "Lpf2/config.hpp"

#include "Board.h"
#include "BuiltInRGB.h"
#include "Ports.h"
#include "Utils.h"
#include "ExtSerialGPIO.h"

#include "Lpf2/HubEmulation.hpp"
#include "Lpf2/Hub.hpp"
#include "Lpf2/Virtual/Port.hpp"
#include "Lpf2/Virtual/Device.hpp"
#include "Lpf2/DeviceDescLib.hpp"
#include "Lpf2/Devices/ColorSensor.hpp"

#include "mod_hub.h"

void setup();
void loop();

extern "C" {
extern bool _btLibraryInUse;
}

void hub_init()
{
    _btLibraryInUse = true;
    initArduino();
    setup();
}

void hub_main_task(void *pvParameter)
{
    vTaskDelay(200 / portTICK_PERIOD_MS); // Wait for the mp_task to start and do its initializations

    while (true)
    {
        loop();
    }
}

Lpf2::Virtual::Port vLEDPort;
Lpf2::Virtual::GenericDevice vLED(Lpf2::DeviceDescriptors::HUB_LED);

int vLEDWriteCallback(uint8_t mode, const std::vector<uint8_t> &data, void* userData);

void setup()
{
    heap_caps_check_integrity_all(true);
    lpf2_log_printf("Booted.\n");
    Lpf2::DeviceRegistry::registerDefault();
    Lpf2::DeviceDescRegistry::registerDefault();

    BuiltInRGB_init();
    BuiltInRGB_setColor(0, 0, 0);

    gpio_set_pull_mode((gpio_num_t)I2C_SDA, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode((gpio_num_t)I2C_SCL, GPIO_PULLUP_ONLY);
    I2C_HW.begin(I2C_SDA, I2C_SCL, 400000);

    Ports_init();

    mod_hub_ports_init();

    vLED.setWriteDataCallback(vLEDWriteCallback);
    vLEDPort.attachDevice(&vLED);
}

void loop()
{
    vTaskDelay(1);
    Ports_update();
}

int vLEDWriteCallback(uint8_t mode, const std::vector<uint8_t> &data, void* userData)
{
    if (mode == 0 && data.size() >= 1)
    {
        Lpf2::ColorIDX color = (Lpf2::ColorIDX)data[0];
        BuiltInRGB_setColorIdx(color);
    }
    else if (mode == 1 && data.size() >= 3)
    {
        uint8_t r = data[0];
        uint8_t g = data[1];
        uint8_t b = data[2];
        BuiltInRGB_setColor(r, g, b);
    }
    return 0;
}