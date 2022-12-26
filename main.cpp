#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Snake.h"

int main() {
Snake snake(40, 40);
//Game game(&snake, 20);

Snake snake2(40, 40);
Game game(&snake, &snake2, 20);
game.Render();
    return 0;
}
