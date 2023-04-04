#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

extern std::vector<std::string> CardPool;

typedef struct Poker{
	std::string name;
	int playerID = 0;
	int score = 0;
	int chip = 120;
	bool isFlod = false;
	std::vector<std::string> Card;
};
extern Poker PokerPlayer[10];
extern bool isPoker;
extern std::vector<std::string> PokerDecor;

int check_poker_playerNumber(std::string Instructions, std::string playerlist);
void StarPlay(Poker* porke, int stcPokerPlayerNumber);
int Check_same(std::string Name, int FrontNumber);
bool Start_Poker_mode(std::string Instructions, std::string Name);
int Poker_main(std::string Instructions, std::string Name);
int Add_Chippool(std::string Instructions, std::string Name);