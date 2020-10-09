//
// Created by yudjin on 10/6/20.
//

#include "Player.h"

void Player::move(int deltaX, int deltaY, bool is_available) {
    if(is_available) {
        x += deltaX;
        y += deltaY;
    }
}

