#pragma once
#include "tge_render.h"
#include <time.h>

double delta_time;


struct GameHandlerSettings {
    int update_rate;
};

#ifdef TGE_UNIX
#define _INTERNAL_GameHandler_GetDeltaTime()                                \
    do {                                                                    \
        clock_gettime(CLOCK_MONOTONIC, &current_time);                      \
                                                                            \
        delta_time = (current_time.tv_sec - last_time.tv_sec) +             \
            (current_time.tv_nsec - last_time.tv_nsec) / 1000000000.0;      \
                                                                            \
        last_time = current_time;                                           \
    } while (0)
#endif

#if CFG_RENDER_DEFER_AUTO_RENDER_TO_GAMEHANDLER
#define GameHandler_CallGameObjectUpdate(gameobject_ptr)    \
    GameObject_CallUpdate(gameobject_ptr);                  \
    render_PushToScreenBuffer(gameobject_ptr)
#else
#define GameHandler_CallGameObjectUpdate(gameobject_ptr)    \
    GameObject_CallUpdate(gameobject_ptr)
#endif


#define GameHandler_CallAllGameObjectsUpdate()                                      \
    do {                                                                            \
        struct ListNode* cursor = active_scene->gameobject_head;                    \
        while (cursor) {                                                            \
            GameHandler_CallGameObjectUpdate(ptr_to_GameObject(cursor->value_ptr)); \
                                                                                    \
            cursor = cursor->next;                                                  \
        }                                                                           \
    } while (0)




void
GameHandler_SetActiveScene(
    struct Scene* new_scene)
{
    render_SetActiveScene(new_scene);
}


void 
GameHandler_InitGameScreen(
    int screen_size_x,
    int screen_size_y)
{
    render_Init(screen_size_x, screen_size_y);
}

struct timespec last_time = {0, 0};
struct timespec current_time;

void
GameHandler_Update()
{
    clock_gettime(CLOCK_MONOTONIC, &last_time);

    double total = 0;

    update_loop:
        #if (CFG_GAME_USE_DELTATIME)
            _INTERNAL_GameHandler_GetDeltaTime();
            total += delta_time;
        #endif
        
        #if (!CFG_GAMEOBJECT_DISABLE_EVENT_UPDATE)
            GameHandler_CallAllGameObjectsUpdate();
        #endif

        render_RenderFrame();
        printf("%lf <-", total);

    goto update_loop;
}