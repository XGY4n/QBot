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
#\b\w+(?="><b\b)

Pmessage = "[Python]" + time.strftime('[%Y-%m-%d %H:%M:%S]',time.localtime(time.time()))
musicPath = "D:\\pojt\\QQbot\\music\\"
cookie2 = {'_ntes_nnid=bfa1c4284263e4375b6c9d06d8634ff5,1625386968719; _ntes_nuid=bfa1c4284263e4375b6c9d06d8634ff5; NMTID=00OWlKc8wFVjfcqtEhmtqPhuzo6bQ4AAAF6cNQ5oQ; WEVNSM=1.0.0; WNMCID=bbgnqv.1625390594493.01.0; WM_TID=E2bvjX+rCodBAEVERFZ6vpE6pnSGMTiz; timing_user_id=time_tHHR4KE1K1; __snaker__id=AjrekHuuJgk9FTgJ; _9755xjdesxxd_=32; gdxidpyhxdE=fiXYTPawGo4K4ADWhirr72EM3u9vs9dWLrhq9BL5oGBzwN1528tcLWtHpHHSjTQWQQ8o+6MQBayI0bueQbI04Cy/GVnJixZDS2KAyncLjn45BU0\eYt9EVIthTwL0rjKBecQu\G6XVUSgqCduqHu3csiIZL4xPVXoHmujRcIp5b\iyQ7:1648274726684; ntes_kaola_ad=1; _iuqxldmzr_=32; MUSICIAN_COMPANY_LAST_ENTRY=1490643130_musician; WM_NI=KM6DiIpHyb6LFIwR10m8a5mF+FwsFUfoZGMgurIoSDtfuNLVEkwc3f7Cz6ZF3k51vjOvrSklyJi7iyZ3M75K63VQAbNhJSTHdKT7CAY0t4YAdSo2eY5oKbEVZiXpDBECVDg=; WM_NIKE=9ca17ae2e6ffcda170e2e6ee88f25da5e8b6daaa53bb9e8eb2d54a939a8a85b57bf6989684f959f68caea9b22af0fea7c3b92a8993faa5ec43b498b783b5488697b9b3b43cafe8afd6f04ee99ab994c55fa6b196a8d06db7ae8790d250b8babbafcf5e87b5b984b26ef59db6d7d94ef1b5fbd2f5628daabeb4ea68bb96a7d8ec739aed83d8b841f6ed9ab2c46a8eb886b4d744a8959cd8c24b9bf0bcd5dc4ba88da1d3e853f7b18583c85e9ab79891c74a879d9aa5e637e2a3; JSESSIONID-WYYY=VYsAmz9WrO5l8J4FYSXBR9KEBEraWAC6+09eYBOhXfl\XF1sqTSv5s4vpk9akmTn800XuNoB5XwhjFZcFbioUGJ69CXmf5NKdxF0/TbWp9guf2bhi60J\Jf7+5MkD/g8R9vzNaCD9K20qF6aiXCHxdsAEYi5STQxswyYE6\EGNyRyYmb:1648982611431; vinfo_n_f_l_n3=a5158feeb23d83ce.1.2.1649048820915.1649067989554.1649265739526'}
LogPath = "D:\\pojt\\QQbot\\log\\"+time.strftime('%Y-%m-%d',time.localtime(time.time())) + ".log"



def getsong(url,search):
    print(Pmessage+url)
    with open(LogPath, mode='a+', encoding='utf-8') as file_obj:
        file_obj.write(Pmessage + url+"\n")   
    file_obj.close()
    try:
        header = {
        #'Cookie' : cookie2,
        'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Safari/537.36 Edg/100.0.1185.29',
        }
        r = requests.get(url, timeout=30, headers=header, stream=True)#
    except:#BaseException
        print("fall")
        time.sleep(10)
    f = open(musicPath + search + '.mp3', 'wb')
    f.write(r.content)
    f.close()
    print(Pmessage + "End "+ str(search))
    sys.exit(0)

def take_song(sID,search):
    Dpath = "http://music.163.com/song/media/outer/url?id={}.mp3".format(sID)
    Mp3Path = "http://music.163.com/api/song/enhance/player/url?id={}&ids=[{}]&br=3200000".format(sID, sID)
    print(Pmessage + Mp3Path)
    with open(LogPath, mode='a+', encoding='utf-8') as file_obj:
        file_obj.write(Pmessage + Mp3Path+"\n")   
    file_obj.close() 
    browser.get(Mp3Path)
    browser.delete_all_cookies()
    with open('D:\pojt\QQbot\python\cookies-163.txt','r') as f:
        cookies_list = json.load(f)
        for cookie in cookies_list:
            browser.add_cookie(cookie)
    browser.refresh()
    time.sleep(0.5)
    text = browser.find_element(By.XPATH,"/html/body")
    rowid = text.get_attribute("innerHTML")#innerHTML #outerHTML #textContent /
    key = re.compile('http://+.+?.mp3')    #"http://?.+?"
    id = re.findall(key,rowid)
    for link in id:
        #print(link)
        #string2=link[:-1]
        string2 = link
        #print(string2)
        browser.quit()
    getsong(string2,search)


def getID(search):
    text = browser.find_element(By.XPATH,"/html/body/div[3]/div/div[2]/div[2]/div/div/div[1]/div[2]/div/div")
    rowid = text.get_attribute("innerHTML")#innerHTML #outerHTML #textContent /
    #print(rowid)
    key = re.compile('\\b\w+(?="><b\\b)')
    id = re.findall(key,rowid)
    for link in id:
        #print(link)
        take_song(link,search)


if __name__ == '__main__':
    option = webdriver.ChromeOptions()
    option.add_experimental_option("excludeSwitches", ['enable-automation', 'enable-logging'])
    option.add_argument('--headless')
    browser = webdriver.Chrome(options=option)
    search = sys.argv[1] #"冬之花"sys.argv[1]TwistedNerve
    #search = "冬之花" #"冬之花"sys.argv[1]TwistedNerve
    URLsearch = "https://music.163.com/#/search/m/?s={}&type=1".format(search)
    browser.get(URLsearch)
    browser.delete_all_cookies()
    browser.switch_to.frame('g_iframe')
    time.sleep(0.5)      
    getID(search)
    browser.quit()
#'http://music.163.com/song/media/outer/url?id=1896116362.mp3'//
# https://music.163.com/#/search/m/?s=%E5%86%AC%E4%B9%8B%E8%8A%B1&type=1
#/html/body/div[3]/div/div[2]/div[2]/div/div/div[1]/div[2]/div
#/html/body/div[3]/div/div[2]/div[2]/div/div/div[1]/div[2]/div 
