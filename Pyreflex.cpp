#include "Pyreflex.h"

Pyreflex::Pyreflex()
{
    this->loadcount = _PyCfg->CountSectionA();
}
Pyreflex::~Pyreflex()
{

}

bool Pyreflex::_Py_load_()
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
bool Pyreflex::_Py_excut(Pyreflex::CPRA analysis, const std::string& ex)
{
    Py_Initialize();
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyObject* out = NULL;
    const char* ans;
    std::string Path;
    std::string result_temp;
    wchar_t* res2;
    //LOG_writer(Now_time() + "ASK NewBing: " + Ins);
    res2 = multi_Byte_To_Wide_Char(ex);
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python')");
    pModule = PyImport_ImportModule(analysis.Py_Call_File.c_str());
    pFunc = PyObject_GetAttrString(pModule, analysis.Py_Call_Fun.c_str());
    pArg = Py_BuildValue("(u)", res2);
    out = PyObject_CallObject(pFunc, pArg);
    PyArg_Parse(out, "s", &ans);
    Send_StringTEXT_Message(UTF82Char(ans));
    Py_Finalize();
    return true;
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

Pyreflex::CInI_Py_Reflex_analysis  Pyreflex::_Py_Reflex_analysis(CInI::INI_MAP<std::string>& load_x)
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
            analysis.Py_Call_Fun = keyValue.second;
            break;
        case Py_Return_type:
            analysis.Py_Return_type = keyValue.second;
            break;
        }
    }
    return analysis;
}