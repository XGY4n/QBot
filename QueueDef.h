#pragma once
#using "./c#qqmessage/uaiQmsgc.dll"
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
#include <msclr\marshal_cppstd.h>

using namespace uaiQmsgc;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
#pragma comment(lib, "comsuppw.lib")
/*typedef struct Poker
{
    std::string name;
    int score = 0;
    int chip = 0;
};
Poker poker[1145];*/
//extern std::queue<std::string> Qmessage;
//extern std::queue<std::string> QInstructionsMessage;
//deque
extern std::deque<std::string> Qmessage;
extern std::deque<std::string> QInstructionsMessage;