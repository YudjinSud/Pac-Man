//
// Created by yudjin on 11/24/20.
//

#ifndef OOP_FIELDUTILS_H
#define OOP_FIELDUTILS_H

#include <vector>

using std::vector;

#include "../Field.h"

#include "Point2D.h"

typedef vector<vector<Cell>> fieldMatrix;

class FieldUtils {
public:
    static Point2D findShortestMove(Point2D start, Point2D finish);

    bool checkConnectedComponent;


};


#endif //OOP_FIELDUTILS_H
