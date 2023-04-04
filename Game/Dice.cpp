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
#include <shlobj.h>
#include <io.h>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>
#include <mysql.h>
#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"Dice.h"


DicePlayer Player[3];
std::deque<DicePlayer>PlayerQueue;
static bool isFull = false;
static int First = 0;
static int Second = 1;
static int demark = 1;
static int Number;
static int tempPoint = 0;
static std::string startr;
std::vector<std::string>PlayerList;
std::vector<int>DicePoint;
//std::vector<int>chooseDice;


bool Start_Dice_mode(std::string Instructions, std::string Name)
{
	Send_StringTEXT_Message("Dice mode");
	Send_StringTEXT_Message(Name + " wait player 1/2");
	Player[0].name = Name;
	PlayerList.push_back(Name);
	Player[0].isStartPerson = true;
	Player[0].point = 0;
	PlayerQueue.push_back(Player[0]);
	return true;
}



void Dice_end()
{
	Send_StringTEXT_Message("Dice game end");
	memset(&Player, 0x00, sizeof(Player));
	PlayerQueue.~deque<DicePlayer>();
	isFull = false;
	isDice = false;
	tempPoint = 0;
	Number=0;
}


void start_game(std::string Instructions, std::string Name)
{
	std::string playDiceMessage;

	Player[demark].name = Name;
	PlayerList.push_back(Name);
	Player[demark].isStartPerson = true;
	Player[demark].point = 0;
	for (int i = 0; i < 6; i++)
	{
		int rander = 1 + rand() % 6;
		DicePoint.push_back(rander);
		playDiceMessage = playDiceMessage + "Dice" + std::to_string(i+1) + "=" + std::to_string(rander) + " ";
	}
	Send_StringTEXT_Message(Name + " join success");
	Send_StringTEXT_Message("game start player " + Player[demark].name + " this round dice");
	//Player[1].DicePoint.clear();
	Send_StringTEXT_Message(playDiceMessage);
	PlayerQueue.push_back(Player[demark]);
	Send_StringTEXT_Message(Player[demark].name + " round");
}



void new_round(std::string Instructions, std::string Name)
{
		
		demark == 1 ? demark = 0 : demark = 1;
		bool isdead = false;
		tempPoint = 0;
		Send_StringTEXT_Message(Player[demark].name + " round");
		std::string playDiceMessage;
		for (int i = 0; i < 6; i++)
		{
			int rander = 1 + rand() % 6;
			DicePoint.push_back(rander);
			playDiceMessage = playDiceMessage + "Dice" + std::to_string(i+1) + "=" + std::to_string(rander)+" ";
			if (rander == 1 || rander == 5)
				isdead = true;
		}
		if (isdead)
		{
			Send_StringTEXT_Message(Player[demark].name + ";this round dice");
			//Player[1].DicePoint.clear();
			Send_StringTEXT_Message(playDiceMessage);
			PlayerQueue.push_back(Player[demark]);
			return ;
		}
		else
		{
			Send_StringTEXT_Message(playDiceMessage);
			Send_StringTEXT_Message("no useful dice your roundpoint reset and rounds pass!");
			Send_StringTEXT_Message(Name + " round end all point : " + std::to_string(Player[demark].point));
			DicePoint.clear();
			Number = 0;
			tempPoint = 0;
			new_round(Instructions, Name);
			return ;
		}

		
}


int same_round(std::string Instructions, std::string Name,int DiceNumber)
{
	bool isdead = false;
	Send_StringTEXT_Message(Player[demark].name + " round");
	std::string playDiceMessage;
	for (int i = 0; i < 6 - DiceNumber; i++)
	{
		int rander = 1 + rand() % 6;
		DicePoint.push_back(rander);
		playDiceMessage = playDiceMessage + "Dice" + std::to_string(i + 1) + "=" + std::to_string(rander) + " ";
		if (rander == 1 || rander == 5)
			isdead = true;
	}
	if (isdead)
	{
		Send_StringTEXT_Message(Player[demark].name + " this round dice");
		//Player[1].DicePoint.clear();
		Send_StringTEXT_Message(playDiceMessage);
		PlayerQueue.push_back(Player[demark]);
		return 0;
	}
	else
	{
		Send_StringTEXT_Message(Player[demark].name + " this round dice");
		Send_StringTEXT_Message(playDiceMessage);
		Send_StringTEXT_Message("no useful dice your roundpoint reset and rounds pass!");
		Send_StringTEXT_Message(Player[demark].name + " round end all point : " + std::to_string(Player[demark].point));
		DicePoint.clear();
		Number = 0;
		new_round(Instructions, Name);
		return 0;
	}
}


