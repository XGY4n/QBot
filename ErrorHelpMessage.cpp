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
        "������ʹ���ֲ�\n\
        1.���л�����ʹ�� # ��ͷ���ַ���\n\
        2.���ڿ��Ź���Ϊ#v. /#m. /#rxdn /#dice /#p. ָ��ı������: # + ָ��ͷ. + ָ����Ϣ\n\
            ����1:����BվidΪ114514��������ע��vtbָ��Ϊ #v.114514 (����.txt)\n\
            ����2:���������Ƹ�����֮��ָ��Ϊ #s.��֮�� (����.mp3)\n\
            ����3:���������������ָ��Ϊ #r2d6 (���ض�Ӧֵ),�������Ӹ���Ӧ��С��5,����Ӧ��С��999999����ᱨ��\n\
            ����4:1v1ҡ����С��Ϸ #dice , �� #join ������Ϸ,����������Ϸģʽʱ���� #help ��ȡ����ģʽ����\n\
            ����5:�����˿���Ϸ #p.x ,����xΪ�����,�� #join ������Ϸ,�����˿���Ϸģʽʱ���� #help ��ȡ�˿�ģʽ����\n\
        3.����������Ƥ��û��ָ��ͷ��ָ��:#ͼƬ(�ظ�һ��ͼƬ),#�����Ի���(�ظ������ԵĻ�,����û��Ӷ�Ӧ�ظ��⽫����No such function)\n\
        4.���������������� \n\
            1.����Ϊ������\n\
            2.���ֻ����������û�ѵ�Ԥ�ڵ���������ϸ����(�� �ո� ���� - ����)����ԭ���Ե�����-����-����ר�������� ��:��֮��-�m���ƴ�-<<TOKYO-POPCHRISTMAS2021>>";

           return  HelpMessage;
}

std::string Send_Error_Message()
{
    std::string ErrorMessage = "�ļ�ץȡ������߳�������˴���,��@xgt��������/�����";
    return ErrorMessage;
}

std::string Send_WrongInput_Message()
{
    std::string WrongInputMessage = "ִ��ʧ��!ָ��ͷ��ȷ��ָ��ֵ�����Ϲ���,����#�� + help�鿴�����������/����";
    return WrongInputMessage;
}

//std::string Send_Error_Message()

std::string Send_Wait_Message()
{
    std::string WaitMessage = "��~/����";
    return WaitMessage;
}

std::string NO_Function()
{
    std::string NoFunction = " /NO NO such function";
    return NoFunction;
}

