#pragma once
#include<string>
enum Self_mode {
    BOT_SELF_RESTART,
    BOT_SEVER_RESTART,
    BOT_TUNNEL_RESTART,
    BOT_KILL,
    take_place

};
typedef enum Self_mode Sf_mode;

enum  Self_mode_Status_code {
    SELF_INS_NULL,
    SELF_RESTART_SUCCESS,
    SEVER_RESTART_SUCCESS,
    SEVER_EXISTS,
    SEVER_RESTART_FAIL,
    TUNNEL_RESTART_FAIL,
    TUNNEL_RESTART_SUCCESS,
    TUNNEL_EXISTS,
    Self_EXECUT_SEUCCESS,
    

    Self_KILL
};
typedef enum Self_mode_Status_code Sf_Status_code;
DWORD Sever_run_check(std::wstring name);
Sf_Status_code Self_Mode_main(std::string Instructions, std::string QQnumber);