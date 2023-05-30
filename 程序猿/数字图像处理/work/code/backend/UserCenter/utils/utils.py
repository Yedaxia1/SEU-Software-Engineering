import os
import random

def get_verify_code(length):
    all_str = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    return ''.join([random.choice(all_str) for i in range(length)])

def rm_dir(path):
    ls = os.listdir(path)
    for i in ls:
        f_path = os.path.join(path, i)
        # 判断是否是一个目录,若是,则递归删除
        if os.path.isdir(f_path):
            rm_dir(f_path)
        else:
            os.remove(f_path)

def del_file(path):
    rm_dir(path)
    os.rmdir(path)
