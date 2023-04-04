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
#include <shlobj.h>
#include <io.h>
#include <Python.h>
#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"163music.h"
#include"Python_main.h"
#include"BiliVFollow.h"

class CPythonCall 
{
	public: 
		CPythonCall(enum Python_mode mode, std::string Instructions);
		~CPythonCall();

};

