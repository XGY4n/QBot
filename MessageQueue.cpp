#using "./c#qqmessage/uaiQmsgc.dll"
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
#include <msclr\marshal_cppstd.h>
#include"ChineseString.h"
#include"systemStringtoString.h"
#include"QueueDef.h"
#include"QueueOperation.h"
#include"InstructionPart.h"
#include"Timelog.h"
#include"SendMessage.h"
#include"Botlog.h"
#include"UIAMsg.h"
using namespace uaiQmsgc;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

#define _TIMER_(N, B) ((N).compare((B)) == 0) ? std::this_thread::sleep_for(std::chrono::milliseconds(timer_s+=100)) :timer_s = 0;

std::string RawMessage;
std::string message;
std::string name;
std::string QQnumber;
std::string finalMesssage;
std::string DataTime;

typedef enum {
    Bot_Call = 1,
    Bot_NotCall = -3,
    Bot_SelfCall = -2,
}QueueCall;

void sendClick(HWND hwnd, int x, int y)
{
    LPARAM lParam = MAKELPARAM(x, y);
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    Sleep(50);
    PostMessage(hwnd, WM_LBUTTONUP, 0, lParam);
    Sleep(50);
}



void MoveWindowOffScreen(HWND hwnd)
{
    // 获取屏幕分辨率
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 获取窗口大小
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    // 将窗口移动到屏幕外
    MoveWindow(hwnd, screenWidth, screenHeight, windowWidth, windowHeight, TRUE);
}



