#ifndef OOP_CELL_H
#define OOP_CELL_H

enum Items {
    weapon,
    medicine,
    enemy
};

enum Type {
    start,
    normal,
    end

};

class Cell {

public:
    bool is_available = 1;
    Items item;
    Type type = normal;

};


#endif //OOP_CELL_H
