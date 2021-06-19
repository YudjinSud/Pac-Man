#ifndef OOP_FIELD_H
#define OOP_FIELD_H

#include "Cell.h"
#include "Item.h"
#include "ICreator.h"
#include "CoinCreator.h"

#include <iterator>
#include <iostream>
#include <vector>

const int width = 10;
const int height = 10;
const int start_no = 1;
const int end_no = 66;

// По краям графа должны быть еще ряды/столбцы чтобы можно было удобно
// запускать алгоритмы (по сути границы поля)
#define wallOffset 2

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct FieldSerialization;

class Field {
private:
    Field(int start_num, int end_num);

    void createGraph();

    static Field *field;

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

    bool isAvailable(int x, int y) const;

    void makeWall(int num);

    void makeWall(int x, int y);

    void initItems(int *startCoords, const ICreator &creator);

    static int *coordsByNum(int num);

    ~Field();

    Cell **_cells;

    Player *player;

    class FieldSerialization {
    public:

        FieldSerialization(){};

        FieldSerialization(Cell **pCell, int start, int end, size_t sizeAll, size_t availableSize, Player *player) :
                start(start), end(end), sizeAll(sizeAll), availableSize(availableSize), player(player) {
            ICreator *coinsFabric = new CoinCreator();
            for (int i = 0; i < height + wallOffset; i++) {
                for (int j = 0; j < width + wallOffset; j++) {
                    this->cells[i][j].x = pCell[i][j].x;
                    this->cells[i][j].y = pCell[i][j].y;
                    this->cells[i][j].num = pCell[i][j].num;
                    this->cells[i][j].is_available = pCell[i][j].is_available;

                    this->cells[i][j].item = coinsFabric->factoryMethod(pCell[i][j].x,
                                                                        pCell[i][j].y);
                    this->cells[i][j].item->setAlive(pCell[i][j].item->isAlive());


//                    std::cout << "i j" << cells[i][j].item->print();
                }
//                std::cout << "\n";
            }
            this->start = start;
            this->end = end;
            this->sizeAll = sizeAll;
            this->availableSize = availableSize;
        };

        Cell cells[height + wallOffset][width + wallOffset];
        int start;
        int end;
        size_t sizeAll;
        size_t availableSize;
        Player *player;
    };

    class Snapshot {
    private:
        FieldSerialization _state;

    public:
        explicit Snapshot(FieldSerialization serialization) : _state(serialization) {};

        FieldSerialization getState() {
            return this->_state;
        }
    };


    Snapshot *save() {
        FieldSerialization state = {this->_cells, this->_start_no, this->_end_no, this->sizeAll,
                                    this->availableSize, this->player};
        return new Snapshot(state);
    };

    void restore(Snapshot *state) {
        for (int i = 0; i < height + wallOffset; i++) {
            for (int j = 0; j < width + wallOffset; j++) {
                this->_cells[i][j] = state->getState().cells[i][j];
            }
        }
        this->_start_no = state->getState().start;
        this->_end_no = state->getState().end;
        this->sizeAll = state->getState().sizeAll;
        this->availableSize = state->getState().availableSize;
        this->player = player;
    }
};


#endif
