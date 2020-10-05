#ifndef OOP_FIELD_H
#define OOP_FIELD_H

#include "Cell.h"

#include <iterator>
#include <iostream>

const int width  = 10;
const int height = 10;

// По краям графа должны быть еще ряды/столбцы чтобы можно было удобно
// запускать алгоритмы (по сути границы поля)
#define wallOffset 2

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

class Field {
private:
    Field(int start_num, int end_num);

    void createGraph();

    static Field *field;

    Cell **_cells;
    int _start_no;
    int _end_no;

    size_t sizeAll = (width + wallOffset) * (height + wallOffset);

    size_t availableSize = sizeAll;

    int dfs(Cell from, bool *visited);

    class iterator : public std::iterator<std::output_iterator_tag, Cell> {
    public :
        explicit iterator(Field &field, size_t index = 0);

        Cell operator*() const;

        iterator &operator++();

        iterator &operator++(int);

        bool operator!=(const iterator &) const;

    private:
        size_t nIndex = 0;
        Field &field;
    };

public:

    Field(Field &);                      // Конструктор копирования
    Field &operator=(const Field &);              // Оператор копирования
    Field(Field &&) noexcept;             // Конструктор перемещения
    Field &operator=(Field &&) noexcept;  // Оператор перемещения

    iterator begin();

    iterator end();

    size_t size() const;

    static Field *GetInstance(int start_num, int end_num);

    bool checkConnectedComponent();

    bool isAvailable(int x, int y);

    void makeWall(int num);

    void makeWall(int x, int y);

    ~Field();
};


#endif
