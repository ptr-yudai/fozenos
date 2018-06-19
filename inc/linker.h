#pragma once

#include "stdint.h"

extern uint32_t _KERNEL_TOP, _KERNEL_BOTTOM;

#define __KERNEL_TOP    &_KERNEL_TOP
#define __KERNEL_BOTTOM &_KERNEL_BOTTOM
