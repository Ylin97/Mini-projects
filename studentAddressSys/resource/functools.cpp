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

using std::cin;
using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::string;
using std::ios_base;
using std::endl;
using std::setw;

LinkList & loadStud(LinkList &studs, const string filename)
{
    ifstream fin;
    // 读入所有学生的信息
    fin.open(filename);
    string stud_info_str;
    vector<string> stud_info_vec;
    while (getline(fin, stud_info_str))
    {
        stud_info_vec = split(stud_info_str, ";");
        Student stud(stud_info_vec);
        studs.addNode(stud, "tail");
    }
    fin.clear();  // 重置输入
    fin.close();  // 关闭文件
    return studs;
}

void saveStud(const LinkList &studs, const string filename)
{
    ofstream fout(filename);
    LinkList::PNode ptmp;
    int len = studs.getSize();
    for (int i = 1; i <= len; i++)
    {
        ptmp = studs.getNode(i);
        fout << ptmp->data.getID() << ";"
             << ptmp->data.getName() << ";"
             << ptmp->data.getAddress() << endl;
    }
    fout.close();
}

void saveStud(const vector<Student> &studs, const string filename)
{
    ofstream fout(filename);
    int len = studs.size();
    for (int i = 0; i < len; i++)
    {
        fout << studs[i].getID() << ";"
             << studs[i].getName() << ";"
             << studs[i].getAddress() << endl;
    }
    fout.close();
}

vector<string> split(const string& str, const string delim)
{
	vector<string> res;
	if ("" == str)
    {
        return res;
    }
	//先将要切割的字符串从string类型转换为char*类型
	char * strs = new char[str.length() + 1]; //不要忘了
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}
	return res;
}

void welcome()
{
    printf("**************************************************\n");
    printf("__          __  _                                 \n"
           "\\ \\        / / | |                              \n"
           " \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___     \n"
           "  \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\\n"
           "   \\  /\\  /  __/ | (_| (_) | | | | | |  __/     \n"
           "    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| \n"
           "                                                  \n"
           "\n          ------学生籍贯信息记录簿系统v0.01       \n");
    printf("**************************************************\n");
}

string menu()
{
    printf("\n********************功能菜单********************\n");
    printf("\ta) 查询学生                         \n"
           "\tb) 编辑学生                         \n"
           "\tc) 添加学生                         \n"
           "\td) 删除学生                         \n"
           "\te) 提取数据                         \n"
           "\tf) 显示信息                         \n"
           "\tq) 退出系统                         \n");
    printf("请选择您要进行的操作 (按 Enter 键结束输入): ");
    string options("abcdefq");
    return options;
}

void login()
{
    // pass
}

void logout()
{
    // pass
}

void confirm()
{
    // pass
}

void quit()
{
    // 
}

char getChoice(const string options)
{
    char ch;
    while ((ch = tolower(getchar())) && (options.find(ch) == options.npos))
    {
        cerr << "您的输入有误!!请重新输入: ";
        if (ch != '\n')
        {
            eatline();
        }
    }
    eatline();
    return ch;
}

void searchFunc(const LinkList &studs, bool pause)
{
    cout << "\n********************查询学生********************\n" << endl;
    cout << "a) 按ID查询\tb) 按姓名查询\tc) 按籍贯查询\td) 默认(按ID查询)\tq) 退出\n" << endl;
    cout << "请输入查询方式 (按Enter键确定): ";
    char opt = getChoice("abcdq");
    string id;
    string name;
    string address;
    vector<Student> res_vector;
    int len = 0;
    switch (opt)
    {
        case 'a':
        case 'd':
            cout << "请输入学生的学号: ";
            getline(cin, id);
            res_vector = studs.search(id, "id");
            if (res_vector.empty())
            {
                cout << "\n未查询到学生'" << id << "'!!!\n" << endl;
            }
            else
            {
                cout << "\n学生'" << id << "'的信息如下:\n";
                showStudFmt(res_vector);
            }
            break;
        case 'b':
            cout << "请输入学生姓名: ";
            getline(cin, name);
            res_vector = studs.search(name, "name");
            if (res_vector.empty())
            {
                cout << "\n未查询到学生'" << name << "'!" << endl;
            }
            else
            {
                cout << "\n学生'" <<  name << "'的信息如下:" << endl;
                showStudFmt(res_vector);
            }
            break;
        case 'c':
            cout << "请输入学生籍贯: ";
            getline(cin, address);
            res_vector = studs.search(address, "address");
            if (res_vector.empty())
            {
                cout << "\n未查询到籍贯为'" << address << "'的学生!" << endl;
            }
            else
            {
                len = res_vector.size();
                cout << "\n籍贯为'" << address << "'的学生:" << endl;
                showStudFmt(res_vector);
            }
            break;
        case 'q':
            break;
    }
    if (pause)
    {
        press2Continue();
    }
}

