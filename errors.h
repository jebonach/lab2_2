#pragma once
#include <vector>
#include <string>
#include "NewExceptions.h"

struct ErrorInfo {
    int code;
    std::string message;
};

extern std::vector<ErrorInfo> g_ErrorTable; 

void handleException(const MyException &ex);
