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

def Pmessage():
    TableMessage = "[Python]" + time.strftime('[%Y-%m-%d %H:%M:%S]',time.localtime(time.time()))    
    return TableMessage


def bt_main(name):
    option = webdriver.ChromeOptions()
    option.add_experimental_option("excludeSwitches", ['enable-automation', 'enable-logging'])
    option.add_argument('--headless') 
    browser = webdriver.Chrome(chrome_options=option)
    search = name 
    URLsearch = "http://eclso.net/soso/{}.html".format(search)
    browser.get(URLsearch)
    time.sleep(0.5) 
    try:
        text = browser.find_element(By.XPATH,"/html/body/div[1]/div[4]/div/div[2]/div[1]/div[1]/div[1]/h3/a")
        rowid = text.get_attribute("outerHTML")
        browser.quit()
        key = re.compile('(?<="/cili/).+(?=.html")')  
        id = re.findall(key,rowid)
        for link in id:
            fmd5 = link   
            print(fmd5)
        bt = "magnet:?xt=urn:btih:"+fmd5
        print(Pmessage() + bt) 
    except:
        bt = ""
    return bt

