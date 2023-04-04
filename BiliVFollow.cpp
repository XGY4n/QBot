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
#include <shlobj.h>
#include <io.h>
#include <Python.h>
#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"Python_main.h"

#define _isNUMBER_(num) (num < 48 || num > 57)?1:0


void send_vtbTXT(std::string Biliuid)
{
    std::string coPath = "./vtb";
    coPath = coPath + Biliuid + ".jpg";
    int temp = check_file(coPath);
    if (temp == -1)
    {
        Send_StringTEXT_Message(Send_Error_Message());
        return;
    }
    char path[166];
    strcpy(path, coPath.c_str());
    LOG_writer(Now_time() + path);
    HWND WIN = FindWindow(_T("TXGuiFoundation"), _T("不常用群聊"));
    Send_StringTEXT_Message("Please check this file!");
    Send_File(coPath);
}


void make_TXT(std::string Biliuid)
{
    std::string ExPath = "./python/followings.py ";
    ExPath = ExPath + Biliuid;
    LOG_writer(Now_time() + ExPath);
    system(ExPath.c_str());//to python
    Sleep(1000);
    send_vtbTXT(Biliuid);
}



void check_Bilvtb(std::string Instructions)
{
    Send_StringTEXT_Message(Send_Wait_Message());
    std::cout<< Now_time() << "BilCheck : " << Instructions << std::endl;
    int start = Instructions.find(".");
    std::string Biliuid;
    if (start + 1 == Instructions.size())
        Send_StringTEXT_Message(Send_WrongInput_Message());
    for (int i = start + 1; i < Instructions.size(); i++)
    {
        if (Instructions[i] >= 48 && Instructions[i] <= 57)
            Biliuid = Biliuid + Instructions[i];      
        else
        {
            Send_StringTEXT_Message(Send_WrongInput_Message());
            return;
        }
    }
    make_TXT(Biliuid);
}




PY_Status_code Python_follow_main(std::string uid)
{
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    const char* ans;
    std::string Path;
    wchar_t* res2;
    for (int i = 0; i < uid.size(); i++)
        if (_isNUMBER_(uid[i]))
            return BILI_INS_WRONG;
    Send_StringTEXT_Message(Send_Wait_Message());
    LOG_writer(Now_time() + "Take uid: " + uid);
    res2 = multi_Byte_To_Wide_Char(uid);
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python')");
    pModule = PyImport_ImportModule("vtb");
    pFunc = PyObject_GetAttrString(pModule, "vtb_main");
    pArg = Py_BuildValue("(u)", res2);
    out = PyObject_CallObject(pFunc, pArg);
    PyArg_Parse(out, "s", &ans);
    Path = Path + ans;
    std::cout << Path << std::endl;
    if (check_file(ans) == -1)
        return FILE_NOT_FIND;
    Send_File(Path);
    return EXECUT_SEUCCESS;
}