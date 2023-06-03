#pragma once


#define xy_to_Vec2D(x, y) ((struct Vec2D) {x, y})
#define xy_to_index(x, y, grid_x_max) y * grid_x_max + x
#define Vec2D_to_screen_index(vector) vector.y * screen_size.x + vector.x
#define Vec2D_to_buffer_index(vector) vector.y * (screen_size.x + 1) + vector.x
#define Vec2D_to_grid_size_bytes(vector) vector.y * vector.x
#define xy_to_screen_index(xy_x, xy_y) xy_y * screen_size.x + xy_x
#define xy_to_buffer_index(xy_x, xy_y) xy_y * (screen_size.x + 1) + xy_x
#define buffer_index_to_xy(index)   \
    (struct Vec2) {(index) % (screen_size.x + 1), (index) / (screen_size.x + 1)}

#define ptr_to_GameObject(ptr) ((struct GameObject*) ptr)