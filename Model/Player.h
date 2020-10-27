//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Field.h"

#define startScore 0
#define startLife 3


class Player {
public :
    Player(int x, int y) : x(x), y(y) {};

    void move(int deltaX, int deltaY, bool is_available);

    ~Player() = default;

    int x, y;

    int score = startScore, life = startLife;

    Player &operator+=(const Item &right) {
        this->score += right.getWeight();
        return *this;
    }

    void Attach(ILogger *logger);

    void Detach(ILogger *logger);

    void Notify();

    friend std::istream &operator>>(std::istream &input, Player &player);

    friend std::ostream &operator<<(std::ostream &output, const Player &player);

private:
    std::list<ILogger *> loggers;
};


#endif //OOP_PLAYER_H
