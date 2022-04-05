import os


base_path = os.path.dirname(os.path.abspath(__file__))

def build():
    os.chdir("{}/build".format(base_path))

    os.system("cmake ..")
    ret = os.system("make -j4")
    if ret != 0:
        return
    os.chdir(base_path)
    os.system("cd target && ./c_compiler.exe")

build()