//
// Created by yudjin on 10/27/20.
//

#ifndef OOP_FILELOGGER_H
#define OOP_FILELOGGER_H

#include "ILogger.h"
#include "../Player.h"

class FileLogger : public ILogger {

    std::ofstream *outFileStream;

public:
    explicit FileLogger(Item *item, std::string);
    explicit FileLogger(Player *player, std::string);

    void unSubscribe() override ;

    ~FileLogger() override;

    void Update() override;
};


#endif //OOP_FILELOGGER_H
