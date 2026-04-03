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

#include "Utils.h"
#include "Lpf2/config.hpp"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_cali_scheme.h"
#include <driver/gpio.h>

unsigned long util_panStartTime = 0;

int panValue()
{
    const unsigned long halfPeriod = 3000; // 3 seconds
    const unsigned long fullPeriod = 6000; // 6 seconds

    unsigned long now = LPF2_GET_TIME();
    unsigned long t = (now - util_panStartTime) % fullPeriod;

    if (t < halfPeriod)
    {
        // 0 -> 180
        return Lpf2::Utils::map(t, 0l, halfPeriod, 0l, 180l);
    }
    else
    {
        // 180 -> 0
        return Lpf2::Utils::map(t - halfPeriod, 0l, halfPeriod, 180l, 0l);
    }
}