#pragma once
#using "./c#qqmessage/uaiQmsgc.dll"
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
#include<stdio.h>
#include <msclr\marshal_cppstd.h>

void check_push(std::string name, std::string QQnumber, std::string message, std::string time);

void push_to_QInstructions(std::string Instructions);

std::string pop_QInstructionsMessage();