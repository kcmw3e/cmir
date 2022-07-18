#include "x11_cmir/xwindow.h"

cmir_window_x11_ext_init_t window_x11_ext_default = {
    .xcb_info = {
        .depth = XCB_COPY_FROM_PARENT,
        .border_width = 0,
        .class = XCB_WINDOW_CLASS_INPUT_OUTPUT,
        .visual = XCB_COPY_FROM_PARENT,
        .visual_mask = 0,
        .value_list = NULL,
    },
};


xerr_t cmir_window_x11_ext_init_default(cmir_window_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    init->ext.x11 = window_x11_ext_default;

    return XERR_SUCCESS;
}


xerr_t window_init_ext_validate(const cmir_window_init_t* init);
xerr_t window_init_ext_parity(cmir_window_t* window, const cmir_window_init_t* init);
xerr_t window_xcb_window_new(cmir_window_t* window, const cmir_window_init_t* init);

xerr_t cmir_window_x11_ext_new(cmir_window_t* window, const cmir_window_init_t* init) {
    if (window == NULL || init == NULL) return XERR_NULL_CHECK_FAILURE;

    xerr_t result;
    
    result = window_init_ext_validate(init);
    if (result != XERR_SUCCESS) return result;

    result = window_init_ext_parity(window, init);
    if (result != XERR_SUCCESS) return result;

    result = window_xcb_window_new(window, init);
    if (result != XERR_SUCCESS) return result;

    return XERR_SUCCESS;
}

xerr_t init_ext_xcb_info_validate(const cmir_window_x11_ext_init_t* ext_init);

xerr_t window_init_ext_validate(const cmir_window_init_t* init) {
    if (init == NULL) return XERR_NULL_CHECK_FAILURE;

    const cmir_window_x11_ext_init_t* ext_init = &(init->ext.x11);

    xerr_t result;

    result = init_ext_xcb_info_validate(ext_init);
    if (result != XERR_SUCCESS) return result;

    return XERR_SUCCESS;
}

xerr_t init_ext_xcb_info_validate(const cmir_window_x11_ext_init_t* ext_init) {
    if (ext_init == NULL) return XERR_NULL_CHECK_FAILURE;

    const cmir_window_x11_ext_init_xcb_info_t* info = &(ext_init->xcb_info);

    switch (info->class) {
        case (XCB_WINDOW_CLASS_COPY_FROM_PARENT):
        case (XCB_WINDOW_CLASS_INPUT_ONLY):
        case (XCB_WINDOW_CLASS_INPUT_OUTPUT):
            break;
        default:
            return XERR_UNDEFINED;
    }

    return XERR_SUCCESS;
}


xerr_t window_init_ext_parity(cmir_window_t* window, const cmir_window_init_t* init) {
    if (window == NULL || init == NULL) return XERR_NULL_CHECK_FAILURE;

    cmir_window_x11_ext_t* x11_ext = &(window->ext.x11);
    const cmir_window_x11_ext_init_t* x11_ext_init = &(init->ext.x11);

    UNUSED(x11_ext);
    UNUSED(x11_ext_init);

    return XERR_SUCCESS;
}

xerr_t window_xcb_window_new(cmir_window_t* window, const cmir_window_init_t* init) {
    if (window == NULL || init == NULL) return XERR_NULL_CHECK_FAILURE;

    cmir_instance_t* instance = init->req.instance;

    xcb_connection_t* xcb_con = instance->ext.x11.xcb_con;

    const struct xcb_setup_t* xcb_setup = xcb_get_setup(xcb_con);

    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_setup);
    xcb_screen_t xcb_screen = *(iter.data);

    xcb_window_t xcb_win = xcb_generate_id(xcb_con);

    //xcb_window_init_t xcb_init = *(init->xcb_window_init);
    //xcb_init.visual = xcb_screen.root_visual;

    cmir_window_x11_ext_init_xcb_info_t xcb_info = init->ext.x11.xcb_info;

    uint8_t depth = xcb_info.depth;
    xcb_window_t parent = xcb_screen.root;
    int16_t x = init->opt.x;
    int16_t y = init->opt.y;
    uint16_t width = init->opt.width;
    uint16_t height = init->opt.height;
    uint16_t border_width = xcb_info.border_width;
    uint16_t class = xcb_info.class;
    xcb_visualid_t visual = xcb_info.visual;
    uint32_t value_mask = xcb_info.visual_mask;
    const void* value_list = xcb_info.value_list;

    xcb_void_cookie_t create_cki = xcb_create_window_checked(xcb_con, depth, xcb_win, parent,
                                                             x, y, width, height, border_width,
                                                             class, visual, value_mask, value_list);
    
    size_t title_len = strnlen(init->opt.title, CMIR_MAX_NAME_LEN);
    xcb_change_property_checked(xcb_con,
                                XCB_PROP_MODE_REPLACE, xcb_win,
                                XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
                                8, (uint32_t)title_len, init->opt.title);
    
    xcb_void_cookie_t map_cki = xcb_map_window_checked(xcb_con, xcb_win);

    int flush_result = xcb_flush(xcb_con);
    if (flush_result <= 0) return XERR_UNDEFINED;

    xcb_generic_error_t* cki_result;

    cki_result = xcb_request_check(xcb_con, create_cki);
    if (cki_result != NULL) return XERR_UNDEFINED;

    cki_result = xcb_request_check(xcb_con, map_cki);
    if (cki_result != NULL) return XERR_UNDEFINED;

    window->ext.x11.xcb_window = xcb_win;

    return XERR_SUCCESS;
}


void cmir_window_x11_ext_destroy(cmir_window_t* window) {
    xcb_connection_t* xcb_con = window->r.instance->ext.x11.xcb_con;
    xcb_destroy_window(xcb_con, window->ext.x11.xcb_window);
}
