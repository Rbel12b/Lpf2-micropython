#pragma once

#include "Lpf2/Port.hpp"

#include "mp_bridge.h"

class PortTrampoline : public Lpf2::Port
{
public:
    mp_obj_t self;

    PortTrampoline(mp_obj_t self_in) : self(self_in) {}

    void update() override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_update);
        mp_bridge_call_function_0(method);
    }

    int writeData(uint8_t modeNum, const std::vector<uint8_t> &data) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_writeData);

        mp_obj_t args[2] = {
            mp_bridge_obj_new_int(modeNum),
            mp_bridge_obj_new_bytes(data.data(), data.size())};

        mp_obj_t ret = mp_bridge_call_function_n_kw(method, 2, 0, args);
        return mp_bridge_obj_get_int(ret);
    }

    void startPower(int8_t pw) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_startPower);
        mp_bridge_call_function_1(method, mp_bridge_obj_new_int(pw));
    }

    void setAccTime(uint16_t accTime, Lpf2::AccelerationProfile accProfile = 1) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_setAccTime);
        mp_obj_t args[2] = {
            mp_bridge_obj_new_int(accTime),
            mp_bridge_obj_new_int(accProfile)};
        mp_bridge_call_function_n_kw(method, 2, 0, args);
    }

    void setDecTime(uint16_t decTime, Lpf2::AccelerationProfile decProfile = 1) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_setDecTime);
        mp_obj_t args[2] = {
            mp_bridge_obj_new_int(decTime),
            mp_bridge_obj_new_int(decProfile)};
        mp_bridge_call_function_n_kw(method, 2, 0, args);
    }

    void startSpeed(int8_t speed, uint8_t maxPower, uint8_t useProfile = 0) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_startSpeed);
        mp_obj_t args[3] = {
            mp_bridge_obj_new_int(speed),
            mp_bridge_obj_new_int(maxPower),
            mp_bridge_obj_new_int(useProfile)};
        mp_bridge_call_function_n_kw(method, 3, 0, args);
    }

    void startSpeedForTime(uint16_t time, int8_t speed, uint8_t maxPower, Lpf2::BrakingStyle endState, uint8_t useProfile = 0) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_startSpeedForTime);
        mp_obj_t args[5] = {
            mp_bridge_obj_new_int(time),
            mp_bridge_obj_new_int(speed),
            mp_bridge_obj_new_int(maxPower),
            mp_bridge_obj_new_int((uint8_t)endState),
            mp_bridge_obj_new_int(useProfile)};
        mp_bridge_call_function_n_kw(method, 5, 0, args);
    }

    void startSpeedForDegrees(uint32_t degrees, int8_t speed, uint8_t maxPower, Lpf2::BrakingStyle endState, uint8_t useProfile = 0) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_startSpeedForDegrees);
        mp_obj_t args[5] = {
            mp_bridge_obj_new_int(degrees),
            mp_bridge_obj_new_int(speed),
            mp_bridge_obj_new_int(maxPower),
            mp_bridge_obj_new_int((uint8_t)endState),
            mp_bridge_obj_new_int(useProfile)};
        mp_bridge_call_function_n_kw(method, 5, 0, args);
    }

    void gotoAbsPosition(int32_t absPos, uint8_t speed, uint8_t maxPower, Lpf2::BrakingStyle endState, uint8_t useProfile = 0) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_gotoAbsPosition);
        mp_obj_t args[5] = {
            mp_bridge_obj_new_int(absPos),
            mp_bridge_obj_new_int(speed),
            mp_bridge_obj_new_int(maxPower),
            mp_bridge_obj_new_int((uint8_t)endState),
            mp_bridge_obj_new_int(useProfile)};
        mp_bridge_call_function_n_kw(method, 5, 0, args);
    }
        
    void presetEncoder(int32_t pos) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_presetEncoder);
        mp_bridge_call_function_1(method, mp_bridge_obj_new_int(pos));
    }

    int setMode(uint8_t mode) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_setMode);
        mp_obj_t ret = mp_bridge_call_function_1(method, mp_bridge_obj_new_int(mode));
        return mp_bridge_obj_get_int(ret);
    }

    int setModeCombo(uint8_t idx) override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_setModeCombo);
        mp_obj_t ret = mp_bridge_call_function_1(method, mp_bridge_obj_new_int(idx));
        return mp_bridge_obj_get_int(ret);
    }

    bool deviceConnected() override
    {
        mp_obj_t method = mp_bridge_load_attr(self, MP_QSTR_deviceConnected);
        mp_obj_t ret = mp_bridge_call_function_0(method);
        return mp_bridge_obj_is_true(ret);
    }
};