//
// Created by yudjin on 11/24/20.
//

#ifndef OOP_IENEMYSTATE_H
#define OOP_IENEMYSTATE_H

#include "Enemy.h"
#include "Algorithms/Point2D.h"

#include <iostream>

using std::cout;

enum Colors{
    RED,
    PINK,
    INKY,
    ORANGE,
    BLUE // energized
};

class IEnemyState {
protected:
    Enemy<IEnemyState> *enemy_;

    Colors color;

public:
    virtual ~IEnemyState() {};

    void setEntity(Enemy<IEnemyState> *enemy) {
        this->enemy_ = enemy;
    }

    virtual Point2D generateMove() = 0;
};


#endif //OOP_IENEMYSTATE_H
