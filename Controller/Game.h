//
// Created by yudjin on 10/5/20.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H


#include <iostream>

#include "../View/Gui.h"
#include "../Model/Field.h"
#include "../Model/Logger/ConsoleLogger.h"
#include "../Model/Logger/FileLogger.h"
#include "../Model/CoinCreator.h"

#define LOG_FILE "../logs.txt"

class Game {
public:

    ~Game();

    void tick();

    void draw();

    void init();

    void processInput();

    sf::Event events;

    Gui gui;

    Field *f;

    ILogger *consoleLogger;
    ILogger *fileLogger;

private:
    int start,  end;
    int *startCoords, *endCoords;

    Player *player;

    void checkCoinsStatus();

    void checkEndStatus();

};


#endif //OOP_GAME_H
