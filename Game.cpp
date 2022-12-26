#include "Game.h"
#include <iostream>

Game::Game(Snake *snake_ptr, Snake *snake2_ptr, size_t tile_size) : snake_ptr_(snake_ptr), snake2_ptr_(snake2_ptr),
                                                                    tile_size_({(unsigned) tile_size,
                                                                                (unsigned) tile_size}), speed_(15) {

    if (snake_ptr_ != nullptr) {
        window_size_.x = snake_ptr_->field_width * tile_size_.x;
        window_size_.y = snake_ptr_->field_height * tile_size_.y;

        ground_.loadFromFile("../images/ground_128px.png");
        ground_texture_.loadFromImage(ground_);
        ground_texture_.setSmooth(true);

        snake_img_.loadFromFile("../images/sprites.png");
        snake_texture_.loadFromImage(snake_img_);
        snake_texture_.setSmooth(true);

        x_scale_ = (float) tile_size_.x / 64;
        y_scale_ = (float) tile_size_.y / 64;

        for (int y = 0; y < snake_ptr_->field_height; y++) {
            for (int x = 0; x < snake_ptr_->field_width; x++) {
                auto tile = new sf::Sprite;
                tile->setPosition(x * tile_size_.x, y * tile_size_.y);
                tile->scale(x_scale_, y_scale_);
                tile_map_.push_back(*tile);
            }
        }

/*        for (int i = 0; i <= window_size_.x / 128; i++) {
            for (int j = 0; j <= window_size_.y / 128; j++) {
                auto ground = new sf::Sprite;
                ground->setTexture(ground_texture_);
                ground->setPosition(i * 128, j * 128);
                field_map_.push_back(*ground);
            }
        }*/

//        if (window_size_.x % 64 != 0 && window_size_.y % 64 != 0)
//        {
//            auto ground = new sf::Sprite;
//            ground->setTexture(ground_texture_);
//            ground->setPosition((window_size_.x / 64) * 64, (window_size_.y / 64) * 64);
//            field_map_.push_back(*ground);
//        }
//        if (window_size_.x % 64 != 0) {
//            for (int i = 0; i < window_size_.y / 64; i++) {
//                auto ground = new sf::Sprite;
//                ground->setTexture(ground_texture_);
//                ground->setPosition((window_size_.x / 64) * 64, i * 64);
//                field_map_.push_back(*ground);
//            }
//        }
//        if (window_size_.y % 64 != 0) {
//            for (int i = 0; i < window_size_.x / 64; i++) {
//                auto ground = new sf::Sprite;
//                ground->setTexture(ground_texture_);
//                ground->setPosition(i * 64, (window_size_.y / 64) * 64);
//                field_map_.push_back(*ground);
//            }
//        }

        snake_ptr_->initialize();
        snake2_ptr_->initialize();
        window_.create(sf::VideoMode{window_size_.x, window_size_.y}, "HARD SNAKER");
        window_.setVerticalSyncEnabled(false);
        window_.setFramerateLimit(15);

    } else std::cout << "Invalid Ptr\n";
}

Game::Game(Snake *snake_ptr, size_t tile_size) : snake_ptr_(snake_ptr),
                                                 tile_size_({(unsigned) tile_size, (unsigned) tile_size}), speed_(15) {
    if (snake_ptr_ != nullptr) {
        window_size_.x = snake_ptr_->field_width * tile_size_.x;
        window_size_.y = snake_ptr_->field_height * tile_size_.y;

        ground_.loadFromFile("../images/ground_128px.png");
        ground_texture_.loadFromImage(ground_);
        ground_texture_.setSmooth(true);

        snake_img_.loadFromFile("../images/sprites.png");
        snake_texture_.loadFromImage(snake_img_);
        snake_texture_.setSmooth(true);

        x_scale_ = (float) tile_size_.x / 64;
        y_scale_ = (float) tile_size_.y / 64;

        for (int y = 0; y < snake_ptr_->field_height; y++) {
            for (int x = 0; x < snake_ptr_->field_width; x++) {
                auto tile = new sf::Sprite;
                tile->setPosition(x * tile_size_.x, y * tile_size_.y);
                tile->scale(x_scale_, y_scale_);
                tile_map_.push_back(*tile);
            }
        }
        snake_ptr_->initialize();
        window_.create(sf::VideoMode{window_size_.x, window_size_.y}, "HARD SNAKER");
        window_.setVerticalSyncEnabled(false);
        window_.setFramerateLimit(15);
    } else std::cout << "Invalid Ptr\n";
}

