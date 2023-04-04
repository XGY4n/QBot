#pragma once
#include <queue>
#include <map>
#include <string>
using namespace std;
std::string toLower(std::string);
std::string grower(std::string);
class Bot
{
public:
	Bot();
	~Bot();
	void talk(string);
	string answerTo(string);
	void newAnswer(string);
	void load(); /** load all memory **/
	void save(); /** save all memory **/

private:
	map <string, map <string, int> > memory;
	string answer;
	bool firstTime;
};