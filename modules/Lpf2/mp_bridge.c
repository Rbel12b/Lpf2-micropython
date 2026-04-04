#include "py/runtime.h"
#include "mp_bridge.h"

mp_obj_t mp_bridge_obj_new_int(int v) {
    return mp_obj_new_int(v);
}

mp_obj_t mp_bridge_obj_new_bytes(const byte *data, size_t len)
{
    return mp_obj_new_bytes(data, len);
}
mp_obj_t mp_bridge_obj_new_bool(mp_int_t x)
{
    return mp_obj_new_bool(x);
}
mp_int_t mp_bridge_obj_get_int(mp_const_obj_t arg)
{
    return mp_obj_get_int(arg);
}
bool mp_bridge_obj_is_true(mp_obj_t arg)
{
    return mp_obj_is_true(arg);
}
mp_obj_t mp_bridge_call_function_n_kw(mp_obj_t fun, size_t n, size_t kw, const mp_obj_t *args)
{
    return mp_call_function_n_kw(fun, n, kw, args);
}

mp_obj_t mp_bridge_call_function_0(mp_obj_t fun)
{
    return mp_call_function_0(fun);
}

mp_obj_t mp_bridge_call_function_1(mp_obj_t fun, mp_obj_t arg)
{
    return mp_call_function_1(fun, arg);
}

mp_obj_t mp_bridge_load_attr(mp_obj_t obj, qstr attr) {
    return mp_load_attr(obj, attr);
}

void mp_bridge_get_buffer_raise(mp_obj_t obj, mp_buffer_info_t *bufinfo, mp_uint_t flags)
{
    mp_get_buffer_raise(obj, bufinfo, flags);
}
