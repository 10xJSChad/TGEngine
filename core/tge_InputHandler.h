#pragma once


#ifdef TGE_UNIX
#include <termios.h>
#include <unistd.h> 
static struct termios oldt, newt;


#define InputHandler_Init()                         \
    do {                                            \
        atexit(InputHandler_Cleanup);               \
                                                    \
        tcgetattr(STDIN_FILENO, &oldt);             \
        newt = oldt;                                \
        newt.c_lflag &= ~(ICANON);                  \
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);    \
    } while(0)


void
InputHandler_Cleanup()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}


static inline int 
InputHandler_KeyboardInput()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}


static inline 
int InputHandler_getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}


#if (CFG_INPUT_GETCHAR_UNLOCKED)
#define InputHandler_GetChar() getchar_unlocked()
#else
#define InputHandler_GetChar() getchar()
#endif

#endif