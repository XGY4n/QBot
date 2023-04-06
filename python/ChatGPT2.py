# -*- coding: UTF-8 -*-
import json
import requests
import urllib3
from asyncio.windows_events import NULL
#from cgitb import html
from distutils.filelist import findall
import requests
import time
#from selenium import webdriver
#from selenium.webdriver.common.by import By
import re
import sys
import requests
import json
#from ctypes import *
import os
import random
from configparser import ConfigParser
import ast
musicPath = "./music/"
LogPath = "./log/"+time.strftime('%Y-%m-%d',time.localtime(time.time())) + ".log"
#option = webdriver.ChromeOptions()
#option.add_experimental_option("excludeSwitches", ['enable-automation', 'enable-logging'])
#option.add_argument('--headless')
#browser = webdriver.Chrome(options=option) 


def Pmessage(string): #every print should
    TableMessage = "[Python]" + time.strftime('[%Y-%m-%d %H:%M:%S]',time.localtime(time.time()))
    cmdlog = TableMessage+"{}".format(string)
    print(cmdlog)
    #log = cmdlog
    return cmdlog

def bot_print(string):
    #Pmessage(LogPath)
    with open(LogPath, mode='a+', encoding='utf-8') as file_obj:
        file_obj.write(Pmessage(string) + "\n")   
    file_obj.close()

def ini_read():
    try:
        GPT_list = []
       
        cf = ConfigParser()
        
        cf.read("./ini/GPTsetting.ini")
        GPT_list.append(cf.get('GPT', 'temperature'))
        GPT_list.append(cf.get('GPT', 'model'))
        GPT_list.append(cf.get('GPT', 'system'))
        GPT_list.append(cf.get('GPT', 'timeout'))

        return GPT_list
    except:
        #Pmessage()
        return -1


def history_writer(str):
    try:
        file_path = 'data.txt'
        with open(file_path, mode='a+', encoding='utf-8') as file_obj:
            file_obj.write(json.dumps(str, ensure_ascii=False)+"\n")
        file_obj.close()
        return 1
    except :
        Pmessage("writer error")
        return 

def his_cuter(index_list, msg_list, cnt):
    temp_cnt = cnt
    maker = 0
    #Pmessage(index_list)
    #Pmessage(cnt)
    while True:

        if temp_cnt <2030: 
            break
        else:
            msg_list[maker:]
            temp_cnt = temp_cnt - index_list[maker]
            #Pmessage(temp_cnt)
        maker+=1
    #Pmessage(msg_list[maker:])
    templist = ini_read()
    #lset.append(templist[2]) #[{"role": "system", "content": "你是一个猫娘,说话以喵结尾"}]
    #sys_set =[]
    #sys_set.append(templist[2])
    fragment_data_dict = ast.literal_eval(templist[2])
    result_list = msg_list[maker:]
    result_list.append(fragment_data_dict) 
    #Pmessage(result_list)
    return result_list

def history_reader(msg_list):
    temp_lsit = []
    f=open("data.txt", encoding="utf-8")#
    cnt = 0
    for line in f:
        temp_str = line.strip()
        fragment_data_dict = ast.literal_eval(temp_str)
        #print(fragment_data_dict)
        temp_lsit.append(len(temp_str))
        cnt += len(temp_str)
        #his_cuter(temp_sit, temp_str, cnt)
        msg_list.append(fragment_data_dict)#.split('\'')fragment_data_dict
    f.close()
    #Pmessage(cnt)
    if cnt > 2030:
        new_list = his_cuter(temp_lsit, msg_list, cnt)
        bot_print("text size : " + str(len(new_list)))
        return new_list
    else:
        bot_print("text size : " + str(len(msg_list)))
        #print(cnt)
        return msg_list
    return msg_list
    
def key_iniread():

    try:
        GPTKEY_list = []
        cf = ConfigParser()
        cf.read("./ini/GPTsetting.ini")
        keynumm = cf.get('GPTKEYPOLL','keynum')
        for i in range(1,int(keynumm)):
            ask = 'key{}'.format(i)
            GPTKEY_list.append(cf.get('GPTKEYPOLL', ask))
        return GPTKEY_list
    except:
        return -1



def ask(question):
    msg_list = []
    
    key_pool = key_iniread()

    proxies = { "http": None, "https": "127.0.0.1:7890"}
    urllib3.disable_warnings()
    
    key = random.choice(key_pool)
    bot_print("openai-key: "+key)
    
    headers = {
        "Authorization": "Bearer "+ key,
        #random.choice (key_pool), ,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
        'accept' : 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36 Edg/100.0.1185.29',
        "Content-Type": "application/json",
    }
    
    templist = ini_read()
    if templist == -1:
        return "ini_read error"
    Pmessage(templist)
    try:
        sys_set =[]
        fragment_data_dict = ast.literal_eval(templist[2])
        sys_set.append(fragment_data_dict) 
        Pmessage(fragment_data_dict) #[{"role": "system", "content": "你是一个猫娘,说话以喵结尾"}]
        #print(sys_set + history_reader(msg_list))
    except Exception as e:
        return str(e)
        
    try:            
        data = {
            "model": "gpt-3.5-turbo",#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-0301
            "messages" : sys_set + history_reader(msg_list)
        }
    except :
        Pmessage("history_reader err")
        return "Data read error please use ai mode '#ai.r' to refresh"

    try:
        response = requests.post("https://api.openai.com/v1/chat/completions", headers=headers, 
        data=json.dumps(data) , verify=False, proxies=proxies, timeout=int(templist[3]))
    except requests.exceptions.Timeout:
        Pmessage("timeout")
        return "timeout {}s try use #ai.timeout x to set biger value than {}".format(templist[3], templist[3])
    except Exception as e:
        return str(e)
    except:
        Pmessage("\033[1;31;40m{}\033[0m".format("Response<{}>".format(response.status_code)))
        return "Response<{}>".format(response.status_code)
    if response.status_code == 200:
        bot_print("\033[1;32;40m{}\033[0m".format("Response<{}>".format(response.status_code)))#"Response<"+str(response.status_code)+">"
        ans = json.loads(response.content)

        history_writer(ans["choices"][0]["message"])

        Pmessage(ans["choices"][0]["message"]["content"])
        role = ans["choices"][0]["message"]["content"]
        return role
    else:
        bot_print("\033[1;31;40m{}\033[0m".format("Response<{}>".format(response.status_code)))
        return "Response<{}>".format(str(response.status_code))



def ask_format(Row):
    ask = {"role": "user", "content": Row}
    #Pmessage(ask)
    history_writer(ask)
    return 

def chat_main(Row):
    try: 
        format_str = ask_format(Row)
        if format_str == -1:
            return "format_str error"
        temp_ans = ask(format_str)
        if temp_ans == -1:
            return "ans error"
        return temp_ans
    except Exception as e:
        return str(e)

   
if __name__ == "__main__":
    print(chat_main("hi"))