void Game::RenderSnake(Snake *snake_ptr) {

    for (int i = 0; i < snake_ptr->field_height * snake_ptr->field_width; i++) {
        if (snake_ptr->body.head[X_COORDINATE] * tile_size_.x == tile_map_[i].getPosition().x && ///head
            snake_ptr->body.head[Y_COORDINATE] * tile_size_.y == tile_map_[i].getPosition().y) {
            tile_map_[i].setRotation(0);
            int x;
            int y;
            if (snake_ptr->body.current_direction == Direction::DIRECTION_UP) {x = 3; y = 0; }
            else if (snake_ptr->body.current_direction == Direction::DIRECTION_DOWN) {x = 4; y = 1; }
            else if (snake_ptr->body.current_direction == Direction::DIRECTION_LEFT) {x = 3; y = 1; }
            else {x = 4; y = 0;}
            if (snake_ptr == snake_ptr_) {
                tile_map_[i].setTexture(snake_texture_);
                tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                tile_map_[i].setColor({0, 150, 0, 255});
            }
            else if (snake_ptr == snake2_ptr_){
                tile_map_[i].setTexture(snake_texture_);
                tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
            }
            else {
                tile_map_[i].setTexture(snake_texture_);
                tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                tile_map_[i].setColor({255, 0, 0, 255});
            }
            continue;
        }
        bool flag = false;
        for (int j = 1; j < snake_ptr->body.length - 1; j++) {
//            std::cout << snake_ptr->body.positions[j][X_COORDINATE];
            if (snake_ptr->body.positions[j][X_COORDINATE] * tile_size_.x == tile_map_[i].getPosition().x &&
                snake_ptr->body.positions[j][Y_COORDINATE] * tile_size_.y == tile_map_[i].getPosition().y) {
                tile_map_[i].setRotation(0);
                int x;
                int y;
                int x_dif_next_current = snake_ptr->body.positions[j + 1][X_COORDINATE] - snake_ptr->body.positions[j][X_COORDINATE];
                int x_dif_current_prev = snake_ptr->body.positions[j][X_COORDINATE] - snake_ptr->body.positions[j - 1][X_COORDINATE];
                int y_dif_next_current = snake_ptr->body.positions[j + 1][Y_COORDINATE] - snake_ptr->body.positions[j][Y_COORDINATE];
                int y_dif_current_prev = snake_ptr->body.positions[j][Y_COORDINATE] - snake_ptr->body.positions[j - 1][Y_COORDINATE];
                if (x_dif_next_current == 0) {
                    if (y_dif_next_current == 1) {
                        if (x_dif_current_prev == 1) {x = 2; y = 0;}
                        else if (x_dif_current_prev == -1) {x = 0; y = 0;}
                        else if (x_dif_current_prev == 0) {x = 2; y = 1;}
                    }
                    else if (y_dif_next_current == -1) {
                        if (x_dif_current_prev == 1) {x = 2; y = 2;}
                        else if (x_dif_current_prev == -1) {x = 0; y = 1;}
                        else if (x_dif_current_prev == 0) {x = 2; y = 1;}
                    }
                }
                else if (x_dif_next_current == 1) {
                    if (y_dif_current_prev == 1) {x = 0; y = 1;}
                    else if (y_dif_current_prev == 0) {x = 1; y = 0;}
                    else if (y_dif_current_prev == -1) {x = 0; y = 0;}
                }
                else if (x_dif_next_current == -1) {
                    if (y_dif_current_prev == 1) {x = 2; y = 2;}
                    else if (y_dif_current_prev == 0) {x = 1; y = 0;}
                    else if (y_dif_current_prev == -1) {x = 2; y = 0;}
                }
                if (snake_ptr == snake_ptr_) {
                    tile_map_[i].setTexture(snake_texture_);
                    tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                    tile_map_[i].setColor({0, 150, 0, 255});
                }
                else if (snake_ptr == snake2_ptr_){
                    tile_map_[i].setTexture(snake_texture_);
                    tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                }
                else {
                    tile_map_[i].setTexture(snake_texture_);
                    tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                    tile_map_[i].setColor({255, 0, 0, 255});
                }
                //std::cout << snake_ptr->body.positions[j][X_COORDINATE] << " " << snake_ptr->body.positions[j][Y_COORDINATE] << '\n';
                flag = true;
                continue;
            }
        }
        if (flag) {
            flag = false;
            continue;
        }
        if (snake_ptr->body.positions[snake_ptr->body.length - 1][X_COORDINATE] * tile_size_.x == tile_map_[i].getPosition().x && ///tail
            snake_ptr->body.positions[snake_ptr->body.length - 1][Y_COORDINATE] * tile_size_.y == tile_map_[i].getPosition().y) {
            tile_map_[i].setRotation(0);

            int x;
            int y;
            int x_dif_next_current = snake_ptr->body.positions[snake_ptr->body.length - 2][X_COORDINATE] - snake_ptr->body.positions[snake_ptr->body.length - 1][X_COORDINATE];
            int y_dif_next_current = snake_ptr->body.positions[snake_ptr->body.length - 2][Y_COORDINATE] - snake_ptr->body.positions[snake_ptr->body.length - 1][Y_COORDINATE];
            if (x_dif_next_current == 0) {
                if (y_dif_next_current == 1) {x = 4; y = 3;}
                else if (y_dif_next_current == -1) {x = 3; y = 2;}
            }
            else if (y_dif_next_current == 0) {
                if (x_dif_next_current == 1) {x = 4; y = 2;}
                else if (x_dif_next_current == -1) {x = 3; y = 3;}
            }
            if (snake_ptr == snake_ptr_) {
                tile_map_[i].setTexture(snake_texture_);
                tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                tile_map_[i].setColor({0, 150, 0, 255});
            }
            else if (snake_ptr == snake2_ptr_){
                tile_map_[i].setTexture(snake_texture_);
                tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
            }
            else {
                tile_map_[i].setTexture(snake_texture_);
                tile_map_[i].setTextureRect(sf::IntRect(64 * x, 64 * y, 64, 64));
                tile_map_[i].setColor({255, 0, 0, 255});
            }
            continue;
        }
        if (snake_ptr->food.position_x * tile_size_.x == tile_map_[i].getPosition().x &&
            snake_ptr->food.position_y * tile_size_.y == tile_map_[i].getPosition().y) {
            tile_map_[i].setRotation(0);
            tile_map_[i].setTexture(snake_texture_);
            tile_map_[i].setTextureRect(sf::IntRect(64 * 0, 64 * 3, 64, 64));
//            tile_map_[i].setColor({150,0,0,255});
            continue;
        }
    }
}

