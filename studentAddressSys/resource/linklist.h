// 自定义的单链表头文件
#ifndef LinkLIST_H_
#define LinkLIST_H_
#include <iostream>
#include <vector>
#include "student.h"
using std::string;


class LinkList
{
private:
    typedef Student Item;
    struct Node
    {
        Item data;    // 数据域
        Node * next;  // 指针域
    };
    
    Node *head;       // 头指针
    Node *tail;       // 尾指针
    int size;         // 当前链表长度

    // 简介: 排序结点比较函数
    // 参数:
    //     x   : 结点x \< LinkList::Node >
    //     y   : 结点y \< LinkList::Node >
    //     key : 用于比较的的属性名 \< std::string >
    //     reverse : 是否降序排序  \< bool >
    // 返回值:
    //     返回一个布尔值
    bool cmpfunc(const Node *x, const Node *y,
                    const string key, const bool reverse);
public:
    typedef struct Node* PNode;
    LinkList();
    LinkList(const LinkList &L);
    ~LinkList();

    // 简介: 链表判空
    // 参数: 无
    // 返回值: 
    //     返回一个布尔值, 表示当前链表是否为空('空'为 true, '非空'为 false)
    bool isEmpty(); 

    // 简介: 使用头插法或尾插法往链表中添加新结点
    // 参数:
    //     item : 结点的数据域的引用 \< LinkList::Item >
    //     type : 插入方式("head"或"tail"), 默认为 "head" \< std::string >
    // 返回值:
    //     返回一个布尔值, 表示是否添加成功
    bool addNode(const Item &item, string type = "head"); 
    
    // 简介: 在ppos所指向结点的前面插入新结点
    // 参数:
    //     item : 结点的数据域的引用 \< LinkList::Item >
    //     ppos : 指向目标结点的指针 \< LinkList::Node* >
    // 返回值:
    //     返回一个布尔值, 表示是否添加成功
    bool addNode(const Item &item, Node * ppos); 
    
    // 简介: 在第pos个位置前插入新结点
    // 参数:
    //     item : 结点的数据域的引用 \< LinkList::Item >
    //     pos  : 将要插入结点的位置 \< int >
    // 返回值:
    //     返回一个布尔值, 表示是否添加成功
    bool addNode(const Item &item, int pos);
    
    // 简介: 删除ppos所指向的结点
    // 参数:
    //     ppos : 指向将要删除结点的指针 \< LinkList::Node* >
    // 返回值:
    //     返回一个布尔值, 表示是否删除成功
    bool removeNode(Node * ppos);  
    
    // 简介: 删除第pos个位置处的结点
    // 参数:
    //     pos : 将要删除的结点的位置 \< int >
    // 返回值:
    //     返回一个布尔值, 表示是否删除成功
    bool removeNode(int pos); 
    
    // 简介: 按指定方式删除结点
    // 参数: 
    //     str  : 删除结点的属性值 \< std::string >
    //     type : 删除结点的属性名, 默认是 "id" \< std::string >
    // 返回值:
    //     返回一个布尔值, 表示是否删除成功
    bool removeNode(const string str, string type = "id");  
    
    // 简介: 链表就地排序
    // 参数:
    //     key     : 指明用来排序比较的特征, 默认是 "id" \< std::string >
    //     reverse : 是否需要降序排序, 默认是 false \< bool >
    // 返回值: 无
    void sort(const string key = "id", bool reverse = false);  
    
    // 简介: 清空当前链表(只清除除头结点之外的结点)
    // 参数: 无
    // 返回值: 无
    void clean(); 
    
    // 简介: 遍历整个链表
    // 参数: 无
    // 返回值: 无
    void traverse() const;    
    
    // 简介: 获取当前链表的长度
    // 参数: 无
    // 返回值:
    //     返回当前的链表长度 \< int >
    int getSize() const;      
    
    // 简介: 获取第pos个结点
    // 参数: 
    //     pos : 要获取的结点位置 \< int >
    // 返回值:
    //     返回指向第pos结点的指针 \< LinkList::PNode > 
    PNode getNode(int pos) const;   
    
    // 简介: 获取学号为 id 的结点
    // 参数:
    //     id : 学生的学号 \< std::string >
    // 返回值:
    //     返回指向学号为 id 的结点的指针 \< LinkList::PNode >
    PNode getNode(const string id) const;  
    
    // 简介: 按指定方式查找结点
    // 参数: 
    //     str     : 要查找的属性值
    //     type    : 要查找的属性名, 默认是 "name" \< std::string >
    //     inverse : 是否反选, 默认为 false \< bool >
    // 返回值:
    //     返回一个向量, 它包含了所有符合查询条件的结点的数据域 \< std::vector\<Student::Student> >
    vector<Student> search(string str, string type = "name", bool inverse = false) const; 
    
    LinkList & operator=(const LinkList &L);
    
    // 简介: 合并两个链表
    // 参数: 
    //     L1 : 链表1 \< LinkList::LinkList >
    //     L2 : 链表2 \< LinkList::LinkList >
    // 返回值:
    //     返回L1和L2合并的新列表 \< LinkList::LinkList >
    friend LinkList operator+(const LinkList &L1, const LinkList &L2);
};
#endif