int  Tpush_rawmessage_to_queue()//this function to take Rawmessage from QQ
{
    std::unique_ptr<Botlog> log{ new Botlog{} };
    std::unique_ptr<UIAMsg> _Getmsg{ new UIAMsg{} };
    std::string tempp;
    Program^ messagee = gcnew Program();//UIA class
    Chinese ch;//CN string 
    std::string LatestMessage;
    int timer_s = 0;
    bool heart_beat = true;
    std::string front_data;
    HWND hwnd = FindWindow(_T("TXGuiFoundation"), _T("消息管理器"));
    std::cout << hwnd << std::endl;
    Chinese Qmsg;
    MoveWindowOffScreen(hwnd);
    while (1)
    {
        
        sendClick(hwnd, 646,113);
        //HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(InI_Group_Name()));//
        //SetForegroundWindow(MainGroup);
       // MarshalString(messagee->Take(), RawMessage);//systemstring to string Take() is C# function cant take UIA message
        RawMessage = _Getmsg->UIAGet_Msg_String();//newone();
        //RawMessage = newone();
        //std::cout<<RawMessage<<std::endl;
        _TIMER_(RawMessage, LatestMessage)
            if (timer_s == 1500)
                log->Record(Botlog::LEVEL_SUCCESS, Botlog::OWNER_SELF,std::string("Heart Beat"));//LOG_writer("[Self]" + Now_time() + "Heart beat");
            else if (timer_s > 1500)
                timer_s = 1500;
        LatestMessage = RawMessage;
        Chinese::Qmsg result;
        try
        {
             
             result = Qmsg.Qmsgmake2(RawMessage);
             //std::cout << "|" << result.DataTime << "|" << result.name << "|" << result.message<< "|" << result.QQnumber<< std::endl;
             name = result.name;//make_name(RawMessage);//Make the nearest Message username
             QQnumber = result.QQnumber;//make_number(RawMessage);//Make the nearest Message UserQQnumber
             message = result.message;//make_message(RawMessage);//Make the nearest Message UserMessage
             DataTime = result.DataTime;//make_time(RawMessage);//Make the nearest Message SendTime
             std::string mas = "[" + DataTime + "]" + name + "(" + QQnumber + ")" + message;
        }
        catch (const std::out_of_range& e)
        { 
            //std::cout << e.what() << std::endl; 
            //Send_StringTEXT_Message(std::string(e.what()));//
            name = make_name(RawMessage);//Make the nearest Message username
            QQnumber = make_number(RawMessage);//Make the nearest Message UserQQnumber
            message = make_message(RawMessage);//Make the nearest Message UserMessage
            DataTime = make_time(RawMessage);//Make the nearest Message SendTime
            std::string mas = "[" + DataTime + "]" + name + "(" + QQnumber + ")" + message;
            if (DataTime.compare(front_data) != 0)
            {
                front_data = DataTime;
                log->Record(Botlog::LEVEL_WARNIGN, Botlog::OWNER_SELF, std::string(e.what()));
            }

            //Send_StringTEXT_Message(std::string(e.what()+"use algorithm II"));
        }

        std::string mas = "[" + DataTime + "]" + name + "(" + QQnumber + ")" + message;
        int Mark = raw_check(message);//Check the nearest Message is call bot or not
        //std::cout << "__"<< DataTime <<"__" << std::endl;
        if (Mark == Bot_SelfCall)//have
        {
            if (tempp.compare(mas) != 0)
            {
                tempp ="[" +  DataTime + "]" + name + "(" + QQnumber + ")" + message;

                //LOG_writer("[Self]" + Now_time() +  tempp);
                log->Record(Botlog::LEVEL_SUCCESS, Botlog::OWNER_SELF,tempp);
                //LOG_writer(Now_time() + mas);
            }
            else
            {
                tempp = "[" + DataTime + "]" + name + "(" + QQnumber + ")" + message;
                //LOG_writer(DataTime + "]" + name + "(" + QQnumber + ")" + message);
            }
        }
        else if (Mark == Bot_Call)
        {
            check_push(name, QQnumber, message, DataTime);

            //LOG_writer("[Self]" + Now_time() + "[" + tempp);
            //check_push(name, QQnumber, message, DataTime);
        }
        else if (Mark == Bot_NotCall)//string dont include #
        {
            if (tempp.compare(mas) != 0)
            {
                tempp = "[" + DataTime +  "]" + name + "(" + QQnumber + ")" + message;

                //LOG_writer("[Not Call]" + Now_time()  + tempp);
                log->Record(Botlog::LEVEL_SUCCESS, Botlog::OWNER_UNDEF, tempp);
                //LOG_writer(Now_time() + mas);
            }    
            else
            {
                tempp = "[" + DataTime + "]" + name + "(" + QQnumber + ")" + message;
                //LOG_writer(DataTime + "]" + name + "(" + QQnumber + ")" + message);
            }
        }
        else
        {
            Send_StringTEXT_Message("undefine error");;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
        Sleep(150);
    }
}

void Tcheck_number_qmessage()
{
    int temp = 0;
    while (1)
    {
        if (temp != Qmessage.size())
            std::cout << Now_time() << "Qmessage : " << Qmessage.size() << std::endl;
        else
            temp = Qmessage.size();
       if (Qmessage.size() != 0)//first queue have number
       {
           //push_to_QInstructions(make_Instructions(Qmessage.front()));
           push_to_QInstructions(Qmessage.front());
           //delet # and push this string to the sencond queue
       }
       Sleep(150);
    }
}

void Take_QInstructions()
{
    int temp = 0;
    std::thread User[10] ;
    int counter = 0;
    while (1)
    {
        if (temp != QInstructionsMessage.size())
            std::cout<< Now_time() << "Instructions : " << QInstructionsMessage.size() << std::endl;
        else
            temp = QInstructionsMessage.size();
        if (QInstructionsMessage.size() != 0)//sencond queue have number
        {                
               std::cout << Now_time() << QInstructionsMessage.front() << std::endl;
                std::string pop_message = pop_QInstructionsMessage(); //Instructions_main   check_Instructions             
                std::thread ExecutedInstructions (Instructions_main, make_Instructions_message(pop_message), make_Instructions_name(pop_message), make_Instructions_QQnumber(pop_message));//pop_QInstructionsMessage() make_Instructions_QQnumber(pop_message)
                ExecutedInstructions.join();//pop the Instructions and join the message to the thread executed Instructions
            /*for (int i = 0; i < QInstructionsMessage.size(); i++)
            {
                std::cout << Now_time() << QInstructionsMessage.front() << std::endl;
                std::string pop_message = pop_QInstructionsMessage();    
                User[i] =  std::thread(Instructions_main, make_Instructions_message(pop_message), make_Instructions_name(pop_message), make_Instructions_QQnumber(pop_message));//pop_QInstructionsMessage() make_Instructions_QQnumber(pop_message)
                counter++;
               //check_Instructions(make_Instructions_message(pop_message), make_Instructions_name(pop_message));std::thread
            }
            for (int th = 0; th < counter; th++)
            {
                if (User[th].joinable())
                    User[th].join();
                else
                    break;
            }*/
                
        }
       Sleep(300);
    }
}