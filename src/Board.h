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
#ifndef _BOARD_H_
#define _BOARD_H_

// Onboard RGB LED
#define HUB_LED_PIN 40

// Port pwm pins
#define PORT_A_PWM_1 21
#define PORT_A_PWM_2 10

#define PORT_B_PWM_1 7
#define PORT_B_PWM_2 6

#define PORT_C_PWM_1 48
#define PORT_C_PWM_2 47

#define PORT_D_PWM_1 4
#define PORT_D_PWM_2 5

// Port ID pins
#define PORT_A_ID_1 15
#define PORT_A_ID_2 16

#define PORT_B_ID_1 17
#define PORT_B_ID_2 18

#define PORT_C_ID_1 13
#define PORT_C_ID_2 12

#define PORT_D_ID_1 11
#define PORT_D_ID_2 14

#define PORT_A_PWM_UNIT mcpwm_unit_t(0)
#define PORT_A_PWM_TIMER mcpwm_timer_t(0)

#define PORT_B_PWM_UNIT mcpwm_unit_t(0)
#define PORT_B_PWM_TIMER mcpwm_timer_t(1)

#define PORT_C_PWM_UNIT mcpwm_unit_t(0)
#define PORT_C_PWM_TIMER mcpwm_timer_t(2)

#define PORT_D_PWM_UNIT mcpwm_unit_t(1)
#define PORT_D_PWM_TIMER mcpwm_timer_t(0)

// Port Hardware serial numbers
#define PORT_A_HWS 1
#define PORT_B_HWS 2
#define PORT_C_HWS 0
#define PORT_D_HWS -1

#define I2C_SDA 8
#define I2C_SCL 42
#define I2C_HW Wire1

#define BNO08X_INT -1
#define BNO08X_RST -1

// The SC16IS750's pin used to disable TX outputs when the port is in UART mode. Connected to the #OE pin of the TX output buffer.
#define PORT_D_TX_DISABLE 2

#endif