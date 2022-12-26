
#include <iostream>
#include "Snake.h"
#include "Game.h"

Snake::Body::Body(size_t game_field_width, size_t game_field_height) : game_field_width(game_field_width),
                                                                       game_field_height(game_field_height) {
    positions = new int *[game_field_width * game_field_height];
    for (int i = 0; i < game_field_width * game_field_height; i++)
        positions[i] = new int[2];
    head = new int[2];
}

Snake::Body::~Body() {
    for (int i = 0; i < game_field_width * game_field_height; i++)
        delete[] positions[i];
    delete[] positions;
    delete[] head;
}

int *Snake::Body::getHead() const {
    this->head[X_COORDINATE] = this->positions[0][X_COORDINATE]; ///may be troubles
    this->head[Y_COORDINATE] = this->positions[0][Y_COORDINATE];
    return head;
}

Snake::Snake(const size_t field_width, const size_t field_height) : field_width(field_width),
                                                                    field_height(field_height),
                                                                    body(field_width, field_height), food(1, 1) {}

void Snake::initialize() {
    body.current_direction = body.previos_direction = Direction::DIRECTION_UP;
    body.length = 4;
    int width_pos = rand() % field_width;
    for (int i = 0; i < body.length; i++) {
        this->body.positions[i][X_COORDINATE] = width_pos;
        this->body.positions[i][Y_COORDINATE] = field_height / 2;
    }
    body.getHead();
    gen_new_food_position();
}

void Snake::gen_new_food_position() {
    food.position_x = rand() % field_width;
    food.position_y = rand() % field_height;
    if (food_inside_snake())
        gen_new_food_position();
}

bool Snake::food_inside_snake() {
    for (int i = 0; i < body.length; i++)
        if (body.positions[i][X_COORDINATE] == food.position_x && body.positions[i][Y_COORDINATE] == food.position_y)
            return true;
    return false;
}

