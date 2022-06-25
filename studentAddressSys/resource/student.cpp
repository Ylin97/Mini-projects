// Student类的方法实现
#include <iostream>
#include <iomanip>
#include <string>
#include "student.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::ios_base;
using std::setw;
using std::endl;

Student::Student()
{
    id      = "None";
    name    = "None";
    address = "None";
}

Student::Student(const Student &stud)
{
    id      = stud.getID();
    name    = stud.getName();
    address = stud.getAddress();
}

Student::Student(const vector<string> &stud)
{
    id      = stud[0];
    name    = stud[1];
    address = stud[2];
}

Student::Student(string _id, string _name, string _address)
{
    id      = _id;
    name    = _name;
    address = _address;
}

Student::~Student()
{
    // pass
}

void Student::setID(string _id)
{
    id = _id;
}

void Student::setName(string _name)
{
    name = _name;
}

void Student::setAddress(string _address)
{
    address = _address;
}

void Student::input()
{
    string tmp_str;
    cout << "请输入学生的学号: ";
    while (getline(cin, tmp_str) && tmp_str.empty())
    { // 排除输入为空行的情况
        cout << "学号不能为空! 请重新输入: ";
    }
    setID(tmp_str);
    cout << "请输入学生的姓名: ";
    while (getline(cin, tmp_str) && tmp_str.empty())
    {
        cout << "姓名不能为空! 请重新输入: ";
    }
    setName(tmp_str);
    cout << "请输入学生的籍贯: ";
    while (getline(cin, tmp_str) && tmp_str.empty())
    {
        cout << "籍贯不能为空! 请重新输入: ";
    }
    setAddress(tmp_str);
}

Student & Student::operator=(const Student &stud)
{
    if (this == &stud)
    {
        return *this;
    }
    id      = stud.getID();
    name    = stud.getName();
    address = stud.getAddress();
    return *this;
}

void Student::show() const
{
    // 设置对齐方式为 "向右对齐", 并保存原始对齐方式
    auto origin_fmt = cout.setf(ios_base::right, ios_base::adjustfield);
    cout << "***************************************\n\n";
    cout << setw(9) << "ID: " << id << endl;
    cout << setw(9) << "Name: " << name << endl;
    cout << setw(9) << "Address: " << address << endl;
    cout << "\n***************************************\n";
    // 恢复原始的对齐方式
    cout.setf(origin_fmt, ios_base::adjustfield);
}