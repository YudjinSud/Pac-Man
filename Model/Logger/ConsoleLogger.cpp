//
// Created by yudjin on 10/27/20.
//

#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger(Item *item) {
    this->loggerName = "ConsoleLogger";
    this->_item = item;
    this->_item->Attach(this);
}

ConsoleLogger::ConsoleLogger(Player *player) {
    this->loggerName = "ConsoleLogger";
    this->_player = player;
    this->_player->Attach(this);
}

void ConsoleLogger::Update() {
    std::cout << currentDateTime();
    if (this->_item) {
        std::cout  << *(this->_item);
    } else if (this->_player) {
        std::cout  << *(this->_player);
    }
}

void ConsoleLogger::unSubscribe() {
    if (this->_item) {
        this->_item->Detach(this);
    } else if (this->_player) {
        this->_player->Detach(this);
    }
}


