//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

//Интерфейс объекта поля (монетка или буст)
class Item {
public:
    virtual ~Item() {};
    virtual void create() = 0;
};

class Coin : public Item {
public:
    void create() override {
        return;
    }

    ~Coin() override {

    }
};

#endif //OOP_ITEM_H
