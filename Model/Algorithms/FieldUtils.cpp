//
// Created by yudjin on 11/24/20.
//

#include "FieldUtils.h"

Point2D FieldUtils::findShortestMove( Point2D start, Point2D finish) {
    int dx = finish.x - start.x;
    int dy = finish.y - start.y;
    if(abs(dx) > abs(dy)) {
        return {dx/abs(dx), 0};
    }
    else {
        if(dy != 0) {
            return {0, dy / abs(dy)};
        }
    }
}
