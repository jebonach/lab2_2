#include "errors.h"
#include <iostream>

void handleException(const MyException &ex) {
    switch (ex.getType()) {

    case ErrorType::OutOfRange:
        switch (ex.getCode()) {
        case 0:
            std::cout << "[OutOfRange code=0] index < 0" << std::endl;
            break;
        case 1:
            std::cout << "[OutOfRange code=1] index >= size" << std::endl;
            break;
        case 2:
            std::cout << "[OutOfRange code=2] start > end" << std::endl;
            break;
        case 3:
            std::cout << "[OutOfRange code=3] empty" << std::endl;
            break;
        default:
            std::cout << "[OutOfRange code=?]" << std::endl;
            break;
        }
        break;

    case ErrorType::InvalidArg:
        switch (ex.getCode()) {
        case 0:
            std::cout << "[InvalidArg code=0] menu input not an integer?" << std::endl;
            break;
        case 1:
            std::cout << "[InvalidArg code=1] array input was not integer?" << std::endl;
            break;
        default:
            std::cout << "[InvalidArg code=?]" << std::endl;
            break;
        }
        break;

    case ErrorType::NegativeSize:
        switch (ex.getCode()) {
        case 0:
            std::cout << "[NegativeSize code=0] DynamicArray got negative size" << std::endl;
            break;
        default:
            std::cout << "[NegativeSize code=?]" << std::endl;
            break;
        }
        break;

    default: // Unknown
        std::cout << "[Unknown type], code=" << (int)ex.getCode() << std::endl;
        break;
    }

    // Можно при желании вывести ex.what():
    // std::cout << "  (" << ex.what() << ")" << std::endl;
}
