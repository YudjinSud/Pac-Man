#ifndef OOP_FIELD_H
#define OOP_FIELD_H

#include "Cell.h"

const int width =  3;
const int height = 3;

class SimpleIterator;

class Field
{
private:
    Field(int start_num, int end_num) : _start_no(start_num), _end_no(end_num)
    {
        _cells[start_num/height][start_num % width].type = start;
        _cells[end_num/height][end_num % width].type = end;
    }

    ~Field() {}

    Field( const Field&);      // запретили конструктор копирования
    Field& operator=( Field& ); // запретили присваивания
    Field(Field && ); // Не нужен в синглтоне
    Field& operator=(Field &&);

    static Field* field;

    Cell _cells[height][width];
    int _start_no;
    int _end_no;


public:

    friend class SimpleIterator;
    static Field *GetInstance(int start_num, int end_num);


    SimpleIterator *createIterator() const;

};


class SimpleIterator
{
    int index;
    const Field *field;
public:
    SimpleIterator(const Field *f) : field(f)
    {}

    void first() {
        index = 0;
    }

    void next() {
        index++;
    }

    int isDone() {
        return index ==  width*height;
    }

    Cell currentItem() {
        return field->_cells[index / height][index % width];
    }
};


#endif
