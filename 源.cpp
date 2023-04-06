#using "./c#qqmessage/UIAgetinformation.dll"
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
#include <deque>
#include"QueueDef.h"
#include"MessageQueue.h"
#include"Timelog.h"
#include"SendMessage.h"
#include"ini.h"
#include"ChineseString.h"
#include"ChatGPT.h"

using namespace UIATest;//c# UIA to take message from QQ
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

#pragma comment(lib, "comsuppw.lib")
#define _INIPATH_ "./ini"

std::string GroupName = InI_Group_Name();// InI_Group_Name();//"aa";
HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(GroupName));


void wait_scan(std::string GroupName)
{
    //std::cout << GroupName << std::endl;
    while (1)
    {
        std::cout << GroupName << std::endl;
        HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(GroupName));//"多媒体部防疫爱好者的"
        if (MainGroup != 0)
        {
            SetForegroundWindow(MainGroup);
            std::cout << "Bot Online" << std::endl;
            //Send_StringTEXT_Message("Bot online");
            return;
        }
        std::cout << "waiting" << std::endl;
        Sleep(1000);
        system("cls");
    }
}




int main()
{
    system("cls");
    wait_scan(GroupName);


    
    //std::cout
    //wait uia scan
    std::thread TakeRowQmessage(Tpush_rawmessage_to_queue);
    //this thread to push the message to first queue
    std::thread Takenumber(Tcheck_number_qmessage);
    //this thread to check the message to first queue
    std::thread TakeInstructions(Take_QInstructions);
    //this thread to push the first queue Instructions to sencond queue
    TakeRowQmessage.join();
    Takenumber.join();
    TakeInstructions.join();

    //Py_Finalize();
	return 0;
}