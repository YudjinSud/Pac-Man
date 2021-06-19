//
// Created by yudjin on 10/25/20.
//

#ifndef OOP_ILOGGER_H
#define OOP_ILOGGER_H

#include "iostream"
#include "fstream"
#include "../Item.h"

class Item;
class Player;

class ILogger {
public:
    virtual ~ILogger() {};

    virtual void Update() = 0;

    virtual void unSubscribe() = 0;

    static std::string currentDateTime();

    std::string loggerName;

protected:

    Item * _item = nullptr;
    Player * _player = nullptr;
};


#endif //OOP_ILOGGER_H
