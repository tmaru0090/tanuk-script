#!/usr/bin/env python
import os
import os.path
import time 
import subprocess

cmake_conf_path = "./CMakeLists.txt"
current_time = time.time()
modification_time = os.path.getmtime(cmake_conf_path)
diff_time = current_time - modification_time
def build():
    cmake_command = ["cmake","../","-GNinja"]
    ninja_command = ["ninja"]
    # 1分以内に更新があった場合
    if diff_time <= 60:
        print('"',cmake_conf_path,'"',"が","更新されたのでビルド情報を更新します")
        os.chdir("build")
        subprocess.run(cmake_command)
        print("ビルド中...")
        subprocess.run(ninja_command)

    # 更新がない場合
    else:
        print(cmake_conf_path,"の","更新がないため通常通りビルドをします")
        os.chdir("build")
        print("ビルド中...")
        subprocess.run(ninja_command)

build()
