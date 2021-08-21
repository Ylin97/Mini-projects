### 说明   
+ 此脚本的功能：将 txt 电子书转为适合手机阅读的格式。  
	1. 自动将文件编码转为 utf-8；  
    2. 自动删除多余空白符和空行；
    3. 自动识别章节号；
    4. 自动将长段进行分段。  
+ 此脚本基于 Python 3 语法编写，请使用 Python 3 解释器执行此脚本；如果没有安装 Python 3 解释器，请往 Python [官网](https://www.python.org/downloads/)   下载安装。Windows系统在安装时，选择将 ``Add Python 3.x to PATH``。（Win10 用户推荐下载应用商店版本 [Python 3.9](https://www.microsoft.com/zh-cn/p/python-39/9p7qfqmjrfp7#activetab=pivot:overviewtab)）。   
+ 此脚本用到了``chardet``这个第三方模块，如果没有安装，请在 终端 或 命令提示符 或  Windows PowerShell 中使用 pip 安装：    
	```shell   
    pip3 install chardet 
	```
  
+ 此脚本不能自动删除行首行尾的特殊字符，请手动将多余的字符删除或替换成空白符。  


### 用法  
先将``TXTebook_formatter.py``复制到 txt 电子书所在的目录（文件夹）下，然后根据系统执行如下操作： 

**Linux 和 MacOS:**    
打开终端（Terminal），将工作路径切换到 txt 小说所在的目录，然后在终端（Terminal）中执行如下命令：   

```shell
python ./TXTebook_formatter.py   
```

**Windows: **    
正常情况下直接双击 ``TXTebook_formatter.py`` 文件就可以运行脚本了，如果双击不能运行则按下面方法执行：

打开 命令提示符 或 Windows PowerShell 或 Windows Terminal，将工作路径切换的 txt 小说所在目录，然后执行如下命令：   
```shell  
python .\TXTebook_formatter.py
```

最后根据提示输入需要修改的文件的完整文件名，再按 Enter 键即可。  