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
#include"SendMessage.h"
#include"ChineseString.h"
#include"Timelog.h"
#include"ini.h"

//HWND WIN = FindWindow(_T("TXGuiFoundation"), _T("不常用群聊"));

//this to function copy message to Clipboard
//HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(GroupName));
int CopyFileToClipboard(char szFileName[])
{
    UINT uDropEffect;
    HGLOBAL hGblEffect;
    LPDWORD lpdDropEffect;
    DROPFILES stDrop;
    HGLOBAL hGblFiles;
    LPSTR lpData;
    uDropEffect = RegisterClipboardFormat(LPCWSTR("Preferred DropEffect"));
    hGblEffect = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, sizeof(DWORD));
    lpdDropEffect = (LPDWORD)GlobalLock(hGblEffect);
    *lpdDropEffect = DROPEFFECT_COPY;
    GlobalUnlock(hGblEffect);
    stDrop.pFiles = sizeof(DROPFILES);
    stDrop.pt.x = 0;
    stDrop.pt.y = 0;
    stDrop.fNC = FALSE;
    stDrop.fWide = FALSE;
    hGblFiles = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, \
       sizeof(DROPFILES) + strlen(szFileName) + 2);
    lpData = (LPSTR)GlobalLock(hGblFiles);
    memcpy(lpData, &stDrop, sizeof(DROPFILES));
    strcpy(lpData + sizeof(DROPFILES), szFileName);
    GlobalUnlock(hGblFiles);
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_HDROP, hGblFiles);
    SetClipboardData(uDropEffect, hGblEffect);
    CloseClipboard();
    return 1;
}

//this part send File and message to user
void Send_StringTEXT_Message(std::string StringTEXT, std::string UserName)
{

    HWND User = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(UserName));
    std::string s = "> " + StringTEXT;
    setlocale(LC_ALL, "chs");
    TCHAR text[3000];
    _stprintf_s(text, 3000, _T("%S"), s.c_str());
    for (int i = 0; i < lstrlen(text); i++)
        SendMessage(User, WM_IME_CHAR, text[i], 0);
    Sleep(50);
    SendMessage(User, WM_KEYDOWN, VK_RETURN, 0);
    Sleep(50);
}
void Send_File(std::string Path, std::string UserName)
{
    HWND User = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(UserName));
    char path[3000];
    strcpy(path, Path.c_str());
    CopyFileToClipboard(path);
    SendMessage(User, WM_PASTE, 0, 0);
    Sleep(200);
    SendMessage(User, WM_KEYDOWN, VK_RETURN, 0);
    Sleep(100);
}


//this part send File and message to Group
void Send_StringTEXT_Message(std::string StringTEXT)
{
    std::string group = InI_Group_Name();
    HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(group));//"_T()408"
    SetForegroundWindow(MainGroup);
    std::string s ="> " + StringTEXT; 
    setlocale(LC_ALL, "chs");
    TCHAR text[5000] ;
    _stprintf_s(text, 5000, _T("%S"), s.c_str());
    for (int i = 0; i < lstrlen(text); i++)
        SendMessage(MainGroup, WM_IME_CHAR, text[i], 0);
    Sleep(50);
    SendMessage(MainGroup, WM_KEYDOWN, VK_RETURN, 0);
    Sleep(50);
}
void Send_wStringTEXT_Message(wchar_t * StringTEXT)
{
    std::string group = InI_Group_Name();
    HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(InI_Group_Name()));//"_T()408"
    SetForegroundWindow(MainGroup);
    std::wstring s = L"> ";
    s=s+StringTEXT;
    setlocale(LC_ALL, "chs");
    for (int i = 0; i < s.size(); i++)
        SendMessage(MainGroup, WM_IME_CHAR, s[i], 0);
    Sleep(50);
    SendMessage(MainGroup, WM_KEYDOWN, VK_RETURN, 0);
    Sleep(50);
}
void Send_File(std::string Path)
{
    HWND MainGroup = FindWindow(_T("TXGuiFoundation"), multi_Byte_To_Wide_Char(InI_Group_Name()));
    char path[2255];
    strcpy(path, Path.c_str());
    CopyFileToClipboard(path);
    SendMessage(MainGroup, WM_PASTE, 0, 0);
    Sleep(100);
    SendMessage(MainGroup, WM_KEYDOWN, VK_RETURN, 0);
    Sleep(100);
    LOG_writer(Path);
}


//this part is ?
static int z_pos(uint8_t x)
{
    for (int i = 0; i < 5; i++, x <<= 1) {
        if ((x & 0x80) == 0)
            return i;
    }

    return 4;
}
std::wstring utf8_to_wstring(const std::string& str)
{
    std::wstring loc;
    uint8_t mask[5] = { 0x7f, 0x3f, 0x1f, 0x0f, 0x7 };

    for (size_t i = 0; i < str.length();) {
        int byte_cnt = z_pos(str[i]);
        uint16_t sum = str[i] & mask[byte_cnt];

        for (size_t j = 1; j < byte_cnt; j++) {
            sum <<= 6;
            sum |= str[i + j] & mask[1];
        }

        i += byte_cnt ? byte_cnt : 1;
        loc.push_back(sum);
    }

    return loc;
}

//this function
int check_file(std::string path)
{
    long handle = -1;
    int time = 0;
    struct _finddata_t fileinfo;
    //handle = _findfirst(path.c_str(), &fileinfo);
    for (int time = 0; time <6; time++)
    {
        handle = _findfirst(path.c_str(), &fileinfo);
        //std::cout << fileinfo.name << std::endl;
        if (handle != -1)
            break;
        Sleep(500);
    }
    return(handle == -1 ) ?  -1 :  1;
}

std::string img_find()
{
    __int64  Handle;
    __int64 creat_time;
    int temp = 0;
    std::string neartest_path;
    long jpg_num = 0;
    struct __finddata64_t  FileInfo;
    if ((Handle = _findfirst64("G:/Record/3244014271/Image/Group/*.jpg", &FileInfo)) == -1L)
    {
        Send_StringTEXT_Message("picture error");
        temp = FileInfo.time_create;
    }
    else
    {
        printf("%s\n", FileInfo.name);
        temp = FileInfo.time_create;
        neartest_path = FileInfo.name;
        while (_findnext64(Handle, &FileInfo) == 0)
        {
            jpg_num++;
            printf("%s\n", FileInfo.name);
            std::cout << FileInfo.time_create << std::endl;
            if (temp < FileInfo.time_create)
            {
                temp = FileInfo.time_create;
                neartest_path = FileInfo.name;
            }
            else
            {

            }
        }
        _findclose(Handle);
    }
    printf("%d\n", jpg_num);
    //std::cout << "neartest :" << neartest_path << std::endl;
    neartest_path = "G:\\Record\\3244014271\\Image\\Group\\" + neartest_path;
    LOG_writer(neartest_path);
    return neartest_path;
}
//(1U<<0)