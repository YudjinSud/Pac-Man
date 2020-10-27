//
// Created by yudjin on 10/6/20.
//

#include "Player.h"

#define log(x)  #x" = " << x << '\n'

void Player::move(int deltaX, int deltaY, bool is_available) {
    if(is_available) {
        x += deltaX;
        y += deltaY;
    }
    Notify();
    //std::cout << *this;
}


std::ostream &operator << (std::ostream &output, const Player &player) {
    output << "-------------Player-------------\n";
    output << log(player.x) << log(player.y) << log(player.life) << log(player.score);
    output << "------------EndPlayer-------------\n";
    return output;
}

void Player::Attach(ILogger *logger) {
    loggers.push_back(logger);
}

void Player::Detach(ILogger *logger) {
    std::cout << "Unsubscribed " << logger->loggerName << "\n";
    loggers.remove(logger);
}

void Player::Notify() {
    for(auto it : loggers) {
        (*it).Update();
    }
}

