# -*- coding: UTF-8 -*-
#MADE BY BILIBILI XGY4N
from asyncio.windows_events import NULL
#from subprocess import HIGH_PRIORITY_CLASS
import requests
import time
import json
#import MySQLdb
#import pygame
import sys
from PIL import Image,  ImageFilter
from PIL import Image, ImageDraw, ImageFont
import textwrap
from string import ascii_letters
import sys
import os
#import tamil 
#import cv2
#import numpy as np
import random
cookie1 = 'buvid3=8014F736-BF6F-2FAC-F9C9-2419A041E58B01093infoc; i-wanna-go-back=-1; _uuid=7CF1065104-AB109-42610-2223-106772B64F710F01555infoc; buvid4=59D4DF69-400D-3E75-0546-BF49A73F687280823-022012016-TwAeKfdjlGF9QScwEXv4FqyZboyvwg5rKzOAzTvAJ1AFk1+ukJT7Ag%3D%3D; sid=j4ry8w7e; fingerprint=dad2dddcbfd481174d180f0cec822d7c; buvid_fp_plain=undefined; buvid_fp=dea24cee2969b3488ac8e3725526749a; DedeUserID=173517990; DedeUserID__ckMd5=0ee1dcbf23bc8b10; SESSDATA=8fc20b1c%2C1659632285%2Cf18f4*21; bili_jct=cfe331161230fcd23c8fe9a6ab634412; b_ut=5; blackside_state=1; rpdid=0zbfVFXxwS|VLaegLey|46d|3w1Ngool; CURRENT_BLACKGAP=0; CURRENT_FNVAL=4048; innersign=0; b_lsid=3BD68E13_17ECDC8C354; PVID=2; bsource=search_bing; LIVE_BUVID=AUTO9616441324561436; bp_video_offset_173517990=624026140724849500'
cookie2 = 'buvid3=FDD99964-7CA8-48D5-9149-E9E677AF1C87138381infoc; rpdid=|(ku|um)l~|J0J''ulm)lmY)R); _uuid=F963B598-9B1F-7A4D-BD9A-FF7649928CB603251infoc; buvid4=5F86D2B0-16D4-AC73-8103-C49D26BB759104300-022020617-TwAeKfdjlGHch0oYx00AishgEK04DNFKGzMArbp9VgS8EjL1RPy4Fw==; fingerprint=4816e9b13be01e0d606bfb0f85009c77; buvid_fp_plain=undefined; DedeUserID=667796358; DedeUserID__ckMd5=f0f7af2ca182c48a; i-wanna-go-back=-1; b_ut=5; buvid_fp=873766b853f6aec1f173969f4e678da3; SESSDATA=17196d65,1659691972,b0172*21; bili_jct=4069af6fe48d989b63307b516512d34d; sid=kij9kxkq; CURRENT_BLACKGAP=0; CURRENT_FNVAL=80; bp_video_offset_667796358=624142122023923700; innersign=0; b_lsid=2ACC4E71_17ED33F2187; PVID=2'
avl = 0
LogPath = "D:\\pojt\\QQbot\\log\\"+time.strftime('%Y-%m-%d',time.localtime(time.time())) + ".log"
Pmessage = "[Python]" + time.strftime('[%Y-%m-%d %H:%M:%S]',time.localtime(time.time()))
#-------------------------------------------------------BV to AV-------------------------------------------------------------------
table='fZodR9XQDSUm21yCkr6zBqiveYah8bt4xsWpHnJE7jL5VG3guMTKNPAwcF'
tr={}
for i in range(58):
	tr[table[i]]=i
s=[11,10,3,8,4,6]
xor=177451812
add=8728348608

def dec(x):
	r=0
	for i in range(6):
		r+=tr[x[s[i]]]*58**i
	return (r-add)^xor

#def enc(x):
	x=(x^xor)+add
	r=list('BV1  4 1 7  ')
	for i in range(6):
		r[s[i]]=table[x//58**i%58]
	return ''.join(r)
#-----------------------------------------------------------------------------------------------------------------------------------




#-------------------------------------------------------伪装----------------------------------------------------------------------------
def get_html(url):
    headers = {
        'Cookie' : cookie2,
        'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36',
    }
    r = requests.get(url, timeout=30,headers=headers)
    r.raise_for_status()
    r.endcodding = 'utf-8'
    #print(r.text)
    return r.text
#----------------------------------------------------------------------------------------------------------------------------------------------




#------------------------------------------------------------------------url message---------------------------------------------------------
def replirelp(comments,s,numb,mark):
    k=0
    while k<numb:
        comment=s['data']['replies'][mark]['replies'][k]
        InfoDict={} 
        InfoDict['uid']=comment['member']['mid']
        InfoDict['Uname']=comment['member']['uname'] 
        InfoDict['Like']=comment['like'] 
        InfoDict['Content']=comment['content']['message']  
        InfoDict['Time']=time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(comment['ctime'])) 
        comments.append(InfoDict)
        k+=1
        time.sleep(2)


