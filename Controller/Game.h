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
#include "../Model/Enemy.h"
#include "../Model/Akabei.h"
#include "../Model/Scared.h"
#include "../Model/FieldCaretaker.h"

#define LOG_FILE "../logs.txt"

class Game {
public:
    void init();

private:
    int *startCoords, *endCoords;

    Player *player;

    FieldCaretaker *fieldCaretaker;

    void checkCoinsStatus();

    void checkEndStatus();

    bool collisionWithEnemies();

    std::list<Enemy<IEnemyState> *> enemies;

    void tick();

    void draw();

    void processInput();

    sf::Event events;

    Gui gui;

    Field *f;

    ILogger *consoleLogger;
    ILogger *fileLogger;

};


#endif //OOP_GAME_H
