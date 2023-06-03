#pragma once


#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define TGE_UNIX
#endif

#if defined(_WIN32) || defined(_WIN64)
#define TGE_WINDOWS
#endif


/*
 * Whether to allow the use of sleep() in the GameHandler's update
 * loop to slow the loop down, disabling this will give a minor
 * performance increase.
 */
#define CFG_GAME_ALLOW_UPDATE_SLEEP true

/* 
 * Whether to use deltatime or not, there is not much
 * there is no built-in replacement for deltatime.
 */
#define CFG_GAME_USE_DELTATIME true

/*
 * Automatically pushes the gameobject into the screen buffer/render queue
 * when its position is changed with GameObject_SetPos.
 * 
 * Using this is completely pointless if CFG_RENDER_AUTO_RENDER_GAMEOBJECTS
 * is enabled, as the renderer will take care of pushing GameObjects to the
 * screen buffer on its own.
 */
#define CFG_GAMEOBJECT_PUSH_TO_SCREENBUFFER_ON_SETPOS false 

/* Prevents the Event_Spawned function from being called automatically */
#define CFG_GAMEOBJECT_DISABLE_EVENT_SPAWNED false

/* Prevents the Event_Destroyed function from being called automatically */
#define CFG_GAMEOBJECT_DISABLE_EVENT_DESTROYED false

/* Prevents the Event_Update function from being called automatically */
#define CFG_GAMEOBJECT_DISABLE_EVENT_UPDATE false

/* Hide the cursor on init */
#define CFG_RENDER_HIDE_CURSOR_ON_INIT true

/* Clear the screen on init */
#define CFG_RENDER_CLEAR_ON_INIT true

/* The char to draw when a tile is not occupied by anything */
#define CFG_RENDER_EMPTY_TILE_SPRITE '.'

/* Tile seperator, is printed after every character */
#define CFG_RENDER_DELIMITER '\0'

/*
 * Whether to let the renderer take care of iterating through
 * and drawing all GameObjects on its own, with no manual control
 * past the render settings of individual GameObjects supported.
 * 
 * It's best to leave this or the next setting on, you can disable both if you
 * really know what you're doing and are ok with needing to write your own
 * function to push the appropriate GameObjects to the screen buffer.
 */
#define CFG_RENDER_AUTO_RENDER_GAMEOBJECTS false

/*
 * !! Will not work if CFG_GAMEOBJECT_DISABLE_EVENT_UPDATE is disabled !!

 * Same as CFG_RENDER_AUTO_RENDER_GAMEOBJECTS but the GameHandler
 * module pushes the GameObjects to the screen buffer while iterating
 * through them to call their GameHandler_Update functions.
 * 
 * This is a performance increase at the cost of more coupling,
 * if you would prefer rendering be left to the renderer exclusively,
 * disable this and enable CFG_RENDER_AUTO_RENDER_GAMEOBJECTS.
 * 
 * In practice, they do the same thing, just don't use both.
 */
#define CFG_RENDER_DEFER_AUTO_RENDER_TO_GAMEHANDLER true

/*
 * Basically just automatic validation of certain things
 * to prevent bugs that can arise from imperfect use
 * of TGE, this is intended to mitigate everything
 * breaking from easy to make mistakes at a
 * (very, very minor) performance cost.
 * 
 * As of writing this, it prevents GameObjects from
 * being re-rendered for each time GameObject_SetPos is called
 * before the frame is rendered.
 * 
 * Personally I'd leave this disabled for development just because
 * it will correct mistakes without letting you know they exist,
 * which will likely just leave a bunch of very mild 'bugs' in the code.
 */
#define CFG_SAFE_MODE false