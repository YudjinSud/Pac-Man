//
// Created by yudjin on 10/6/20.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

//Интерфейс объекта поля (монетка или буст)
class Item {
public:
    Item(int x, int y) : x {x}, y{y} {}
     ~Item() {};

    int x, y;
};

class Coin : public Item {
public:
    Coin(int x, int y) : Item {x, y} {}
    bool isAlive = true;
    ~Coin()  = default;
};

#endif //OOP_ITEM_H
