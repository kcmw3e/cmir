// license
// ---------------------------------------------------------------------------------------------- //
// Copyright (c) 2022, Casey Walker
// All rights reserved.
// 
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.
//
//
// xwindow.h
// ---------------------------------------------------------------------------------------------- //
// X11 window for cmir window

#ifndef XWINDOW_H
#define XWINDOW_H

#include <string.h>
#include <cuti.h>
#include <xcb/xcb.h>

typedef struct cmir_window_x11_ext cmir_window_x11_ext_t;
typedef struct cmir_window_x11_ext_init cmir_window_x11_ext_init_t;
typedef struct cmir_window_x11_ext_init_xcb_info cmir_window_x11_ext_init_xcb_info_t;

struct cmir_window_x11_ext {
    xcb_window_t xcb_window;
};

struct cmir_window_x11_ext_init {
    struct cmir_window_x11_ext_init_xcb_info {
        uint8_t depth;
        // int16_t x;
        // int16_t y;
        // uint16_t width;
        // uint16_t height;
        uint16_t border_width;
        xcb_window_class_t class;
        xcb_visualid_t visual;
        uint32_t visual_mask;
        const void* value_list;
    } xcb_info;
};

#include "cmir.h"

xerr_t cmir_window_x11_ext_init_default(cmir_window_init_t* init);
xerr_t cmir_window_x11_ext_new(cmir_window_t* window, const cmir_window_init_t* init);
void cmir_window_x11_ext_destroy(cmir_window_t* window);

#endif // XWINDOW_H
