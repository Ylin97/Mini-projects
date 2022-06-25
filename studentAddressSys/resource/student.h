// Student 类定义
#ifndef STUDENT_H_
#define STUDENT_H_
#include <iostream>
#include <vector>
using std::string;
using std::vector;

class Student
{
private:
    string id;       // 学生学号
    string name;     // 学生姓名
    string address;  // 学生籍贯
public:
    Student();
    Student(const Student &stud);
    Student(const vector<string> &stud);
    Student(string _id, string _name, string _address);
    ~Student();
    // 设置学生学号
    void setID(string _id);
    // 设置学生姓名
    void setName(string _name);
    // 设置学生籍贯
    void setAddress(string _address);
    // 从键盘输入学生信息
    void input();
    // 获取学生学号
    inline string getID() const { return id; }
    // 获取学生姓名
    inline string getName() const { return name; }
    // 获取学生籍贯
    inline string getAddress() const { return address; }
    Student & operator=(const Student &stud);
    // 显示学生信息
    void show() const;
};
#endif