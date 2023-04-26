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
#include"CInI.h"

#define _ISNOTFOUND_(str) (str.size() == 0) ? 1 : 0
#define P_MuicePath "E:/Qbot/resource/music/"

std::string MusicPath = "E:/Qbot/resource/music/";

std::string musicID_standardization(std::string musicID)//make name lawful  \\resource
{
    //std::cout << musicID << std::endl;
    for (int i = 0; i < musicID.size(); i++)
    {
        if (musicID[i] == '&')
            musicID.replace(i, 1, "AND");
        else if (musicID[i] == ':')
            musicID.replace(i, 1, "-");
        else if (musicID[i] == '?')
            musicID.replace(i, 1, "-");
    }
    return musicID;
}


void send_mp3(std:: string musicID)
{
    std::unique_ptr<CInI> ini{ new CInI{"./ini/GroupName.ini"} };
    std::string MusicPath = ini->FindValueA<std::string>("music","Path"); //"E:\\Qbot\\resource\\music\\";
    MusicPath = MusicPath + musicID + ".mp3";
    //std::cout << MusicPath <<std::endl;
    LOG_writer(Now_time() + MusicPath);
    int temp = check_file(MusicPath);
    if (temp == -1)
    {
        Send_StringTEXT_Message(Send_Error_Message());
        return;
    } 
    Send_StringTEXT_Message("VIP support from 钟/亲亲~ Please check this .mp3!");
    Sleep(100);
    Send_File(MusicPath);
}



void make_music(std::string musicID)
{
    musicID = musicID_standardization(musicID);
    std::string ExPath = "./python/163.py";
    ExPath = ExPath + musicID;
    //std::cout << ExPath << std::endl;
    LOG_writer(Now_time() + ExPath);
    system(ExPath.c_str());
    Sleep(2500);
    send_mp3(musicID);
}



void check_music(std::string Instructions)
{
    Send_StringTEXT_Message(Send_Wait_Message());
    LOG_writer(Now_time() + "Take song: " + Instructions);
    //std::cout<<Now_time() << "Catch song:" << Instructions << std::endl;
    int start = Instructions.find(".");
    std::string musicID;
    if (start + 1 == Instructions.size())
        Send_StringTEXT_Message(Send_WrongInput_Message());
    for (int i = start + 1; i < Instructions.size(); i++)
        musicID = musicID + Instructions[i];
    make_music(musicID);
}



PY_Status_code Python_music_main(std::string musicID)
{
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    const char* ans;
    std::string Path;
    wchar_t* res2;
    musicID = musicID_standardization(musicID);
    Send_wStringTEXT_Message(_WAITMESSAGE_);
    LOG_writer(Now_time() + "Take song: " + musicID);
    res2 = multi_Byte_To_Wide_Char(musicID);
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python')");//D:\\pojt\\QQbot
    pModule = PyImport_ImportModule("163musicV1");
    pFunc = PyObject_GetAttrString(pModule, "music_main");
    pArg = Py_BuildValue("(u)", res2);
    out = PyObject_CallObject(pFunc, pArg);
    PyArg_Parse(out, "s", &ans);
    if (_ISNOTFOUND_(UTF82Char(ans)))
        return WEB_NOT_FIND;
    Path = std::string(P_MuicePath) + UTF82Char(ans);
    if (check_file(Path) == -1)
        return FILE_NOT_FIND;
    Send_wStringTEXT_Message(L"Uploading VIP support from 钟 😘");
    Send_File(Path);
    return EXECUT_SEUCCESS;
}




PY_Status_code Python_bt_main(std::string message)
{
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    const char* ans;
    std::string Path;
    wchar_t* res2;
    message = musicID_standardization(message);
    Send_wStringTEXT_Message(_WAITMESSAGE_);
    LOG_writer(Now_time() + "Take bt: " + message);
    res2 = multi_Byte_To_Wide_Char(message);
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('D:\\pojt\\QQbot\\python')");
    pModule = PyImport_ImportModule("takebt");
    pFunc = PyObject_GetAttrString(pModule, "bt_main");
    pArg = Py_BuildValue("(u)", res2);
    out = PyObject_CallObject(pFunc, pArg);
    PyArg_Parse(out, "s", &ans);
    if (_ISNOTFOUND_(UTF82Char(ans)))
        return WEB_NOT_FIND;
    Send_StringTEXT_Message(UTF82Char(ans));
    return EXECUT_SEUCCESS;
}



PY_Status_code Python_com_main(std::string message)
{
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    const char* ans;
    std::string Path;
    wchar_t* res2;
    message = musicID_standardization(message);
    Send_wStringTEXT_Message(_WAITMESSAGE_);
    LOG_writer(Now_time() + "Take bilicomments: " + message);
    res2 = multi_Byte_To_Wide_Char(message);
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('D:\\pojt\\QQbot\\python')");
    pModule = PyImport_ImportModule("bilisql");
    pFunc = PyObject_GetAttrString(pModule, "sql_main");
    pArg = Py_BuildValue("(u)", res2);
    out = PyObject_CallObject(pFunc, pArg);
    PyArg_Parse(out, "s", &ans);
    Send_StringTEXT_Message(UTF82Char(ans));
    return EXECUT_SEUCCESS;
}


PY_Status_code Python_movie_main(std::string message)
{
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    const char* ans;
    std::string Path;
    wchar_t* res2;
    message = musicID_standardization(message);
    Send_wStringTEXT_Message(_WAITMESSAGE_);
    LOG_writer(Now_time() + "Take bt: " + message);
    res2 = multi_Byte_To_Wide_Char(message);
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('D:\\pojt\\QQbot\\python')");
    pModule = PyImport_ImportModule("moive");
    pFunc = PyObject_GetAttrString(pModule, "moive_main");
    pArg = Py_BuildValue("(u)", res2);
    out = PyObject_CallObject(pFunc, pArg);
    PyArg_Parse(out, "s", &ans);
    if (_ISNOTFOUND_(UTF82Char(ans)))
        return WEB_NOT_FIND;
    Send_StringTEXT_Message(UTF82Char(ans));
    return EXECUT_SEUCCESS;
}