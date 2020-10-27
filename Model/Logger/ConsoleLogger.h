//
// Created by yudjin on 10/27/20.
//

#ifndef OOP_CONSOLELOGGER_H
#define OOP_CONSOLELOGGER_H

#include "ILogger.h"
#include "../Player.h"


class ConsoleLogger : public ILogger {
public:
    explicit ConsoleLogger(Item *item);
    explicit ConsoleLogger(Player *player);

    void unSubscribe() override;

    void Update() override;
};

#endif //OOP_CONSOLELOGGER_H
