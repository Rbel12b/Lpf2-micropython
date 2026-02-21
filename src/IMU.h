#pragma once

#include <Wire.h>
#include "SparkFun_BNO08x_Arduino_Library.h"

extern BNO08x IMU;

int IMU_init(TwoWire &wirePort);
int IMU_update();