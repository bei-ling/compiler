from email.mime import base
import os
import time

base_path = os.path.dirname(os.path.abspath(__file__))
target_path = os.path.join(base_path, "target")

def build():
    os.chdir(base_path)
    os.system("rm -r {}/c_compiler.exe".format(target_path))
    os.chdir("{}/build".format(base_path))
    os.system("cmake .. -G 'Ninja'")
    ret = os.system("ninja -j4")
    if ret != 0:
        return
    os.chdir(base_path)
    os.system("cd target && ./c_compiler.exe")

start_time = time.time()
build()
end_time = time.time()
print("build time cost: {}s".format(end_time - start_time))