void addFunc(LinkList &studs, bool pause)
{
    cout << "\n********************添加学生********************\n" << endl;
    cout << "a) 在首部添加\tb) 在末尾添加\tc) 在指定位置添加 q) 退出\n" << endl;
    cout << "请输入添加方式 (按Enter键确定): ";
    char opt = getChoice("abcq");
    Student stud;
    int pos;
    switch (opt)
    {
        case 'a':
            inputStud(studs, stud);
            if (addConfirm(stud) && studs.addNode(stud, "head"))
            {
                cout << "\n添加学生('" << stud.getID() << "," << stud.getName()
                     << "," << stud.getAddress() << "')成功!" << endl;
            }
            else
            {
                cout << "\nWARN: 未添加任何学生!" << endl; 
            }
            break;
        case 'b':
            inputStud(studs, stud);
            if (addConfirm(stud) && studs.addNode(stud, "tail"))
            {
                cout << "\n添加学生('" << stud.getID() << "," << stud.getName()
                     << "," << stud.getAddress() << "')成功!" << endl;
            }
            else
            {
                cout << "\nWARN: 未添加任何学生!" << endl; 
            }
            break;
        case 'c': 
            cout << "请输入插入位置 (1-" << studs.getSize() << "): ";
            cin >> pos;
            eatline();
            inputStud(studs, stud);
            if (addConfirm(stud) && studs.addNode(stud, pos))
            {
                cout << "\n添加学生('" << stud.getID() << "," << stud.getName()
                     << "," << stud.getAddress() << "')成功!" << endl;
            }
            else
            {
                cout << "\nWARN: 未添加任何学生!" << endl; 
            }
            break;
        case 'q':
            break;
    }
    if (pause)
    {
        press2Continue();
    }
}

void inputStud(const LinkList &studs, Student &stud)
{
    LinkList::PNode pNode = studs.getNode(1);
    string tmp_str;
    cout << "请输入学生的学号: ";
    while (getline(cin, tmp_str))
    {
        if (tmp_str.empty())
        {
            cout << "学号不能为空!!!请重新输入: ";
            continue;
        }
        vector<Student> res_vector = studs.search(tmp_str, "id");
        if (res_vector.empty() || (res_vector[0].getID() == pNode->data.getID()))
        {
            break;
        }
        cout << "学号为'" << tmp_str << "'的学生已经存在!!! ==> ("
             << res_vector[0].getID() << "," << res_vector[0].getName()
             << "," << res_vector[0].getAddress() << ")" << endl;
        cout << "请输入新的学号: "; 
    }
    stud.setID(tmp_str);
    cout << "请输入学生的姓名: ";
    while (getline(cin, tmp_str) && tmp_str.empty())
    {
        cout << "姓名不能为空!!!请重新输入: ";
    }
    stud.setName(tmp_str);
    cout << "请输入学生的籍贯: ";
    while (getline(cin, tmp_str) && tmp_str.empty())
    {
        cout << "籍贯不能为空!!!请重新输入: ";
    }
    stud.setAddress(tmp_str);
}

bool addConfirm(const Student &stud)
{
    cout << "将添加新学生('" << stud.getID() << ","
         << stud.getName() << "," << stud.getAddress()
         << "')进系统, 请确定是否添加?[Y/n]: ";
    char ch = tolower(cin.get());
    if ('y' == ch)
    {
        eatline();
        return true;
    }
    else
    {
        if (ch != '\n')
        {
            eatline();
        }
        return false;
    }
}

