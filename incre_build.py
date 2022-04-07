from email.mime import base
import os
import shutil

base_path = os.path.dirname(os.path.abspath(__file__))
build_path = os.path.join(base_path, "build")
test_path = os.path.join(base_path, "test")

endsflag = [".o", "build.ninja", ".ninja_deps", ".ninja_log", "rules.ninja"]

def list_all_files(rootdir: str) -> list:
    _files = []
    file_list = os.listdir(rootdir)# 列出文件夹下的所有目录和文件
    for file_name in file_list:
        file_path = os.path.join(rootdir, file_name)
        if os.path.isdir(file_path):
            _files.extend(list_all_files(file_path))
        for flag in endsflag:
            if file_path.endswith(flag):
                _files.append(file_path)

    return _files


def backup():

    incre_files = list_all_files(build_path)
    os.chdir(build_path)

    for file_path in incre_files:
        copy_path = file_path.replace(build_path, test_path)
        file_dir = os.path.dirname(copy_path)
        if not os.path.exists(file_dir):
            os.makedirs(file_dir)
        os.system("cp -p {} {}".format(file_path, copy_path))
        print("--", copy_path)
    print("-- backup success!")

    
def start():
    incre_files = list_all_files(test_path)
    os.chdir(test_path)

    for file_path in incre_files:
        copy_path = file_path.replace(test_path, build_path)
        file_dir = os.path.dirname(copy_path)
        if not os.path.exists(file_dir):
            print(file_dir)
            os.makedirs(file_dir)
        # -p很重要,需要每次保证拷贝的ninja文件时间戳保持一致
        os.system("cp {} {}".format(file_path, copy_path))
        print("--", copy_path)

 
os.system("cd {} ; rm -r build/*".format(base_path))
start()
# backup()