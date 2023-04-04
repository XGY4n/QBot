import json
import requests
import urllib3
from asyncio.windows_events import NULL
from cgitb import html
from distutils.filelist import findall
import requests
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
import re
import sys
import requests
import json
from ctypes import *
import os
from configparser import ConfigParser

musicPath = "D:\\pojt\\QQbot\\music\\"
LogPath = "D:\\pojt\\QQbot\\log\\"+time.strftime('%Y-%m-%d',time.localtime(time.time())) + ".log"
#option = webdriver.ChromeOptions()
#option.add_experimental_option("excludeSwitches", ['enable-automation', 'enable-logging'])
#option.add_argument('--headless')
#browser = webdriver.Chrome(options=option) 

def Pmessage(string): #every print should
    TableMessage = "[Python]" + time.strftime('[%Y-%m-%d %H:%M:%S]',time.localtime(time.time())) 
    print(TableMessage + string)  
    log = TableMessage + string
    return log

def bot_print(string):
    with open(LogPath, mode='a+', encoding='utf-8') as file_obj:
        file_obj.write(Pmessage(string) + "\n")   
    file_obj.close()

def ini_read():

    GPT_list = []
    #file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../ini/GPTsetting.ini")
    cf = ConfigParser()
    cf.read('D:\\pojt\\QQbot\\ini\\GPTsetting.ini', encoding='utf-8')
    GPT_list.append(cf.get('GPT', 'temperature'))
    GPT_list.append(cf.get('GPT', 'model'))
    print(GPT_list)
    return GPT_list


def chat(question):
    try:
        setting = ini_read()
    except Exception as e:
        print(e)
    try:
        url = 'https://api.openai.com/v1/completions'
        # url = 'http://cgt.jahwaec.com'https://api.openai.com/v1/completions
        header = {'Content-type': 'application/json',
                'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
                'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36 Edg/100.0.1185.29',
                'Authorization':   "Bearer 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"} # �A��chatgtp key
        data = {
            'model': setting[1],#'text-davinci-003',#str(setting[1]),
            'prompt': 'Human:' + question,
            # 'prompt': question,
            'temperature': float(setting[0]),#0.9,
            'max_tokens': 2500,
            'top_p': 1,
            'frequency_penalty': 0.0,
            'presence_penalty': 0.6,
            'stop': ["Human:", "AI:"],
        }
        urllib3.disable_warnings()
        response = requests.post(url=url, data=json.dumps(data), headers=header, verify=False)
        res = ini
        answer = res["choices"][0]["text"].strip()
        #bot_print(res)
        return answer
    except Exception as e:
        print(e)
        return 'Brokenn'
 
 

def ChatGTP_main(ask):
    ask_temp = ask
    ans = chat(ask_temp)
    print(ans)
    return ans