def Make_picture():
    ram = random.randint(1,50)
    impath = 'D:\\pojt\\QQbot\\resource\\picture\\a\\{}.jpg'.format(str(ram))
    print(Pmessage + impath)
    im = Image.open(impath)
    imagePixmap = im.size	# 宽高像素
    a = im.width
    b = im.height
    #print(imagePixmap, a, b)
    if a>b:
        k = a/b
    else:
        k = b/a
    imBackground = im.resize((int(a/k*1.6),int(b/k*1.6))) #k =1.54
    imBackground.save('D:\\pojt\\QQbot\\resource\\vtb\\temp.jpg')
    im2=Image.open('D:\\pojt\\QQbot\\resource\\vtb\\temp.jpg')  
    im2=im2.filter(ImageFilter.GaussianBlur(radius=3))  
    im2.save('D:\\pojt\\QQbot\\resource\\vtb\\temp.jpg')  
	#current_dir = os.getcwd()
    #Pname = avs +'.jpg'
    font_path = os.path.join("D:\\pojt\\QQbot\\python\\fonts\\")
    img_path = os.path.join("D:\\pojt\\QQbot\\resource\\vtb\\")
    image = Image.open(os.path.join(img_path, 'temp.jpg'))
    draw = ImageDraw.Draw(im=image)
    with open("D:\\pojt\\QQbot\\resource\\vtb\\"+str(avs)+".txt", 'r', encoding='utf-8') as tv:
        text = tv.read()
        fnt = ImageFont.truetype(os.path.join(font_path, 'msyh.ttc'), 80)
        avg_char_width = sum(fnt.getsize(char)[0] for char in ascii_letters) / len(ascii_letters)
        max_char_count = int( (image.size[0] * .95) / avg_char_width )
        text = textwrap.fill(text=text, width=max_char_count)
        draw.text((image.size[0]/2,image.size[1]/2), text, font=fnt, fill='#ffffff', anchor='mm' ,stroke_width=2, stroke_fill="#000000")
    image.save(os.path.join(img_path, str(avs)+'.jpg'))
    os.remove("D:\\pojt\\QQbot\\resource\\vtb\\temp.jpg")


##723681437
def get_content(url):
    comments = []
    html = get_html(url)

    try:
        s=json.loads(html)
    except:
        print("jsonload error")
    #print(s)
    num=len(s['data']['list']) 
    if num == 0:
        return -1
    i=0
    strrimg = ""
    with open(LogPath, mode='a+', encoding='utf-8') as file_obj:
        file_obj.write(Pmessage + "D:\\pojt\\QQbot\\resource\\vtb\\"+avs+".txt"+"\n")  
    file_obj.close()
    Paat = "D:\\pojt\\QQbot\\resource\\vtb\\{}.txt".format(avs)

    with open(Paat, mode="w", encoding='utf-8') as f:
        while i<num:
            comment=s['data']['list'][i]
            #print(comment)
            InfoDict={} 
            InfoDict['uid']=comment['mid']
            InfoDict['Uname']=comment['uname'] 
            InfoDict['Time']=time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(comment['mtime'])) 
            print(InfoDict['uid'],InfoDict['Uname'],InfoDict['Time']) 
            imgstr = 'uid:{}-name:{}\n'.format(InfoDict['uid'], InfoDict['Uname'])
            strrimg = strrimg+imgstr
            try:
                f.write('uid:{}\t name:{}\t \n'.format(InfoDict['uid'], InfoDict['Uname']))
            except:
                print("out2File error")
            comments.append(InfoDict)
            i=i+1
    f.close()
    
    return comments
#-------------------------------------------------------------------------------------------------------------------------------------------



#---------------------------------------------------------------SQLPART----------------------------------------------------------------
def SQL(dict,j,db,cursor,number):
    
    i=0
    j=j+1
    for comment in dict:
        i=i+1
        number+=1
        try: 
            sql = "insert into Bil(BiliName,UserMessage,Userlike,MassageTime) VALUES(\'{}\',\'{}\',{},\'{}\')" .format(comment['Uname'],comment['Content'],comment['Like'],comment['Time'])
            print(sql)
            try:        
                cursor.execute(sql)
                db.commit()
            except:
                print("sqlstr error")
                db.rollback()
        except:
            print("sqlwrong")        
    print('finish')
    print(number)
    if comment['Uname'] == NULL:
        return -1
           

#--------------------------------------------------------------------main-----------------------------------------------------------------------------------------------

def start(avs,avl):
    #db = MySQLdb.connect("localhost", "root", "100798943", "bili", charset='utf8' )
    #cursor = db.cursor()
    for av in range(avs, avl+1):
        number = 0
        e=0
        page=1
        j=1          
        print(Pmessage,"ready start user",av) 
        while e == 0 :
            #"https://api.bilibili.com/x/v2/reply?pn="+ str(page)+"&type=1&oid="+str(av)
            #https://api.bilibili.com/x/relation/same/followings?pn="+ str(page)+"vmid="+str(av)+"&order=desc&jsonp=jsonp
            url = "https://api.bilibili.com/x/relation/same/followings?pn="+ str(page)+"&vmid="+str(av)+"&order=desc&jsonp=jsonp"
            with open(LogPath, mode='a+', encoding='utf-8') as file_obj:
                file_obj.write(Pmessage + "https://api.bilibili.com/x/relation/same/followings?pn="+ str(page)+"&vmid="+str(av)+"&order=desc&jsonp=jsonp"+"\n")  
            print(Pmessage,url)
            try:
                number2 = 0
                content=get_content(url)
                print(Pmessage,"page:",page)
            #SQL(content,j,db,cursor,number)
                j=j+1
                page=page+1
                if page%10 == 0:
                    time.sleep(1)
                if content == -1:
                    e=1
            except:
                #print("Expected upper bound of message volume in current time: ",page*20)#当前时间内信息量预计上界
                print(Pmessage,"END ",av) 
                #time.sleep(5)
                e=1


if __name__ == '__main__':
    #avs = int(input("please enter min "))
    #avl = int(input("please enter max "))
    #paras = sys.argv[1] #返回一个列表形式
    avs = sys.argv[1]
    avl = sys.argv[1]
    avs = int(sys.argv[1])
    avl = int(sys.argv[1])
    '''avs = 189546454
    avl = 189546454'''
    start(avs,avl)
    Make_picture()
'''import  os
os.system( 'pause' )'''

