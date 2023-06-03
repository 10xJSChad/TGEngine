#pragma once
#include "tge_config.h"
#include "tge_render.h"


struct GameHandlerSettings {
    int update_delay;
};


struct timespec _INTERNAL_GameHandler_last_time = {0, 0};
struct timespec _INTERNAL_GameHandler_current_time;
struct timespec _INTERNAL_GameHandler_sleep_timespec;

struct GameHandlerSettings GameHandler_settings;

double delta_time;


#if (CFG_INPUT_ENABLED)
#include "tge_InputHandler.h"
#define GameHandler_UpdateActions(code)     \
    while (!InputHandler_KeyboardInput()) { \
        code                                \
    }                                       \
    (void) InputHandler_getch(); exit(1);
#else
#define GameHandler_UpdateActions(code) code
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
    clock_gettime(CLOCK_MONOTONIC, &_INTERNAL_GameHandler_last_time);

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
GameHandler_UpdateLoop()
{
    double total = 0;
    update_loop:
        GameHandler_UpdateActions(
            #if (CFG_GAME_ALLOW_UPDATE_SLEEP)
            if (GameHandler_settings.update_delay)
                GameHandler_Sleep(GameHandler_settings.update_delay);
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
        )
    goto update_loop;
}