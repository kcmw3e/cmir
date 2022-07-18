#ifndef CMIR_PLATFORMS_H
#define CMIR_PLATFORMS_H

#include <cuti.h>

enum cmir_platform {
    CMIR_PLATFORM_NONE,
    CMIR_PLATFORM_X11,
    CMIR_PLATFORM_WAYLAND,
};
typedef enum cmir_platform cmir_platform_t;

xerr_t cmir_platform_validate(cmir_platform_t platform);

#endif // CMIR_PLATFORMS_H
