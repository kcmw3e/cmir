// license
// ---------------------------------------------------------------------------------------------- //
// Copyright (c) 2022, Casey Walker
// All rights reserved.
// 
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.
//
//
// cmir_window.h
// ---------------------------------------------------------------------------------------------- //
// Window for cmir

#ifndef CMIR_WINDOW_H
#define CMIR_WINDOW_H

#include <string.h>
#include <cuti.h>

#include "cmir.h"

typedef struct cmir_window cmir_window_t;
typedef union cmir_window_ext cmir_window_ext_t;

typedef struct cmir_window_init cmir_window_init_t;
typedef union cmir_window_ext_init cmir_window_ext_init_t;

#include "x11_cmir/xwindow.h"

union cmir_window_ext {
    cmir_window_x11_ext_t x11;
};

struct cmir_window {
    struct cmir_window_readable {
        const char* title;
        int x;
        int y;
        uint32_t width;
        uint32_t height;
        cmir_instance_t* instance;
    } r;
    struct cmir_window_writeable {
        void* user_data;
    } w;
    cmir_window_ext_t ext;
};

union cmir_window_ext_init {
    cmir_window_x11_ext_init_t x11;
};

struct cmir_window_init {
    struct cmir_window_init_optional {
        const char* title;
        int x;
        int y;
        uint32_t width;
        uint32_t height;
    } opt;
    struct cmir_window_init_required {
        const cmir_platform_t platform;
        cmir_instance_t* instance;
    } req;
    cmir_window_ext_init_t ext;
};

xerr_t cmir_window_init_default(cmir_window_init_t* init);
xerr_t cmir_window_new(cmir_window_t* window, const cmir_window_init_t init);
void cmir_window_destroy(cmir_window_t* window);

#endif // XWINDOW_H
