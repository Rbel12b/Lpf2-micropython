extern "C" {
#include "py/runtime.h"
}

#define LOAD_STORE_VAL(val, type) \
    if (dest[0] == MP_OBJ_NULL) {\
        dest[0] = mp_obj_new_##type(val); \
    } else { \
        val = mp_obj_get_##type(dest[1]); \
        dest[0] = MP_OBJ_NULL; \
    }

#define LOAD_STORE_VAL_2(val, get, set) \
    if (dest[0] == MP_OBJ_NULL) {\
        dest[0] = mp_obj_new_##set(val); \
    } else { \
        val = mp_obj_get_##get(dest[1]); \
        dest[0] = MP_OBJ_NULL; \
    }

#define CASE_VAL_NAME(name, type) \
    case MP_QSTR_##name:{ \
        LOAD_STORE_VAL(self->name, type); \
        break; \
    }

#define CASE_VAL_NAME_2(name, get, set) \
    case MP_QSTR_##name:{ \
        LOAD_STORE_VAL_2(self->name, get, set); \
        break; \
    }

#define CASE_VAL_NAME_MEMBER(name, member, type) \
    case MP_QSTR_##name:{ \
        LOAD_STORE_VAL(self->member, type); \
        break; \
    }

#define CASE_VAL_NAME_MEMBER_2(name, member, get, set) \
    case MP_QSTR_##name:{ \
        LOAD_STORE_VAL_2(self->member, get, set); \
        break; \
    }

#include "mod_types.h"
extern "C" {
#define SELF_TYPE mp_obj_lpf2_mode_t

static mp_obj_t lpf2_mode_make_new(const mp_obj_type_t *type,
                                    size_t n_args,
                                    size_t n_kw,
                                    const mp_obj_t *args)
{

    SELF_TYPE *o = (SELF_TYPE*)m_malloc_with_finaliser(sizeof(SELF_TYPE));
    o->base.type = type;

    o->cpp_obj = new Lpf2::Mode;
    o->owned = true;

    return MP_OBJ_FROM_PTR(o);
}

static void lpf2_mode_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    auto self = GET_SELF_CPP();

    switch (attr)
    {
    case MP_QSTR_name:
    {
        if (dest[0] == MP_OBJ_NULL) {
            dest[0] = mp_obj_new_str(self->name.c_str(), self->name.length());
        } else {
            size_t len;
            auto s = mp_obj_str_get_data(dest[1], &len);
            self->name = std::string(s, len);
            dest[0] = MP_OBJ_NULL;
        }
        break;
    }
    CASE_VAL_NAME(min, float);
    CASE_VAL_NAME(max, float);
    CASE_VAL_NAME(PCTmin, float);
    CASE_VAL_NAME(PCTmax, float);
    CASE_VAL_NAME(SImin, float);
    CASE_VAL_NAME(SImax, float);
    CASE_VAL_NAME_MEMBER_2(inMapping, in.val, uint, int_from_uint);
    CASE_VAL_NAME_MEMBER_2(outMapping, out.val, uint, int_from_uint);
    CASE_VAL_NAME_MEMBER_2(dataSets, data_sets, uint, int_from_uint);
    CASE_VAL_NAME_2(format, uint, int_from_uint);
    CASE_VAL_NAME_2(figures, uint, int_from_uint);
    CASE_VAL_NAME_2(decimals, uint, int_from_uint);
    CASE_VAL_NAME_MEMBER_2(motorBias, motor_bias, uint, int_from_uint);
    case MP_QSTR_flags:
    {
        if (dest[0] == MP_OBJ_NULL) {
            dest[0] = mp_obj_new_int((*((uint64_t*)self->flags.bytes)));
        } else {
            (*((uint64_t*)self->flags.bytes)) = mp_obj_get_int(dest[1]);
            dest[0] = MP_OBJ_NULL;
        }
        break;
    }
    case MP_QSTR_rawData:
    {
        if (dest[0] == MP_OBJ_NULL) {
            dest[0] = mp_obj_new_bytes(self->rawData.data(), self->rawData.size());
        } else {
            mp_buffer_info_t buf;
            mp_get_buffer_raise(dest[1], &buf, MP_BUFFER_READ);
            self->rawData = std::vector<uint8_t>(
                (uint8_t*)buf.buf,
                (uint8_t*)buf.buf + buf.len
            );
            dest[0] = MP_OBJ_NULL;
        }
        break;
    }
    
    default:
        dest[1] = MP_OBJ_SENTINEL;
        break;
    }
}

LPF2_DEFINE_METHOD(mode_del, (mp_obj_t self_in)
{
    auto self = GET_SELF();
    LPF2_LOG_V("Deleting Mode, owner: %s", self->owned ? "true" : "false");
    if (self->owned && self->cpp_obj)
    {
        delete self->cpp_obj;
        self->cpp_obj = nullptr;
    }
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

static const mp_rom_map_elem_t lpf2_mode_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&LPF2_GET_METHOD_OBJ(mode_del))},
};

static MP_DEFINE_CONST_DICT(lpf2_mode_locals_dict, lpf2_mode_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_mode_type, 
    MP_QSTR_mode,
    MP_TYPE_FLAG_NONE,
    make_new, (void*)lpf2_mode_make_new,
    attr, (void*)lpf2_mode_attr,
    locals_dict, &lpf2_mode_locals_dict
);

#undef SELF_TYPE
#define SELF_TYPE mp_obj_lpf2_version_t

static mp_obj_t lpf2_version_make_new(const mp_obj_type_t *type,
                                    size_t n_args,
                                    size_t n_kw,
                                    const mp_obj_t *args)
{

    SELF_TYPE *o = (SELF_TYPE*)m_malloc_with_finaliser(sizeof(SELF_TYPE));
    o->base.type = type;

    o->cpp_obj = new Lpf2::Version;
    o->owned = true;

    return MP_OBJ_FROM_PTR(o);
}

static void lpf2_version_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    auto self = GET_SELF_CPP();

    switch (attr)
    {
    CASE_VAL_NAME_MEMBER_2(build, Build, uint, int_from_uint);
    CASE_VAL_NAME_MEMBER_2(major, Major, uint, int_from_uint);
    CASE_VAL_NAME_MEMBER_2(minor, Minor, uint, int_from_uint);
    CASE_VAL_NAME_MEMBER_2(bugfix, Bugfix, uint, int_from_uint);
    
    default:
        dest[1] = MP_OBJ_SENTINEL;
        break;
    }
}

LPF2_DEFINE_METHOD(version_del, (mp_obj_t self_in)
{
    auto self = GET_SELF();
    LPF2_LOG_V("Deleting Version, owner: %s", self->owned ? "true" : "false");
    if (self->owned && self->cpp_obj)
    {
        delete self->cpp_obj;
        self->cpp_obj = nullptr;
    }
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

static const mp_rom_map_elem_t lpf2_version_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&LPF2_GET_METHOD_OBJ(version_del))},
};

static MP_DEFINE_CONST_DICT(lpf2_version_locals_dict, lpf2_version_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_version_type, 
    MP_QSTR_version,
    MP_TYPE_FLAG_NONE,
    make_new, (void*)lpf2_version_make_new,
    attr, (void*)lpf2_version_attr,
    locals_dict, &lpf2_version_locals_dict
);
}