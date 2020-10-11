#ifndef OOP_CELL_H
#define OOP_CELL_H

#define adjacencySize 4 // Вверх, вниз, влево, вправо

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

private:
    Items item;
    Type type = normal;

public:
    bool is_available = true;
    int adjacencyList[adjacencySize][2];
    int num;
    int x, y;

    ~Cell() = default;
};


#endif //OOP_CELL_H