void editFunc(LinkList &studs, bool pause)
{
    cout << "请输入您想要编辑的学生的学号('d'显示所有学生, 's'进行查询, 'q'退出): ";
    char ch;
    while ((ch = tolower(cin.get())) && (ch != 'd') && (ch != 's') 
                                     && (ch != 'q') && (!isdigit(ch)))
    {
        cout << "您的输入有误! 请重新输入: ";
        if (ch != '\n')
        {
            eatline();
        }  
    }
    if ('d' == ch)
    {
        eatline();
        studs.sort();
        showStudFmt(studs);
        editFunc(studs);
    }
    else if ('s' == ch)
    {
        eatline();
        searchFunc(studs, false);
        editFunc(studs);
    }
    else if ('q' == ch)
    {
        eatline();
        return;
    }
    else
    {
        cin.unget();  // 将读取的数字字符丢回输入缓冲区
        string id;
        LinkList::PNode pNode;
        while (getline(cin, id))
        {
            pNode = studs.getNode(id);
            if (pNode)
            {
                break;
            }
            cout << "\n学号为'" << id << "'的学生不存在!!!请输入新的学号: ";
        }

        // LinkList::PNode pNode = studs.getNode(id);
        if (modifyStud(studs, pNode))
        {
            cout << "学生'" << pNode->data.getName() << "("
                 << pNode->data.getID() << ")的信息修改成功!" << endl;
        }
        else
        {
            cout << "\nWARN: 学生'" << pNode->data.getName() << "("
                 << pNode->data.getID() << ")的信息修改失败!!!" << endl;
        }
        if (pause)
        {
            press2Continue();
        }
    }
}

bool modifyStud(LinkList &studs, LinkList::PNode pNode)
{
    string tmp_str;
    Student new_stud;
    cout << "请输入学生的学号(或按 Enter 键保持当前值'" 
         << pNode->data.getID() << "'): ";
    while (getline(cin, tmp_str))
    {
        vector<Student> res_vector = studs.search(tmp_str, "id");
        if (res_vector.empty() || (res_vector[0].getID() == pNode->data.getID()))
        {
            break;
        }
        cout << "学号为'" << tmp_str << "'的学生已经存在!!! ==> ("
             << res_vector[0].getID() << "," << res_vector[0].getName()
             << "," << res_vector[0].getAddress() << ")" << endl;
        cout << "请输入新的学号: "; 
    }
    if (!tmp_str.empty())
    {
        new_stud.setID(tmp_str);
    }
    else
    {
        new_stud.setID(pNode->data.getID());
    }
    cout << "请输入学生的姓名(或按Enter键保持当前值'"
         << pNode->data.getName() << "'): ";
    getline(cin, tmp_str);
    if (!tmp_str.empty())
    {
        new_stud.setName(tmp_str);
    }
    else
    {
        new_stud.setName(pNode->data.getName());
    }
    cout << "请输入学生的籍贯(或按Enter键保持当前值'"
         << pNode->data.getAddress() << "'): ";
    getline(cin, tmp_str);
    if (!tmp_str.empty())
    {
        new_stud.setAddress(tmp_str);
    }
    else
    {
        new_stud.setAddress(pNode->data.getAddress());
    }
    cout << "\n学生'" << pNode->data.getID() << " ("
         << pNode->data.getName() << "," 
         << pNode->data.getAddress() << ")'的信息将改为:\n\n";
    cout << new_stud.getID() << "," << new_stud.getName()
         << "," << new_stud.getAddress() << endl;
    cout << "\n是否保存修改结果? (Y/n): ";
    char ch = tolower(cin.get());
    if (ch != '\n')
    {
        eatline();
    }
    if ('y' == ch)
    {
        pNode->data = new_stud;
        return true;
    }
    return false;
}
     
void deleteFunc(LinkList &studs, bool pause)
{
    cout << "\n********************删除学生********************\n" << endl;
    cout << "a) 按学号删除\tb) 按名字删除\tc) 按位置删除\tq) 退出\n" << endl;
    cout << "请输入删除方式 (按Enter键确定): ";
    char opt = getChoice("abcq");
    string id;
    string name;
    int pos, len;
    LinkList::PNode ptmp;
    vector<Student> res_vector;
    switch (opt)
    {
        case 'a':
            cout << "请输入要删除学生的学号: ";
            while (getline(cin, id) && id.empty())
            {
                cout << "学号不能为空!!!请重新输入: ";
            }
            res_vector = studs.search(id, "id");
            if (res_vector.empty())
            {
                cout << "\n未找到学号为'" << id << "'的学生!!!\n" << endl;
            }
            else if (delConfirm(res_vector[0]))
            {
                studs.removeNode(id, "id");
                cout << "\n删除学生'" << res_vector[0].getID()
                     << "(" << res_vector[0].getName() << ","
                     << res_vector[0].getAddress() << ")'成功!\n" << endl;
            }
            else 
            {
                cout << "\nWARN: 未删除任何学生!!!\n" << endl;
            }
            break;
        case 'b':
            cout << "请输入要删除学生的姓名: ";
            while (getline(cin, name) && name.empty())
            {
                cout << "姓名不能为空!!!请重新输入: ";
            }
            res_vector = studs.search(name, "name");
            len = res_vector.size();
            for (int i = 0; i < len; i++)
            {
                if (delConfirm(res_vector[i]))
                {
                    studs.removeNode(res_vector[i].getID(), "id");
                    cout << "\n删除学生'" << res_vector[i].getID()
                         << "(" << res_vector[i].getName() << ","
                         << res_vector[i].getAddress() << ")'成功!\n" << endl;
                }
                else
                {
                    cout << "\nWARN: 未删除学生'" << res_vector[i].getID()
                         << "(" << res_vector[i].getName() << ","
                         << res_vector[i].getAddress() << ")'!!!\n" << endl;
                }
            }
            break;
        case 'c':
            cout << "请输入要删除学生的位置[1-" << studs.getSize() << "]: ";
            while ((cin >> pos) &&(pos < 1) || (pos > studs.getSize()))
            {
                cout << "当前删除的位置只能是[1-" << studs.getSize() << "]!!!请重新输入: ";
            }
            eatline();
            ptmp = studs.getNode(pos);
            if (delConfirm(ptmp->data))
            {
                studs.removeNode(pos);
                cout << "\n删除学生'" << ptmp->data.getID()
                     << "(" << ptmp->data.getName() << ","
                     << ptmp->data.getAddress() << ")'成功!\n" << endl;
            }
            else
            {
                cout << "\nWARN: 未删除任何学生!!!\n" << endl; 
            }
            break;
    }
    if (pause)
    {
        press2Continue();
    }
}

