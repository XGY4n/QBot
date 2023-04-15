#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <Python.h>
#include <deque>
#include <fstream>
#include <locale>
#include <codecvt>
#include <fstream>
#include <tchar.h>
#include"Timelog.h"
#include"SendMessage.h"
#include"163music.h"
#include"BiliVFollow.h"
#include"ErrorHelpMessage.h"
#include"ChineseString.h"
#include"ini.h"
#include"CInI.h"

extern class ChatGPT;



class ChatGPT
{
public:
    ChatGPT();
    ~ChatGPT();

public: 

    //std::string ChatGPT_add_turns(std::string ask);
    std::string ChatGPT_aks(std::string question);

    void ChatGPT_pylode();

    void ChatGPT_deque();

    std::string ChatGPT::ChatGPT_ans();

    void ChatGPT_cuter();

    void ChatGPT_refersh();

    void ChatGPT_Instructions_make(std::string ins);

    void ChatGPT_Ins_main(std::string Ins);

    void ChatGPT_OPENAI(std::string Ins);

    void ChatGPT_NEWBING(std::string Ins);

    std::string ask = "";
    std::string ans = "";
    std::string histroy_str = "";
    std::string result;
    std::string temp_str;
    std::string AI_Ins_head;

    std::string AI_Ins;

    bool mode = 1;
    //std::pair<int, int > msg_inf;
    std::deque<std::string> Turns;
    std::deque<std::string>::iterator it;
    std::vector<std::pair<int, int >> ans_mark;
    std::vector<std::string> modle = {"text-davinci-003","text-babbage-001", "text-curie-001", "text-ada-001"};
    //std::map<int, int> ans_mark;
    int ans_count = 0;
};

//ChatGTP AI;