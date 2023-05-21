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
#include <deque>
#include <msclr\marshal_cppstd.h>
#include"QueueDef.h"
#include"ChatGPT.h"
using namespace uaiQmsgc;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
#pragma comment(lib, "comsuppw.lib")

std::deque<std::string> Qmessage;
std::deque<std::string> QInstructionsMessage;
/*
* this .h file to defind two deque
* Qmessage is the queue to push the string bring # it define to message call bot
* QInstructionsMessage is the queue to push the final message whitch will be Execut
*/