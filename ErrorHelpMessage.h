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

#define _FILERROR_ "�ļ�ץȡ������߳�������˴���,��@xgt��������/�����"
#define _WEBERROR_ "��Դ������"
#define _WAITMESSAGE_ "��~/����"
#define _INSWRONG_ "ִ��ʧ��!ָ��ͷ��ȷ��ָ��ֵ�����Ϲ���,����#�� + help�鿴�����������/����"
#define _NOFUNCTION_ " /NO NO such function"
#define _HELPIMG_ "D:\\pojt\\QQbot\\picture\\main_help.png"
#define _SPEAK_ "hi I am a QQbot made by xgt he is my father/tp"
#define _SEVEREXMESG_ "sever is already running"
#define _TUNNElFAILMSG_ "sever is already running"
#define _NOTADIM_ "�Ǻǣ�Ⱥ������װ����Աƭ���˰ɣ���һ��ѯ�ҽ���Ⱥ������䱬�������һ���Ӻ䱬�����������Һܴ�Ŀ��"

std::string Send_Help_Message();

std::string Send_Error_Message();

//std::string Send_Error_Message();

std::string Send_Wait_Message();

std::string Send_WrongInput_Message();

std::string NO_Function();