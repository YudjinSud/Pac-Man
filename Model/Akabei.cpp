//
// Created by yudjin on 11/24/20.
//

#include "Akabei.h"

Point2D Akabei::generateMove() {
    return FieldUtils::findShortestMove(this->enemy_->getPosition(),
            this->enemy_->getPlayerPosition());
}
