import time
musicPath = "./resource/music/"
imgPath = "./resource/picture/"
LogPath = "./log/"+time.strftime('%Y-%m-%d',time.localtime(time.time())) + ".log"
def Pmessage(string): 
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
