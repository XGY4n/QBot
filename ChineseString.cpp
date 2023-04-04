#include"ChineseString.h"
#include"Timelog.h"
#include<string>
#include <locale>
#include <codecvt>
#include <tchar.h>

typedef enum {
    Bot_Call = 1,
    Bot_NotCall,
    Bot_SelfCall = -2,
}QueueCall;

Chinese::Chinese()
{

}

Chinese::~Chinese()
{

}

wchar_t* Chinese::MBCSToUnicode(wchar_t* buff, const char* str)
{
    wchar_t* wp = buff;
    char* p = (char*)str;
    while (*p)
    {
        if (*p & 0x80)
        {
            *wp = *(wchar_t*)p;
            p++;
        }
        else
        {
            *wp = (wchar_t)*p;
        }
        wp++;
        p++;
    }
    *wp = 0x0000;
    return buff;
}

char* Chinese::unicodeToMBCS(char* buff, const wchar_t* str)
{
    wchar_t* wp = (wchar_t*)str;
    char* p = buff, * tmp;
    while (*wp)
    {
        tmp = (char*)wp;
        if (*wp & 0xFF00)
        {
            *p = *tmp;
            p++;
            tmp++;
            *p = *tmp;
            p++;
        }
        else
        {
            *p = *tmp;
            p++;
        }
        wp++;
    }
    *p = 0x00;
    return buff;
}

std::wstring Chinese::strToWstr(std::string& input)
{
    size_t len = input.size();
    wchar_t* b = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    MBCSToUnicode(b, input.c_str());
    std::wstring r(b);
    free(b);
    return r;
}

char* Chinese::wstrToChar(std::wstring& wstr)
{
    char* re = wstrToChar(wstr.c_str());
    return re;
}

char* Chinese::wstrToChar(const wchar_t* wstr)
{
    int len = wcslen(wstr);
    char* buff = (char*)malloc((len * 2 + 1) * sizeof(char));
    char* re = unicodeToMBCS(buff, wstr);
    free(buff);
    return re;
}

std::string Chinese::wstrToStr(std::wstring& wstr)
{
    size_t len = wstr.size();
    char* b = (char*)malloc((2 * len + 1) * sizeof(char));
    unicodeToMBCS(b, wstr.c_str());
    std::string r(b);
    free(b);
    return r;
}



std::string make_message(std::string RawMessage)//# 35
{
    int ret;
    int start = 0;
    int end = 0;
    int flage = 0;
    Chinese ch;
    std::wstring w_str = ch.strToWstr(RawMessage);
    // for (int i = 0; i < w_str.size(); i++)
    for (int i = w_str.size(); i > 0; i--)
    {
        //cout<<w_str[i]<<endl;//int(RawMessage[i])
        if (w_str[i] == 13 && flage == 0)
        {
            end = i;
            flage = 1;
        }
        else if (w_str[i] == 13 && flage == 1)
        {
            start = i;
            break;
        }
    }
    /*cout << "Start :" << start << endl;
    cout << "end :" << end << endl;*/
    std::wstring sendname;
    for (int i = start + 2; i < end; i++)
    {
        sendname = sendname + w_str[i];
        //cout << w_str[i] << endl;
    }
    std::string ans = ch.wstrToStr(sendname);
    //std::cout << "message: " << ans << std::endl;
    return ans;
}

std::string make_name(std::string RawMessage)
{
    int ret;
    int start = 0;
    int end = 0;
    Chinese ch;
    std::wstring w_str = ch.strToWstr(RawMessage);
        for (int i = w_str.size(); i > 0; i--)
        {
            //cout << w_str[i] <<" "<<i<< endl;//int(RawMessage[i])
            if (start != 0 && end != 0)
            {
                break;
            }
            else
            {
                if (w_str[i] == 49057)
                {
                    start = i;
                }
                else if (w_str[i] == 40 || w_str[i] == 60)
                {
                    end = i;
                }
            }
        }
    std::wstring sendname;

    for (int i = start + 1; i < end; i++)
    {
        sendname = sendname + w_str[i];
    }
    std::string ans = ch.wstrToStr(sendname);
    //std::cout << ans << std::endl;
    return ans;
    //std::cout<<ret<<std::endl;
}

std::string make_number(std::string RawMessage)
{
    int ret;
    int start = 0;
    int end = 0;
    Chinese ch;
    std::wstring w_str = ch.strToWstr(RawMessage);
    // for (int i = 0; i < w_str.size(); i++)
    for (int i = w_str.size(); i > 0; i--)
    {
        //cout<<w_str[i]<<endl;//int(RawMessage[i])
        if (start != 0 && end != 0)
        {
            break;
        }
        else
        {
            if (w_str[i] == 40 || w_str[i] == 60)
            {
                start = i;
            }
            else if (w_str[i] == 41 || w_str[i] == 62)
            {
                end = i;
            }
        }

    }
    std::wstring sendname;
    for (int i = start + 1; i < end; i++)
    {
        sendname = sendname + w_str[i];
        //cout <<w_str[i] << endl;
    }
    std::string ans = ch.wstrToStr(sendname);
    //std::cout << ans << std::endl;
    return ans;
}

