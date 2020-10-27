//
// Created by yudjin on 10/6/20.
//

#include <sstream>
#include "Item.h"

std::ostream &operator << (std::ostream &output, const Item& item) {
    output << item.print();
    return output;
}