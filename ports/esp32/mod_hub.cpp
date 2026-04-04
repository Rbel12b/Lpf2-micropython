#include "Ports.h"
#include "mod_types.h"
#include "mod_hub.h"

extern "C"
{
    // --- instances ---
    static mp_obj_lpf2_local_port_t port_A_obj;
    static mp_obj_lpf2_local_port_t port_B_obj;

    void mod_hub_ports_init()
    {
        port_A_obj.base.type = &lpf2_local_port_type;
        port_A_obj.cpp_obj = &portA;

        port_B_obj.base.type = &lpf2_local_port_type;
        port_B_obj.cpp_obj = &portB;
    }

    // --- ports module ---
    static const mp_rom_map_elem_t ports_globals_table[] = {
        {MP_ROM_QSTR(MP_QSTR_A), MP_ROM_PTR(&port_A_obj)},
        {MP_ROM_QSTR(MP_QSTR_B), MP_ROM_PTR(&port_B_obj)},
    };
    static MP_DEFINE_CONST_DICT(ports_globals, ports_globals_table);

    const mp_obj_module_t hub_ports_module = {
        .base = {&mp_type_module},
        .globals = (mp_obj_dict_t *)&ports_globals,
    };

    // --- hub module ---
    static const mp_rom_map_elem_t hub_globals_table[] = {
        {MP_ROM_QSTR(MP_QSTR_ports), MP_ROM_PTR(&hub_ports_module)},
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