#pragma once

#define X_COORDINATE 0
#define Y_COORDINATE 1

#include <cstdlib>
#include "Game.h"

///перечисление, грубо говоря
enum class Direction {
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
    DIRECTION_UP,
    DIRECTION_DOWN,
};

class Game;

class Snake {
public:
    ///explicit
    Snake(const size_t field_width, const size_t field_height);

    class Body {
    public:
        explicit Body(size_t game_field_width, size_t game_field_height);

        ~Body();

        size_t length;
        Direction previos_direction;
        Direction current_direction;
        size_t game_field_width;
        size_t game_field_height;
        int **positions;
        int *head;

        int *getHead() const;
    };

    class Food {
    public:
        Food(size_t x, size_t y);

        size_t position_x;
        size_t position_y;
    };

    Body body;
    Food food;
//    size_t size;
    size_t field_width;
    size_t field_height;

    void initialize();

    void gen_new_food_position();

    bool food_inside_snake();

    void step(Game &game);

    void redefine_direction(Direction direction);
};