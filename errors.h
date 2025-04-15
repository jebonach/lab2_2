#pragma once
#include <vector>
#include <string>
#include "how_to_train_your_exception.h"

struct ErrorInfo {
    int code;
    std::string message;
};

extern std::vector<ErrorInfo> g_ErrorTable; 

void handleException(const MyException &ex);
