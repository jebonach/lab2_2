#pragma once
#include <exception>
#include <string>

enum class ErrorCode {
    OutOfRange,
    InvalidArg,
    NegativeSize,

    Unknown
};

class MyException : public std::exception {
private:
    ErrorCode code;
    std::string message;

public:
    MyException(ErrorCode c, const std::string &msg)
        : code(c), message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

    ErrorCode getCode() const noexcept {
        return code;
    }
};
