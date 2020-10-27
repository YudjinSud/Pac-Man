//
// Created by yudjin on 10/27/20.
//

#include "FileLogger.h"

void FileLogger::Update() {
    *(this->outFileStream) << currentDateTime();
    if (this->_item != nullptr) {
        *(this->outFileStream) << *(this->_item);
    } else if (this->_player != nullptr) {
        *(this->outFileStream) << *(this->_player);
    }
}

FileLogger::FileLogger(Item *item, std::string logFile) {
    this->loggerName = "FileLogger";
    this->_item = item;
    this->_item->Attach(this);
    this->outFileStream = new std::ofstream(logFile, std::ofstream::out | std::ofstream::ate);
    if (!this->outFileStream)
        throw std::runtime_error("file open stream");
    *outFileStream << *item;
}

FileLogger::~FileLogger() {
    (*outFileStream).close();
    delete outFileStream;
}

FileLogger::FileLogger(Player *player, std::string logFile) {
    this->loggerName = "FileLogger";
    this->_player = player;
    this->_player->Attach(this);
    this->outFileStream = new std::ofstream(logFile, std::ofstream::out | std::ofstream::ate);
    if (!this->outFileStream)
        throw std::runtime_error("file open stream");
    *outFileStream << *player;
}

void FileLogger::unSubscribe() {
    if (this->_item) {
        this->_item->Detach(this);
    } else if (this->_player) {
        this->_player->Detach(this);
    }
}

