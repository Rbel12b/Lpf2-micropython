extern "C" {
#include "py/runtime.h"
}

#define GET_SELF() ((SELF_TYPE*)(MP_OBJ_TO_PTR(self_in)))
#define GET_SELF_CPP() (GET_SELF()->cpp_obj)

#include "Lpf2/Port.hpp"
#include "Lpf2/Local/Port.hpp"

extern "C" {

typedef struct _mp_obj_lpf2_port_t
{
    mp_obj_base_t base;
    Lpf2::Port *cpp_obj;
    bool is_trampoline;
} mp_obj_lpf2_port_t;
extern const mp_obj_type_t lpf2_port_type;

typedef struct _mp_obj_lpf2_local_port_t {
    mp_obj_base_t base;
    Lpf2::Local::Port* cpp_obj;
} mp_obj_lpf2_local_port_t;
extern const mp_obj_type_t lpf2_local_port_type;

} // extern "C"