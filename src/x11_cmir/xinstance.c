#include "x11_cmir/xinstance.h"

cmir_instance_x11_ext_init_t instance_x11_ext_default = {
    .display_name = NULL,
    .screen = 0,
};


xerr_t cmir_instance_x11_ext_init_default(cmir_instance_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    init->ext.x11 = instance_x11_ext_default;

    return XERR_SUCCESS;
}

xerr_t cmir_instance_x11_ext_new(cmir_instance_t* instance, const cmir_instance_init_t* init) {
    if (instance == NULL || init == NULL) return XERR_NULL_CHECK_FAILURE;

    cmir_instance_x11_ext_t* x11_ext = &(instance->ext.x11);
    const cmir_instance_x11_ext_init_t* x11_ext_init = &(init->ext.x11);

    const char* display_name = x11_ext_init->display_name;
    int screen = x11_ext_init->screen;

    xcb_connection_t* xcb_con = xcb_connect(display_name, &screen);
    if (xcb_connection_has_error(xcb_con) > 0) {
        xcb_disconnect(xcb_con);
        return XERR_UNDEFINED;
    }

    x11_ext->xcb_con = xcb_con;

    return XERR_SUCCESS;
}

void cmir_instance_x11_ext_destory(cmir_instance_t* instance) {
    if (instance == NULL) return;

    xcb_disconnect(instance->ext.x11.xcb_con);
}