void Game::RenderLoop() {
    sf::Sprite map_sprite;
    map_sprite.setTexture(ground_texture_);
    while (window_.isOpen()) {
        if (snake2_ptr_ != nullptr) {
            window_.setTitle("Score " + std::to_string(snake_ptr_->body.length - 4) + " : " +
                               std::to_string(snake2_ptr_->body.length - 4));
        } else { window_.setTitle("Score " + std::to_string(snake_ptr_->body.length - 4)); }
        if (snake2_ptr_ != nullptr) {
            if (snakes_.size() != 0) {
                if (snake_die) {
                    if (snake2_die) GameOver("Crazy Snake");
                    else if (crazy_snake_die) GameOver("number-Snake");
                }
                else if (snake2_die) {
                    if (snake_die) GameOver("Crazy Snake");
                    else if (crazy_snake_die) GameOver("letter-snake");
                }
                else if (crazy_snake_die) {
                    if (snake_die) GameOver("number-Snake");
                    else if (snake2_die) GameOver("letter-snake");
                }

            } else {
                if (snake_die) GameOver("number-Snake");
                else if (snake2_die) GameOver("letter-snake");
            }
        }
        sf::Event event{};
        auto view = window_.getDefaultView();
        while (window_.pollEvent(event)) {
            HandleEvent(event, view);
        }
        for (int i = 0; i < tile_map_.size(); i++) {
            tile_map_[i].setRotation(180);
            tile_map_[i].setColor({255,255,255,255});
        }
        ///Draw map
        for (int i = 0; i <= window_size_.x / 128; i++) {
            for (int j = 0; j <= window_size_.y / 128; j++) {
                map_sprite.setPosition(i * 128, j * 128);
                window_.draw(map_sprite);
            }
        }
        if (!snake_die)
        {
            std::thread t1([this]() { RenderSnake(snake_ptr_); });
            t1.join();
    }
        if (snake2_ptr_ != nullptr) {
            if (!snake2_die) {
                std::thread t2([this]() { RenderSnake(snake2_ptr_); });
                t2.join();
            }
        }
        if (snakes_.size() != 0) {
            if (!crazy_snake_die) {
                std::thread t3([this]() { RenderSnake(&snakes_[0]); });
                t3.join();
            }
        }

        for (const auto &item: tile_map_) {
            if (item.getRotation() != 180) window_.draw(item);
        }
        window_.display();
        if (!is_paused_) {
            if (!snake_die) snake_ptr_->step(*this);
        if (snake2_ptr_ != nullptr)
            if (!snake2_die)
                snake2_ptr_->step(*this);
        if (snakes_.size() != 0) {
            if (!crazy_snake_die) {
                int dir = rand() % 4;
                Direction direction;
                if (dir == 0) direction = Direction::DIRECTION_UP;
                if (dir == 1) direction = Direction::DIRECTION_DOWN;
                if (dir == 2) direction = Direction::DIRECTION_LEFT;
                if (dir == 3) direction = Direction::DIRECTION_RIGHT;
                snakes_[0].redefine_direction(direction);
                snakes_[0].step(*this);
            }
        }
        }
    }
}

