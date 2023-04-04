
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
#include <map>
#include <processthreadsapi.h>
#include <tlhelp32.h>
#include <conio.h>
#include <shellapi.h>
#include <Iphlpapi.h>

#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"ini.h"
#include"McServer.h"
#include"SelfMode.h"
#include"ServerStart.h"

std::string Mc_Ver_Peel(std::string Row_Ins)
{
	std::string TempVerPeel;
	for (int i = 9; i < Row_Ins.size(); i++)
	{
		if (Row_Ins[i] == 32)
			break;
		TempVerPeel = TempVerPeel + Row_Ins[i];
	}
	return TempVerPeel;

}



std::string Mc_TunPlan_Peel(std::string Row_Ins)
{
	std::string TempTunPlan;
	for (int i = Row_Ins.size() - 1; i != -1; i--)
	{
		if (Row_Ins[i] == 32)
			break;
		TempTunPlan = TempTunPlan + Row_Ins[i];
	}
	return TempTunPlan;
}




std::string Mc_Server_Path_Check(std::string McVer)
{
	std::string ServerPath;
	ServerPath = McVer_Check(McVer);
	if (ServerPath.size() != 0)
		return ServerPath;
	else
		Send_StringTEXT_Message(" Minecraft version not exist ");

	return ServerPath;
}


std::string Mc_Server_Tunnel_Check(std::string TunnelPaln)
{
	std::string Tunnel;
	Tunnel = Mc_TunnelPlan_Check(TunnelPaln);
	if (Tunnel.size() != 0)
		return Tunnel;
	else
		Send_StringTEXT_Message("Tunnel message not match use default tunnelplan");
	Tunnel = Mc_TunnelPlan_Check("A");
	return Tunnel;
}



std::string Ipv4Str()
{
	std::string user_ip;
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//记录网卡数量
	int netCardNum = 0;
	//记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		delete pIpAdapterInfo;
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{

		while (pIpAdapterInfo)//Killer(R) Wi-Fi 6 AX1650i 160MHz Wireless Network Adapter (201NGW)
		{
			std::string temp = pIpAdapterInfo->AdapterName;
			if (temp.compare("{34C4F700-86BD-42AF-BDAB-3285B2A8796B}") == 0)
			{
				IP_ADDR_STRING* pIpAddrString = &(pIpAdapterInfo->IpAddressList);
				do
				{
					//cout << "IP  " <<  << endl;
					user_ip = pIpAddrString->IpAddress.String;
					pIpAddrString = pIpAddrString->Next;
				} while (pIpAddrString);
				pIpAdapterInfo = pIpAdapterInfo->Next;
			}
			else
				pIpAdapterInfo = pIpAdapterInfo->Next;
		}

	}
	//释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}
	return user_ip;
}

bool start_Tunnel(std::string tunnel, std::string ipv4)
{
	HINSTANCE re_stat;
	std::string cpolarPath = "start D:\\cploar\\cpolar.exe ";
	std::string Tunnelstart = tunnel + " " + ipv4 +":25565";//Tunnelstart.c_str()
	cpolarPath = cpolarPath + Tunnelstart;
	std::cout << cpolarPath << std::endl;
	system(cpolarPath.c_str());
	Sleep(3000);
	return true;
}


bool isReleasePort(unsigned short usPort)
{
	WSADATA wsData;
	::WSAStartup(MAKEWORD(2, 2), &wsData);//
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(usPort);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	int ret = ::bind(s, (LPSOCKADDR)&addr, sizeof(addr));
	if (ret != 0)
	{
		closesocket(s);
		::WSACleanup();
		return true;
	}
	closesocket(s);
	::WSACleanup();
	return false;
}


bool start_serverbat(std::string ServerPath)
{
	HINSTANCE re_stat;

	if (Sever_run_check(L"cpolar.exe") == 0)
	{
		Send_StringTEXT_Message("Tunnel start false please change or add Tunnelplan");
		return false;
	}
	if (Sever_run_check(L"javaw.exe") != 0 || Sever_run_check(L"java.exe") != 0)
	{
		Send_StringTEXT_Message("Server already start !");
		return false;
	}
	//else if()
	re_stat =
		ShellExecuteA(NULL, "open", ServerPath.c_str(),
			NULL, NULL, SW_SHOW);
	Send_StringTEXT_Message("Server loading...please wait");
	while (true)
	{
		if (isReleasePort(25565))
			break;
		Sleep(5000);
	}
	return true;
}



Mc_Status_code Mc_Server_Start(std::string Ins)
{
	Mc_Status_code ex_end = MC_EXECUT_SEUCCESS;
	std::string McVer;
	std::string TunnelPlan;
	std::string ServerPath;
	std::string TunnelMsg;
	std::string IPV4 = Ipv4Str();
	std::string serverIP;
	//25565

	McVer = Mc_Ver_Peel(Ins);
	TunnelPlan = Mc_TunPlan_Peel(Ins);
	ServerPath = Mc_Server_Path_Check(McVer);
	if (ServerPath.size() == 0)
		return ex_end;
	TunnelMsg = Mc_Server_Tunnel_Check(TunnelPlan);
	if (TunnelMsg.size() == 0)
		return ex_end;

	serverIP = TunnelMsg.substr(TunnelMsg.find("=") + 1, TunnelMsg.size());
	std::cout << ServerPath << " " << TunnelMsg << " " << serverIP << std::endl;

	if (start_Tunnel(TunnelMsg, IPV4))
		if (start_serverbat(ServerPath))
			Send_StringTEXT_Message(serverIP);

	return ex_end;
		
}