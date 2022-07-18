// license
// ---------------------------------------------------------------------------------------------- //
// Copyright (c) 2022, Casey Walker
// All rights reserved.
// 
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.
//
//
// cmir_instance.h
// ---------------------------------------------------------------------------------------------- //
// A cmir instance

#ifndef CMIR_INSTANCE_H
#define CMIR_INSTANCE_H

#include <string.h>
#include <cuti.h>

typedef struct cmir_instance cmir_instance_t;
typedef struct cmir_instance_readable cmir_instance_readable_t;
typedef struct cmir_instance_writeable cmir_instance_writeable_t;
typedef union cmir_instance_extension cmir_instance_extension_t;

typedef struct cmir_instance_init cmir_instance_init_t;
typedef struct cmir_instance_init_optional cmir_instance_init_optional_t;
typedef struct cmir_instance_init_required cmir_instance_init_required_t;
typedef union cmir_instance_init_extension cmir_instance_init_extension_t;

#include "cmir.h"

#include "x11_cmir/xinstance.h"

union cmir_instance_extension {
    cmir_instance_x11_ext_t x11;
};

union cmir_instance_init_extension {
    cmir_instance_x11_ext_init_t x11;
};

struct cmir_instance {
    struct cmir_instance_readable {
        cmir_platform_t platform;
        const char* name;
    } r;
    struct cmir_instance_writeable {
        void* user_data;
    } w;
    cmir_instance_extension_t ext;
};

struct cmir_instance_init {
    struct cmir_instance_init_optional {
        const char* name;
    } opt;
    struct cmir_instance_init_required {
        const cmir_platform_t platform;
    } req;
    cmir_instance_init_extension_t ext;
};

// interface
// ---------------------------------------------------------------------------------------------- //
xerr_t cmir_instance_init_default(cmir_instance_init_t* init);
xerr_t cmir_instance_new(cmir_instance_t* instance, const cmir_instance_init_t init);
void cmir_instance_destroy(cmir_instance_t* instance);


#endif // CMIR_INSTANCE_H
