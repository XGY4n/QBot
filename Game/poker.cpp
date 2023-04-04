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
#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"poker.h"
#include"TPWinner.h"
#include"Timelog.h"

std::vector<std::string> PokerPoints {
    "2","3","4","5","6","7","8",
    "9","T","J","Q","K","A"
};

std::vector<std::string> PokerDecor{
    "S","H",
    "D","C"
};

typedef struct Pcard {
    std::string name;
    std::string Card;
};
Pcard WinnerSet[10];

std::string PokerPath = "D:\\pojt\\QQbot\\picture\\pukeImage\\";
std::vector<std::string> Public_CardPool;
std::vector<std::string> CardPool;
Poker PokerPlayer[10];

bool First = 0;
bool flag;
bool isPass = true;

int Player = 0;
static int PlayerWaitNumber;
static int NowPlayer = 1;
static int stcPokerPlayerNumber;
static bool isStart = false;
static int demark = 0;
static std::string playerlist;
static int Chippool = 0;
static int FollowChip = 0;
static int roundcount = 1;
static int playermark = 0;
static int Follow = 0;
static int saveMax = 10;
static int CardMark = 0;
static int isSend = 0;



int Check_isSend(std::string CardName)
{
    if(CardPool.size() == 0 )
        return 1;
    for (int i = 0; i < CardPool.size(); i++)
        if (CardName == CardPool[i])
            return -1;
    return 1;
}


std::string Make_randCard(int mark)
{
    std::string CardName;
    int Decor = 0 + rand() % 3;
    int Point = 0 + rand() % 13;
    CardName = PokerDecor[Decor] + PokerPoints[Point];//+ "_" 
    if (Check_isSend(CardName) == 1)
    {
        PokerPlayer[mark].Card.push_back(CardName);// = CardName;
        CardPool.push_back(CardName);
    }
    else
        CardName = Make_randCard(mark);
    return CardName;
}


std::string Make_randCard_public()
{
    std::string CardName;
    int Decor = 0 + rand() % 3;
    int Point = 0 + rand() % 13;
    CardName = PokerDecor[Decor] + PokerPoints[Point];//+ "_" 
    if (Check_isSend(CardName) == 1)
    {
        CardPool.push_back(CardName);
        Public_CardPool.push_back(CardName);
    }
    else
        CardName = Make_randCard_public();
    return CardName;
}



//first use
/********************************************************************************/
bool Start_Poker_mode(std::string Instructions, std::string Name)
{
    playerlist = playerlist + Name + " ";
    PokerPlayer[demark++].name = Name;
    PlayerWaitNumber = check_poker_playerNumber(Instructions, playerlist) - 1;//Join_message 
    stcPokerPlayerNumber = PlayerWaitNumber + 1;
    if (PlayerWaitNumber > 9)
        Send_StringTEXT_Message(Send_WrongInput_Message());
    (PlayerWaitNumber == 0 || PlayerWaitNumber > 9) ? flag = 0 : flag = 1;
    return flag;
}
/**************************************************************************************************************/



//initialization
/****************************************************************************************************************/
void Game_end()
{
    Send_StringTEXT_Message("pokermode end");
    isPoker = false;
    demark = 0;
    playerlist = "";
    stcPokerPlayerNumber = 0;
    NowPlayer = 1;
    Chippool = 0;
    FollowChip = 0;
    memset(&PokerPlayer, 0x00, sizeof(PokerPlayer));
    isPass = true;
    saveMax = 10;
}

void Check_winner()
{
    //std::vector<std::string >CopmareSet;
    //std::deque<std::string>CopmareSet;
    std::deque<Pcard>CopmareSet;
    std::string Pubilc_line;
    for (int i = 0; i < Public_CardPool.size(); i++)
    {
        Pubilc_line = Pubilc_line + Public_CardPool[i] + " ";
        std::cout << Public_CardPool[i] << std::endl;
    }
    //std::string CopmareSet;

    for (int i = 0; i < stcPokerPlayerNumber; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (PokerPlayer[i].isFlod==false)
            {
                WinnerSet[i].name = PokerPlayer[i].name;
                WinnerSet[i].Card = WinnerSet[i].Card + PokerPlayer[i].Card[j]+ " ";
                std::cout << PokerPlayer[i].name << "  " << PokerPlayer[i].Card[j] << std::endl;
            }
 
        }
           CopmareSet.push_back(WinnerSet[i]);//PokerPlayer[i].Card[j]
           std::cout << WinnerSet[i].Card << std::endl;
    }

    for (int i = 0; i < stcPokerPlayerNumber - 1; i++)
    {
        std::string Pokerline;
        Pokerline = Pubilc_line + CopmareSet[0].Card + CopmareSet[1].Card;
        std::cout << Pokerline << std::endl;
        FILE* fp = NULL;
        fp = fopen("D:\\pojt\\QQbot\\picture\\pukeImage\\Check_Winner.txt", "w+");
        fprintf(fp, Pokerline.c_str());
        fclose(fp);
        //int tempPlayer = stcPokerPlayerNumber;
        int QueueMark;
        int Winner;
        QueueMark = Winnermain();
        if (QueueMark == 0)
        {
            swap(CopmareSet[1].Card, CopmareSet[0].Card);
            swap(CopmareSet[1].name, CopmareSet[0].name);
            CopmareSet.pop_front();
        }
        else if (QueueMark == 1)
        {
            CopmareSet.pop_front();
        }
    }
    std::string Winner = CopmareSet[0].name;
    Send_StringTEXT_Message(Winner + " is winner!!!");
}

