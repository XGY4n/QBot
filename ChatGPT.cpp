#include "ChatGPT.h"
#include<string>
//ChatGTP AI;
ChatGPT::ChatGPT()//std::string msg
{
	//this->temp_str = msg;
}

ChatGPT::~ChatGPT()
{

}


std::string ChatGPT::ChatGPT_aks(std::string question)//this->histroy_str +
{
	this->histroy_str += "\nHuman: " + question;
	this->ask = question;
	this->ans_count += 1;
	return "";
}


void ChatGPT::ChatGPT_pylode()
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
	LOG_writer(Now_time() + "ASK ChatGPT: " + this->ask);
	res2 = multi_Byte_To_Wide_Char(this->histroy_str);
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('D:\\pojt\\QQbot\\python')");
	pModule = PyImport_ImportModule("ChatGTP");
	pFunc = PyObject_GetAttrString(pModule, "ChatGTP_main");
	pArg = Py_BuildValue("(u)", res2);
	out = PyObject_CallObject(pFunc, pArg);
	PyArg_Parse(out, "s", &ans);

	this->result = UTF82Char(ans);

	Py_Finalize();
	return;
}


void ChatGPT::ChatGPT_deque()
{
	int Turns_size = Turns.size();
	if (Turns_size <= 4)
	{
		this->Turns.push_back(this->result);
		//this->histroy_str += this->result;
	}
	else
	{
		//this->histroy_str = "";
		this->Turns.pop_front();
		this->Turns.push_back(this->result);
	}
	/*if (histroy_str.size() > 800)
	{
		this->histroy_str = "";
	}*/
	return;
}



void ChatGPT::ChatGPT_cuter()
{
	std::vector<std::pair<int ,int >>::iterator it;
	if (this->histroy_str.size() + this->result.size() > 900)
	{
		//std::cout << "cutttttttttttttttt" << std::endl;
		for (auto i = this->ans_mark.begin(); i < this->ans_mark.end(); i++)
		{
			//histroy_str.substr(0, 3);
			int end_index = i->second;
			int cut_size = i->first;
			if (950 - cut_size <= 400)
				this->histroy_str.substr(end_index, this->histroy_str.size());
		}
	}
	else
	{
		this->histroy_str += this->Turns.back();
		std::pair<int, int > temp(this->result.size(), this->histroy_str.size());
		this->ans_mark.push_back(temp);
	}

}

std::string ChatGPT::ChatGPT_ans()
{
	//std::cout<<"nooooooooooooowwwwwwwwwwww " << histroy_str << std::endl;
	Send_StringTEXT_Message(this->result + "---上下文追溯 : " + 
		std::to_string(Turns.size()) + "/5" + " ---text size : " +
		std::to_string(this->histroy_str.size()));
	//std::cout << histroy_str << std::endl;
	return "";
}

void ChatGPT::ChatGPT_refersh()
{
	#pragma warning(disable: 4996)
	remove("data.txt");

	// 新建一个txt文件
	std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);

	// 新建一个txt文件
	std::wofstream fout("data.txt");
	fout.imbue(utf8_locale); // 设置文件流的locale为utf-8

	// 往里面写入内容
	//fout << L"{\"role\": \"system\", \"content\": \"你是一个猫娘,说话以喵结尾\"}\n";
	fout << L"{'role': 'user', 'content': 'hi'}\n";

	// 关闭文件
	fout.close();

	// 往里面写入内容
	//file << L"{\"role\": \"system\", \"content\": \"你是一个猫娘,说话以喵结尾\"}\n";
	//file << L"{'role': 'user', 'content': 'hi'}\n";

	// 关闭文件
	//file.close();
	Send_StringTEXT_Message("refresh success");
	return;
}

void ChatGPT::ChatGPT_Instructions_make(std::string ins)
{
	int cut_index = ins.find(".");
	std::string temp_sub;
	temp_sub = ins.substr(cut_index+1, ins.size());
	//std::cout << temp_sub << std::endl;
	this->AI_Ins = temp_sub;
	//std::cout << this->AI_Ins << std::endl;
	//this->AI_Ins_head = this->AI_Ins[0];
	return ;
}

