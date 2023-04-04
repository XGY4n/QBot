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
#include <Iphlpapi.h>

#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"ini.h"
#include"McServer.h"
#include"ServerStart.h"
#include"TunnleRestart.h"
#include"SelfMode.h"

#pragma comment(lib,"Iphlpapi.lib")  
#pragma comment(lib, "ws2_32.lib")  
//25565
#define _isMCInsNULL_(str,post) ((str.size() == (post+1))?1:0)
#define _isMCSEVEREX_(code) ((code) == (Mc_SEVER_EXISTS) ? Send_StringTEXT_Message(_SEVEREXMESG_) : 0)
#define _isMCSEVERSTART_(code) ((code) == (Mc_SEVER_RESTART_FAIL) ? Send_StringTEXT_Message(_TUNNElFAILMSG_) : 0)




std::map<std::string, Mc_mode>Mc_mode_set{
	{"start", MC_SERVER_START},
	{"rt", MC_TUNNEL_RESTART},
	{"help", MC_SERVER_HELP},
	{"kill",MC_SERVER_KILL},
	//{"kill" ,BOT_KILL}
};






std::string Format_Instructions_Mc(std::string Raw)
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
	{
		if (Raw[j] == 32)
			break;
			message = message + Raw[j];
	}

	return message;
}


Mc_Status_code temp_restart()
{
	Send_StringTEXT_Message("Bot-restart successful");
	exit(0);
}

DWORD Mc_Sever_run_check(std::wstring name)
{
	DWORD pid;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (!std::wstring(entry.szExeFile).compare(name))//"bot sever.exe"
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				pid = GetProcessId(hProcess);
				CloseHandle(hProcess);
				return pid;
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}

//D:\pojt\QQbot\Mc
Mc_Status_code sever_restart()
{
	HINSTANCE re_stat;
	Mc_Status_code ReExC;
	if (Mc_Sever_run_check(L"bot sever.exe") != 0)
	{
		ReExC = MC_SEVER_EXISTS;
		return ReExC;
	}
	re_stat = ShellExecuteW(NULL, L"open", L".\\bot sever\\x64\\Debug\\bot sever.exe", NULL, NULL, SW_SHOW);
	re_stat < HINSTANCE(32) ? ReExC = MC_SEVER_RESTART_FAIL : ReExC = MC_SEVER_RESTART_SUCCESS;
	if (ReExC == MC_SEVER_RESTART_SUCCESS)
		Send_StringTEXT_Message("sever restart successful");
	return ReExC;
}

Mc_Status_code tunnel_restart()
{
	HINSTANCE re_stat;
	Mc_Status_code ReExC;
	if (Mc_Sever_run_check(L"cpolar.exe") != 0)
	{
		ReExC = MC_TUNNEL_EXISTS;
		return ReExC;
	}
	re_stat =
		ShellExecuteW(NULL, L"open", L"D:\\cploar\\cpolar.exe", L"cpolar tcp -remote-addr=1.tcp.cpolar.cn:21476  192.168.1.6:25565",
			L"D:\\cploar", SW_SHOW);
	re_stat < HINSTANCE(32) ? ReExC = MC_TUNNEL_RESTART_FAIL : ReExC = MC_TUNNEL_RESTART_SUCCESS;
	if (ReExC == MC_TUNNEL_RESTART_SUCCESS)
		Send_StringTEXT_Message("tunnel restart successful");
	return ReExC;
}


Mc_Status_code Server_Kill()
{
	if (system("TASKKILL /F /IM javaw.exe") != -1)
	{
		Send_StringTEXT_Message("Server shut done");
		exit(0);
	}
	else
		Send_StringTEXT_Message("Kill not done");


	return MC_KILL;
}


Mc_mode Find_Mc_Map_Executmode(std::string Head, std::string Instructions, std::string QQnumber)
{
	Mc_mode mode;
	std::map<std::string, Mc_mode>::iterator it;
	(Head.size() == 0) ? it = Mc_mode_set.find(Instructions) : it = Mc_mode_set.find(Head);
	it == Mc_mode_set.end() ? mode = MC_take_place : mode = it->second;
	return mode;
}

Mc_Status_code Mc_excut(Mc_mode mode, std::string Instructions, std::string QQnumber)
{
	Mc_Status_code stat_code;
	switch (mode)
	{
	case MC_SERVER_START:
		stat_code = Mc_Server_Start(Instructions);
		break;
	case MC_TUNNEL_RESTART:
		Tunnel_restart(Instructions);
		break;
	case MC_SERVER_HELP:
		Send_StringTEXT_Message("#mc.[ex][mc ver][tunnel plan = 'A' | 'B'' ? ...]");
		break;
	case MC_SERVER_KILL:
		if (Sever_run_check(L"javaw.exe") == 0 && Sever_run_check(L"java.exe") == 0 && Sever_run_check(L"cpolar.exe") == 0)
			Send_StringTEXT_Message("mc server or tunnel not exists");
		else
		{
			system("taskkill /f /IM javaw.exe");
			system("taskkill /f /IM java.exe");
			system("taskkill /f /IM cpolar.exe");
			Send_StringTEXT_Message("mc server and tunnel all kill");
		}
		
		break;
	default:
		Send_StringTEXT_Message("some function");
		break;
	}
	//Send_StringTEXT_Message("n function");
	return stat_code;
}

void wrong_check(Mc_Status_code code)
{
	if (code == MC_EXECUT_SEUCCESS) return;
	//_isSEVEREX_(code);
	//_isSEVERSTART_(code);
	return;
}

Mc_Status_code Mc_Mode_main(std::string Instructions, std::string QQnumber)
{
	if (_isMCInsNULL_(Instructions, Instructions.find(".")))
	{
		Send_StringTEXT_Message("Instructions Cant be NULL");
		return MC_INS_NULL;
	}
	std::string self_message = Format_Instructions_Mc(Instructions);
	Mc_mode Execut = Find_Mc_Map_Executmode(self_message, Instructions, QQnumber);
	Mc_Status_code back_code = Mc_excut(Execut, Instructions, QQnumber);
	wrong_check(back_code);
	return back_code;
}