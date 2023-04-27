#pragma once
#include <string>
#include <map>
#include <iostream>
#include "CInI.h"
#include "Python.h"
#include "ChineseString.h"
#include "SendMessage.h"
#include "Botlog.h"
class Pyreflex
{
public:
    typedef struct CInI_Py_Reflex_analysis
    {
        std::string Py_Call_Head;
        std::string Py_Call_Path;
        std::string Py_Call_File;
        std::string Py_Call_Fun;
        std::string Py_Return_type;
    }CPRA;
    enum KeyValue {
        Py_Call_Head,
        Py_Call_Path,
        Py_Call_File,
        Py_Call_Fun,
        Py_Return_type
    };

    std::map<std::string, KeyValue> keyMap = {
        {"Py_Call_Head", Py_Call_Head},
        {"Py_Call_Path", Py_Call_Path},
        {"Py_Call_File", Py_Call_File},
        {"Py_Call_Fun", Py_Call_Fun},
        {"Py_Return_type", Py_Return_type}
    };
public:
    Pyreflex();
    ~Pyreflex();
public:
    bool _Py_load_();
    CInI_Py_Reflex_analysis _Py_Reflex_analysis(CInI::INI_MAP<std::string>& load_x);
    bool _Py_check(CInI::INI_MAP<std::string>& load_x, const std::string& ins_full);
    bool Pyreflex::_Py_cut(std::pair<std::string, std::string>& Excc, std::string ins_full);
    bool _Py_excut(CPRA analysis, const std::string& ex);

public:
    int loadcount;
    std::unique_ptr<CInI> _PyCfg{ new CInI{"./ini/pyload.ini"} };
    std::map<std::string, CInI::INI_MAP<std::string>> reflex_map;
    std::vector<CInI::INI_MAP<std::string>> result;

};

extern std::unique_ptr<Pyreflex> _Py_Reflex;
