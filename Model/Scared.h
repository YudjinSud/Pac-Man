//
// Created by yudjin on 11/24/20.
//

#ifndef OOP_SCARED_H
#define OOP_SCARED_H

#include "IEnemyState.h"

#include "Algorithms/FieldUtils.h"

class Scared : public IEnemyState {
public:
    Scared() {
        this->color = BLUE;
    }
    Point2D generateMove() override;
    virtual ~Scared()  { };
};

#endif //OOP_SCARED_H
