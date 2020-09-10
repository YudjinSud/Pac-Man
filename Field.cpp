#include "Field.h"

Field* Field::field = nullptr;

Field *Field::GetInstance(int start_num, int end_num) {
    if(field == nullptr) {
        field = new Field(start_num, end_num);
    }
    return field;
}

Field::Field(Field &&other) {
//    _cells = other._cells;
//    _start_no = other._start_no;
//    _end_no = other._end_no;
//    delete[] other._cells;
//    other._start_no = 0;
//    other._end_no = 0;
}


SimpleIterator *Field::createIterator() const {
    return new SimpleIterator(this);
}