int raw_check(std::string RawMessage)
{
    int ret = 0;
    //if (RawMessage.find("1364303391") != std::string::npos || RawMessage.find("2995244756") != std::string::npos)//)|| RawMessage.find("xgxg") != std::string::npos
        //return ret;//1364303391
    if (RawMessage.find("> ") != std::string::npos)
        return -2;
    ret = RawMessage.find("#");
    //std::cout << "ret :" << RawMessage.size() << std::endl;
    if (ret == 0)
        return 1;
    else
        return -3;
    //std::cout<<"ret :" << ret << std::endl;
    return ret;
}

std::string make_Instructions_message(std::string QueueTop)
{
    //std::cout << QueueTop << std::endl;
    std::string Instructions;
    int start;
    for (int i = QueueTop.size(); i > 0; i--)
    {
        if (QueueTop[i] == 35)
        {
            start = i;
            break;
        }
    }
    for (int i = start+1; i < QueueTop.size(); i++)
    {
        Instructions = Instructions + QueueTop[i];
    }
    return Instructions;
}

std::string make_time(std::string RawMessage)
{
    int start = 0;
    int end = 0;
    std::string time;
    for (int i = RawMessage.size(); i > 0; i--)
    {
        if (RawMessage[i] == 41)
        {
            start = i;
            break;
        }
    }
    start = start + 3;
    end = start + 8;
    for (int i = start; ; i++)//i < end
    {
        if (RawMessage[i] != 58 && (RawMessage[i] < 48 || RawMessage[i]>57))
            break;
        time = time + RawMessage[i];
    }
   // scout << "time :" << time << endl;
    return time;
}

std::string Chinese_SendMessage(std::string CNmessage)
{
    int ret;
    int start = 0;
    int end = CNmessage.size();
    Chinese ch;
    std::wstring w_str = ch.strToWstr(CNmessage);
    std::wstring sendname;
    for (int i = 0; i < 2; i++)
        sendname = sendname + w_str[i];
    std::string ans = ch.wstrToStr(sendname);
    return ans;
}

std::string Random_Number(int range)
{
    int n = 1 + rand() % range;
    std::cout << Now_time() << n << std::endl;
    return std::to_string(n);
}




std::string make_Instructions_name(std::string QueueTop)
{
    
    std::string Instructions;
    int end;
    for (int i = QueueTop.size(); i > 0; i--)
    {
        if (QueueTop[i] == 35)
        {
            end = i;
            break;
        }
    }
    for (int i = 0; i < end; i++)
        Instructions = Instructions + QueueTop[i];
    return Instructions;
}




std::string make_Instructions_QQnumber(std::string QueueTop)
{
    std::string QQnumber;
    int start;
    int end;
    for (int i = QueueTop.size(); i > 0; i--)
    {
        if (QueueTop[i] == 40)
        {
            start = i;
        }
        if (QueueTop[i] == 41)
        {
            end = i;
        }
    }
    for (int i = start+1; i < end; i++)
        QQnumber = QQnumber + QueueTop[i];
    return QQnumber;
}








std::string Make_Random(std::string Instructions)
{
    std::string rN;
    std::string rC;
    std::string ans;
    if (Instructions.find("d") == std::string::npos)
    {
        ans = "wrong input where is d?";
        return ans;
    }
    int round;
    int RandNumber;
    int start = Instructions.find("r");
    int mid = Instructions.find("d");
    int end = Instructions.size();
    for (int i = start + 2; i < mid; i++)
        rN = rN + Instructions[i];
    for (int i = mid + 1; i < end; i++)
        rC = rC + Instructions[i];
    round = std::stoi(rN);
    RandNumber = std::stoi(rC);
    if (round > 20 || RandNumber >= 999999)
        ans = "x<20 d n<999999";
    else
        for (int i = 0; i < round; i++)
            ans = ans + "骰子" + "["+ std::to_string(i + 1)+"]" + ":" + Random_Number(RandNumber) + " ";
    return ans;
}




std::string GbkToUtf8(const char* src_str)
{
    int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    std::string strTemp = str;
    if (wstr) delete[] wstr;
    if (str) delete[] str;
    return strTemp;
}


std::string UTF8ToGBK(const char* strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);

    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;

    return strTemp;
}

wchar_t* multi_Byte_To_Wide_Char(std::string pKey)
{
    char pCStrKeyy[10000];
    strcpy(pCStrKeyy, pKey.c_str());
    char* pCStrKey = pCStrKeyy;

    int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
    wchar_t* pWCStrKey = new wchar_t[pSize];

    MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
    return pWCStrKey;
}



std::string UTF82Char(const char* szU8)
{
    std::string ans;
    int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, szU8, (int)strlen(szU8), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    MultiByteToWideChar(CP_UTF8, NULL, szU8, (int)strlen(szU8), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    int len = WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), NULL, 0, NULL, NULL);
    char* c = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), c, len, NULL, NULL);
    c[len] = '\0';
    delete[] wszString;
    ans = c;
    return ans;
}


char* wideCharToMultiByte(wchar_t* pWCStrKey)
{

    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];

    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    return pCStrKey;
}

std::wstring string2wstring(std::string str)
{
    std::wstring result;
    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    TCHAR* buffer = new TCHAR[len + 1];
    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';             //添加字符串结尾  
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}
