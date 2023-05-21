#include "Pyreflex.h"

Pyreflex::Pyreflex()
{
    this->loadcount = _PyCfg->CountSectionA();
}
Pyreflex::~Pyreflex()
{

}

bool Pyreflex::testPythoninitialize()
{
    std::unique_ptr<CInI> Py_ini{ new CInI{"./ini/Pyloadsetting.ini"} };
    //Py_ini->FindValueW<std::wstring>(L"PYTHONHOME", L"HOME");
    std::cout << Py_ini->FindValueA<std::string>("PYTHONHOME", "HOME") << std::endl;
    std::string py_hometemp = Py_ini->FindValueA<std::string>("PYTHONHOME", "HOME");
    std::string py_lib = Py_ini->FindValueA<std::string>("PYTHONLIB", "LIB");
    std::cout << py_lib << std::endl;

    Py_SetPythonHome(multi_Byte_To_Wide_Char(py_hometemp));

    Py_Initialize();

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    if (!Py_IsInitialized())
    {
        PyErr_Print();
        return 0;
    }
    PyRun_SimpleString("print('PYTHON TEST PASS STAGE 1')\n");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python')");

    pModule = PyImport_ImportModule("pyloadtest");
    if (pModule == NULL)
    {
        PyErr_Print();
        return 0;
    }
    Py_Finalize();
    return 1;
}

bool Pyreflex::initializePython()
{
    std::unique_ptr<Botlog> log{ new Botlog{} };
    this->result = this->_PyCfg->ReadAllA();
    for (const auto& iniSection : this->result)
    {
        //std::cout << "[" << iniSection.section << "]" << std::endl;
        for (const auto& keyValue : iniSection.parameters)
        {
            if (keyValue.first.compare("Py_Call_Head") == 0)
            {
                // reflex_map.first = keyValue.second;
                // reflex_map.
                reflex_map.insert(std::make_pair(keyValue.second, iniSection));
            }
            log->Record(Botlog::LEVEL_SUCCESS, Botlog::OWNER_SELF, keyValue.first + "=>" + keyValue.second);
            //std::cout << keyValue.first << "=" << keyValue.second << std::endl;
        }
    }
    return true;
}


bool Pyreflex::getPythonObject(Pyreflex::CPRA& analysis, PyObject*& pFunc, PyObject* pModule)
{
    pFunc = PyObject_GetAttrString(pModule, analysis.Py_Call_Func.c_str());
    if (pFunc == NULL) {

        PyErr_Print();
        Send_StringTEXT_Message("PyObject_GetAttrString ERROR");
        return false;
    }
    return true;
}

bool Pyreflex::callPythonFunction(PyObject*& out, PyObject* pFunc, PyObject* pArg)
{
    out = PyObject_CallObject(pFunc, pArg);
    if (out == NULL) {
        PyErr_Print();
        Send_StringTEXT_Message("PyObject_CallObject ERROR");
        return false;
    }

    return true;
}

bool Pyreflex::loadPythonModule(Pyreflex::CPRA& analysis,PyObject*& pModule)
{
    PyRun_SimpleString("import sys");

    PyRun_SimpleString("sys.path.append('./python')");

    pModule = PyImport_ImportModule(analysis.Py_Call_File.c_str());
    if (pModule == NULL) {
        PyErr_Print();
        Send_StringTEXT_Message("PyImport_ImportModule ERROR");
        return false;
    }
    return true;
}


bool convertFromPython(Pyreflex::CPRA analysis)
{
    
    return true;
}

