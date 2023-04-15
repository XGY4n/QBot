#include<iostream>
#include<string>
#include <windows.h>
#include"ChineseString.h"
#define _ININAME_ "./ini/GroupName.ini"
#define _ADIMINI_ "./ini/ADIMLIST.ini"
#define _MCVERPATH_ "./ini/McVer.ini"
#define _MCTUNNEL_ "./ini/McTunnelPlan.ini"
#define _GTPSETTING_ "./ini/GPTsetting.ini"
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")
	
std::wstring string2wstring2(const std::string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	std::wstring result = pwchar;
	return result;
}

std::string InI_Group_Name()
{
	LPCTSTR lpFileName = TEXT("./ini/GroupName.ini");
	WCHAR content[100];
	//std::cout << content << std::endl;
	DWORD status = ::GetPrivateProfileString(TEXT("Group1"), TEXT("name"), TEXT(""), content, 100, lpFileName);
	std::string g_name = UTF82Char(wideCharToMultiByte(content));
	//std::wcout << content << std::endl;
	return g_name;
}

bool adim_check(std::string QQnumber)
{
	LPCTSTR lpFileName = TEXT(_ADIMINI_);
	WCHAR content[100];
	UINT List_number = ::GetPrivateProfileInt(TEXT("Administrator"), TEXT("number"),  0, lpFileName);
	//std::cout << List_number << std::endl;
	for (int i = 0; i < List_number; i++)
	{
		WCHAR content[100];
		std::wstring selection = L"Administrator-"+std::to_wstring(i);
		DWORD status = ::GetPrivateProfileString(LPCTSTR(selection.c_str()), TEXT("QQNumber"), TEXT(""), content, 100, lpFileName);

		if (!QQnumber.compare(UTF82Char(wideCharToMultiByte(content))))
			return true;
	}
	return false;
}



std::string McVer_Check(std::string McVer)
{
	std::string ServerPath ;
	LPCTSTR lpFileName = TEXT(_MCVERPATH_);
	WCHAR content[100];
	UINT List_number = ::GetPrivateProfileInt(TEXT("ServerList"), TEXT("Number"), 0, lpFileName);
	std::cout<<"aaaa:" << List_number << std::endl;
	for (int i = 0; i < List_number; i++)
	{
		WCHAR content[100];
		std::wstring selection = string2wstring(McVer);//L"Administrator-" + std::to_wstring(i);
		DWORD status = ::GetPrivateProfileString(LPCTSTR(selection.c_str()), TEXT("ServerPath"), TEXT(""), content, 100, lpFileName);
		ServerPath = UTF82Char(wideCharToMultiByte(content));
		if (status != 0)
			return ServerPath;
	}
	return ServerPath;
}

//cpolar tcp -remote-addr=1.tcp.cpolar.cn:21476

std::string Mc_TunnelPlan_Check(std::string McTunnelPlan)
{
	std::string ServerPath;
	LPCTSTR lpFileName = TEXT(_MCTUNNEL_);
	WCHAR content[100];
	UINT List_number = ::GetPrivateProfileInt(TEXT("TunnelList"), TEXT("Number"), 0, lpFileName);
	//std::cout<<"aaaa:" << List_number << std::endl;
	for (int i = 0; i < List_number; i++)
	{
		WCHAR content[100];
		std::wstring selection = string2wstring(McTunnelPlan);//L"Administrator-" + std::to_wstring(i);
		DWORD status = ::GetPrivateProfileString(LPCTSTR(selection.c_str()), TEXT("Tunnel"), TEXT(""), content, 100, lpFileName);
		ServerPath = UTF82Char(wideCharToMultiByte(content));
		if (status != 0)
			return ServerPath;
	}
	return ServerPath;
}

