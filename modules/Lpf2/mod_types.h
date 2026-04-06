extern "C" {
#include "py/runtime.h"
}

#define GET_SELF() ((SELF_TYPE*)(MP_OBJ_TO_PTR(self_in)))
#define GET_SELF_CPP() (GET_SELF()->cpp_obj)

#include "Lpf2/Port.hpp"
#include "Lpf2/Local/Port.hpp"
#include "Lpf2/LWPConst.hpp"

#define DEFINE_METHOD(name, method, fun_obj_def) \
    static mp_obj_t lpf2_##name method \
    static fun_obj_def(lpf2_##name##_obj, lpf2_##name);

#define DEFINE_METHOD_VAR_BETWEEN(name, method, min_args, max_args) \
    static mp_obj_t lpf2_##name(size_t n_args, const mp_obj_t *args) method \
    static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lpf2_##name##_obj, min_args, max_args, lpf2_##name);

#define GET_METHOD_OBJ(name) lpf2_##name##_obj

extern "C" {

typedef struct _mp_obj_lpf2_port_t
{
    mp_obj_base_t base;
    Lpf2::Port *cpp_obj = nullptr;
    bool owned = false; // owned by the mp obj
    bool is_trampoline = false;
} mp_obj_lpf2_port_t;
extern const mp_obj_type_t lpf2_port_type;
extern const mp_obj_type_t lpf2_local_port_type;

typedef struct _mp_obj_lpf2_mode_t
{
    mp_obj_base_t base;
    Lpf2::Mode *cpp_obj = nullptr;
    bool owned = false; // owned by the mp obj
} mp_obj_lpf2_mode_t;
extern const mp_obj_type_t lpf2_mode_type;

} // extern "C"