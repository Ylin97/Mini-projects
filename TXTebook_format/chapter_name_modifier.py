# coding=utf-8


import re
import os
import sys
from shutil import copy2

from chardet.universaldetector import UniversalDetector


# CHAPTER_NUM = ['零', '一', '二', '三', '四', '五', '六', '七', '八', '九']
def main():
    filename = input("请输入文件名：")

    # r_str = repr(input("请输入标题正则表达式："))
    r_str = r'^\s*([\<\(\（]\w{1,5}[\>\)\）]).{0,24}'
    r = re.compile(r_str)

    file_to_utf8(filename)

    with open('tmp_' + filename, 'r', encoding='utf-8') as fr:
        with open(filename, 'w', encoding='utf-8') as fw:
            count = 0
            for text in fr.readlines():
                if re.match(r, text):
                    count += 1
                    fw.write(f'第{count}章\n')
                else:
                    fw.write(text)


def detect_encoding(filepath):
    """检测文件编码
    Args:
        detector: UniversalDetector 对象
        filepath: 文件路径
    Return:
        file_encoding: 文件编码
        confidence: 检测结果的置信度，百分比
    """
    chinese_codings = ['GBK', 'GB2312', 'GB18030']  # 字符集 GB2312 < GBK < GB18030
    detector = UniversalDetector()
    detector.reset()
    for each in open(filepath, 'rb'):
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


def file_to_utf8(filename):
    """将文件编码转为utf-8"""
    tmp_file = 'tmp_' + filename
    copy2(filename, tmp_file)
    old_file = filename[:-4] + '_old' + filename[-4:]
    os.rename(filename, old_file)

    with open(tmp_file, 'r') as file:
        file_encoding, confidence = detect_encoding(tmp_file)
    
    if (file_encoding != 'unknown') and (confidence > 0.75):
        if file_encoding != 'utf-8':
            with open(tmp_file, 'r', encoding=file_encoding, errors='replace') as file:
                text = file.read()
            # with open('u' + filename, 'w', encoding='utf-8', errors='replace') as file:
            with open(tmp_file, 'w', encoding='utf-8', errors='replace') as file:
                file.write(text)


if __name__ == "__main__":
    sys.exit(main())