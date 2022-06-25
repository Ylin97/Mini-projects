#ifndef FUNCTOOLS_H_
#define FUNCTOOLS_H_
#include "student.h"
#include "linklist.h"

// 简介: 字符串分割函数
// 参数: 
//     str   : 将要分割的字符串 \< std::string >
//     delim : 分割符, 可以同时指定多个分割符 \< std::string >
// 返回值: 
//     返回一个包含所有分割结果的向量 \< std::vector\<std::string> >   
vector<string> split(const string& str, const string delim);

// 简介: 载入学生信息
// 参数: 
//     studs    : 记录所有学生信息的链表的引用 \< LinkList::LinkList& >
//     filename : 要打开的学生信息文件名, 默认是 'students.txt' \< std::string >
// 返回值:
//     返回studs的引用 \<LinkList::LinkList&>
LinkList & loadStud(LinkList &studs, const string filename = "students.txt");

// 简介: 保存学生信息
// 参数:
//     studs    : 学生信息链表的引用 \< LinkList::LinkList& >
//     filename : 保存信息的文件名, 默认是 'students.txt' \< std::string >
// 返回值: 无
void saveStud(const LinkList &studs, const string filename = "students.txt");

// 简介: 保存学生信息
// 参数:
//     studs    : 学生信息向量的引用 \< std::vector<Student>& >
//     filename : 保存信息的文件名, 默认是 'students.txt' \< std::string >
// 返回值: 无
void saveStud(const vector<Student> &studs, const string filename);

// 简介: 起始页面 (欢迎界面)
// 参数: 无
// 返回值 : 无
void welcome();    

// 简介: 功能菜单界面
// 参数: 无
// 返回值: 
//     返回包含所有菜单选项标签的字符串(例如'abcdefq') \< std::string >
string menu();  

// 简介: 登入界面 
// 参数: 无
// 返回值: 无    
void login();  

// 简介: 登出界面 
// 参数: 无
// 返回值: 无
void logout(); 

// 简介: 确认界面    
// 参数: 无
// 返回值: 无
void confirm();

// 简介: 退出界面      
// 参数: 无
// 返回值: 无
void quit();     

// 简介: 获取用户选择
// 参数: 
//     options : 所有选项标签字符串(例如'abcq') \< std::string >
// 返回值:
//     返回一个选项标签字符 \< char >
char getChoice(const string options);

// 简介: 登录选项执行函数
// 参数: 无
// 返回值: 无
void loginFunc();  

// 简介: 登出选项执行函数   
// 参数: 无
// 返回值: 无
void logoutFunc();  

// 简介: 查询选项执行函数  
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >
// 返回值: 无
void searchFunc(const LinkList &studs, bool pause = true);  

// 简介: 添加选项执行函数  
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >  
// 返回值: 无
void addFunc(LinkList &studs, bool pause = true); 

// 简介: 输入学生信息
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >  
// 返回值: 无
void inputStud(const LinkList &studs, Student &stud);

// 简介: 确定是否添加学生
// 参数:
//     stud : 将要确认添加的学生 \< Student::Student >
// 返回值:
//     返回一个布尔值, 表示是否添加成功 \< bool >
bool addConfirm(const Student &stud); 

// 简介: 编辑选项执行函数
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >  
// 返回值: 无
void editFunc(LinkList &studs, bool pause = true);

// 简介: 修改学生信息
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pNode : 指向将要修改的结点的指针 \< LinkList::PNode > 
// 返回值:
//     返回一个布尔值, 表示是否修改成功
bool modifyStud(LinkList &studs, LinkList::PNode pNode);

// 简介: 删除选项执行函数     
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >   
// 返回值: 无
void deleteFunc(LinkList &studs, bool pause = true);


// 简介: 确定是否删除学生
// 参数:
//     stud : 将要确认删除的学生 \< Student::Student >
// 返回值:
//     返回一个布尔值, 表示是否删除成功 \< bool >
bool delConfirm(const Student &stud); 


// 简介: 显示选项执行函数 
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >
// 返回值: 无
void showFunc(LinkList &studs, bool pause = true); 

// 简介: 格式化显示所有学生的信息
// 参数:
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
// 返回值: 无
void showStudFmt(const LinkList &studs);

// 简介: 格式化显示所有学生的信息
// 参数:
//     studs : 学生信息向量的引用 \< std::vector<Student>& >
// 返回值: 无
void showStudFmt(const vector<Student> &studs);

// 简介: 提取数据执行函数
// 参数: 
//     studs : 学生信息链表的引用 \< LinkList::LinkList& >
//     pause : 是否执行 '按Enter键继续....' 来暂停程序 \< bool >   
// 返回值: 无  
void extractFunc(const LinkList &studs, bool pause = true);

// 简介: 保存提取的数据
// 参数:
//     studs    : 学生信息向量的引用 \< std::vector<Student>& >
//     filename : 将要保存的文件名, 默认将根据籍贯名生成 \< std::string >
// 返回值: 无
void extractSave(const vector<Student> &studs, string filename);

// 简介: 退出选项执行函数
// 参数: 无
// 返回值: 无    
void quitFunc();      

// 简介: 清空输入缓冲区的内容
// 参数: 无
// 返回值: 无
void eatline();

// 简介: '按Enter键继续....' 执行函数
// 参数: 无
// 返回值: 无
void press2Continue();
#endif