void Game::HandleEvent(sf::Event &event, sf::View &view) {
    switch (event.type) {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Space: {

                    break;
                }
                case sf::Keyboard::Add: {
                    if (speed_ <= 100) {
                        speed_ += 5;
                        window_.setFramerateLimit(speed_);
                    }
                    break;
                }
                case sf::Keyboard::Subtract: {
                    if (speed_ >= 5) {
                        speed_ -= 5;
                        window_.setFramerateLimit(speed_);
                    }
                    break;
                }
                case sf::Keyboard::G: {
                    Game::GameOver("Nobody");
                    //s2
                    break;
                }
                case sf::Keyboard::R: {
                    snake_ptr_->initialize();
                    if (snake2_ptr_ != nullptr) snake2_ptr_->initialize();
                    break;
                }
                case sf::Keyboard::C: {
                    if (snakes_.size() == 0) {
                        snakes_.emplace_back(snake_ptr_->field_width, snake_ptr_->field_height);
                        snakes_[0].initialize();
                    }
                    break;
                }
                case sf::Keyboard::W: {
                    snake_ptr_->redefine_direction(Direction::DIRECTION_UP);
                    break;
                }
                case sf::Keyboard::S: {
                    snake_ptr_->redefine_direction(Direction::DIRECTION_DOWN);
                    break;
                }
                case sf::Keyboard::A: {
                    snake_ptr_->redefine_direction(Direction::DIRECTION_LEFT);
                    break;
                }
                case sf::Keyboard::D: {
                    snake_ptr_->redefine_direction(Direction::DIRECTION_RIGHT);
                    break;
                }
                case sf::Keyboard::Up: {
                    if (snake2_ptr_ != nullptr) snake2_ptr_->redefine_direction(Direction::DIRECTION_UP);
                    break;
                }
                case sf::Keyboard::Down: {
                    if (snake2_ptr_ != nullptr) snake2_ptr_->redefine_direction(Direction::DIRECTION_DOWN);
                    break;
                }
                case sf::Keyboard::Left: {
                    if (snake2_ptr_ != nullptr) snake2_ptr_->redefine_direction(Direction::DIRECTION_LEFT);
                    break;
                }
                case sf::Keyboard::Right: {
                    if (snake2_ptr_ != nullptr) snake2_ptr_->redefine_direction(Direction::DIRECTION_RIGHT);
                    break;
                }
                case sf::Keyboard::P: {
                    if (is_paused_) is_paused_ = false;
                    else is_paused_ = true;
                    break;
                }
                case sf::Keyboard::M: {
                    PlayMusic();
                    break;
                }
                default: {
                }
            }
            break;
        default: {
        }
    }

}

void Game::PlayMusic() {
//    sf::SoundBuffer buffer;
//    buffer.loadFromFile("brue.ogg");
//    sf::Sound sound;
//    sound.setBuffer(buffer);
//    std::cout << sound.getStatus();
//    sound.play();
    if (music_.Playing) {
        music_.openFromFile("brue.wav");
        music_.play();
    }
}

Game::~Game() {
    ////TODO
}

void Game::Render() {
    std::thread renderTh([this]() { RenderLoop(); });
    renderTh.join();
}

