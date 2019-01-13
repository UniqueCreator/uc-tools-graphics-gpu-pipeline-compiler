#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifdef NOMINMAX
    #include <windows.h>
#else
    #define NOMINMAX
    #include <windows.h>
    #undef NOMINMAX
#endif

#include "targetver.h"



