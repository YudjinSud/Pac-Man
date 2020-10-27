//
// Created by yudjin on 10/27/20.
//

#include "CoinCreator.h"

Coin *CoinCreator::factoryMethod(int x, int y) const {
    Coin *c = new Coin(x, y);
    return c;
}