void Game::RenderScore() {

    std::cout << "AAAAAAA";
    sf::RenderWindow window;
    sf::Vector2<unsigned int> window_size;
    window_size.x = 100;
    window_size.y = 100;

    sf::Font font_press_enter;
    font_press_enter.loadFromFile("../fonts/font_press_enter.ttf");
    sf::Text text_ent(" ", font_press_enter, 10);
    text_ent.setColor(sf::Color::White);

    window.create(sf::VideoMode{window_size.x, window_size.y}, "score");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(15);
    while (window.isOpen()) {
        window.clear();
        sf::Event event{};
        auto view = window.getDefaultView();
        if (snake2_ptr_ != nullptr) {
            text_ent.setString(std::to_string(snake_ptr_->body.length - 4) + " : " +
                               std::to_string(snake2_ptr_->body.length - 4));
        } else { text_ent.setString(std::to_string(snake_ptr_->body.length - 4)); }

        window.draw(text_ent);
        bool flag = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                flag = true;
                break;
            }
        }
        if (flag) break;
    }
}

void Game::GameOver(std::string winner) {
    sf::Font font;
    font.loadFromFile("../fonts/font.ttf");
    sf::Text text("GAME OVER", font, snake_ptr_->field_height);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    sf::Font font_press_enter;
    font_press_enter.loadFromFile("../fonts/font_press_enter.ttf");
    sf::Text text_win("Win: " + winner, font_press_enter, snake_ptr_->field_height);
    text_win.setColor(sf::Color::Green);

    sf::Text text_ent("Press ENTER to continue", font_press_enter, snake_ptr_->field_height / 2);
    text_ent.setColor(sf::Color::White);
//    sf::Texture texture;
//    texture.loadFromFile("../images/game_over.jpeg");
//    sf::Sprite sprite;
//    sprite.setTexture(texture);
//    sprite.setPosition(0, 0);
    is_paused_ = true;
    snake_ptr_->initialize();
    snake_die = false;
    if (snake2_ptr_ != nullptr) {
        snake2_ptr_->initialize();
        snake2_die = false;
    }
    if (snakes_.size() != 0) {
        snakes_[0].initialize();
        crazy_snake_die = false;
    }
    window_.clear();
    while (window_.isOpen()) {
        auto view = window_.getDefaultView();
        text.setPosition(view.getCenter().x - snake_ptr_->field_width * 2,
                         view.getCenter().y - snake_ptr_->field_height * 2);
        window_.draw(text);
        text_win.setPosition(view.getCenter().x - snake_ptr_->field_width * 2,
                             view.getCenter().y + snake_ptr_->field_height);
        window_.draw(text_win);
        text_ent.setPosition(view.getCenter().x - snake_ptr_->field_width * 2,
                             view.getCenter().y + snake_ptr_->field_height * 2);
        window_.draw(text_ent);
//        window_.draw(sprite);
        window_.display();/////////////////
        sf::Event event{};
        bool flag = false;
        while (window_.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Enter) {
                flag = true;
                break;
            }
            if (event.type == sf::Event::Closed) {
                window_.close();
                flag = true;
                break;
            }
        }
        if (flag) break;
    }
    is_paused_ = false;
}

void Game::GameOver() {
    sf::Font font;
    font.loadFromFile("../fonts/font.ttf");
    sf::Text text("GAME OVER", font, snake_ptr_->field_height);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    sf::Font font_press_enter;
    font_press_enter.loadFromFile("../fonts/font_press_enter.ttf");
    sf::Text text_ent("Press ENTER to continue", font_press_enter, snake_ptr_->field_height / 2);
    text_ent.setColor(sf::Color::White);
//    sf::Texture texture;
//    texture.loadFromFile("../images/game_over.jpeg");
//    sf::Sprite sprite;
//    sprite.setTexture(texture);
//    sprite.setPosition(0, 0);
    is_paused_ = true;
    snake_ptr_->initialize();
    snake_die = false;

    window_.clear();
    while (window_.isOpen()) {
        auto view = window_.getDefaultView();
        text.setPosition(view.getCenter().x - snake_ptr_->field_width * 2,
                         view.getCenter().y - snake_ptr_->field_height * 2);
        window_.draw(text);
        text_ent.setPosition(view.getCenter().x - snake_ptr_->field_width * 2,
                             view.getCenter().y + snake_ptr_->field_height * 2);
        window_.draw(text_ent);
//        window_.draw(sprite);
        window_.display();/////////////////
        sf::Event event{};
        bool flag = false;
        while (window_.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Enter) {
                flag = true;
                break;
            }
            if (event.type == sf::Event::Closed) {
                window_.close();
                flag = true;
                break;
            }
        }
        if (flag) break;

    }
}