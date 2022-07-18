#include "cmir_platforms.h"

xerr_t cmir_platform_validate(cmir_platform_t platform) {
    switch (platform) {
        case CMIR_PLATFORM_X11:
        case CMIR_PLATFORM_WAYLAND:
            return XERR_SUCCESS;
        case CMIR_PLATFORM_NONE:
            return XERR_UNDEFINED;
        default:
            return XERR_UNDEFINED;
    }

    return XERR_UNDEFINED;
}