void Pyreflex::returnPythonreflex(std::string return_type, const std::string& reflex_str ,wchar_t* reflex_wstr )
{
    Pyreflex::PyReturnType returntpye;
    //std::basic_ostream<CharT>& out = getOutputStream<CharT>();
    if (ReturnTypeMap.find(return_type) != ReturnTypeMap.end())
    {
        returntpye = ReturnTypeMap[return_type];
        switch (returntpye)
        {
            case STRING:
                Send_StringTEXT_Message(reflex_str);
                break;
            case WSTRING:
                Send_wStringTEXT_Message(reflex_wstr);
                break;
            case FILE:
                Send_StringTEXT_Message(reflex_str);
                break;
            case UNKNOWN:
                Send_StringTEXT_Message("return type not define");
            break;
        }
        return ;
    }
    else
    {
        return ;
    }
}


bool Pyreflex::executePythonReflex(Pyreflex::CPRA analysis, const std::string& execute)
{
    Py_Initialize();

    if (!Py_IsInitialized()){
        PyErr_Print();
        Send_StringTEXT_Message("Py_IsInitialized ERROR");
        return false;
    }

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;

    const char* ans_string = "";
    wchar_t* ans_wstring = L"";
    std::string Path;
    std::string result_temp;
    wchar_t* execute_buffer;
    int success ;


    execute_buffer = multi_Byte_To_Wide_Char(execute);

    if(!loadPythonModule(analysis, pModule))
        return false;
    if(!getPythonObject(analysis, pFunc, pModule))
        return false;

    pArg = Py_BuildValue("(u)", execute_buffer);

    if(!callPythonFunction(out, pFunc, pArg))
        return false;

    //import to overwriter
    if (!analysis.Py_Return_type.compare("str")|| !analysis.Py_Return_type.compare("file"))
        success = PyArg_Parse(out, "s", &ans_string);
    else if(!analysis.Py_Return_type.compare("wstr"))
        success = PyArg_Parse(out, "u", &ans_wstring);
    
    if (!success) {
        PyErr_Print(); 
        Send_StringTEXT_Message("PyArg_Parse ERROR");
        return false;
    }
    Py_Finalize();

    returnPythonreflex(analysis.Py_Return_type, ans_string, ans_wstring);
    return true ;

}

bool Pyreflex::_Py_cut(std::pair<std::string, std::string>& Excc, std::string ins_full)
{
    std::string _Call_Header;
    std::string _Call_Ex;
    int pos = ins_full.find(".");
    if (pos == std::string::npos)
        return false;
    _Call_Header = ins_full.substr(0, pos + 1);
    _Call_Ex = ins_full.substr(pos + 1);
    //std::cout << _Call_Header << " " << _Call_Ex << std::endl;
    //std::pair<std::string , std::string> Excc;
    Excc = std::make_pair(_Call_Header, _Call_Ex);
    return true;
}

bool Pyreflex::_Py_check(CInI::INI_MAP<std::string>& load_x, const std::string& Ex_Header)
{
    //std::cout << Ex_Header << std::endl;
    if (reflex_map.find(Ex_Header) != reflex_map.end())
    {
        load_x = reflex_map[Ex_Header];
        return true;
    }
    else
    {
        return false;
        // key does not exist
    }
}

Pyreflex::CInI_Py_Reflex_analysis Pyreflex::_Py_Reflex_analysis(CInI::INI_MAP<std::string>& load_x)
{
    Pyreflex::CPRA analysis;
    for (const auto& keyValue : load_x.parameters)
    {
        // std::cout<<"++++++++   "<< keyValue.first<<" -----"<< keyValue.second<< std::endl;
        switch (keyMap[keyValue.first])
        {
            case Py_Call_Head:
                analysis.Py_Call_Head = keyValue.second;
                break;
            case Py_Call_Path:
                analysis.Py_Call_Path = keyValue.second;
                break;
            case Py_Call_File:
                analysis.Py_Call_File = keyValue.second;
                break;
            case Py_Call_Fun:
                analysis.Py_Call_Func = keyValue.second;
                break;
            case Py_Return_type:
                analysis.Py_Return_type = keyValue.second;
                break;
        }
    }
    return analysis;
}

int Pyreflex::getReflexNumb()
{
    return this->loadcount;
}