//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

#include <random>
#include <ctime>
#include <iostream>
#include <list>

#include "Logger/ILogger.h"


class ILogger;

//Интерфейс объекта поля (монетка или буст)
class Item {
private:
    Item();

public:
    Item(int x, int y) : _x(x), _y(y) {}

    virtual ~Item() = default;

    //region Get
    virtual int getWeight() const = 0;

    virtual bool isAlive() const = 0;

    virtual int getX() const = 0;

    virtual int getY() const = 0;
    //endregion

    //region Set
    void setAlive(bool val) {
        _isAlive = val;
        Notify();
    }

    void setX(int x) { _x = x; }

    void setY(int y) { _y = y; }
    //endregion

    //region Logging System
    virtual void Attach(ILogger *logger) = 0;

    virtual void Detach(ILogger *logger) = 0;

    virtual void Notify() const = 0;

    friend std::istream &operator>>(std::istream &input, Item &item);

    friend std::ostream &operator<<(std::ostream &output, const Item &item);

    virtual std::string print() const = 0;
    //endregion

protected:
    const int weight = 1;
    int _x, _y;
    bool _isAlive;
};



class Boost : public Item {
    Boost(int x, int y) : Item(x, y) {}

    ~Boost() override {}
};


class Teleport : public Item {
    Teleport(int x, int y) : Item(x, y) {}

    ~Teleport() override {}
};


#endif //OOP_ITEM_H