bool delConfirm(const Student &stud)
{
    cout << "将从系统中删除学生('" << stud.getID() << ","
         << stud.getName() << "," << stud.getAddress()
         << "'), 请确定是否删除?[Y/n]: ";
    char ch = tolower(cin.get());
    if ('y' == ch)
    {
        eatline();
        return true;
    }
    else
    {
        if (ch != '\n')
        {
            eatline();
        }
        return false;
    }
}

void extractFunc(const LinkList &studs, bool pause)
{
    cout << "\n********************抽取数据********************\n" << endl;
    cout << "a) 按ID查询\tb) 按姓名查询\tc) 按籍贯查询\td) 默认(按ID查询)\tq) 退出\n" << endl;
    cout << "请输入查询方式 (按 Enter 键确定): ";
    char opt = getChoice("abcdq");
    string id;
    string name;
    string address;
    string save_filename = "student";
    vector<Student> res_vector;
    int len = 0;
    switch (opt)
    {
        case 'a':
        case 'd':
            cout << "请输入学生的学号('!'开头表示反选, 例如'!62221007'将查找所有学号不是'62221007'的学生): ";
            getline(cin, id);
            if ('!' == id[0])
            {
                res_vector = studs.search(id.substr(1), "id", true);
                save_filename += "_un" + id.substr(1) + ".txt";
            }
            else
            {
                res_vector = studs.search(id, "id");
                save_filename += "_" + id + ".txt";
            }
            if (res_vector.empty())
            {
                cout << "\n未查询到学生'" << id << "'!!!\n" << endl;
            }
            else
            {
                cout << "\n学生'" << id << "'的信息如下:\n";
                showStudFmt(res_vector);
                cout << endl;
            }
            break;
        case 'b':
            cout << "请输入学生姓名('!'开头表示反选, 例如'!lisi'将查找所有姓名不是'lisi'的学生): ";
            getline(cin, name);
            if ('!' == name[0])
            {
                res_vector = studs.search(name.substr(1), "name", true);
                save_filename += "_un" + name.substr(1) + ".txt";
            }
            else
            {
                res_vector = studs.search(name, "name");
                save_filename += "_" + name + ".txt";
            }
            if (res_vector.empty())
            {
                cout << "\n未查询到学生'" << name << "'!" << endl;
            }
            else
            {
                cout << "\n学生'" <<  name << "'的信息如下:" << endl;
                showStudFmt(res_vector);
            }
            break;
        case 'c':
            cout << "请输入学生籍贯('!'开头表示反选, 例如'!sichuan'将查找所有籍贯不是'sichuan'的学生): ";
            getline(cin, address);
            if ('!' == address[0])
            {
                res_vector = studs.search(address.substr(1), "address", true);
                save_filename += "_un" + address.substr(1) + ".txt";
            }
            else
            {
                res_vector = studs.search(address, "address");
                save_filename += "_" + address + ".txt";
            }
            if (res_vector.empty())
            {
                cout << "\n未查询到籍贯为'" << address << "'的学生!" << endl;
            }
            else
            {
                len = res_vector.size();
                cout << "\n籍贯为'" << address << "'的学生:" << endl;
                showStudFmt(res_vector);
            }
            break;
        case 'q':
            break;
    }
    if (!res_vector.empty())
    {
        cout << "是否保存结果?[Y/n]: ";
        char ch = tolower(cin.get());
        if ('y' == ch)
        {
            eatline();
            extractSave(res_vector, save_filename);
        }
        else if (ch != '\n')
        {
            eatline();
        }
    }
    if (pause)
    {
        press2Continue();
    }
}

