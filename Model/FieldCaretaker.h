//
// Created by yudjin on 12/15/20.
//

#ifndef OOP_FIELDCARETAKER_H
#define OOP_FIELDCARETAKER_H

#include "Field.h"


class FieldCaretaker {
private:
    std::vector<Field::Snapshot *> snapshots_;

    Field *field;

public:
    FieldCaretaker(Field *field) : field(field){};

    void initFromFile();
    void saveToFile();
    void backUp();
    void undo();
    void history();
};


#endif //OOP_FIELDCARETAKER_H
