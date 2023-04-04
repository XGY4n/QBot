#pragma once
#include <iostream>
#include<string>
#include <tchar.h>
class Chinese
{
public:
	Chinese();
	~Chinese();

	//char* to wchar_t*
	wchar_t* MBCSToUnicode(wchar_t* buff, const char* str);
	//wchar* to char*
	char* unicodeToMBCS(char* buff, const wchar_t* str);
	//string to wstring
	std::wstring strToWstr(std::string& input);
	std::string wstrToStr(std::wstring& wstr);

	char* wstrToChar(std::wstring& wstr);
	char* wstrToChar(const wchar_t* wstr);
};

std::string make_name(std::string RawMessage);

std::string make_number(std::string RawMessage);

std::string make_message(std::string RawMessage);

std::string make_time(std::string RawMessage);

std::string make_Instructions_message(std::string QueueTop);

std::string make_Instructions_name(std::string QueueTop);

std::string make_Instructions_QQnumber(std::string QueueTop);

std::string Chinese_SendMessage(std::string CNmessage);

int raw_check(std::string message);

std::string Random_Number(int range);

std::string Make_Random(std::string Instructions);

std::string GbkToUtf8(const char* src_str);

std::string UTF8ToGBK(const char* strUTF8);

wchar_t* multi_Byte_To_Wide_Char(std::string pKey);

std::string UTF82Char(const char* szU8);

char* wideCharToMultiByte(wchar_t* pWCStrKey);

std::wstring string2wstring(std::string str);
