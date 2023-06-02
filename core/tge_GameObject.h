#pragma once
#include "tge_GameHandler.h"
#include "tge_datatypes.h"


struct GameObject {
    struct Vec2D position;
    void (*Event_Spawned) (struct GameObject* self);
    void (*Event_Destroyed) (struct GameObject* self);
    void (*Event_Update) (struct GameObject* self);
};


void GameObject_SetPos(struct GameObject* target_gameobject_ptr, struct Vec2D new_pos);


#if CFG_SAFE_MODE
#define _GameObject_SetPos_Internal(gameobject_ptr, new_pos_vec2D)  \
    render_ClearFromScreenBuffer(gameobject_ptr);                   \
    gameobject_ptr->position = new_pos_vec2D
#else
#define _INTERNAL_GameObject_SetPos(gameobject_ptr, new_pos_vec2D)  \
    gameobject_ptr->position = new_pos_vec2D
#endif


#define GameObject_CallUpdate(gameobject_ptr)   \
    gameobject_ptr->Event_Update(gameobject_ptr)


#define GameObject_SetPos(gameobject_ptr, new_pos_vec2D)            \
    do {                                                            \
        _INTERNAL_GameObject_SetPos(gameobject_ptr, new_pos_vec2D); \
        if (CFG_GAMEOBJECT_PUSH_TO_SCREENBUFFER_ON_SETPOS)          \
            render_PushToScreenBuffer(gameobject_ptr);              \
    } while (0)



/* Does nothing, used for event placeholders */
void
GameObject_BlankFunction() {};


struct GameObject*
GameObject_Create()
{
    struct GameObject* new_gameobject = calloc(1, sizeof(struct GameObject));
    new_gameobject->Event_Spawned = GameObject_BlankFunction;
    new_gameobject->Event_Destroyed = GameObject_BlankFunction;
    new_gameobject->Event_Update = GameObject_BlankFunction;
    return new_gameobject;
}
