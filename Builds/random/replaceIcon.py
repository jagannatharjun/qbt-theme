
import os
import subprocess
import shutil
import json

iconDir = '.\material-white\\icons\\' 

jsons = str()
with open(iconDir + 'iconconfig.json' , 'r') as f:
    jsons = f.read()

imap = json.loads(jsons)

ext = ['.svg', '.png']
for dirpath, dirnames, files in os.walk(iconDir):
    for f in files:
        if os.path.splitext(f)[1] not in ext:
            continue
        fullfileName =  os.path.join(dirpath, f)
        print(fullfileName)
        subprocess.run(['C:\Program Files (x86)\Google\Chrome\Application\chrome.exe', fullfileName])
        usedIn = list()
        for k,v in imap.items():
            if  os.path.splitext(os.path.split(v)[1])[0] == os.path.splitext(os.path.split(f)[1])[0]:
                print(k)
        
        replacement = input('Replacement -> ')
        replacement = replacement.strip("\"")
        if len(replacement) > 0:
            replacementDest = dirpath + os.sep + os.path.splitext(f)[0] + os.path.splitext(replacement)[1]
            os.system('del {}'.format(fullfileName))
            os.system('move "{}" "{}"'.format(replacement, replacementDest))
