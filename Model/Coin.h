//
// Created by yudjin on 10/27/20.
//

#ifndef OOP_COIN_H
#define OOP_COIN_H

#include "Item.h"

class Coin : public Item {
public:
    Coin(int x, int y) : Item(x, y) {}

    ~Coin() override {}

    int getWeight() const override;

    bool isAlive() const override;

    int getX() const override;

    int getY() const override;


    void Attach(ILogger *logger) override;

    void Detach(ILogger *logger) override;

    void Notify() const override;

    std::string print() const override;

private:
    std::list<ILogger *> loggers;
};


#endif //OOP_COIN_H
