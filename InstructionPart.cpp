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
#include <Python.h>
#include <msclr\marshal_cppstd.h>
#include <memory>

#include"QueueDef.h"
#include"SendMessage.h"
#include"163music.h"
#include"BiliVFollow.h"
#include"ErrorHelpMessage.h"
#include"ChineseString.h"
#include"FakeAI.h"
#include"poker.h"
#include"Timelog.h"
#include"Dice.h"
#include"Python_main.h"
#include"mysql_main.h"
#include"SelfMode.h"
#include"ini.h"
#include"McServer.h"
#include"ChatGPT.h"
#include"Botlog.h"
//#include"CInI.h"
//#include"CInIReader.h"


#define _isHEADINS_(INS) ((INS.find(".") == INS.npos) ? true : false)
#define _PICTUREPATH_ "./resource/picture/a/"
#define _isHEADNULL_(INS_HEAD) 
#define _isADMIN_(ID) (!ID.compare("3121913693") ? true : false)
#define _isADMIN2_(ID)(!ID.compare("971206816") ? true : false)
#define _KILLSELF_ 	Send_StringTEXT_Message("Bot-Offline"),exit(0);


bool isPoker = false;
bool isDice = false;

//ChatGPT AI;// = std::unique_ptr<>;
std::unique_ptr<ChatGPT> AI{ new ChatGPT{} };

typedef enum  {
	Bot_Speak,
	Bot_Picture,
	Bot_Poker,
	Bot_Dice,
	Bot_help,
	Bot_OnceRand,
	Bot_Rand,
	Bot_Python_music,
	Bot_Python_vtb,
	Bot_chat,
	Bot_play_Poker,
	Bot_play_Dice,
	Bot_off,
	Bot_rand_once,
	Bot_Python_bt,
	Bot_sql_test,
	Bot_Python_com,
	Bot_Python_moive,
	Bot_Self_mode,
	Bot_MC_mode,
	Bot_ChatGTP,
	Bot_ChatGTP_refresh,
	Bot_rand,
	Bot_GetLog
}Bot_mode;


std::map<std::string, Bot_mode>Instructions_set{
	{"speak",Bot_Speak},
	{"图片",Bot_Picture},
	{"s.", Bot_Python_music},
	{"p.", Bot_Poker},
	{"dice", Bot_Dice},
	{"help", Bot_help},
	{"off", Bot_off},
	{"v.", Bot_Python_vtb},
	{"t.", Bot_Python_bt},
	{"sql.", Bot_sql_test},
	{"c.", Bot_Python_com},
	{"m.", Bot_Python_moive},
	{"bot.", Bot_Self_mode},
	{"mc." , Bot_MC_mode},
	{"ai.", Bot_ChatGTP},
	{"r.", Bot_rand},
	{"getlog", Bot_GetLog},
};


int check_Instructions(std::string Instructions, std::string Name, std::string QQnumber);


std::string Creat_Head(std::string Ins, std::string Name, std::string QQnumber)
{
	if (_isHEADINS_(Ins))
		return std::string();
	std::string Ins_Head;
	for (int H_post = 0; H_post < Ins.size(); H_post++)
	{
		if (Ins[H_post] == 46)
		{
			Ins_Head = Ins_Head + Ins[H_post];
			break;
		}
		Ins_Head = Ins_Head + Ins[H_post];
	}
	return Ins_Head;
}


Bot_mode Find_Map_Executmode(std::string Head, std::string Instructions, std::string Name, std::string QQnumber)
{
	Bot_mode mode = Bot_ChatGTP;
	std::map<std::string, Bot_mode>::iterator it;
	(Head.size() == 0) ? it = Instructions_set.find(Instructions) : it = Instructions_set.find(Head);
	it == Instructions_set.end() ? mode = Bot_chat : mode = it->second;
	return mode;
}


