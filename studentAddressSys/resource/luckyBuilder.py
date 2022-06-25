import os
import sys
import argparse
from chardet.universaldetector import UniversalDetector


Manual = """
Usage: python build.py [OPTION]... [FILE]...
e.g. python buil.py -o main -e gbk

OPTION:
    -o, --ofile <filename>                    : 最后生成的可执行文件名 (默认为 main)
    -e, --encode <encoding>                   : 指定字符编码 (默认为 utf-8, 在Windows系统中生成的
                                                可执行文件中的中文字符可能会乱码, 此时可以尝试指定为 gbk)
    -h, --help                                : 显示帮助信息
"""
          

def compile_with_encoding(src_files:list=[], 
                          compiler:str='g++', 
                          outfile:str='main', 
                          encoding:str='utf-8',
                          debug=False):
    """
    通过指定编码方式编译源代码文件

    Args:
        src_files : 用于编译的源代码文件名列表. 如果命令行提供了, 则优先使用命令行的值
        compiler  : 编译器名称(或路径, 默认是 g++). 如果命令行提供了, 则优先使用命令行的值
        outfile   : 最后生成的可执行文件名 (默认: main). 如果命令行提供了, 则优先使用命令行的值
        encoding  : 目标编码方式. 如果命令行提供了, 则有限使用命令行的值 (默认: utf-8, 在Windows系统中
                    生成的可执行文件中的中文字符可能会乱码, 此时可以尝试指定为 gbk)
        debug     : 是否为生成的可执行文件添加调试信息 (对应 g++ 的 '-g' 选项, 默认: false)
    Return:
        None
    """
    # 命令行参数解析
    parse = argparse.ArgumentParser(description="Convert encoding for source files and compile them by g++")
    parse.add_argument("-c", "--compiler", help="Compiler, usually is g++")
    parse.add_argument("-g", "--debug", help="produce debugging information", action="store_true")
    parse.add_argument("-o", "--outfile", help="the name of the executable file (default: main)")
    parse.add_argument("-e", "--encode", help="encoding for characters in executable file")
    parse.add_argument("files", nargs="*")
    args = parse.parse_args()      
    # 源码文件
    if  args.files:
        src_files = args.files
    if not src_files:
        print(f"{__file__}: error: Source file required\n")
        print("Usage: python luckyBuilder.py [OPTIONS] file...")
        print("e.g. python luckyBuilder.py tools.cpp main.cpp -o main -e gbk")
        return
    # 头文件
    hdr_files = [x for x in os.listdir(".") if x.endswith('.h')]
    tmp_path = 'tmp'
    # 检查临时目录
    if not os.path.exists(tmp_path):
        os.mkdir(tmp_path)
    # cmd 命令拼接
    ### 编译器
    if args.compiler:
        cmd = args.compiler
    else:
        cmd = compiler
    ### debug 参数
    if args.debug:
        cmd += " -g "
    elif debug:
        cmd += " -g "
    ### 源代码文件
    for i in range(len(src_files)):
        cmd += ' ' + os.path.join(tmp_path, src_files[i])
    ### 生成的可执行文件名    
    if args.outfile:
        cmd += ' -o ' + args.outfile 
    else:
        cmd += ' -o ' + outfile
    # 转换编码
    if args.encode and args.encode.lower() == 'gbk':
         convert2gbk(src_files + hdr_files)
    elif encoding and encoding.lower() == 'gbk':
        convert2gbk(src_files + hdr_files)
    else:
        convert2utf8(src_files + hdr_files)
    # 执行编译命令
    os.system(cmd)
    # 删除临时文件
    for f in os.listdir(tmp_path):
        os.remove(os.path.join(tmp_path, f))
    os.rmdir(tmp_path)


def convert2gbk(files: list):
    """
    将文件编码转为GBK
    
    Args:
        files : 要转换的文件的文件名列表
    Return:
        None
    """
    for i in range(len(files)):
        filename = files[i]
        tmp_file = os.path.join('tmp', filename)

        file_encoding, confidence = detect_encoding(filename)

        if (file_encoding != 'unknown') and (confidence > 0.75):
            with open(filename, 'r', encoding=file_encoding, errors='replace') as fr:
                text = fr.read()
            with open(tmp_file, 'w', encoding='gbk', errors='replace') as fw:
                fw.write(text)


def convert2utf8(files: list):
    """
    将文件编码转为utf-8
    
    Args:
        files : 要转换文件的文件名列表
    Return:
        None
    """
    for i in range(len(files)):
        filename = files[i]
        tmp_file = os.path.join('tmp', filename)

        file_encoding, confidence = detect_encoding(filename)

        if (file_encoding != 'unknown') and (confidence > 0.75):
            with open(filename, 'r', encoding=file_encoding, errors='replace') as fr:
                text = fr.read()
            with open(tmp_file, 'w', encoding='utf-8', errors='replace') as fw:
                fw.write(text)

                
def detect_encoding(filepath):
    """
    检测文件编码 

    Args:
        detector : UniversalDetector 对象
        filepath : 文件路径
    Return:
        file_encoding : 文件编码
        confidence    : 检测结果的置信度，百分比
    """
    chinese_codings = ['GBK', 'GB2312', 'GB18030']  # 字符集 GB2312 < GBK < GB18030
    detector = UniversalDetector()
    detector.reset()
    with open(filepath, 'rb') as fr:
        for each in fr.readlines():
            detector.feed(each)
            if detector.done:
                break
    detector.close()
    file_encoding = detector.result['encoding']
    confidence = detector.result['confidence']
    if file_encoding is None:
        file_encoding = 'unknown'
        confidence = 0.99
    elif file_encoding in chinese_codings:
        file_encoding = 'GB18030'
    return file_encoding, confidence


if __name__ == "__main__":
    sys.exit(compile_with_encoding())