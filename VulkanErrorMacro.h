//
// Created by momer on 4/22/2026.
//

#ifndef MGRS_VULKAN_ERROR_MACRO_H
#define MGRS_VULKAN_ERROR_MACRO_H
#include <stdio.h>

#define CHECK_VK_RESULT(result, msg) \
    if (result != VK_SUCCESS) \
    {\
        fprintf(stderr, "Error in %s:%d -%s, code %x\n", __FILE__, __LINE__, msg, result ) \
        exit(1)\
    }

#endif //MGRS_VULKAN_ERROR_MACRO_H