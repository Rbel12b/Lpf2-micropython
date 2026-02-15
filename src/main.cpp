#include "config.h"
#include <Arduino.h>

#include "Board.h"
#include "BuiltInRGB.h"
#include "Ports.h"
#include "Utils.h"

#include "Lpf2HubEmulation.hpp"
#include "Lpf2Hub.hpp"
#include "Lpf2Virtual/Lpf2PortVirtual.hpp"
#include "Lpf2Virtual/Lpf2VirtualDevice.hpp"
#include "Lpf2DeviceDescLib.hpp"
#include "Lpf2Devices/ColorSensor.hpp"

extern "C" int serial_vprintf(const char *fmt, va_list args)
{
    BuitlInRGB_setColor(0, 10, 0);
    va_list copy;
    va_copy(copy, args);

    int len = vsnprintf(nullptr, 0, fmt, copy);
    va_end(copy);

    if (len <= 0)
        return 0;

    std::vector<char> buf(len + 1);
    vsnprintf(buf.data(), buf.size(), fmt, args);

    Serial.write((uint8_t *)buf.data(), len);
    return len;
}

Lpf2HubEmulation vHub("Technic Hub", Lpf2HubType::CONTROL_PLUS_HUB);
Lpf2Hub hub;

void setup()
{
    heap_caps_check_integrity_all(true);
    Serial.begin(981200);
    lpf2_log_printf("booted.");

    Lpf2DeviceRegistry::registerDefault();
    Lpf2DeviceDescRegistry::registerDefault();

    esp_log_set_vprintf(serial_vprintf);

    BuitlInRGB_init();
    BuitlInRGB_setColor(0, 0, 10);

    initPorts();

    util_panStartTime = millis();

#if EMULATE_HUB == 1
    vHub.attachPort((Lpf2PortNum)Lpf2ControlPlusHubPort::A, &portA);
    vHub.start();
    vHub.setHubBatteryLevel(50);
    vHub.setHubBatteryType(Lpf2BatteryType::NORMAL);
#else
    hub.init();
#endif
}

auto portALastDeviceType = Lpf2DeviceType::UNKNOWNDEVICE;
bool isSubscribed = false;

void loop()
{
    vTaskDelay(1);

    updatePorts();
    if (portB.deviceConnected())
    {
        auto s = portB.getInfoStr();
        for (size_t i = 0; i < s.size(); i += 128)
        {
            Serial.write(s.data() + i, std::min<size_t>(128, s.size() - i));
            delay(1); // let other tasks breathe
        }
    }
#if EMULATE_HUB == 1
    vHub.update();

    if (vHub.isSubscribed != isSubscribed)
    {
        isSubscribed = vHub.isSubscribed;
        if (isSubscribed)
        {
            BuitlInRGB_setColor(0, 10, 0);
        }
        else
        {
            BuitlInRGB_setColor(10, 0, 0);
        }
    }

    // a way to reset
    if (portA.getDeviceType() == Lpf2DeviceType::TECHNIC_LARGE_LINEAR_MOTOR)
    {
        ESP.restart();
    }
#else
    if (!hub.isConnected() && !hub.isConnecting())
    {
        hub.init();
        vTaskDelay(500);
    }

    // connect flow. Search for BLE services and try to connect if the uuid of the hub is found
    if (hub.isConnecting())
    {
        hub.connectHub();
        if (hub.isConnected())
        {
            Serial.println("Connected to HUB");
        }
        else
        {
            Serial.println("Failed to connect to HUB");
        }
    }

    if (hub.isConnected())
    {
        hub.update();
        static bool printedInfos = false;
        if (!printedInfos && hub.infoReady())
        {
            auto s = hub.getAllInfoStr();
            for (size_t i = 0; i < s.size(); i += 128)
            {
                Serial.write(s.data() + i, std::min<size_t>(128, s.size() - i));
                delay(1); // let other tasks breathe
            }
            printedInfos = true;
        }

        auto &r_portA = *hub.getPort(Lpf2PortNum(Lpf2ControlPlusHubPort::A));
        if (r_portA.deviceConnected())
        {
            static bool portASetupDone = false;
            if (!portASetupDone)
            {
                r_portA.setMode(0);
                portASetupDone = true;
            }

            if (r_portA.getDeviceType() == Lpf2DeviceType::TECHNIC_COLOR_SENSOR)
            {
                auto device = new TechnicColorSensor(r_portA);
    
                switch (device->getColorIdx())
                {
                case Lpf2Color::BLACK:
                    BuitlInRGB_setColor(0, 0, 0);
                    break;
                case Lpf2Color::BLUE:
                    BuitlInRGB_setColor(0, 0, 50);
                    break;
                case Lpf2Color::GREEN:
                    BuitlInRGB_setColor(0, 50, 0);
                    break;
                case Lpf2Color::RED:
                    BuitlInRGB_setColor(50, 0, 0);
                    break;
                case Lpf2Color::WHITE:
                    BuitlInRGB_setColor(50, 50, 50);
                    break;
                case Lpf2Color::YELLOW:
                    BuitlInRGB_setColor(50, 50, 0);
                    break;
                case Lpf2Color::ORANGE:
                    BuitlInRGB_setColor(50, 20, 0);
                    break;
                case Lpf2Color::PURPLE:
                    BuitlInRGB_setColor(30, 0, 30);
                    break;
                case Lpf2Color::PINK:
                    BuitlInRGB_setColor(50, 0, 20);
                    break;
                case Lpf2Color::LIGHTBLUE:
                    BuitlInRGB_setColor(0, 20, 50);
                    break;
                case Lpf2Color::CYAN:
                    BuitlInRGB_setColor(0, 50, 50);
                    break;
    
                default:
                    BuitlInRGB_setColor(0, 0, 0);
                    break;
                }
            }
        }
    }
#endif
}