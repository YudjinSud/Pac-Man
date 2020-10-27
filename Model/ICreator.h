//
// Created by yudjin on 10/27/20.
//

#ifndef OOP_ICREATOR_H
#define OOP_ICREATOR_H

#include "Item.h"

//Factory
class ICreator {
public:
    virtual ~ICreator() {};

    virtual Item *factoryMethod(int x, int y) const = 0;
};


#endif //OOP_ICREATOR_H
