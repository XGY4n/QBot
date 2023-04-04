#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

typedef struct DicePlayer {
	bool isStartPerson;
	std::string name;
	int point = 0;
	int DiceNumber = 5;
};
extern std::vector<int>DicePoint;
extern DicePlayer Player[3];
extern bool isDice;
extern std::deque<DicePlayer>PlayerQueue;
bool Start_Dice_mode(std::string Instructions, std::string Name);
int Dice_main(std::string Instructions, std::string Name);