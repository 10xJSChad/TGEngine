#pragma once
#include "tge_GameObject.h"


struct Scene {
    struct Vec2D scene_dimensions;
    struct GridTile* scene_grid;
    struct ListNode* gameobject_head;
};


struct GridTile {
    char char_representation;
    struct ListNode* collider_occupants;
};


struct Scene*
Scene_Create(
    int screen_size_x,
    int screen_size_y)
{
    struct Scene* new_scene = calloc(1, sizeof new_scene);
    new_scene->scene_dimensions = xy_to_Vec2D(screen_size_x, screen_size_y);
    new_scene->gameobject_head = ListNode_Create(NULL);
    return new_scene;
}


struct Scene
Scene_PushGameObject(
    struct Scene* scene,
    struct GameObject* gameobject)
{
    if (!scene->gameobject_head->value_ptr)
        scene->gameobject_head = ListNode_Create(gameobject);
}


struct Scene
Scene_SpawnGameObject(
    struct Scene* scene,
    struct GameObject* gameobject)
{
    Scene_PushGameObject(scene, gameobject);

    #if (!CFG_GAMEOBJECT_DISABLE_EVENT_SPAWNED)
    gameobject->Event_Spawned(gameobject);
    #endif
}