import sys
from luckyBuilder import *


if __name__ == '__main__':
    srcfiles = ['student.cpp', 'linklist.cpp', 'functools.cpp', 'main.cpp']
    sys.exit(compile_with_encoding(srcfiles, encoding='gbk'))