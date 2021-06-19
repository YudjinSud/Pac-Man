//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Field.h"
#include "Algorithms/Point2D.h"
#define startScore 0
#define startLife 3


class Player {
public :
    Player(Point2D pos) : position(pos) {};

    void move(Point2D delta, bool is_available);

    ~Player() = default;

    Point2D position;

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
