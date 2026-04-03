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
#ifndef _PORTS_H_
#define _PORTS_H_

#include "Arduino.h"
#include "Lpf2/DeviceManager.hpp"
#include "ESP32S3_IO.h"
#include "Lpf2/HubEmulation.hpp"
#include "Lpf2/Local/Port.hpp"

extern Lpf2::Local::Port portA;
extern Lpf2::Local::Port portB;
extern Lpf2::Local::Port portC;
extern Lpf2::Local::Port portD;

void Ports_init();
void Ports_update();

#endif