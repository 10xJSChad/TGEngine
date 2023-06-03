#pragma once

#ifdef TGE_UNIX
#include <time.h>
#include<unistd.h>


#define GameHandler_Sleep(time_ms)                                              \
    _INTERNAL_GameHandler_sleep_timespec.tv_sec = time_ms / 1000;               \
    _INTERNAL_GameHandler_sleep_timespec.tv_nsec = (time_ms % 1000) * 1000000;  \
    nanosleep(&_INTERNAL_GameHandler_sleep_timespec, NULL);


#define _INTERNAL_GameHandler_GetDeltaTime()                                    \
    do {                                                                        \
        clock_gettime(CLOCK_MONOTONIC, &_INTERNAL_GameHandler_current_time);    \
                                                                                \
        delta_time = (                                                          \
            _INTERNAL_GameHandler_current_time.tv_sec                           \
            - _INTERNAL_GameHandler_last_time.tv_sec)                           \
            + (_INTERNAL_GameHandler_current_time.tv_nsec                       \
              - _INTERNAL_GameHandler_last_time.tv_nsec)                        \
              / 1000000000.0;                                                   \
                                                                                \
        _INTERNAL_GameHandler_last_time = _INTERNAL_GameHandler_current_time;   \
    } while (0)


#define render_HideCursor() printf("\e[?25l");
#define render_ShowCursor() printf("\e[?25h");
#define render_SetCursorPos(x,y) printf("\033[%d;%dH", (y), (x))
#define render_Clear() system("clear")
#endif