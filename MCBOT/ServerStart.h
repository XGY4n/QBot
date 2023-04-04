#pragma once
#include"McServer.h"

Mc_Status_code Mc_Server_Start(std::string Ins);
bool start_Tunnel(std::string tunnel, std::string ipv4);
std::string Ipv4Str();