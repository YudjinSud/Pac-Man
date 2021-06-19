//
// Created by yudjin on 11/24/20.
//

#include "Scared.h"

Point2D Scared::generateMove() {
    Point2D shortest = FieldUtils::findShortestMove(this->enemy_->getPosition(),
                                        this->enemy_->getPlayerPosition());
    Point2D farthest = {-shortest.x, -shortest.y};
    return farthest;
}
