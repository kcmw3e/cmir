// license
// ---------------------------------------------------------------------------------------------- //
// Copyright (c) 2022, Casey Walker
// All rights reserved.
// 
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.
//
//
// xinstance.h
// ---------------------------------------------------------------------------------------------- //
// X11 instance for cmir instance

#ifndef XINSTANCE_H
#define XINSTANCE_H

#include <string.h>
#include <cuti.h>
#include <xcb/xcb.h>

typedef struct cmir_instance_x11_ext cmir_instance_x11_ext_t;
typedef struct cmir_instance_x11_ext_init cmir_instance_x11_ext_init_t;

struct cmir_instance_x11_ext {
    xcb_connection_t* xcb_con;
};

struct cmir_instance_x11_ext_init {
    const char* display_name;
    int screen;
};

#include "cmir.h"

xerr_t cmir_instance_x11_ext_init_default(cmir_instance_init_t* init);
xerr_t cmir_instance_x11_ext_new(cmir_instance_t* instance, const cmir_instance_init_t* init);
void cmir_instance_x11_ext_destory(cmir_instance_t* instance);

#endif // XINSTANCE_H
