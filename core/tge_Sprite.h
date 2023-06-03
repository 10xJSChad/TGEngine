#pragma once
#include <stdarg.h>


enum SpriteType {
    SPRITE_FLAT,
    SPRITE_ANIMATED,
    SPRITE_CHARACTER
};


struct SpriteCharacter {
    struct Vec2D relative_position;
    char* color;
    char character;
};


struct SpriteTile {
    /* Position relative to the root tile */
    struct Vec2D relative_pos;
    struct SpriteCharacter sprite_character;
};


struct Sprite {
    enum SpriteType sprite_type;
    struct Vec2D sprite_dimensions;
    struct SpriteCharacter* sprite_character_grid;
    size_t sprite_character_grid_length;
    char ignored_char;
};


void 
print_sprite(
    char** lines)
{
    while (lines[0] != NULL) {
        printf("%s\n", lines[0]);
        ++lines;
    }
}


struct Sprite*
Create_Sprite_Basic()
{
    struct Sprite* new_sprite = calloc(1, sizeof(struct Sprite));
    new_sprite->sprite_type = SPRITE_CHARACTER;
    
    struct SpriteCharacter* new_sprite_character = calloc(
        1, sizeof(struct SpriteCharacter));

    new_sprite_character[0].character = 'X';
    new_sprite_character[0].color = "\x1b[0m"; // COLOR_RESET
    return new_sprite;
}