#include "cmir_instance.h"

const cmir_instance_init_t cmir_instance_defaults = {
    .opt = {
        .name = "",
    },
    .req = {
        .platform = CMIR_PLATFORM_NONE,
    },
    .ext = {{0}},
};

xerr_t instance_init_ext_default(cmir_instance_init_t* init);

xerr_t cmir_instance_init_default(cmir_instance_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    init->opt = cmir_instance_defaults.opt;

    xerr_t result;

    result = instance_init_ext_default(init);

    return result;
}

xerr_t instance_init_ext_default(cmir_instance_init_t* init) {
    switch (init->req.platform) {
        case (CMIR_PLATFORM_X11):
            return cmir_instance_x11_ext_init_default(init);
        case (CMIR_PLATFORM_WAYLAND):
            return XERR_UNDEFINED;
        case (CMIR_PLATFORM_NONE):
            return XERR_UNDEFINED;
        default:
            return XERR_UNDEFINED;
    }

    return XERR_UNDEFINED;
}


xerr_t instance_init_validate(const cmir_instance_init_t* init);
xerr_t instance_init_parity(cmir_instance_t* instance, const cmir_instance_init_t* init);
xerr_t instance_ext_new(cmir_instance_t* instance, const cmir_instance_init_t* init);

xerr_t cmir_instance_new(cmir_instance_t* instance, const cmir_instance_init_t init) {
    if (instance == NULL) return XERR_NULL_CHECK_FAILURE;
    
    xerr_t result;

    result = instance_init_validate(&init);
    if (result != XERR_SUCCESS) return result;

    result = instance_init_parity(instance, &init);
    if (result != XERR_SUCCESS) return result;

    result = instance_ext_new(instance, &init);
    if (result != XERR_SUCCESS) return result;

    return XERR_SUCCESS;
}

xerr_t instance_init_validate(const cmir_instance_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    switch (init->req.platform) {
        case (CMIR_PLATFORM_X11):
        case (CMIR_PLATFORM_WAYLAND):
            break;
        case (CMIR_PLATFORM_NONE):
            return XERR_UNDEFINED;
        default:
            return XERR_UNDEFINED;
    }

    if (init->opt.name == NULL) return XERR_NULL_CHECK_FAILURE;
    if (strnlen(init->opt.name, CMIR_MAX_NAME_LEN) == CMIR_MAX_NAME_LEN) return XERR_UNDEFINED;

    return XERR_SUCCESS;
}

xerr_t instance_init_parity(cmir_instance_t* instance, const cmir_instance_init_t* init) {
    if (instance == NULL || init == NULL) return XERR_NULL_CHECK_FAILURE;

    instance->r.name = init->opt.name;
    instance->r.platform = init->req.platform;

    return XERR_SUCCESS;
}

xerr_t instance_ext_new(cmir_instance_t* instance, const cmir_instance_init_t* init) {
    if (instance == NULL || init == NULL) return XERR_NULL_CHECK_FAILURE;

    cmir_platform_t platform = init->req.platform;

    switch (platform) {
        case (CMIR_PLATFORM_X11):
            return cmir_instance_x11_ext_new(instance, init);
        case (CMIR_PLATFORM_WAYLAND):
            return XERR_UNDEFINED;
        case (CMIR_PLATFORM_NONE):
            return XERR_UNDEFINED;
        default:
            return XERR_UNDEFINED;
    }
    return XERR_UNDEFINED;
}


void cmir_instance_destroy(cmir_instance_t* instance) {
    if (instance == NULL) return;

    cmir_platform_t platform = instance->r.platform;
    
    switch (platform) {
        case (CMIR_PLATFORM_X11):
            cmir_instance_x11_ext_destory(instance);
            break;
        case (CMIR_PLATFORM_WAYLAND):
            break;
        case (CMIR_PLATFORM_NONE):
            break;
        default:
            break;
    }
}