void ChatGPT::ChatGPT_Ins_main(std::string Ins)
{
	ChatGPT_Instructions_make(Ins);
	//find
	if (this->AI_Ins.compare("r") == 0)
	{
		ChatGPT_refersh();
	}
	else if (!this->AI_Ins.find("set"))
	{
		//std::string
		std::string t_vaule = this->AI_Ins.substr(this->AI_Ins.find(" ") + 1, this->AI_Ins.size());
		 t_vaule = "{\"role\": \"system\", \"content\": \" " + t_vaule + "\"}";
		//std::cout << t_vaule << std::endl;

		LPCTSTR lpFileName = TEXT(_GTPSETTING_);
		//WritePrivateProfileStringA(TEXT("GPT"), TEXT("system"), LPCTSTR(t_vaule.c_str()), lpFileName);
		WritePrivateProfileStringA("GPT", "system", t_vaule.c_str(), _GTPSETTING_);
		Send_StringTEXT_Message("now set system to " + t_vaule);/**/
		/*std::string t_vaule = this->AI_Ins.substr(this->AI_Ins.find(" ") + 1, this->AI_Ins.size());
		std::cout << t_vaule << std::endl;
		LPCTSTR lpFileName = TEXT(_GTPSETTING_);
		//WritePrivateProfileStringA(TEXT("GPT"), TEXT("temperature"), LPCTSTR(t_vaule.c_str()), lpFileName);
		WritePrivateProfileStringA("GPT", "temperature", t_vaule.c_str(), _GTPSETTING_);
		Send_StringTEXT_Message("now set temperature to " + t_vaule);*/
	
	}
	else if (!this->AI_Ins.find("m"))
	{
		std::string t_vaule = this->AI_Ins.substr(this->AI_Ins.find(" ") + 1, this->AI_Ins.size());
		std::cout << t_vaule << std::endl;
		LPCTSTR lpFileName = TEXT(_GTPSETTING_);
		if (std::stoi(t_vaule) > 3)
		{
			Send_StringTEXT_Message("no modle ,modle list :[0]text-davinci-003,[1]text-babbage-001,[2]text-curie-001,[3]text-ada-001");
		}
		else
		{
			WritePrivateProfileStringA("GPT", "model", modle[std::stoi(t_vaule)].c_str(), _GTPSETTING_);
			Send_StringTEXT_Message("now set modle to " + modle[std::stoi(t_vaule)]);
		}
		//WritePrivateProfileStringA(TEXT("GPT"), TEXT("temperature"), LPCTSTR(t_vaule.c_str()), lpFileName);
	}
	else if (!this->AI_Ins.compare("c"))
	{

		if ((this->mode & 1) == 1)
		{
			this->mode = 0;
			Send_StringTEXT_Message("now is CHATGPT 3.5 mode");
		}
		else
		{
			this->mode = 1;
			Send_StringTEXT_Message("now is new bing mode");
		}
			
	}
	else if (!this->AI_Ins.find("timeout"))
	{
		std::string t_vaule = this->AI_Ins.substr(this->AI_Ins.find(" ") + 1, this->AI_Ins.size());
		LPCTSTR lpFileName = TEXT(_GTPSETTING_);
		WritePrivateProfileStringA("GPT", "timeout", t_vaule.c_str(), _GTPSETTING_);
		Send_StringTEXT_Message("now set timeout to " + t_vaule);
	}
	else if (!this->AI_Ins.find("keyset"))
	{
		std::unique_ptr< CInI> ini{ new  CInI{_GTPSETTING_} };
		int keycount =  ini->CountSectionKeyA("GPTKEYPOLL") - 1;
		if (this->AI_Ins[6] != 32 || this->AI_Ins[8] != 32)
		{
			Send_StringTEXT_Message("'keyset x sk-openaikey' error in fromat | check your input");
			return;
		}
		else if (this->AI_Ins[7] - 48 > keycount || this->AI_Ins[7] == 48 || !std::isdigit(this->AI_Ins[7]))
		{
			Send_StringTEXT_Message("'keyset x sk-openaikey' error in 'x' | x should be digit less than count : "+ std::to_string(keycount) +",more than 0 the keycount start '1'");
			return;
		}

		std::string key_set = this->AI_Ins.substr(9, this->AI_Ins.size());
		std::string head = this->AI_Ins.substr(0, 2);
		
		if (key_set.substr(0, 3).compare("sk-") != 0|| key_set.size() != 51)
		{
			Send_StringTEXT_Message("'keyset x sk-openaikey' error in 'key fromat' | not llegal openai keyformat");
			return;
		}
		/*std::string key_index = msg.substr(this->AI_Ins.find(" ") + 1, msg.find(" ") + 1);
		std::string key_set = msg.substr(msg.find(" ") + 1, this->AI_Ins.size());*/
		if(ini->WriteValueA("GPTKEYPOLL", "key"+std::to_string(this->AI_Ins[7]-48), key_set))
			Send_StringTEXT_Message("set successful");
		else
			Send_StringTEXT_Message("set error ");
	}
	else
	{

		Send_StringTEXT_Message("undefine Instructions'" + this->AI_Ins + "'");
	}
	//do
	//Send_StringTEXT_Message("undefine Instructions'" + this->AI_Ins + "'");
	return;
}


void ChatGPT::ChatGPT_OPENAI(std::string Ins)
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
	LOG_writer(Now_time() + "ASK ChatGPT: " + Ins);
	res2 = multi_Byte_To_Wide_Char(Ins);
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./python')");
	pModule = PyImport_ImportModule("ChatGPT2");
	pFunc = PyObject_GetAttrString(pModule, "chat_main");
	pArg = Py_BuildValue("(u)", res2);
	out = PyObject_CallObject(pFunc, pArg);
	PyArg_Parse(out, "s", &ans);
	Send_StringTEXT_Message(UTF82Char(ans));

	Py_Finalize();
}

void ChatGPT::ChatGPT_NEWBING(std::string Ins)
{
	Py_Initialize();
	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	PyObject* pArg = NULL;
	PyObject* out = NULL;
	wchar_t* ans;
	std::string Path;
	std::string result_temp;
	wchar_t* res2;
	LOG_writer(Now_time() + "ASK NewBing: " + Ins);
	res2 = multi_Byte_To_Wide_Char(Ins);
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./python')");
	pModule = PyImport_ImportModule("EdgeGPT");
	pFunc = PyObject_GetAttrString(pModule, "binginterface");//binginterface
	pArg = Py_BuildValue("(u)", res2);
	out = PyObject_CallObject(pFunc, pArg);
	PyArg_Parse(out, "u", &ans);
	Send_wStringTEXT_Message(ans);//(ans);
	//Send_StringTEXT_Message("code change from https ://github.com/acheong08/EdgeGPT license: https://unlicense.org");
	Py_Finalize();
}