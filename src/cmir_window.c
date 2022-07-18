#include "cmir_window.h"

cmir_window_init_t cmir_window_defaults = {
    .opt = {
        .title = "Wowza",
        .x = 0,
        .y = 0,
        .width = 122,
        .height = 213,
    },
    .req = {
        .platform = CMIR_PLATFORM_NONE,
    },
};

xerr_t cmir_window_ext_init_default(cmir_window_init_t* init);

xerr_t cmir_window_init_default(cmir_window_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    init->opt = cmir_window_defaults.opt;

    xerr_t result;
    
    result = cmir_window_ext_init_default(init);
    if (result != XERR_SUCCESS) return result;

    return XERR_SUCCESS;
}

xerr_t cmir_window_ext_init_default(cmir_window_init_t* init) {
    if (init == NULL) return XERR_UNDEFINED;

    switch (init->req.platform) {
        case (CMIR_PLATFORM_X11):
            return cmir_window_x11_ext_init_default(init);
        case (CMIR_PLATFORM_WAYLAND):
            return XERR_UNDEFINED;
        case (CMIR_PLATFORM_NONE):
            return XERR_UNDEFINED;
        default:
            return XERR_UNDEFINED;
    }

    return XERR_UNDEFINED;
}


xerr_t window_init_validate(const cmir_window_init_t* init);
xerr_t window_init_parity(cmir_window_t* window, const cmir_window_init_t* init);
xerr_t window_ext_new(cmir_window_t* window, const cmir_window_init_t* init);

xerr_t cmir_window_new(cmir_window_t* window, const cmir_window_init_t init) {
    if (window == NULL) return XERR_NULL_CHECK_FAILURE;

    xerr_t result;

    result = window_init_validate(&init);
    if (result != XERR_SUCCESS) return result;

    result = window_init_parity(window, &init);
    if (result != XERR_SUCCESS) return result;

    result = window_ext_new(window, &init);
    if (result != XERR_SUCCESS) return result;

    return XERR_SUCCESS;
}

xerr_t window_init_validate(const cmir_window_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    xerr_t result;
    
    result = cmir_platform_validate(init->req.platform);
    if (result != XERR_SUCCESS) return result;

    if (init->req.instance == NULL) return XERR_NULL_CHECK_FAILURE;
    if (init->req.instance->r.platform != init->req.platform) return XERR_UNDEFINED;

    if (init->opt.width == 0 || init->opt.height == 0) return XERR_UNDEFINED;
    if (init->opt.title == NULL) return XERR_NULL_CHECK_FAILURE;
    if (strnlen(init->opt.title, CMIR_MAX_NAME_LEN) == CMIR_MAX_NAME_LEN) return XERR_UNDEFINED;

    return XERR_SUCCESS;
}

xerr_t window_init_parity(cmir_window_t* window, const cmir_window_init_t* init) {
    window->r.title = init->opt.title;
    window->r.x = init->opt.x;
    window->r.y = init->opt.y;
    window->r.width = init->opt.width;
    window->r.height = init->opt.height;
    window->r.instance = init->req.instance;

    return XERR_SUCCESS;
}

xerr_t window_ext_new(cmir_window_t* window, const cmir_window_init_t* init) {
    switch (init->req.platform) {
        case (CMIR_PLATFORM_X11):
            return cmir_window_x11_ext_new(window, init);
        case (CMIR_PLATFORM_WAYLAND):
            return XERR_UNDEFINED;
        case (CMIR_PLATFORM_NONE):
            return XERR_UNDEFINED;
        default:
            return XERR_UNDEFINED;
    }
    
    return XERR_UNDEFINED;
}
