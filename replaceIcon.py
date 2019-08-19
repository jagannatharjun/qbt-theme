
import os
import subprocess
import shutil

iconDir = '.\material'


for dirpath, dirnames, files in os.walk(iconDir):
    for f in files:
        fullfileName = dirpath + os.sep + f
        print(fullfileName)
        subprocess.run(['C:\Program Files (x86)\Google\Chrome\Application\chrome.exe', fullfileName])
        replacement = input('Replacement -> ')
        replacement = replacement.strip("\"")
        if len(replacement) > 0:
            replacementDest = dirpath + os.sep + os.path.splitext(f)[0] + os.path.splitext(replacement)[1]
            os.system('del {}'.format(fullfileName))
            os.system('move "{}" "{}"'.format(replacement, replacementDest))
