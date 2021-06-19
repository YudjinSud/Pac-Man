//
// Created by yudjin on 11/24/20.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include "Player.h"
#include "Algorithms/Point2D.h"

#define scaredTime 10

class IEnemyState;

template<class Type>
class Enemy {
private:
    Type *enemyType;
    Player *player;

    int scaredTimer;

public:
    Enemy(Player *player, Point2D pos) : enemyType(nullptr), player(player) {
        this->position = pos;
    }

    Point2D position;

    void transitionState(IEnemyState *state) {
        if(this->enemyType != nullptr) {
            delete this->enemyType;
        }
        this->enemyType = state;
        this->enemyType->setEntity(this);
    }

    void scare() {
//        IEnemyState *scared = new Scared()
//        transitionState(scared);
        scaredTimer = scaredTime;
    }

    void update() {
        scaredTimer--;
        makeMove();
        if(scaredTimer == 0) {
            //transitionState(new Type());
        }
    }

    void makeMove() {
        this->position += enemyType->generateMove();
    }


    Point2D getPosition() {
        return this->position;
    }

    Point2D getPlayerPosition(){
        if(this->player != nullptr) {
            return {this->player->position.x, this->player->position.y};
        }
    }
};

#endif //OOP_ENEMY_H
