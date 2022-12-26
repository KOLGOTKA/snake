#pragma once

#include "Snake.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <thread>
#include <queue>

class Snake;
class Game {
public:
    Game(Snake *snake_ptr, Snake *snake2_ptr, size_t tile_size);

    Game(Snake *snake_ptr, size_t tile_size);

    void Render();
    ~Game();

    friend class Snake;
private:
    sf::Image ground_;
    sf::Texture ground_texture_;
    sf::Image snake_img_;
    sf::Texture snake_texture_;

    sf::RenderWindow window_;
    float x_scale_;
    float y_scale_;

//    Snake snake2;
    Snake *snake_ptr_;
    Snake *snake2_ptr_;
    void GameOver(std::string winner);
    void GameOver();
    bool is_paused_{};
    bool snake_die = false;
    bool snake2_die = false;
    bool crazy_snake_die = false;
    std::vector<Snake> snakes_;

    int speed_;
    sf::Vector2<unsigned int> window_size_;
    sf::Vector2<unsigned int> tile_size_;
    std::vector<sf::Sprite> tile_map_;
    std::vector<sf::Sprite> field_map_;
    sf::Music music_;

//    std::queue<sf::Event> events_;
    void RenderLoop();

    void RenderSnake(Snake *snake_ptr);
    void RenderScore();
    void HandleEvent(sf::Event &event, sf::View &view);

    void PlayMusic();

};


