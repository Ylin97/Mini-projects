# 程序编译说明  

## 前言  

编译此程序前请确保您的系统中已经配置好了**g++ 编译器**。如果您不确定您的系统中是否已经配置好了**g++ 编译器**，那么对于 Windows 系统您可以打开**命令提示符**或**Powershell**，对于 Linux 或 MacOS 系统您可以打开 **Terminal** 输入命令``g++ -v``，如果输出了 **g++** 的版本信息（见下图）则说明您的系统中已经配置好了 **g++ 编译器**，否则说明您的系统中还没有配置。如果您的系统中尚未配置 **gcc 编译器**，那么请按照下面的步骤进行配置，否则直接跳到第三步 **编译主程序** 进行编译。  

![image-20220625133501742](https://ylin-typora01.oss-cn-shenzhen.aliyuncs.com/images/image-20220625133501742.png)   

## 配置g++编译器   

### 1 解压 mingw64 工具包

首先将源代码文件夹内的``mingw64.rar``压缩包解压到一个任意的文件目录下（例如：D:\Tools，**注意！路径不能有中文字符！！！**），然后进入解压后的``mingw64``文件夹，复制里面的``bin``文件夹的路径（例如: D:\Tools\mingw64\bin），如图所示：

![image-20220624203058530](https://ylin-typora01.oss-cn-shenzhen.aliyuncs.com/images/image-20220624203058530.png)



### 2 添加环境变量

然后点击“开始”菜单的设置按钮（或按 **Win + i** 快捷键）打开设置，选择 **系统 -- 关于 -- 高级系统设置**，如图所示：  

![image-20220624203341832](https://ylin-typora01.oss-cn-shenzhen.aliyuncs.com/images/image-20220624203341832.png)



接着点击 **环境变量 **，再点击 **用户环境变量** 里面的``Path``变量，点击 **编辑 -- 新建**，然后将刚刚复制的``mingw64\bin``粘贴进去（例如我这里是 D:\Tools\mingw64\bin），确认无误后逐层点击 **确定** 退出环境变量设置。具体操作如图所示：  

![image-20220625122945085](https://ylin-typora01.oss-cn-shenzhen.aliyuncs.com/images/image-20220625122945085.png)

### 3 验证 g++ 是否配置成功  

点击任务栏的搜索按钮搜索“命令提示符”，或者按快捷键 **Win + r** 输入``cmd``，然后再打开的命令行界面输入``g++ -v``（Linux 或 MacOS 通过“Terminal” 输入），如果输出了 g++ 的版本信息则说明您的 g++ 编译器已经配置成功；如果没有输出 g++ 的版本信息，那么您可以尝试重启一下您的电脑，然后重新打开命令提示符或 Terminal 窗口输入``g++ -v``进行验证，如若还是未输出版本信息，那么请检查上一步的环境变量是否添加成功，检查或重新添加 mingw64 的环境变量后再进行验证。如果还是不行，那请您自行上网搜索“Windows 配置 mingw”（Linux 或 MacOS 只需通过包管理器安装 **GCC 编译器包** 即可，通常情况下包管理器会自动帮您配置好环境，而无需您自己手动配置）。   

## 编译主程序  

在确认配置好了**g++编译器**后，您只需双击源代码文件夹里面的``build.bat``批处理文件（Linux 或 MacOS 请执行``build.sh``）即可完成主程序的编译，默认生成的可执行文件名是``main.exe``。同时您也可以通过直接输入命令的方式编译主程序，打开**命令提示符窗口**或者**Powershell**（Linux 或 MacOS 打开 Terminal），将工作目录切换到源代码文件夹，然后输入编译命令: 

Windows 系统输入：

```powershell
g++ .\student.cpp .\linklist.cpp .\functools.cpp .\main.cpp -o main.exe
```

Linux 或 MacOS 系统输入：  

```shell
g++ ./student.cpp ./linklist.cpp ./functools.cpp ./main.cpp -o main
```

![image-20220625133031356](https://ylin-typora01.oss-cn-shenzhen.aliyuncs.com/images/image-20220625133031356.png)

如果您想进行调试，那么请在**为文件打上断点后**，双击源代码文件夹内的``debug_build.bat``批处理文件（Linux 或 MacOS 请执行``debug_build.sh``）。当然您也可以手动编译，并在编译时加上调试参数``-g``（*注意！此方法可能只在 vscode 里面有效*）:  

Windows 系统输入：  

```Powershell
g++ -g .\student.cpp .\linklist.cpp .\functools.cpp .\main.cpp -o main.exe
```

Linux 或 MacOS 系统输入：  

```shell
g++ -g ./student.cpp ./linklist.cpp ./functools.cpp ./main.cpp -o main
```

## 运行主程序  

直接双击编译生成的``main.exe``程序即可，如果出现乱码，而您的系统中安装了 **Python解释器**，那么请用 **Python解释器** 执行``build.py``脚本，该脚本会自动将编码转为``GBK``，执行命令如下：   

```shell
python build.py
```

当然，您还可以使用其他的文本编辑器（例如：Windows 记事本）将``linklist.h``、``linklist.cpp``、``student.h``、``student.cpp``、``functools.h``、``functools.cpp``、``main.cpp``这 7 个文件的编码更改成``gbk``后保存，然后重新双击``build.bat``批处理文件，即可生成无乱码的可执行文件``main.exe``。

