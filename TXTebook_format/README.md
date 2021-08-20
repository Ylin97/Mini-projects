### 说明   
+ 此脚本的功能：将 txt 电子书转为适合手机阅读的格式。  
+ 此脚本基于 Python 3 语法编写，请使用 Python 3 解释器执行此脚本；如果没有安装 Python 3 解释器，请往 Python [官网](https://www.python.org/downloads/)   下载安装。  
+ 此脚本用到了``chardet``这个第三方模块，如果没有安装，请在终端或、命令提示符或 Windows PowerShell 中使用 pip 安装：    
	```shell   
    pip3 install chardet 
	```
  
+ 此脚本不能自动删除行首行尾的特殊字符，请手动将多余的字符删除或替换成空白符。  


### 用法  
先将脚本文件复制到 txt 电子书所在的目录（文件夹）下，然后根据系统执行如下命令： 
**Linux 和 MacOS:**    
在终端（Terminal）中执行如下命令：   
```shell
python ./TXTebook_formatter.py   
```

**Windows: **  
在命令提示符、Windows PowerShell或Windows Terminal中执行如下命令：   
```shell  
python .\TXTebook_formatter.py
```

最后根据提示输入需要修改的文件的完整文件名，再按回车即可。  