//
// Created by yudjin on 10/27/20.
//

#include "Coin.h"



std::string Coin::print() const {
    std::string s;
    s +=  "-------------Coin-------------\n";
    s += "Coin.x = " + std::to_string(this->_x) + "\n";
    s += "Coin.y = " + std::to_string(this->_y) + "\n";
    s += "Coin.isAlive = " + std::to_string(this->_isAlive) + "\n";
    s += "Coin.weight = " + std::to_string(this->weight) + "\n";
    s += "------------EndCoin-------------\n";
    return s;
}

void Coin::Attach(ILogger *logger) {
    loggers.push_back(logger);
}

void Coin::Detach(ILogger *logger) {
    std::cout << "Unsubscribed " << logger->loggerName << "\n";
    loggers.remove(logger);
}

void Coin::Notify() const {
    for(auto it : loggers) {
        (*it).Update();
    }
}

int Coin::getX() const {
    return this->_x;
}

int Coin::getY() const {
    return this->_y;
}

bool Coin::isAlive() const {
    return _isAlive;
}

int Coin::getWeight() const {
    return weight;
}
