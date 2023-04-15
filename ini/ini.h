#pragma once
#include<iostream>
#include<string>
#include <windows.h>
#include"ChineseString.h"
#define _ININAME_ "./GroupName.ini"
#define _ADIMINI_ "./ini"
#define _MCVERPATH_ "./ini/McVer.ini"
#define _MCTUNNEL_ "./ini/McTunnelPlan.ini"
#define _GTPSETTING_ "./ini/GPTsetting.ini"
#define _GTPSETTINGW_ L"./ini/GPTsetting.ini"

extern std::string GroupName;
extern HWND MainGroup;
std::string InI_Group_Name();
bool adim_check(std::string QQnumber);
std::string McVer_Check(std::string McVer);
std::string Mc_TunnelPlan_Check(std::string McTunnelPlan);

