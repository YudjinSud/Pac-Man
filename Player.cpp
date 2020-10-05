//
// Created by yudjin on 10/6/20.
//

#include "Player.h"

Player::Player(int x, int y) : x(x), y(y) {
    life = 3;
    score = 0;
}

void Player::move(int deltaX, int deltaY, bool is_available) {
    if(is_available) {
        x += deltaX;
        y += deltaY;
    }
}