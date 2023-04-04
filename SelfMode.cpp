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
#include <map>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#include <conio.h>
#include <shellapi.h>
#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"SelfMode.h"
#include"ini.h"
//25565
#define _isInsNULL_(str,post) ((str.size() == (post+1))?1:0)
#define _isSEVEREX_(code) ((code) == (SEVER_EXISTS) ? Send_StringTEXT_Message(_SEVEREXMESG_) : 0)
#define _isSEVERSTART_(code) ((code) == (SEVER_RESTART_FAIL) ? Send_StringTEXT_Message(_TUNNElFAILMSG_) : 0)




std::map<std::string, Self_mode>Self_mode_set{
	{"reb", BOT_SELF_RESTART},
	{"res", BOT_SEVER_RESTART},
	{"rt", BOT_TUNNEL_RESTART},
	{"kill" ,BOT_KILL}
};


std::string Format_Instructions_self(std::string Raw)
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


Sf_Status_code temp_restart()
{
	Send_StringTEXT_Message("Bot-restart successful");
	exit(0);
}

DWORD Sever_run_check(std::wstring name)
{
	DWORD pid;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (!std::wstring(entry.szExeFile).compare( name))//"bot sever.exe"
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				pid = GetProcessId(hProcess);
				CloseHandle(hProcess);
				//std::cout << 111111 << std::endl;
				return pid;
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}


Sf_Status_code sever_restart()
{
	HINSTANCE re_stat;
	Sf_Status_code ReExC;
	if (Sever_run_check(L"bot sever.exe") != 0)
	{
		ReExC = SEVER_EXISTS;
		return ReExC;
	}
	re_stat = ShellExecuteW(NULL, L"open", L"D:\\pojt\\bot sever\\x64\\Debug\\bot sever.exe", NULL, NULL, SW_SHOW);
	re_stat < HINSTANCE(32) ? ReExC = SEVER_RESTART_FAIL : ReExC = SEVER_RESTART_SUCCESS;
	if (ReExC == SEVER_RESTART_SUCCESS)
		Send_StringTEXT_Message("sever restart successful");
	return ReExC;
}

Sf_Status_code tunnel_restart()
{
	HINSTANCE re_stat;
	Sf_Status_code ReExC;
	if (Sever_run_check(L"cpolar.exe") != 0)
	{
		ReExC = TUNNEL_EXISTS;
		return ReExC;
	}
	re_stat = 
		ShellExecuteW(NULL, L"open", L"D:\\cploar\\cpolar.exe", L"cpolar tcp -remote-addr=1.tcp.cpolar.cn:21476  192.168.1.9:28624  ",
		 L"D:\\cploar", SW_SHOW);
	re_stat < HINSTANCE(32) ? ReExC = TUNNEL_RESTART_FAIL : ReExC = TUNNEL_RESTART_SUCCESS;
	if (ReExC == TUNNEL_RESTART_SUCCESS)
		Send_StringTEXT_Message("tunnel restart successful");
	return ReExC;
}


Sf_Status_code Kill()
{
	if (system("TASKKILL /F /IM Start-QQBot.exe") != -1)
	{
		Send_StringTEXT_Message("BOT-offline");
		exit(0);
	}
	else
		Send_StringTEXT_Message("Kill not done");

	
	return Self_KILL;
}


Self_mode Find_Self_Map_Executmode(std::string Head, std::string Instructions, std::string QQnumber)
{
	Self_mode mode;
	std::map<std::string, Self_mode>::iterator it;
	(Head.size() == 0) ? it = Self_mode_set.find(Instructions) : it = Self_mode_set.find(Head);
	it == Self_mode_set.end() ? mode = take_place : mode = it->second;
	return mode;
}

Sf_Status_code Self_excut(Self_mode mode, std::string Instructions, std::string QQnumber)
{
	Sf_Status_code stat_code;
	switch (mode)
	{
		
		case BOT_SELF_RESTART:
			stat_code = temp_restart();
			break;
		case BOT_SEVER_RESTART:
			stat_code = sever_restart();
			break;
		case BOT_TUNNEL_RESTART:
			stat_code = tunnel_restart();
			break;
		case BOT_KILL:
			stat_code = Kill();
			break;
		default:
			Send_StringTEXT_Message("no function");
			break;
	}
	return stat_code;
}

void wrong_check(Self_mode_Status_code code)
{
	if (code == Self_EXECUT_SEUCCESS) return;
	_isSEVEREX_(code);
	_isSEVERSTART_(code);
	return;
}

Self_mode_Status_code Self_Mode_main(std::string Instructions, std::string QQnumber)
{
	if (_isInsNULL_(Instructions, Instructions.find(".")))
	{
		Send_StringTEXT_Message("Instructions Cant be NULL");
		return SELF_INS_NULL;
	}
	std::string self_message = Format_Instructions_self(Instructions);
	Self_mode Execut = Find_Self_Map_Executmode(self_message, Instructions, QQnumber);
	Sf_Status_code back_code = Self_excut(Execut, Instructions, QQnumber);
	wrong_check(back_code);
	return back_code;
}