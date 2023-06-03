#include <stdlib.h>
#include <stdio.h>
#include "core/tge_GameHandler.h"
#include "helpers/aliases.h"
#include "helpers/macros.h"

int
main()
{
    // Create the main game scene
    Scene* main_scene = Scene_Create(100, 35);

    // Build the spaceship sprite
    SpriteCharacter SC_SpaceshipFrame = {.character = 'x', .color = COLOR_CYAN};
    SpriteCharacter SC_SpaceshipThrusters = {.character = 'O', .color = COLOR_RED};
    Sprite* SPR_Spaceship;
    
    // Actual sprite creation
    SPRITE_CREATE
    (
        SPRITE_TEMPLATE("......x......", 
                        "|....xxx....|",     
                        "x..xxxxxxx..x",
                        "xxxxxxxxxxxxx",
                        "O.....O.....O");

        SPRITE_TEMPLATE_REPLACE('x', SC_SpaceshipFrame);
        SPRITE_TEMPLATE_REPLACE('O', SC_SpaceshipThrusters);

        SPRITE_IGNORE_CHAR('.');
        SPRITE_SET_TYPE(SPRITE_FLAT);
        SPRITE_ASSIGN(SPR_Spaceship)  
    );

    // Create and configure the spaceship GameObject
    GameObject* GAMEOBJ_SpaceShip = GameObject_Create();
    GAMEOBJ_SpaceShip->sprite = SPR_Spaceship;
    GAMEOBJ_SpaceShip->collider_mode = COLLIDER_SPRITE;
    GAMEOBJ_SpaceShip->collision_rule = COLLISION_FULL;
    GAMEOBJ_SpaceShip->position = xy_to_Vec2D(40, 18);

    // Spawn the spaceship into the main game scene
    Scene_SpawnGameObject(main_scene, GAMEOBJ_SpaceShip);

    // Configure the GameHandler update loop to not run more often than
    // once every 50 milliseconds.
    GameHandlerSettings game_settings = {.update_sleep_amount = 50}; 
    GameHandler_LoadSettings(game_settings);

    // Load the scene and start the game loop
    GameHandler_LoadScene(main_scene);
    GameHandler_Update();
    return 0;
}