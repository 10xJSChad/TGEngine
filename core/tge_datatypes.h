#pragma once
#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "tge_ListNode.h"


struct Vec2D {
    int x;
    int y;
};


#define Vec2D_Add(vector_a, vector_b) \
    ((struct Vec2D) {vector_a.x + vector_b.x, vector_a.y + vector_b.y})

#define Vec2D_Subtract(vector_a, vector_b) \
    ((struct Vec2D) {vector_a.x - vector_b.x, vector_a.y - vector_b.y})

#define Vec2D_Divide(vector, scalar) \
    ((struct Vec2D) {vector.x / scalar, vector.y / scalar})

#define Vec2D_Multiply(vector, scalar) \
    ((struct Vec2D) {vector.x * scalar, vector.y * scalar})

#define Vec2D_Unpack(vector)    \
    vector.x, vector.y

#define Vec2D_InBounds(vector, bounds_Vec2D)            \
    ((vector.x >= 0 && vector.x < bounds_Vec2D.x)       \
    && (vector.y >= 0 && vector.y < bounds_Vec2D.y))
