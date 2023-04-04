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

extern HWND MainGroupp;


int check_file(std::string path);

void Send_StringTEXT_Message(std::string StringTEXT, std::string UserName);
void Send_File(std::string Path, std::string UserName);


void Send_StringTEXT_Message(std::string StringTEXT);
void Send_File(std::string Path);

void Post_StringTEXT_Message(std::string StringTEXT);
void Send_wStringTEXT_Message(wchar_t* StringTEXT);



