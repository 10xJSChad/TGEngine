#pragma once
#include "tge_config.h"
#include "tge_render.h"


struct timespec _INTERNAL_GameHandler_last_time = {0, 0};
struct timespec _INTERNAL_GameHandler_current_time;
struct timespec _INTERNAL_GameHandler_sleep_timespec;

struct GameHandlerSettings GameHandler_settings;

double delta_time;


struct GameHandlerSettings {
    int update_sleep_amount;
};


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
        while (cursor && cursor->value_ptr) {                                       \
            GameHandler_CallGameObjectUpdate(ptr_to_GameObject(cursor->value_ptr)); \
                                                                                    \
            cursor = cursor->next;                                                  \
        }                                                                           \
    } while (0)


void
GameHandler_LoadScene(
    struct Scene* new_scene)
{
    new_scene->scene_grid = calloc(
        1, Vec2D_to_grid_size_bytes(new_scene->scene_dimensions));
    render_SetActiveScene(new_scene);
}


void
GameHandler_LoadSettings(
    struct GameHandlerSettings new_settings)
{
    GameHandler_settings = new_settings;
}


void
GameHandler_Update()
{
    clock_gettime(CLOCK_MONOTONIC, &_INTERNAL_GameHandler_last_time);

    double total = 0;

    update_loop:
        #if (CFG_GAME_ALLOW_UPDATE_SLEEP)
        if (GameHandler_settings.update_sleep_amount != 99)
            GameHandler_Sleep(GameHandler_settings.update_sleep_amount);
        #endif

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