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
#include <msclr\marshal_cppstd.h>
#include"Timelog.h"
#include"QueueOperation.h"
#include"QueueDef.h"
int once = 0;
std::string temp;
void check_push(std::string name, std::string QQnumber, std::string message, std::string time)//
{
    std::string finalMesssage;
    finalMesssage = time+ "]" + name + "(" + QQnumber + ")" + message;
    //std::cout << finalMesssage<< std::endl;
    if (finalMesssage.compare(temp) == 0 )//QInstructionsMessage.front()
    {
        //std::cout << finalMesssage << std::endl;
        std::cout<< Now_time()<<"[" << finalMesssage << "  Wait Queue........." << std::endl;

        //use time to check the message is same or not
    }
    else
    {
        temp = finalMesssage;//save the message to check is same or not
        //std::cout << Now_time() << "fianlMesssage: " << finalMesssage << std::endl;
        LOG_writer(Now_time() + finalMesssage);
        Qmessage.push_back(name+"("+QQnumber+")" + message);//string have # push to first queue call Qmessage
    }
}//this function push message call bot to queue , time is important vaule

void push_to_QInstructions(std::string Instructions)
{
    std::cout << Now_time() <<"push Instructions : " <<Instructions<<std::endl;
    QInstructionsMessage.push_back(Instructions);
    Qmessage.pop_front();
}//this function push the legal Instructions to the sencond queue

std::string pop_QInstructionsMessage()
{
    std::string ExecutInstructions = QInstructionsMessage.front();
    QInstructionsMessage.pop_front();
    return ExecutInstructions;
}//this function use temp string to save the Instructions will be Execut