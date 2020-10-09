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
#define heightPixels 640
#define rectSize 25
#define playerSize 7
#define coinSize 3
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
    int start,  end;
    int *startCoords, *endCoords;

    void drawWall(Cell f);

    void drawPlayer();

    void drawCoins();

    Player *player;

    void checkCoinsStatus();

    void checkEndStatus();

    sf::Event events;

    void drawCircleShape(sf::Color color, int size, int x, int y);
};


#endif //OOP_GAME_H
