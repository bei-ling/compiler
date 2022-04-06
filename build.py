from email.mime import base
import os

base_path = os.path.dirname(os.path.abspath(__file__))
target_path = os.path.join(base_path, "target")

def build():
    os.chdir(base_path)
    os.system("rm -r {}/c_compiler.exe".format(target_path))
    os.system("python3 incre_build.py")
    os.chdir("{}/build".format(base_path))

    os.system("cmake .. -G 'Ninja'")
    os.system("ninja -t restat")
    ret = os.system("ninja -j4")
    if ret != 0:
        return
    os.chdir(base_path)
    os.system("cd target && ./c_compiler.exe")

build()