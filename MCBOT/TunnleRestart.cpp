#include"SendMessage.h"
#include"ChineseString.h"
#include"ErrorHelpMessage.h"
#include"Timelog.h"
#include"ini.h"
#include"McServer.h"
#include"SelfMode.h"
#include"ServerStart.h"
#include "TunnleRestart.h"

std::string TR_TunPlan_Peel(std::string Row_Ins)
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

void Tunnel_restart(std::string Row_Ins)
{
	std::string TunnlePlan = TR_TunPlan_Peel(Row_Ins);
	if (TunnlePlan.size() > 1)
	{
		Send_StringTEXT_Message("tunnelplan input error should be 1 byte uppercase");
		return;
	}
	std::string Tunnle = Mc_TunnelPlan_Check(TunnlePlan);
	if (Tunnle.size() != 0)
	{
		int CpolarPid = Sever_run_check(L"cpolar.exe");
		if (CpolarPid != 0)
		{
			Send_StringTEXT_Message("tunnel exist");
			system("taskkill /f /IM cpolar.exe" );//((std::to_string(CpolarPid))).c_str()
			Send_StringTEXT_Message("kill end tunnel restarting... please wait");
		}
		else
		{
			Send_StringTEXT_Message("tunnel not exist");
			Send_StringTEXT_Message("tunnel starting... please wait");
		}
		std::string Tunnle = Mc_TunnelPlan_Check(TunnlePlan);
		start_Tunnel(Tunnle, Ipv4Str());
	}	
	else
		Send_StringTEXT_Message("tunnelplan not find reinput");

	if (Sever_run_check(L"cpolar.exe") != 0)
		Send_StringTEXT_Message("tunnelplan restart successful " + Tunnle.substr(Tunnle.find("=") + 1, Tunnle.size()));	
	else
		Send_StringTEXT_Message("tunnelplan restart no successful");

	return;
}