#pragma once
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
#include <regex>
#include <msclr\marshal_cppstd.h>

#define _FILERROR_ "文件抓取有误或者程序出现了错误,请@xgt或者重试/快哭了"
#define _WEBERROR_ "资源不存在"
#define _WAITMESSAGE_ "别急~/亲亲"
#define _INSWRONG_ "执行失败!指令头正确但指令值不符合规则,输入#号 + help查看帮助你这低能/流汗"
#define _NOFUNCTION_ " /NO NO such function"
#define _HELPIMG_ "D:\\pojt\\QQbot\\picture\\main_help.png"
#define _SPEAK_ "hi I am a QQbot made by xgt he is my father/tp"
#define _SEVEREXMESG_ "sever is already running"
#define _TUNNElFAILMSG_ "sever is already running"
#define _NOTADIM_ "呵呵，群友你又装管理员骗我了吧，下一轮询我将把群里面给轰爆，他妈的一下子轰爆，相信这会给我很大的快感"

std::string Send_Help_Message();

std::string Send_Error_Message();

//std::string Send_Error_Message();

std::string Send_Wait_Message();

std::string Send_WrongInput_Message();

std::string NO_Function();