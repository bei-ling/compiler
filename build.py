import os


base_path = os.path.dirname(os.path.abspath(__file__))

os.chdir("{}/build".format(base_path))

os.system("cmake ..")
os.system("make -j4")
os.chdir(base_path)
os.system("cd target && ./c_compiler.exe")