int Check_same(std::string Name, int FrontNumber)//check name is same or not
{
    for (int i = 0; i < FrontNumber+1; i++)
    {
        if (!PokerPlayer[i].name.compare(Name))
        {
            Send_StringTEXT_Message("u cant rejoin!");
            return -1;
        }
    }
    return 1;
}

int Poker_initialization(std::string Instructions, std::string Name)
{
    if (!Instructions.compare("join") && stcPokerPlayerNumber != NowPlayer)
    {
        if (Check_same(Name, demark)==-1)
            return 0;
        PokerPlayer[demark++].name = Name;
        playerlist = playerlist + Name + " ";
        Send_StringTEXT_Message("now players : " + playerlist);//Join_message
        Send_StringTEXT_Message("player " + Name + " join success");//Join_message
        NowPlayer++;
        stcPokerPlayerNumber == NowPlayer ? StarPlay(PokerPlayer, stcPokerPlayerNumber) :
            Send_StringTEXT_Message("now player :" + std::to_string(NowPlayer) + "/" + std::to_string(stcPokerPlayerNumber));
        return 0;
    }
    else if (!Instructions.compare("end"))
    {
        Game_end();
        return 0;
    }
    else
        Send_StringTEXT_Message("u cant do this at poker time! send #end to end pokermode/youl");
    return 0;
}


int check_poker_playerNumber(std::string Instructions, std::string playerlist)
{
	Send_StringTEXT_Message("starting poker mode");
    int start = Instructions.find(".");
    std::string UserNumber;
    if (start + 1 == Instructions.size())
    {
        Send_StringTEXT_Message(Send_WrongInput_Message());
        return 0;
    }
    else
    {
        for (int i = start + 1; i < Instructions.size(); i++)
            UserNumber = UserNumber + Instructions[i];
		Player = std::stoi(UserNumber);
        Send_StringTEXT_Message("now players : " + playerlist);//Join_message
        Send_StringTEXT_Message("wait player 1/" +  std::to_string(Player));
        return Player;
    }
}

void StarPlay(Poker* porke, int stcPokerPlayerNumber)
{
    int a = 0;
    int b = 0;
    while (1)
    {
        if (a != b)break;
        a = 0 + rand() % (stcPokerPlayerNumber);
        b = 0 + rand() % (stcPokerPlayerNumber);
    }
    Send_StringTEXT_Message("大盲注 10 Chip: " + PokerPlayer[a].name +
        " 小盲注 5 Chip: "+ PokerPlayer[b].name);
    Chippool += 15;
    FollowChip += 10;
    Send_StringTEXT_Message("start !");
    First = true;
    for (int i = 0; i < stcPokerPlayerNumber; i++)
    {
        for (int j = 0; j < 2; j++)
            Send_File(PokerPath + Make_randCard(i) + ".jpg", PokerPlayer[i].name);
            //Send_File(PokerPath + Random_Number(52) + ".jpg", PokerPlayer[i].name);
        Sleep(500);
        CardMark = 0;
        Send_StringTEXT_Message("send to " + PokerPlayer[i].name + " end");
    }
    HWND MainGroup = FindWindow(_T("TXGuiFoundation"), _T("不常用群聊"));
    SetForegroundWindow(MainGroup);
    Send_StringTEXT_Message("round " + std::to_string(roundcount)+" 筹码池:"+ 
        std::to_string(Chippool) + " Call:" + std::to_string(FollowChip));
    Send_StringTEXT_Message("now is " + PokerPlayer[playermark].name + " round");
    isStart = true;
}
/******************************************************************************************************************************/





