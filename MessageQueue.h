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
#include<stdio.h>
#include"QueueDef.h"
#include <msclr\marshal_cppstd.h>

int  Tpush_rawmessage_to_queue();//std::string RawMessage

void Tcheck_number_qmessage();

void Take_QInstructions();
