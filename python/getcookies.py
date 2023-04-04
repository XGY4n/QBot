from asyncio.windows_events import NULL
from cgitb import html
from distutils.filelist import findall
#import requests
import time
from selenium import webdriver
from selenium import webdriver
from selenium.webdriver.common.by import By
import urllib.request as urqt
import urllib.parse as urps
import os
import re
import sys
#import requests
import json


option = webdriver.ChromeOptions()
option.add_experimental_option("excludeSwitches", ['enable-automation', 'enable-logging'])
driver = webdriver.Chrome(chrome_options=option)


driver.get('https://music.163.com/')

driver.delete_all_cookies()
time.sleep(40)
with open('D:\\pojt\\QQbot\\x64\\Release\\cookies-163.txt','w') as f:
    f.write(json.dumps(driver.get_cookies()))

driver.close()