void extractSave(const vector<Student> &studs, string filename)
{
    string new_filename;
    cout << "请输入保存文件文件名(默认:" << filename << "): ";
    getline(cin, new_filename);
    if (new_filename.empty())
    {
        saveStud(studs, filename);
    }
    else
    {
        saveStud(studs, new_filename);
    }
}

void showFunc(LinkList &studs, bool pause)
{
    cout << "\n********************显示信息********************\n" << endl;
    cout << "a) 直接输出\tb) 按学号排序\tc) 按姓名排序\td) 按籍贯排序\t"
         << "q) 退出\n" << endl;
    cout << "请输入显示方式 (按Enter键确定): ";
    char opt = getChoice("abcdq");
    char ch;
    switch (opt)
    {
        case 'a':
            showStudFmt(studs);
            break;
        case 'b':
            cout << "是否需要降序排序 (默认为升序)[Y/n]: ";
            ch = tolower(cin.get());
            if ('y' == ch)
            {
                studs.sort("id", true);
            }
            else
            {
                studs.sort("id");
            }
            showStudFmt(studs);
            if (ch != '\n')
            {
                eatline();
            }
            break;
        case 'c':
            cout << "是否需要降序排序 (默认为升序)[Y/n]: ";
            ch = tolower(cin.get());
            if ('y' == ch)
            {
                studs.sort("name", true);
            }
            else
            {
                studs.sort("name");
            }
            showStudFmt(studs);
            if (ch != '\n')
            {
                eatline();
            }
            break;
        case 'd':
            cout << "是否需要降序排序 (默认为升序)[Y/n]: ";
            ch = tolower(cin.get());
            if ('y' == ch)
            {
                studs.sort("address", true);
            }
            else
            {
                studs.sort("address");
            }
            showStudFmt(studs);
            if (ch != '\n')
            {
                eatline();
            }
            break;
        case 'q':
            break;
    }
    if (pause)
    {
        press2Continue();
    }
}

// 格式化显示所有学生的信息
void showStudFmt(const LinkList &studs)
{
    cout << "\n+=================###学生籍贯信息列表###=================+\n";
    cout << "|                                                        |\n";
    cout << "|        ID        " << "|     NAME     " << "|     NATIVE PLACE     |"
         << endl;
    cout << "+------------------+--------------+----------------------+\n";
    LinkList::PNode p = studs.getNode(1);
//  设置对齐方式为 "向左对齐", 并保存原始的对齐方式
    auto origin_fmt = cout.setf(ios_base::left, ios_base::adjustfield);
    while (p)
    {
        cout << "|  " << setw(16) << p->data.getID();
        cout << "|  " << setw(12) << p->data.getName();
        cout << "|  " << setw(20) << p->data.getAddress();
        cout << "|\n";
        cout << "+------------------+--------------+----------------------+\n";
        p = p->next;
    }
    cout << endl;
//  恢复原始的对齐方式
    cout.setf(origin_fmt, ios_base::adjustfield);
}

void showStudFmt(const vector<Student> &studs)
{
    cout << "\n+=================###学生籍贯信息列表###=================+\n";
    cout << "|                                                        |\n";
    cout << "|        ID        " << "|     NAME     " << "|     NATIVE PLACE     |"
         << endl;
    cout << "+------------------+--------------+----------------------+\n";
    int len = studs.size();
//  设置对齐方式为 "向左对齐", 并保存原始的对齐方式
    auto origin_fmt = cout.setf(ios_base::left, ios_base::adjustfield);
    for (int i = 0; i < len; i++)
    {
        cout << "|  " << setw(16) << studs[i].getID();
        cout << "|  " << setw(12) << studs[i].getName();
        cout << "|  " << setw(20) << studs[i].getAddress();
        cout << "|\n";
        cout << "+------------------+--------------+----------------------+\n";
    }
    cout << endl;
//  恢复原始的对齐方式
    cout.setf(origin_fmt, ios_base::adjustfield);
}
    
void quitFunc()
{
    cout << "\n系统关闭, 欢迎您再次使用!" << endl;
}

void eatline()
{
    while (cin.get() != '\n')
        continue;
}

void press2Continue()
{
    cout << "\n按 Enter 键继续....";
    eatline();
}