#include "CInIReader.h"
//#include "CInI.h"


CInIReader::CInIReader()
{

}

CInIReader::~CInIReader()
{

}


std::string CInIReader::mc_ver(std::string Mcver)
{
	std::string ServerPath = "not find";
	this->lpFileName = TEXT(_MCVERPATH_);
	//this->content[100];
	UINT List_number = ::GetPrivateProfileInt(TEXT("ServerList"), TEXT("Number"), 0, lpFileName);
	//std::cout<<"aaaa:" << List_number << std::endl;
	for (int i = 0; i < List_number; i++)
	{
		this->content[100];
		std::wstring selection = string2wstring(Mcver);//L"Administrator-" + std::to_wstring(i);
		this->status = ::GetPrivateProfileString(LPCTSTR(selection.c_str()), TEXT("ServerPath"), TEXT(""), content, 100, lpFileName);
		ServerPath = WCHAR2String(content);
		if (status != 0)
			return ServerPath;
	}
	return ServerPath;
}