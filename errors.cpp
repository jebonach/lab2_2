// errors.cpp
#include "errors.h"
#include <iostream>
#include <stdexcept>

void handleException(const std::exception &e) {
    if (auto *oor = dynamic_cast<const std::out_of_range*>(&e)) {
        std::cerr << "[OutOfRange] " << oor->what() << std::endl;
    } else if (auto *inv = dynamic_cast<const std::invalid_argument*>(&e)) {
        std::cerr << "[InvalidArgument] " << inv->what() << std::endl;
    } else {
        std::cerr << "[Exception] " << e.what() << std::endl;
    }
}
