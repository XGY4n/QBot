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
def moive_main(name):
    option = webdriver.ChromeOptions()
    option.add_experimental_option("excludeSwitches", ['enable-automation', 'enable-logging'])
    option.add_argument('--headless') 
    path = "C:\\Users\\DELL\\Desktop\\code\\bili\\chromedriver.exe"
    browser = webdriver.Chrome(chrome_options=option,executable_path=path)
    search = name
    URLsearch = "https://www.tuoluoy.com/vodsearch/-------------.html?wd={}".format(search)
    browser.get(URLsearch)
    time.sleep(0.5) 
    try:
        text = browser.find_element(By.XPATH,"/html/body/div[1]/div[1]/div[3]/ul[1]/li/a")
        rowid = text.get_attribute("outerHTML")
        #print(rowid)          
        key = re.compile('(?<=" href=").+(?=" title=")')  
        id = re.findall(key,rowid)
        for link in id:
            html_link = link
            #print(html_link)
        final_html = "https://www.tuoluoy.com/{}".format(html_link)        
    except:
        final_html = ""
    return final_html