void Snake::step(Game &game) {
    for (int i = body.length; i > 0; i--) {
        body.positions[i][X_COORDINATE] = body.positions[i - 1][X_COORDINATE];
        body.positions[i][Y_COORDINATE] = body.positions[i - 1][Y_COORDINATE];
    }
    switch (body.current_direction) {
        case Direction::DIRECTION_RIGHT:
//                body.head[X_COORDINATE]++;
            body.positions[0][X_COORDINATE]++;
            break;
        case Direction::DIRECTION_LEFT:
//                body.head[X_COORDINATE]--;
            body.positions[0][X_COORDINATE]--;
            break;

        case Direction::DIRECTION_UP:
//                std::cout << "head: x - " << body.head[X_COORDINATE] << " y - " << body.head[Y_COORDINATE] << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAw\n";
//                body.head[Y_COORDINATE]--;
            body.positions[0][Y_COORDINATE]--;
            break;
        case Direction::DIRECTION_DOWN:
//                body.head[Y_COORDINATE]++;
            body.positions[0][Y_COORDINATE]++;
            break;
    }


    ///safe snake if it move over the screen
    if (body.positions[0][X_COORDINATE] == field_width)
        body.positions[0][X_COORDINATE] = 0;
    else if (body.positions[0][X_COORDINATE] == -1)
        body.positions[0][X_COORDINATE] = field_width - 1;
    else if (body.positions[0][Y_COORDINATE] == field_height)
        body.positions[0][Y_COORDINATE] = 0;
    else if (body.positions[0][Y_COORDINATE] == -1)
        body.positions[0][Y_COORDINATE] = field_height - 1;

//    if (body.head[X_COORDINATE] == field_width)
//        body.head[X_COORDINATE] = 0;
//    else if (body.head[X_COORDINATE] == -1)
//        body.head[X_COORDINATE] = field_width - 1;
//    else if (body.head[Y_COORDINATE] == field_height)
//        body.head[Y_COORDINATE] = 0;
//    else if (body.head[Y_COORDINATE] == -1)
//        body.head[Y_COORDINATE] = field_height - 1;
    body.getHead();
    ///snake eat food
    if (game.snake_ptr_->food.position_x == this->body.head[X_COORDINATE] &&
        game.snake_ptr_->food.position_y == this->body.head[Y_COORDINATE]) {
        game.snake_ptr_->gen_new_food_position();
        this->body.length++;
    }
    if (game.snake2_ptr_ != nullptr) {
        if (game.snake2_ptr_->food.position_x == this->body.head[X_COORDINATE] &&
            game.snake2_ptr_->food.position_y == this->body.head[Y_COORDINATE]) {
            game.snake2_ptr_->gen_new_food_position();
            this->body.length++;
        }
    }
    if (game.snakes_.size() != 0) {
        if (game.snakes_[0].food.position_x == this->body.head[X_COORDINATE] &&
            game.snakes_[0].food.position_y == this->body.head[Y_COORDINATE]) {
            game.snakes_[0].gen_new_food_position();
            this->body.length++;
        }
    }

    ///snake want to die
    if (!(body.positions[0][X_COORDINATE] == body.positions[1][X_COORDINATE] &&
          body.positions[0][Y_COORDINATE] == body.positions[1][Y_COORDINATE])) {
        int length = game.snake_ptr_->body.length;
        if (game.snake2_ptr_ != nullptr) {
            if (game.snake_ptr_->body.length < game.snake2_ptr_->body.length) length = game.snake2_ptr_->body.length;
        }
        for (int i = 1; i < length; i++) {
            if (game.snake_ptr_->body.positions[i][X_COORDINATE] == body.head[X_COORDINATE] &&
                game.snake_ptr_->body.positions[i][Y_COORDINATE] == body.head[Y_COORDINATE]) {
//                    initialize(); ///GAME OVER
                if (game.snake2_ptr_ == nullptr && game.snakes_.size() == 0) {
                    game.GameOver();
                }
                game.snake_die = true;
//                    game.GameOver();
            }
            if (game.snake2_ptr_ != nullptr) {
                if (game.snake2_ptr_->body.positions[i][X_COORDINATE] == body.head[X_COORDINATE] &&
                    game.snake2_ptr_->body.positions[i][Y_COORDINATE] == body.head[Y_COORDINATE]) {
//                        initialize(); ///GAME OVER
                    game.snake2_die = true;
//                        game.GameOver();
                }
                if (game.snake_ptr_->body.head[X_COORDINATE] == game.snake2_ptr_->body.head[X_COORDINATE] &&
                    game.snake_ptr_->body.head[Y_COORDINATE] == game.snake2_ptr_->body.head[Y_COORDINATE]) {
                    if (game.snake_ptr_->body.length >= game.snake2_ptr_->body.length)
                        game.snake2_die = true;///GAME OVER
                    else game.snake_die = true;
//                    game.is_paused_ = true;
//                        game.GameOver();
                }
            }
            if (game.snakes_.size() != 0) {
                if (game.snakes_[0].body.positions[i][X_COORDINATE] == body.head[X_COORDINATE] &&
                    game.snakes_[0].body.positions[i][Y_COORDINATE] == body.head[Y_COORDINATE]) {
//                        initialize(); ///GAME OVER
                    game.crazy_snake_die = true;
//                        game.GameOver();
                }
                if (game.snake_ptr_->body.head[X_COORDINATE] == game.snakes_[0].body.head[X_COORDINATE] &&
                    game.snake_ptr_->body.head[Y_COORDINATE] == game.snakes_[0].body.head[Y_COORDINATE]) {
                    if (game.snake_ptr_->body.length >= game.snakes_[0].body.length)
                        game.crazy_snake_die = true;///GAME OVER
                    else game.snake_die = true;
//                    game.is_paused_ = true;
//                        game.GameOver();
                }
                if (game.snake2_ptr_ != nullptr) {
                    if (game.snake2_ptr_->body.head[X_COORDINATE] == game.snakes_[0].body.head[X_COORDINATE] &&
                        game.snake2_ptr_->body.head[Y_COORDINATE] == game.snakes_[0].body.head[Y_COORDINATE]) {
                        if (game.snake2_ptr_->body.length >= game.snakes_[0].body.length)
                            game.crazy_snake_die = true;///GAME OVER
                        else game.snake2_die = true;
//                    game.is_paused_ = true;
//                        game.GameOver();
                    }
                }
            }
        }
    }
}

void Snake::redefine_direction(Direction direction) {
    if (direction == Direction::DIRECTION_RIGHT && body.current_direction != Direction::DIRECTION_LEFT &&
        body.current_direction != Direction::DIRECTION_RIGHT) {
//            body.previos_direction = body.current_direction;
        body.current_direction = Direction::DIRECTION_RIGHT;
    } else if (direction == Direction::DIRECTION_LEFT && body.current_direction != Direction::DIRECTION_LEFT &&
               body.current_direction != Direction::DIRECTION_RIGHT) {
//            body.previos_direction = body.current_direction;
        body.current_direction = Direction::DIRECTION_LEFT;
    } else if (direction == Direction::DIRECTION_UP && body.current_direction != Direction::DIRECTION_UP &&
               body.current_direction != Direction::DIRECTION_DOWN) {
//            body.previos_direction = body.current_direction;
        body.current_direction = Direction::DIRECTION_UP;
    } else if (direction == Direction::DIRECTION_DOWN && body.current_direction != Direction::DIRECTION_UP &&
               body.current_direction != Direction::DIRECTION_DOWN) {
//            body.previos_direction = body.current_direction;
        body.current_direction = Direction::DIRECTION_DOWN;
    }
}

Snake::Food::Food(size_t x, size_t y) : position_x(x), position_y(y) {
}