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


#define _isInsNULL_(str,post) ((str.size() == (post+1))?1:0)
#define _isFILEEXIST_(code) ((code) == (FILE_NOT_FIND) ? Send_StringTEXT_Message(_FILERROR_) : 0)
#define _isWEBFIND_(code) ((code) == (WEB_NOT_FIND) ? Send_StringTEXT_Message(_WEBERROR_) : 0)
#define _isBILIWRONG_(code) ((code) == (BILI_INS_WRONG) ? Send_StringTEXT_Message(_INSWRONG_) : 0)


std::string Format_Instructions(std::string Raw)
{
	std::string message;
	int start = 0;
	int end = Raw.size();
	for (int i = 0; i < Raw.size(); i++)
	{
		if (Raw[i] == 46)
		{
			start = i;
			break;
		}
	}
	for (int j = start + 1; j < Raw.size(); j++)
		message = message + Raw[j];
	return message;
}


void wrong_check(PY_Status_code code)
{
	if (code == EXECUT_SEUCCESS) return;
	_isFILEEXIST_(code);
	_isWEBFIND_(code);
	_isBILIWRONG_(code);
	return;
}


PY_Status_code Python_main(enum Python_mode mode, std::string Instructions)//type mode
{
	Py_Initialize();
	if (_isInsNULL_(Instructions, Instructions.find(".")))
	{
		Send_StringTEXT_Message("Instructions Cant be NULL");
		return INS_NULL;
	}
	std::string PY_message = Format_Instructions(Instructions);
	PY_Status_code code;
	switch (mode)
	{
		case PYTHON_MODE_163MUSIC:
				code = Python_music_main(PY_message);
			break;
		case PYTHON_MODE_VTB:
				code = Python_follow_main(PY_message);
			break;
		case PYTHON_MODE_BT:
				code = Python_bt_main(PY_message);
			break;
		case PYTHON_MODE_COM:
				code = Python_com_main(PY_message);
			break;
		case PYTHON_MODE_MOVIE:
				code = Python_movie_main(PY_message);
			break;
		case PYTHON_MODE_CHATGTP :
			//code = Python_chatgpt_main();
			break;
		default:
			break;
	}
	wrong_check(code);
	Py_Finalize();
	return PYTHON_END;
}