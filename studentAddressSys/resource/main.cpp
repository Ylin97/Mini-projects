#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include "student.h"
#include "linklist.h"
#include "functools.h"
using namespace std;


int main()
{
    const string studs_info_file("students.txt");
    LinkList studs;  // 全部学生
//  载入学生信息
    loadStud(studs, studs_info_file);
//  显示欢迎界面
    welcome();
    bool isquit = false;
    string options;
    while (!isquit)
    {
//      显示菜单并获取用户选项
        options  = menu();
        char opt = getChoice(options);
//      处理用户选项
        switch(opt)
        {
            case 'a': searchFunc(studs); break;
            case 'b': editFunc(studs); break;
            case 'c': addFunc(studs); break;
            case 'd': deleteFunc(studs); break;
            case 'e': extractFunc(studs); break;
            case 'f': showFunc(studs); break;
            case 'q': quitFunc(); isquit = true; break;
        }
    }
// 保存学生信息
    saveStud(studs, studs_info_file);
    cout << "按 Enter 键退出....";
    cin.get();
    return 0;
}

