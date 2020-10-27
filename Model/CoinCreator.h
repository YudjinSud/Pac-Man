//
// Created by yudjin on 10/27/20.
//

#ifndef OOP_COINCREATOR_H
#define OOP_COINCREATOR_H


#include "ICreator.h"
#include "Coin.h"

class CoinCreator : public ICreator {
public:
    Coin *factoryMethod(int x, int y) const override;

    ~CoinCreator() override = default;
};


#endif //OOP_COINCREATOR_H
