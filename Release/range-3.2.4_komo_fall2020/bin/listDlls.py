import os
from shutil import copyfile

src = "Y:/msys64/mingw64/bin/"
dst = "c:/tmp/range3Dlls/"
fileList = os.listdir()
for i in range(len(fileList)):
    # the index of the last element is "-1"
    fileExt = fileList[i].split(".")[-1]
    if fileExt == "dll":
        #print(fileList[i])
        try:
            copyfile(src+fileList[i], dst+fileList[i])
        except:
            print(fileList[i])
print("done")
