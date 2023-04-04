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
#include"SendMessage.h"
#include"ChineseString.h"
#include"Timelog.h"

std::string Send_Help_Message()
{
    std::string HelpMessage = 
        "机器人使用手册\n\
        1.呼叫机器人使用 # 开头的字符串\n\
        2.现在开放功能为#v. /#m. /#rxdn /#dice /#p. 指令的编码规则: # + 指令头. + 指令信息\n\
            样例1:查找B站id为114514的人所关注的vtb指令为 #v.114514 (返回.txt)\n\
            样例2:查找网易云歌曲冬之花指令为 #s.冬之花 (返回.mp3)\n\
            样例3:随机两个六面骰子指令为 #r2d6 (返回对应值),其中骰子个数应当小于5,面数应当小于999999否则会报错\n\
            样例4:1v1摇骰子小游戏 #dice , 发 #join 加入游戏,进入骰子游戏模式时发送 #help 获取骰子模式帮助\n\
            样例5:德州扑克游戏 #p.x ,其中x为玩家数,发 #join 加入游戏,进入扑克游戏模式时发送 #help 获取扑克模式帮助\n\
        3.关于用来臊皮的没有指令头的指令:#图片(回复一张图片),#攻击性话语(回复攻击性的话,或者没添加对应回复这将反回No such function)\n\
        4.关于音乐搜索功能 \n\
            1.曲库为网易云\n\
            2.如果只搜中文名字没搜到预期的音乐请详细输入(用 空格 或者 - 隔开)歌曲原语言的名字-作者-甚至专辑的名称 如:冬之花-宮本浩次-<<TOKYO-POPCHRISTMAS2021>>";

           return  HelpMessage;
}

std::string Send_Error_Message()
{
    std::string ErrorMessage = "文件抓取有误或者程序出现了错误,请@xgt或者重试/快哭了";
    return ErrorMessage;
}

std::string Send_WrongInput_Message()
{
    std::string WrongInputMessage = "执行失败!指令头正确但指令值不符合规则,输入#号 + help查看帮助你这低能/流汗";
    return WrongInputMessage;
}

//std::string Send_Error_Message()

std::string Send_Wait_Message()
{
    std::string WaitMessage = "别急~/亲亲";
    return WaitMessage;
}

std::string NO_Function()
{
    std::string NoFunction = " /NO NO such function";
    return NoFunction;
}

