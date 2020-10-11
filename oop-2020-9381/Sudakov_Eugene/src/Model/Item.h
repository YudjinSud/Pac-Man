//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

#include <random>
#include <ctime>

//Интерфейс объекта поля (монетка или буст)
class Item {
public:
    Item(int x, int y) : x{x}, y{y} {}

    void generate();

    virtual ~Item() {};

    bool isAlive = true;

    int weight;

    int x, y;
};


class Coin : public Item {
public:
    Coin(int x, int y) : Item{x, y} {}

    ~Coin() override {}
};


class Boost : public Item {
    Boost(int x, int y) : Item{x, y} {};

    ~Boost() override {}
};


class Teleport : public Item {
    Teleport(int x, int y) : Item{x, y} {};

    ~Teleport() override {}
};


//Factory
class Creator {
public:
    virtual ~Creator() {};

    virtual Item* FactoryMethod(int x, int y) const = 0;
};


class CoinCreator : public Creator {
public:
    Coin* FactoryMethod(int x, int y) const override {
        Coin *c = new Coin(x,y);
        c->weight  = 1;
        return c;
    }

    ~CoinCreator() override = default;
};

#endif //OOP_ITEM_H
