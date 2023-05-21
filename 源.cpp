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
#include <deque>
#include"QueueDef.h"
#include"MessageQueue.h"
//#include"Timelog.h"
#include"SendMessage.h"
#include"ini.h"
#include"ChineseString.h"
#include"ChatGPT.h"
#include"Pyreflex.h"
//#include<Python.h>
#include"botinit.h"


using namespace uaiQmsgc;//c# UIA to take message from QQ
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

#pragma comment(lib, "comsuppw.lib")
#define _INIPATH_ "./ini"

std::string GroupName = InI_Group_Name();// InI_Group_Name();//"aa";
HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(GroupName));

std::unique_ptr<Pyreflex> _Py_Reflex{ new Pyreflex{} };

void wait_scan(std::string GroupName)
{
    //std::cout << GroupName << std::endl;
    while (1)
    {
        std::cout << GroupName << std::endl;
        HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(GroupName));//"多媒体部防疫爱好者的"
        HWND MSGC = FindWindow(_T("TXGuiFoundation"), _T("消息管理器"));
        if (MainGroup != 0&& MSGC!=0)
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

int py_test()
{
    std::unique_ptr<CInI> Py_ini{ new CInI{"./ini/Pyloadsetting.ini"} };
    //Py_ini->FindValueW<std::wstring>(L"PYTHONHOME", L"HOME");
    std::cout<< Py_ini->FindValueA<std::string>("PYTHONHOME", "HOME")<<std::endl;
    std::string py_hometemp = Py_ini->FindValueA<std::string>("PYTHONHOME", "HOME");
    std::string py_lib = Py_ini->FindValueA<std::string>("PYTHONLIB", "LIB");
    std::cout << py_lib<<std::endl;

    Py_SetPythonHome(multi_Byte_To_Wide_Char(py_hometemp));

    Py_Initialize();

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    if (!Py_IsInitialized())
    {
        PyErr_Print();
        return 0;
    }
    PyRun_SimpleString("print('PYTHON TEST PASS STAGE 1')\n");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python')");

    pModule = PyImport_ImportModule("pyloadtest");
    if (pModule==NULL)
    {
        PyErr_Print();
        return 0;
    }
    Py_Finalize();
    return 1;
}


int main()
{
    //py_test();
    //system("cls");
    Botinit();
    
    wait_scan(GroupName);

    _Py_Reflex->initializePython();

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