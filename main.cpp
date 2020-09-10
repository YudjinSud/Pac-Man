#include <iostream>

#include "Field.h"

int main() {

    Field *f = Field::GetInstance(0, 4);

    SimpleIterator *it  =  f->createIterator();
    for(it -> first(); !it->isDone(); it->next()) {
        std::cout << it->currentItem().type;
    }

    return 0;
}