int Bot_Execut(Bot_mode mode, std::string Ins, std::string Name, std::string QQnumber)
{
	std::unique_ptr<Botlog> log{ new Botlog{} };
	std::unique_ptr<CInI> ini{ new CInI{"./ini/GroupName.ini"} };
	switch (mode)
	{
		case Bot_Picture:
			Send_File(_PICTUREPATH_ + Random_Number(58) + ".jpg");
			break;
		case Bot_Python_music:
			Python_main(PYTHON_MODE_163MUSIC, Ins);
			break;
		case Bot_Python_vtb:
			Python_main(PYTHON_MODE_VTB, Ins);
			break;
		case Bot_Python_bt:
			Python_main(PYTHON_MODE_BT, Ins);
			break;
		case Bot_Python_moive:
			Python_main(PYTHON_MODE_MOVIE, Ins);
			break;
		case Bot_Dice:
			isDice = Start_Dice_mode(Ins, Name);
			break;
		case Bot_play_Dice:
			Dice_main(Ins, Name);
			break;
		case Bot_help:
			Send_File(_HELPIMG_);
			break;
		case Bot_Speak:
			Send_StringTEXT_Message(_SPEAK_);
			break;
		case Bot_rand_once:
			Send_StringTEXT_Message(Make_Random(Ins));
			break;
		case Bot_Poker:
			isPoker = Start_Poker_mode(Ins, Name);
			break;
		case Bot_play_Poker:
			Poker_main(Ins, Name);
			break;
		case Bot_Python_com:
			Python_main(PYTHON_MODE_COM, Ins);
			break;
		case Bot_sql_test:
			if (_isADMIN_(QQnumber))
				mysql_main(Ins);
			else
				Send_StringTEXT_Message("呃呃你几把谁啊?");
			break;
			
		case Bot_off:
			if (_isADMIN_(QQnumber))
				_KILLSELF_
			else
				Send_StringTEXT_Message("呃呃你几把谁啊?");
			break;
		case Bot_Self_mode:
			if (adim_check(QQnumber))
				Self_Mode_main(Ins, QQnumber);
			else
				Send_StringTEXT_Message(_NOTADIM_);
			break;
		case Bot_MC_mode:
			if (adim_check(QQnumber))
				Mc_Mode_main(Ins, QQnumber);
			else
				Send_StringTEXT_Message(_NOTADIM_);
			break;
		case Bot_ChatGTP:
			if (adim_check(QQnumber))
				AI->ChatGPT_Ins_main(Ins);
			else
				Send_StringTEXT_Message(_NOTADIM_);
			break;
		case Bot_rand:
			Send_StringTEXT_Message(Make_Random(Ins));
			break;
		case Bot_GetLog:
			log->Temp_log(Ins);
			log->Record(Botlog::LEVEL_SUCCESS, Botlog::OWNER_SELF, ini->FindValueA<std::string>("TempPath", "Path"));
			Send_File(ini->FindValueA<std::string>("TempPath", "Path"));
			break;
		default:
			/*Send_StringTEXT_Message("ai");
			break;*/
			if (Ins.size() == 6&& IS_DIGIT_STR(Ins))
			{
				HWND seewo = FindWindow(_T("Chrome_WidgetWin_1"), _T("希沃品课"));
				SetForegroundWindow(seewo);
				Sleep(1000);
				//copy_text_to_clipboard(a);
				for (int j = 0; j < 2; j++)
				{
					for (int i = 0; i < 6; i++)
					{
						PostMessage(seewo, WM_KEYDOWN, Ins[i], 0);
						//PostMessage(hwnd, WM_KEYUP, a[i], 0);
						Sleep(100);// Release CTRL
					}
					Sleep(1000);
					PostMessage(seewo, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(541, 411));
					//发送WM_LBUTTONUP消息，表示鼠标左键松开
					PostMessage(seewo, WM_LBUTTONUP, 0, MAKELPARAM(541, 411));
				}

				Send_StringTEXT_Message("maby?");
				break;
			}
			if (AI->mode)
				AI->ChatGPT_NEWBING(Ins);
			else
				AI->ChatGPT_OPENAI(Ins);

			break;
			/*if (QQnumber.compare("1364303391") == 0 || QQnumber.compare("2995244756") == 0)
				Send_StringTEXT_Message(sql_rand_message(Random_Number(36)));
				//Send_StringTEXT_Message("你说得对但是能不能看完你兄弟演的四叠半神话大系 url: https://www.bilibili.com/bangumi/play/ep82447?spm_id_from=333.1007.top_right_bar_window_default_collection.content.click ");
			else
			{}*/
	}
	return 0;
}


