#include<iostream>
#include<string>
#include <windows.h>
#include"ChineseString.h"
#include <comutil.h>

#define _ININAME_ "./ini/GroupName.ini"
#define _ADIMINI_ "./ini/ADIMLIST.ini"
#define _MCVERPATH_ "./ini/McVer.ini"
#define _MCTUNNEL_ "./ini/McTunnelPlan.ini"
#define _GTPSETTING_ "./ini/GPTsetting.ini"

#pragma comment(lib, "comsuppw.lib")
class CInI
{
	public:
		CInI();
		~CInI();

		/*virtual std::string _strreport();
		virtual bool _boolreport() = 0;*/
		std::string WCHAR2String(WCHAR* front_trans);
		std::wstring string2wstring2(const std::string& s);
		virtual std::string mc_ver(std::string Mcver) {
			return "null";
		}
	private:
		//std::wstring string2wstring2(const std::string& s);
		//std::string WCHAR2String(WCHAR* front_trans);
};


