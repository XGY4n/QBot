#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <comutil.h>

#include"CInI.h"


#define _ININAME_ "./ini/GroupName.ini"
#define _ADIMINI_ "./ini/ADIMLIST.ini"
#define _MCVERPATH_ "./ini/McVer.ini"
#define _MCTUNNEL_ "./ini/McTunnelPlan.ini"
#define _GTPSETTING_ "./ini/GPTsetting.ini"

#pragma comment(lib, "comsuppw.lib")

class CInIReader : public CInI
{
	public:
		CInIReader();
		~CInIReader();
		std::string mc_ver(std::string Mcver);
	private:
		LPCTSTR lpFileName;
		WCHAR content[100];
		DWORD status ;


};