int Make_Chip(std::string Instructions)
{
    int FNumber;
    std::string ans;
    std::stringstream tce;
    int start = Instructions.find(".");
    for (int i = start+1; i < Instructions.size(); i++)
        ans = ans + Instructions[i];
    tce << ans;
    tce >> FNumber;
    std::cout<< FNumber << std::endl;
    std::cout<< ans << std::endl;
    if (PokerPlayer[playermark].chip - FNumber < 0 || FNumber == 0 || FNumber < saveMax)
        return -1;
    else
        return FNumber;
}


int Add_Chippool(std::string Instructions, std::string Name)
{
    int temp = Make_Chip(Instructions);
    if (temp == -1)
    {
        return -1;
    }
    else
    {
        saveMax += temp;
        FollowChip = saveMax;
        Chippool += FollowChip;
        PokerPlayer[playermark].chip = PokerPlayer[playermark].chip - temp;
        return 0;
    }
}

int Add_all(std::string Instructions, std::string Name)
{
    saveMax += PokerPlayer[playermark].chip;
    FollowChip += PokerPlayer[playermark].chip;
    Chippool += PokerPlayer[playermark].chip;
    PokerPlayer[playermark].chip = 0;
    return 0;
}

void Add_call(std::string Instructions, std::string Name)
{
    FollowChip = saveMax;
    Chippool += FollowChip;
    PokerPlayer[playermark].chip = PokerPlayer[playermark].chip - FollowChip;
}

void check_round()
{
    if (playermark == stcPokerPlayerNumber-1)
    {
        
        if (playermark >= stcPokerPlayerNumber-1 && roundcount == 1)
        {
            Send_StringTEXT_Message("round " + std::to_string(roundcount) + " now ChipPool:" +
                std::to_string(Chippool) + " now Filling:" + std::to_string(FollowChip));
            playermark = -1;
            for (int i = 0; i < 3; i++)
            {
                //std::cout<<"Filefrom" << PokerPath + Make_randCard_public() + ".jpg" << std::endl;//+  +
                Send_File(PokerPath + Make_randCard_public() + ".jpg");
                Sleep(500);
            }
            Sleep(1500);
            roundcount++;
            isPass = true;
        }
        else if (playermark >= stcPokerPlayerNumber-1 && roundcount > 1 && roundcount< 4)
        {
            Send_StringTEXT_Message("round " + std::to_string(roundcount+1) + " now ChipPool:" +
                std::to_string(Chippool) + " now Filling:" + std::to_string(FollowChip));
            Sleep(500);
            playermark = -1;
            Send_File(PokerPath + Make_randCard_public() + ".jpg");
            Sleep(1000);
            roundcount++;
            isPass = true;
        }
        else
        {
            Check_winner();
            Game_end();
        }
    }

}


int PlayerRound(std::string Instructions, std::string Name)
{
        if (Name.compare(PokerPlayer[playermark].name))
        {
            Send_StringTEXT_Message("not your round");
            return -1;
        }
        if (PokerPlayer[playermark].isFlod) //== true
        {
            Send_StringTEXT_Message("player fold");
        }
        else if (!Instructions.find("up."))
        {
            int stat;
            stat = Add_Chippool(Instructions, Name);
            if (stat == -1)
            {
                Send_StringTEXT_Message("wrong input");
                return -1;
            }
            isPass = false;
        }
        else if (!Instructions.find("all"))
        {
            Add_all(Instructions, Name);
        }
        else if (!Instructions.find("call"))
        {
            Add_call(Instructions, Name);
        }
        else if (!Instructions.find("fold"))//Fold
        {
            PokerPlayer[playermark].isFlod == true;
            Send_StringTEXT_Message("player " + Name + " fold");
        }
        else if (!Instructions.find("pass"))
        {
            if(isPass == true)
                Send_StringTEXT_Message("player " + Name + " pass");
            else
            {
                Send_StringTEXT_Message("now you only can up or follow the player front you !");
                return -1;
            }
        }
        else if (!Instructions.compare("end"))
        {
            if (!Name.compare(PokerPlayer[0].name))
            {
                Game_end();
            }
            else
            {
                Send_StringTEXT_Message("u cant close this game only Initiator can close");
                return -1;
            }
               
        }
        else
        {
            Send_StringTEXT_Message("wrong input");
            return -1;
        }
        check_round();
        return 0;
}



int Poker_main(std::string Instructions, std::string Name)
{
    if (isStart)
    {
        int stata = PlayerRound(Instructions, Name);
        if(stcPokerPlayerNumber > playermark+1 && stata==0)
            Send_StringTEXT_Message("now is " + PokerPlayer[++playermark].name + " round");
        return 0;
    }
    else
    {
        Poker_initialization(Instructions, Name);
        return 0;
    }
}