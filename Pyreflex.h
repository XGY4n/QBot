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
        std::string Py_Call_Func;
        std::string Py_Return_type;
    }CPRA;

    enum KeyValue {
        Py_Call_Head,
        Py_Call_Path,
        Py_Call_File,
        Py_Call_Fun,
        Py_Return_type
    };

    enum PyReturnType {
        STRING,
        WSTRING,
        FILE,
        UNKNOWN
    };

    std::map<std::string, PyReturnType> ReturnTypeMap = {
        {"str", STRING},
        {"wstr", WSTRING},
        {"file", FILE},
        {"undefine", UNKNOWN},
    //{"Py_Return_type", Py_Return_type}
    };

    std::map<std::string, KeyValue> keyMap = {
        {"Py_Call_Head", Py_Call_Head},
        {"Py_Call_Path", Py_Call_Path},
        {"Py_Call_File", Py_Call_File},
        {"Py_Call_Func", Py_Call_Fun},
        {"Py_Return_type", Py_Return_type}
    };

public:
    Pyreflex();
    ~Pyreflex();

    
public:
    bool initializePython();

    bool testPythoninitialize();

    CInI_Py_Reflex_analysis _Py_Reflex_analysis(CInI::INI_MAP<std::string>& load_x);

    bool _Py_check(CInI::INI_MAP<std::string>& load_x, const std::string& ins_full);

    bool Pyreflex::_Py_cut(std::pair<std::string, std::string>& Excc, std::string ins_full);

    bool executePythonReflex(CPRA analysis, const std::string& execute);

    int getReflexNumb();

private:
    template<typename CharT>
    std::basic_ostream<CharT>& getReturnStreamType()
    {
        if constexpr (std::is_same_v<CharT, char>)
        {
            return std::cout;
        }
        else if constexpr (std::is_same_v<CharT, wchar_t>)
        {
            return std::wcout;
        }
    }

private :

    //void executePythonReflex();
    void convertFromPython(Pyreflex::CPRA analysis );
    void convertToPython();
    bool getPythonObject(Pyreflex::CPRA& analysis, PyObject*& pFunc, PyObject* pModule);
    bool callPythonFunction(PyObject*& out, PyObject* pFunc, PyObject* pArg);
    bool loadPythonModule(Pyreflex::CPRA& analysis, PyObject*& pModule);
    void returnPythonreflex(std::string return_type, const std::string& reflex_str, wchar_t* reflex_wstr);

public:
    int loadcount;
    std::unique_ptr<CInI> _PyCfg{ new CInI{"./ini/pyload.ini"} };
    std::map<std::string, CInI::INI_MAP<std::string>> reflex_map;
    std::vector<CInI::INI_MAP<std::string>> result;

};

extern std::unique_ptr<Pyreflex> _Py_Reflex;
