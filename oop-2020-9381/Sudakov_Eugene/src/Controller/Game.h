//
// Created by yudjin on 10/5/20.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H


#include <iostream>

#include "../Model/Field.h"
#include "../Model/Player.h"


#include "../View/Gui.h"


class Game {
public:
    void tick();

    void draw();

    void init();

    void processInput();

    sf::Event events;

    Gui gui;

    Field *f;

private:
    int start,  end;
    int *startCoords, *endCoords;

    Player *player;

    void checkCoinsStatus();

    void checkEndStatus();

};


#endif //OOP_GAME_H
