#include <assert.h>
#include <math.h>
#include "./point.h"

vec_t vec(float x, float y)
{
    vec_t result = {
        .x = x,
        .y = y
    };
    return result;
}

vec_t vec_from_ps(point_t p1, point_t p2)
{
    vec_t result = {
        .x = p2.x - p1.x,
        .y = p2.y - p1.y
    };
    return result;
}

float vec_arg(vec_t v)
{
    return atan2f(v.y, v.x);
}

float vec_mag(vec_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

vec_t vec_sum(vec_t v1, vec_t v2)
{
    vec_t result = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y
    };
    return result;
}

vec_t vec_neg(vec_t v)
{
    vec_t result = {
        .x = -v.x,
        .y = -v.y
    };

    return result;
}

float vec_length(vec_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

void vec_add(vec_t *v1, vec_t v2)
{
    v1->x += v2.x;
    v1->y += v2.y;
}

vec_t vec_scala_mult(vec_t v, float scalar)
{
    vec_t result = {
        .x = v.x * scalar,
        .y = v.y * scalar
    };
    return result;
}

vec_t vec_entry_mult(vec_t v1, vec_t v2)
{
    vec_t result = {
        .x = v1.x * v2.x,
        .y = v1.y * v2.y
    };

    return result;
}

vec_t vec_entry_div(vec_t v1, vec_t v2)
{
    vec_t result = {
        .x = v1.x / v2.x,
        .y = v1.y / v2.y
    };

    return result;
}

float rad_to_deg(float a)
{
    return 180 / PI * a;
}
