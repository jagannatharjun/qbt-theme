import json
import os
import shutil

iconConfigPath = 'E:\Cpp\Projects\\bittorent\qBittorrent\src\icons\iconconfig.json'
iconDir = 'E:\Cpp\Projects\\bittorent\qBittorrent\src\icons\\'
newIconDir = '.\icons\\'
jsons = str()

with open(iconConfigPath, 'r') as f:
    jsons = f.read()

imap = json.loads(jsons)
ext = ['.svg', '.png']
for v in imap.values():
    iconPath = iconDir + v
    if  len(os.path.splitext(iconPath)[1]) == 0:
        for e in ext:
            if os.path.exists(iconPath + e):
                iconPath = iconPath + e
                break
    if len(iconPath) > 0:
        print(iconPath)
        newIconPath =  newIconDir + iconPath.replace(iconDir, '')
        if not os.path.exists( os.path.dirname(newIconDir)):
            os.mkdir(os.path.dirname(newIconDir + v))
        print(iconPath)
        shutil.copy(src=iconPath, dst = newIconPath)
    else:
        print('error no binding exists for {}'.format(v))