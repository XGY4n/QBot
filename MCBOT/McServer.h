#pragma once
#include<string>

enum Minecraft_mode {
    MC_SERVER_RESTART,
    MC_TUNNEL_RESTART,
    MC_SERVER_START,
    MC_SERVER_HELP,
    MC_SERVER_KILL,
    MC_take_place

};
typedef enum Minecraft_mode Mc_mode;

enum  Minecraft_mode_Status_code {
    MC_INS_NULL,
    MC_RESTART_SUCCESS,
    MC_SEVER_RESTART_SUCCESS,
    MC_SEVER_EXISTS,
    MC_SEVER_RESTART_FAIL,
    MC_TUNNEL_RESTART_FAIL,
    MC_TUNNEL_RESTART_SUCCESS,
    MC_TUNNEL_EXISTS,
    MC_EXECUT_SEUCCESS,


    MC_KILL
};
typedef enum Minecraft_mode_Status_code Mc_Status_code;

Mc_Status_code Mc_Mode_main(std::string Instructions, std::string QQnumber);