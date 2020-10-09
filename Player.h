//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Field.h"


class Player {
public :
    Player(int x, int y) : x(x), y(y) {};

    void move(int deltaX, int deltaY, bool is_available);

    ~Player() = default;

    int x, y;

    int score = 0, life = 3;

    Player& operator+=(const Coin &right) {
        this->score += right.isAlive;
        return *this;
    }

};


#endif //OOP_PLAYER_H
