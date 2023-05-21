#pragma once
#include <iostream>
#include<string>
#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <comutil.h>  
#include<unknwn.h>
#include <queue>
#include <thread>
#include <msclr\marshal_cppstd.h>
//#using "./c#qqmessage/UIAgetinformation.dll"
using namespace System;
void MarshalString(String^ s, std::string& os);
void MarshalString(String^ s, std::wstring& os);