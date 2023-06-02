#pragma once
#include "tge_GameObject.h"


struct Scene {
    struct ListNode* gameobject_head;
};


struct Scene*
Scene_Create()
{
    struct Scene* new_scene = calloc(1, sizeof new_scene);
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