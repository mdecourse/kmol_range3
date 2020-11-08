import os
import shutil

files = os.listdir('./')
for i in range(len(files)):
    try:
        # copy file from Y:\msys64\mingw64\bin
        shutil.copy2('Y:/msys64/mingw64/bin/' + str(files[i]), 'y:/range3_dlls/') 
    except:
        print(files[i])