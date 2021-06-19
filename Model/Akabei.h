//
// Created by yudjin on 11/24/20.
//

#ifndef OOP_AKABEI_H
#define OOP_AKABEI_H

#include "IEnemyState.h"

#include "Algorithms/FieldUtils.h"


class Akabei : public IEnemyState{
public:
    Akabei() {
        this->color = RED;
    }
    Point2D generateMove() override;
    virtual ~Akabei()  {  };
};


#endif //OOP_AKABEI_H
