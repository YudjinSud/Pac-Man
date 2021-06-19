//
// Created by yudjin on 11/24/20.
//

#ifndef OOP_POINT2D_H
#define OOP_POINT2D_H


class Point2D {
public:
    int x, y;

    Point2D &operator+=(const Point2D &right) {
        this->x += right.x;
        this->y += right.y;
        return *this;
    }

    bool operator==(const Point2D &right) {
        return this->x == right.x && this->y == right.y;
    }
};


#endif //OOP_POINT2D_H