bool Game_check(std::string Instructions, std::string Name, std::string QQnumber)
{
	if (isPoker)
	{
		Bot_Execut(Bot_play_Poker, Instructions, Name, QQnumber);
		return true;
	}
	else if (isDice)
	{
		Bot_Execut(Bot_play_Dice, Instructions, Name, QQnumber);
		return true;
	}
	else
		return false;
}


void normal_mode(std::string Instructions, std::string Name, std::string QQnumber)
{
	std::string Ins_Head = Creat_Head(Instructions, Name, QQnumber);
	Bot_mode Execut = Find_Map_Executmode(Ins_Head, Instructions, Name, QQnumber);
	Bot_Execut(Execut, Instructions, Name, QQnumber);/**/
	return ;
}


int Instructions_main(std::string Instructions, std::string Name, std::string QQnumber)
{
	//check_Instructions(Instructions, Name, QQnumber);
	srand((unsigned)time(NULL));
	if (Game_check(Instructions, Name, QQnumber))
		return 0;
	else
		normal_mode(Instructions, Name, QQnumber);
	//std::cout << Instructions << std::endl;
	return 0;/**/
}


int check_Instructions(std::string Instructions, std::string Name, std::string QQnumber)//now the Instructions is ready to executed 
{
	srand((unsigned)time(NULL));//global rand seed 
	if (isPoker)
	{
		Poker_main(Instructions, Name);
	}
	else if (isDice)
	{
		Dice_main(Instructions, Name);
	}
	else
	{
		if (!Instructions.compare("speak"))// say hello~
		{
			Send_StringTEXT_Message("hi I am a QQbot made by xgt he is my father/tp");
		}
		else if (!Instructions.find("v."))//bilivtb follow check
		{
			Python_main(PYTHON_MODE_VTB, Instructions);
		}
		else if (!Instructions.find("m."))//163 music 
		{
			check_music(Instructions);
		}
		else if (!Instructions.compare("help"))//help message
		{
			Send_StringTEXT_Message(Send_Help_Message());
		}
		else if (!Instructions.compare("r.") )//rand one number 1 ~ 25
		{
			Send_StringTEXT_Message(Random_Number(100));
		}
		else if (!Instructions.compare("图片"))//send rand picture 
		{
			Send_File(_PICTUREPATH_ + Random_Number(58) + ".jpg");
		}
		else if (!Instructions.find("p."))
		{
			isPoker = Start_Poker_mode(Instructions, Name);
		}
		else if (!Instructions.find("r"))//x time 1~n rand.
		{
			Send_StringTEXT_Message(Make_Random(Instructions));
		}
		else if (!Instructions.find("s."))
		{
			Python_main(PYTHON_MODE_163MUSIC, Instructions);
		}
		else if (!Instructions.compare("dice"))
		{
			isDice = Start_Dice_mode(Instructions, Name);
		}
		else if (!Instructions.compare("off"))
		{
			if (!QQnumber.compare("3121913693")){
				Send_StringTEXT_Message("Bot-Offline");
				exit(0);
			}
			else
				Send_StringTEXT_Message("呃呃你几把谁啊?");
		}
		else if (!Instructions.compare("test"))//†
		{
			Send_StringTEXT_Message("wait..");
			Py_Initialize();
			const char* a = Instructions.c_str();
			PyObject* pModule, * pFunc;
			PyObject* pArg = NULL;
			PyObject* out = NULL;
			wchar_t* res2 = multi_Byte_To_Wide_Char(Instructions);
			pModule = PyImport_ImportModule("xx"); 
			pFunc = PyObject_GetAttrString(pModule, "music_main");
			pArg = Py_BuildValue("(u)", res2) ;
			out = PyObject_CallObject(pFunc, pArg);
			const char* ans;// = PyBytes_AsString(out);
			PyArg_Parse(out, "s", &ans);		 
			Sleep(2000);
			Send_File("D:\\pojt\\QQbot\\music\\"+ UTF82Char(ans));
			Py_Finalize();
		}
		else
		{
			//Send_StringTEXT_Message(NO_Function());
			Bot turing;//ai class
			turing.talk(Instructions);//chat bot fakeAI
			return 0;
		}
	}
}