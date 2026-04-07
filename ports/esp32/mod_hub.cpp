extern "C" {
#include "py/runtime.h"
}
#include "Ports.h"
#include "mod_types.h"
#include "mod_hub.h"
#include "BuiltInRGB.h"

extern "C"
{
    // --- instances ---
    static mp_obj_lpf2_port_t port_A_obj;
    static mp_obj_lpf2_port_t port_B_obj;
    static mp_obj_lpf2_port_t port_C_obj;
    static mp_obj_lpf2_port_t port_D_obj;
    static mp_obj_lpf2_port_t port_LED_obj;

    void mod_hub_ports_init()
    {
        port_A_obj.base.type = &lpf2_port_type;
        port_A_obj.cpp_obj = &portA;

        port_B_obj.base.type = &lpf2_port_type;
        port_B_obj.cpp_obj = &portB;

        port_C_obj.base.type = &lpf2_local_port_type;
        port_C_obj.cpp_obj = &portC;

        port_D_obj.base.type = &lpf2_port_type;
        port_D_obj.cpp_obj = &portD;

        port_LED_obj.base.type = &lpf2_port_type;
        port_LED_obj.cpp_obj = &vLEDPort;
    }

    // --- ports module ---
    static const mp_rom_map_elem_t ports_globals_table[] = {
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_ports) },
        { MP_ROM_QSTR(MP_QSTR_A), MP_ROM_PTR(&port_A_obj) },
        { MP_ROM_QSTR(MP_QSTR_B), MP_ROM_PTR(&port_B_obj) },
        { MP_ROM_QSTR(MP_QSTR_C), MP_ROM_PTR(&port_C_obj) },
        { MP_ROM_QSTR(MP_QSTR_D), MP_ROM_PTR(&port_D_obj) },
        { MP_ROM_QSTR(MP_QSTR_LED), MP_ROM_PTR(&port_LED_obj) },
    };
    static MP_DEFINE_CONST_DICT(ports_globals, ports_globals_table);

    const mp_obj_module_t hub_ports_module = {
        .base = {&mp_type_module},
        .globals = (mp_obj_dict_t *)&ports_globals,
    };

    // --- log module ---
    static mp_obj_t log_setLevel(mp_obj_t level)
    {
        lpf2_set_runtime_log_level(mp_obj_get_int(level));
        return mp_const_none;
    }

    static MP_DEFINE_CONST_FUN_OBJ_1(log_setLevel_obj, log_setLevel);

    static const mp_rom_map_elem_t log_globals_table[] = {
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_log) },
        { MP_ROM_QSTR(MP_QSTR_setLevel), MP_ROM_PTR(&log_setLevel_obj) },
    };
    static MP_DEFINE_CONST_DICT(log_globals, log_globals_table);

    const mp_obj_module_t hub_log_module = {
        .base = {&mp_type_module},
        .globals = (mp_obj_dict_t *)&log_globals,
    };

    // --- led module ---
    static mp_obj_t led_setColorRGB(mp_obj_t r, mp_obj_t g, mp_obj_t b)
    {
        BuiltInRGB_setColor(mp_obj_get_int(r), mp_obj_get_int(g), mp_obj_get_int(b));
        return mp_const_none;
    }
    static MP_DEFINE_CONST_FUN_OBJ_3(led_setColorRGB_obj, led_setColorRGB);

    static mp_obj_t led_setColor(mp_obj_t idx)
    {
        BuiltInRGB_setColorIdx((Lpf2::ColorIDX)mp_obj_get_int(idx));
        return mp_const_none;
    }
    static MP_DEFINE_CONST_FUN_OBJ_1(led_setColor_obj, led_setColor);

    static const mp_rom_map_elem_t led_globals_table[] = {
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_led) },
        { MP_ROM_QSTR(MP_QSTR_setColorRGB), MP_ROM_PTR(&led_setColorRGB_obj) },
        { MP_ROM_QSTR(MP_QSTR_setColor), MP_ROM_PTR(&led_setColor_obj) },
    };
    static MP_DEFINE_CONST_DICT(led_globals, led_globals_table);

    const mp_obj_module_t hub_led_module = {
        .base = {&mp_type_module},
        .globals = (mp_obj_dict_t *)&led_globals,
    };

    // --- board module ---

    static const mp_rom_map_elem_t board_globals_table[] = {
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_board) },
        { MP_ROM_QSTR(MP_QSTR_SD_MODE), MP_ROM_INT(SD_MODE) },
        { MP_ROM_QSTR(MP_QSTR_SD_SLOT), MP_ROM_INT(SD_SLOT) },
        { MP_ROM_QSTR(MP_QSTR_SD_CS), MP_ROM_INT(SD_CS) },
        { MP_ROM_QSTR(MP_QSTR_SD_SCK), MP_ROM_INT(SD_SCK) },
        { MP_ROM_QSTR(MP_QSTR_SD_MOSI), MP_ROM_INT(SD_MOSI) },
        { MP_ROM_QSTR(MP_QSTR_SD_MISO), MP_ROM_INT(SD_MISO) },
        { MP_ROM_QSTR(MP_QSTR_SD_WIDTH), MP_ROM_INT(SD_WIDTH) },
        { MP_ROM_QSTR(MP_QSTR_SD_CLK), MP_ROM_INT(SD_CLK) },
        { MP_ROM_QSTR(MP_QSTR_SD_CMD), MP_ROM_INT(SD_CMD) },
        { MP_ROM_QSTR(MP_QSTR_SD_D0), MP_ROM_INT(SD_D0) },
        { MP_ROM_QSTR(MP_QSTR_SD_D1), MP_ROM_INT(SD_D1) },
        { MP_ROM_QSTR(MP_QSTR_SD_D2), MP_ROM_INT(SD_D2) },
        { MP_ROM_QSTR(MP_QSTR_SD_D3), MP_ROM_INT(SD_D3) },
    };
    static MP_DEFINE_CONST_DICT(board_globals, board_globals_table);

    const mp_obj_module_t hub_board_module = {
        .base = {&mp_type_module},
        .globals = (mp_obj_dict_t *)&board_globals,
    };

    // --- hub module ---
    static const mp_rom_map_elem_t hub_globals_table[] = {
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_hub) },
        { MP_ROM_QSTR(MP_QSTR_ports), MP_ROM_PTR(&hub_ports_module) },
        { MP_ROM_QSTR(MP_QSTR_log), MP_ROM_PTR(&hub_log_module) },
        { MP_ROM_QSTR(MP_QSTR_led), MP_ROM_PTR(&hub_led_module) },
        { MP_ROM_QSTR(MP_QSTR_board), MP_ROM_PTR(&hub_board_module) },
    };
    static MP_DEFINE_CONST_DICT(hub_globals, hub_globals_table);

    extern "C" __attribute__((used))
    const mp_obj_module_t hub_module = {
        .base = {&mp_type_module},
        .globals = (mp_obj_dict_t *)&hub_globals,
    };

    // --- registration ---
    MP_REGISTER_MODULE(MP_QSTR_hub, hub_module);
} // extern "C"