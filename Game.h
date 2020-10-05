//
// Created by yudjin on 10/5/20.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Field.h"
#include "Player.h"


#define widthPixels 640
#define heightPixels 480
#define rectSize 25
#define playerSize 7
#define latency 5
#define leftX widthPixels / 3
#define leftY heightPixels/ 3


class Game {
public:
    void tick();

    void draw();

    void init();

    void processInput();

    sf::RenderWindow window;

    Field *f;

private:
    void drawWall(Cell f);

    void drawPlayer();

    Player *player;

    sf::Event events;
};


#endif //OOP_GAME_H
