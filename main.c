#include <stdlib.h>
#include <stdio.h>
#include "core/tge_GameHandler.h"


int
main()
{
    struct Scene* main_scene = Scene_Create();
    GameHandler_SetActiveScene(main_scene);
    GameHandler_InitGameScreen(20, 10);

    struct GameObject* enemy = GameObject_Create();
    Scene_SpawnGameObject(main_scene, enemy);
    GameObject_SetPos(enemy, xy_to_Vec2D(7, 4));

    GameHandler_Update();
    return 0;
}