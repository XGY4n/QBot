#pragma once
#include <iostream>
#include <string>
#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <comutil.h>  
#include <unknwn.h>
#include <queue>
#include <thread>
#include <stdio.h>
#include <map>
#include <msclr\marshal_cppstd.h>
#include"QueueDef.h"
#include "ChatGPT.h"

#define IS_DIGIT_STR(str) \
    ([](const string& s) -> bool { \
        for (char c : s) { \
            if (!isdigit(c)) return false; \
        } \
        return true; \
    })(str)


extern std::map<std::string, int>Instructions_set;

int Instructions_main(std::string Instructions, std::string Name, std::string QQnumber);


