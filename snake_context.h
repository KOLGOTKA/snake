#pragma once
#define X_ 0
#define Y_ 1
/*#include <cstdlib>
#include <cstdint>*/

///статическая переменная, которая записывается где-то в памяти программы
const static uint32_t SNAKE_GAME_WIDTH = 36;
const static uint32_t SNAKE_GAME_HEIGHT = 36;
const static uint32_t SNAKE_BLOCK_SIZE_IN_PIXELS = 20;
const static uint32_t SNAKE_MATRIX_SIZE = (SNAKE_GAME_WIDTH * SNAKE_GAME_HEIGHT);

class Snake{
public:
    struct Body {
        int length;
        ///почему здесь он видит Direction, если я не подключал snaker.h
        Direction prev_direction;
        Direction current_direction;

        int position[SNAKE_MATRIX_SIZE][2];
    } body;

    struct Food {
        int x;
        int y;
    } food;

    static void snake_context_initialize(Snake *ctx) {
        ctx->body.current_direction = ctx->body.prev_direction = DIRECTION_UP;
        ctx->body.length = 3;
        for (int i = 0; i < SNAKE_MATRIX_SIZE; ++i) {
            ctx->body.position[i][X_] = 8;
            ctx->body.position[i][Y_] = 8;
        }
        ///TODO NEW FOOD
    }

    static bool snake_context_food_inside(Snake *ctx) {
        for (int i = 0; i < ctx->body.lenght; ++i)
            if (ctx->food.x == *ctx->body.position[i][X_] && ctx->food.y == *ctx->body.position[i][Y_])
                return true;
        return false
    }
    ///what this?                          ///праздник жатвы_____
    static void snake_context_new_food_position(Snake *ctx) {
        while (true) {
            ctx->food.x = rand() % SNAKE_GAME_WIDTH;
            ctx->food.y = rand() % SNAKE_GAME_HEIGHT;
            if (snake_context_food_inside(ctx))
                return;
        }
    }

};