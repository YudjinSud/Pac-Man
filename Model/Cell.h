#ifndef OOP_CELL_H
#define OOP_CELL_H

#include "Item.h"

#define adjacencySize 4 // Вверх, вниз, влево, вправо

class Cell {
public:
    bool is_available = true;
    int adjacencyList[adjacencySize][2];
    int num;
    int x, y;
    Item *item;

    ~Cell() = default;
};


#endif //OOP_CELL_H
