#pragma once


#define SPRITE_TEMPLATE(...)                                                            \
    char** sprite_template = ((char*[]) { __VA_ARGS__, NULL });                         \
    sprite_dimensions.x = strlen(sprite_template[0]);                                   \
    while (sprite_template[sprite_dimensions.y])                                        \
        ++sprite_dimensions.y;                                                          \
                                                                                        \
    created_sprite->sprite_character_grid = calloc(                                     \
        1, sizeof(struct SpriteCharacter) * (sprite_dimensions.x                        \
                                            * sprite_dimensions.y));                    \
                                                                                        \
    created_sprite->sprite_dimensions = sprite_dimensions;                              \
    created_sprite->sprite_character_grid_length = (sprite_dimensions.x                 \
                                                  * sprite_dimensions.y);               \
                                                                                        \
    for (int y = 0; sprite_template[y] != NULL; ++y)                                    \
        for (int x = 0; sprite_template[y][x] != '\0'; ++x) {                           \
            created_sprite->sprite_character_grid[                                      \
                xy_to_index(                                                            \
                    x, y, sprite_dimensions.x)].character = sprite_template[y][x];      \
                                                                                        \
            created_sprite->sprite_character_grid[                                      \
                xy_to_index(                                                            \
                    x, y, sprite_dimensions.x)].relative_position = xy_to_Vec2D(x, y);  \
        }                                                                               \


#define SPRITE_TEMPLATE_REPLACE(replaced, replacement)                                  \
    for (int y = 0; sprite_template[y] != NULL; ++y)                                    \
        for (int x = 0; sprite_template[y][x] != '\0'; ++x) {                           \
            if (sprite_template[y][x] == replaced) {                                    \
            created_sprite->sprite_character_grid[                                      \
                xy_to_index(x, y, sprite_dimensions.x)] = replacement;                  \
                                                                                        \
            created_sprite->sprite_character_grid[                                      \
                xy_to_index(                                                            \
                    x, y, sprite_dimensions.x)].relative_position = xy_to_Vec2D(x, y);  \
        }                                                                               \
    }


#define SPRITE_IGNORE_CHAR(character)  \
    created_sprite->ignored_char = character;


#define SPRITE_CREATE(code)                                                 \
    do {                                                                    \
        struct Sprite* created_sprite = calloc(1, sizeof(struct Sprite));   \
        struct Vec2D sprite_dimensions = {.x = 0, .y = 0};                  \
        code;                                                               \
    } while (0)                                                             \


#define SPRITE_ASSIGN(assignment_target)    \
    assignment_target = created_sprite;


#define SPRITE_SET_TYPE(type)   \
    created_sprite->sprite_type = type;