void count_point(std::vector<int>&chooseDice, int DiceNumber)
{
	//std::sort(chooseDice.begin(), chooseDice.end());
	int add[7] = { 0 };
	for (int i = 0; i < DiceNumber; i++)
	{
		//std::cout << chooseDice[i] << std::endl;
		add[chooseDice[i]]++;
	}
	int cout = 0;
	for (int i = 1; i < 7; i++)
	{
		if (add[i] != 0)
			cout++;
		else if (add[i] == 0 && (cout == 5 || cout == 6))
			add[i] = 0;
	}
	if (cout == 6)
	{
		tempPoint += 1500;
		return;
	}
	else if (cout == 5)
	{
		if (add[1] >= 1)
		{
			tempPoint += 500;
			for (int i = 1; i < 6; i++)
			{
				if(add[i]!=0)
				add[i]--;
			}
		}
		else if (add[2] >= 1)
		{
			tempPoint += 750;
			for (int i = 2; i < 7; i++)
			{
				if (add[i] > 0)
					add[i]--;
			}
		}
	}

	for (int i = 1; i < 7; i++)
	{
		//std::cout << add[i] << std::endl;
		if (add[i] != 0)
		{
			if (i == 1)
			{
				if (add[i] > 3)
					tempPoint += i * 100  * ((add[i] - 3) * 2);
				else if (add[i] == 3)
					tempPoint += i * 10 * 100;
				else
					tempPoint += add[i] * 100 ;
			}
			else if (i == 5)
			{
				if (add[i] > 3)
					tempPoint += i * 100  * ((add[i] - 3) * 2);
				else if (add[i] == 5)
					tempPoint += i * 10 * 100;
				else
					tempPoint += add[i] * 50;
			}
			else 
			{
				if (add[i] == 3)
				{
					tempPoint += i * 100;
				}	
				else if (add[i] > 3)
				{
					tempPoint += add[i] * 100 * ((add[i] - 3) * 2);
				}
				else
				{
					tempPoint = 0;
				}
			}
		}
	}
	if (tempPoint >= 2000)
	{
		Send_StringTEXT_Message("winner is " + Player[demark].name);
		chooseDice.clear();
		Dice_end();
	}
	else
	Send_StringTEXT_Message("your all point is " + std::to_string(Player[demark].point)+ "this round points is "
		+ std::to_string(tempPoint));
	chooseDice.clear();
}



int get_Pick_point(std::string Instructions)
{
	bool cankeep = false;
	std::vector<int>chooseDice;
	int PickNumber = Instructions.size() - 2;
	if (Instructions.size() <= 2)
	{
		Send_StringTEXT_Message("wrong input");
		return -1;
	}
	int start = Instructions.find(".") + 1;
	int l;
	l = Instructions.size() - 2;
	for (int i = start ; i < Instructions.size(); i++ )
	{
		if (Instructions[i] == 48|| Instructions[i]>54)
		{
			Send_StringTEXT_Message("wrong input");
			return -1;
		}
		chooseDice.push_back(DicePoint[Instructions[i] - 49]);
	}
		count_point(chooseDice, l);
	return PickNumber;
}

bool Wait_player(std::string Instructions, std::string Name)
{
	if (!Instructions.compare("join"))
	{
		if (!Name.compare(Player[First].name))
		{
			Send_StringTEXT_Message(Name + " already in list");
			return false;
		}
		else
		{
			start_game(Instructions, Name);
			return true;
		}	
	}
	else if (!Instructions.compare("end"))
	{
		(!Name.compare(Player[0].name)) ?
			Dice_end():Send_StringTEXT_Message("u cant end game u are not person who start game");
		return false;
	}
	else
	{
		Send_StringTEXT_Message("Now Dice mode wrong input!");
		return false;
	}
}


int Check_name(std::string Name)
{
	if (!Name.compare(PlayerList[demark]))
	{
		return 0;
	}
	else
	{
		Send_StringTEXT_Message("not your round");
		return -1;
	}
		
}


int DicePlayer_round(std::string Instructions, std::string Name)
{
	if (Check_name(Name) == -1)
	{
		return -1;
	}
	else if (!Instructions.find("p."))
	{
		int stcode = get_Pick_point(Instructions);
		if (stcode != -1)
			Number += stcode;
		else
		{
			Number = 0;
			Player[demark].point += tempPoint;
			new_round(Instructions, Name);
			DicePoint.clear();
			tempPoint = 0;
		}
		if (stcode == 6|| Number ==6)
		{
			Player[demark].point += tempPoint;
			Send_StringTEXT_Message("all kill! u can keep a new round");
			same_round(Instructions, Name, 0);
			DicePoint.clear();
			tempPoint = 0;
			Number = 0;
		}
		DicePoint.clear();
		//same_round(Instructions, Name, Number);
		Send_StringTEXT_Message(Player[demark].name + " round");
		return 0;
	}
	else if (!Instructions.compare("end"))
	{
		if (!Name.compare(PlayerList[0]))
		{
			Dice_end();
			return 0;
		}
		else
			return -1;
	}
	else if (!Instructions.compare("keep"))
	{
		same_round(Instructions, Name, Number);
	}
	else if (!Instructions.compare("pass"))
	{
		Player[demark].point += tempPoint;
		tempPoint = 0;
		Send_StringTEXT_Message(Name + " round end all point : "+ std::to_string(Player[demark].point));
		if (Player[0].point >= 2000)
		{
			Send_StringTEXT_Message("winner is " + Player[0].name);
			Dice_end();
			return 0;
		}
		else if (Player[1].point >= 2000)
		{
			Send_StringTEXT_Message("winner is " + Player[1].name);
			Dice_end();
			return 0;
		}
		DicePoint.clear();
		Number = 0;
		new_round(Instructions, Name);

		return 0;
	}
	else if (!Instructions.compare("help"))
	{
		Send_File("D:\\pojt\\QQbot\\picture\\diceHelp.jpg");
	}
	else
	{
		Send_StringTEXT_Message("wrong input");
		return 0;
	}
	//check_round();
	return 0;
}


int Dice_main(std::string Instructions, std::string Name)
{
	if (isFull)
	{

		int stutcode = DicePlayer_round(Instructions, Name);
		return 0;
	}
	else
	{
		isFull = Wait_player(Instructions, Name);
		return 0;
	}
}

