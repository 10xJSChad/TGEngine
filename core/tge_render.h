#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tge_datatypes.h"
#include "tge_config.h"
#include "tge_utilmacros.h"
#include "tge_Scene.h"


struct Scene* active_scene;
struct Vec2D screen_size;
size_t screen_buffer_size;
char* screen_buffer;


#ifdef TGE_UNIX
#define render_HideCursor() printf("\e[?25l");
#define render_ShowCursor() printf("\e[?25h");
#define render_SetCursorPos(x,y) printf("\033[%d;%dH", (y), (x))
#define render_Clear() system("clear")
#endif


#define render_PushToScreenBuffer(gameobject)                       \
    if (gameobject->sprite->sprite_type == SPRITE_CHARACTER)         \
        screen_buffer[                                              \
            Vec2D_to_buffer_index(gameobject->position)] = 'X';     \
    else                                                            \
        render_RenderSprite(                                        \
            gameobject->sprite,                                     \
            Vec2D_to_buffer_index(gameobject->position))


#define render_ClearFromScreenBuffer(gameobject)                                    \
    screen_buffer[                                                                  \
        Vec2D_to_buffer_index(gameobject->position)] = CFG_RENDER_EMPTY_TILE_SPRITE


#define render_PushSceneGameObjectsToScreenBuffer()                                 \
    do {                                                                            \
        struct ListNode* cursor = active_scene->gameobject_head;                    \
        while (cursor) {                                                            \
            render_PushToScreenBuffer(((struct GameObject*) cursor->value_ptr));    \
            cursor = cursor->next;                                                  \
        }                                                                           \
    } while (0)



void 
render_RenderSprite(
    struct Sprite* sprite,
    size_t root_buffer_index)
{
    for (int i = 0; i < sprite->sprite_character_grid_length; ++i) {
        printf("%c", sprite->sprite_character_grid[i].character);
    }
    printf("%ld <----", sprite->sprite_character_grid_length);
    exit(1);
}


void
render_StartRender(
    struct Vec2D render_dimensions)
{
    if (CFG_RENDER_HIDE_CURSOR_ON_INIT)
        render_HideCursor();

    if (CFG_RENDER_CLEAR_ON_INIT)
        render_Clear();

    screen_size.x = render_dimensions.x + (render_dimensions.x * !!CFG_RENDER_DELIMITER);
    screen_size.y = render_dimensions.y;
    screen_buffer_size = screen_size.x * (screen_size.y + screen_size.x);
    screen_buffer = calloc(1, screen_buffer_size);
}


void
render_SetActiveScene(
    struct Scene* new_active_scene)
{
    active_scene = new_active_scene;
    render_StartRender(active_scene->scene_dimensions);
}


void
render_RenderFrame()
{
    render_SetCursorPos(0, 0);

    #if CFG_RENDER_AUTO_RENDER_GAMEOBJECTS
    render_PushSceneGameObjectsToScreenBuffer();
    #endif

    
    for (int y = 0; y < screen_size.y; ++y) {
        for (int x = 0; x < screen_size.x; ++x) {
            if (screen_buffer[xy_to_buffer_index(x, y)] == '\0')
                screen_buffer[xy_to_buffer_index(x, y)] = CFG_RENDER_EMPTY_TILE_SPRITE;

            // only include this code if the delimiter is not null
            // micro optimizations are cool and good, right?
            #if CFG_RENDER_DELIMITER
            if (screen_buffer[xy_to_buffer_index(++x, y)] == '\0')
                screen_buffer[xy_to_buffer_index(x, y)] = CFG_RENDER_DELIMITER;
            #endif
        }
        screen_buffer[xy_to_buffer_index(screen_size.x, y)] = '\n';
    }

    #if CFG_SAFE_MODE
    printf("%s", screen_buffer);
    #else
    puts(screen_buffer);
    #endif

    memset(screen_buffer, 0, screen_buffer_size);
}