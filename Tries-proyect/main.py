from os import listdir
from os.path import isfile, isdir

f = open ('direcciones.txt','wb')

def scanear(dir):
    ver = isdir(dir)
    if ver==True:
        for a in listdir(dir):
            scanear(dir+"/"+a)
    else:
        #print(dir)
        f.write(dir+'\n')
scanear("../../..")
# scanear("files")

f.close()
