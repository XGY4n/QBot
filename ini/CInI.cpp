#include "CInI.h"

CInI::CInI()
{

}

CInI::~CInI()
{

}
std::string CInI::WCHAR2String(WCHAR* front_trans)
{
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, front_trans, wcslen(front_trans), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];

    WideCharToMultiByte(CP_OEMCP, 0, front_trans, wcslen(front_trans), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    std::string ans;
    int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, pCStrKey, (int)strlen(pCStrKey), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    MultiByteToWideChar(CP_UTF8, NULL, pCStrKey, (int)strlen(pCStrKey), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    int len = WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), NULL, 0, NULL, NULL);
    char* c = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), c, len, NULL, NULL);
    c[len] = '\0';
    delete[] wszString;
    ans = c;
    return ans;
}


std::wstring CInI::string2wstring2(const std::string& s)
{
    _bstr_t t = s.c_str();
    wchar_t* pwchar = (wchar_t*)t;
    std::wstring result = pwchar;
    return result;
}