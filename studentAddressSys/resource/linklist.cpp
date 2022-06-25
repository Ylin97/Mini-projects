// LinkList 类方法实现
#include <iostream>
#include <iomanip>
#include <vector>
#include "linklist.h"
using namespace std;

LinkList::LinkList()
{
    Node *hnode = new Node;  // 头结点
    hnode->next = nullptr;
    head = tail = hnode;
    size        = 0;
}

LinkList::LinkList(const LinkList &L)
{
    Node *hnode = new Node;  // 头结点
    hnode->next = nullptr;
    head = tail = hnode;
    size = 0;
    Node *p = L.head->next;
    int len = L.size;
    for (int i = 0; i < len; i++)
    {
        Node *pnewNode = new Node;
        pnewNode->data = p->data;
        pnewNode->next = nullptr;
        tail->next = pnewNode;
        tail = pnewNode;
        p = p->next;
        ++size;
    }
}

LinkList::~LinkList()
{
    Node *ptmp;

    while (head)
    {
        ptmp = head;
        head = head->next;
        delete ptmp;
    }
}

bool LinkList::isEmpty()
{
    if (0 == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LinkList::addNode(const Item &item, string type)
{
    if (type != "head" && type != "tail")
    {
        cerr << "插入类型只能为'head' 或 'tail'!" << endl;
        return false;
    }

    Node *pnewNode = new Node;
    if (!pnewNode)
    {
        cerr << "不能分配新结点所需的内存!" << endl;
        return false;
    }
    pnewNode->data = item;
    pnewNode->next = nullptr;
    if (type == "head")
    {
        pnewNode->next = head->next;
        head->next = pnewNode;
        if (tail == head)
        {
            tail = pnewNode;
        }
    }
    else if (type == "tail")
    {
        tail->next = pnewNode;
        tail = pnewNode;
    }
    ++size;
    return true;
}

bool LinkList::addNode(const Item &item, Node * ppos)
{
    if (!ppos)
    {
        cerr << "不能在空指针 ppos 指向的位置之前插入新结点!" << endl;
        return false;
    }
    else if (ppos == head)
    {
        cerr << "不能在指针 ppos 指向的位置(头结点)之前插入新结点!" << endl;
        return false;
    }
    // 分配新结点
    Node *pnewNode = new Node;
    if (!pnewNode)  // 内存分配失败
    {
        cerr << "不能分配新结点所需的内存!" << endl;
        return false;
    }
    pnewNode->data = item;
    pnewNode->next = nullptr;
    // 在ppos所指向结点的后面插入新结点
    if (0 == size)  // 链表为空时
    {
        head->next = tail = pnewNode;
    }
    else
    {
        pnewNode->next = ppos->next;
        ppos->next = pnewNode;
        // 交换数据 (其效果等效于在ppos所指向结点之前插入新结点)
        Item tmp = pnewNode->data;
        pnewNode->data = ppos->data;
        ppos->data = tmp;
    }
    ++size;
    return true;
}

bool LinkList::addNode(const Item &item, int pos)
{
    if (pos < 1)
    {
        cerr << "结点的插入位置应该大于等于1!" << endl;
        return false;
    }
    else if (pos > size)
    {
        cerr << "结点的插入位置超过了链表长度!" << endl;
        return false;
    }
    int i = 1;
    Node *p = head->next;
    while (i < pos)
    {
        p = p->next;
        ++i;
    }
    return addNode(item, p);
}

bool LinkList::removeNode(Node * ppos)
{
    if (!ppos)
    {
        cerr << "不能输出空指针指向对象的!" << endl;
        return false;
    }
    else if (nullptr == head->next)
    {
        cerr << "不能从空链表中删除结点!" << endl;
        return false;
    }

    if (ppos == tail)  // 如果删除的是尾结点
    {
        Node *p = head;
        while (p->next != ppos)
        {
            p = p->next;
        }
        delete tail;
        tail = p;
        tail->next = nullptr;
    }
    else
    {
        // 用ppos所指向结点的后一个结点的数据填充ppos所指向结点
        // 然后删除ppos所指向结点的后一个结点
        Node *ptmp = ppos->next;
        ppos->data = ppos->next->data;
        ppos->next = ppos->next->next;
        delete ptmp;
    }
    --size;
    return true;
}  

bool LinkList::removeNode(int pos)
{
    if (pos < 1)
    {
        cerr << "删除结点的位置应该大于或等于1!" << endl;
        return false;
    }
    else if (0 == size)
    {
        cerr << "不能从空链表中删除结点!" << endl;
        return false;
    }
    else if (pos > size)
    {
        cerr << "删除结点的位置超出链表长度!" << endl;
        return false;
    }

    Node *p = head->next;
    int i = 1;
    while (i < pos)
    {
        p = p->next;
        ++i;
    }
    return removeNode(p);
}

bool LinkList::removeNode(const string str, string type)
{
    Node * p = head->next;
    if (type == "id")
    {
        while (p && (p->data.getID() != str))
        {
            p = p->next;
        }
        if (p)
        {
            return removeNode(p);
        }
    }
    else if (type == "name")
    {
        while (p && (p->data.getName() != str))
        {
            p = p->next;
        }
        if (p)
        {
            return removeNode(p);
        }
    }
    return false;
}

bool LinkList::cmpfunc(const Node *x, const Node *y,
                    const string key, const bool reverse)
{
    string choices = "idnameaddress";
    if (choices.find(key) == choices.npos)
    {
        cerr << "WARN: 仅支持按ID/姓名/籍贯排序!!!下面将按学号排序\n";
    }
    bool res = true;
    if (key == "id")
    {
        // res = atoi(x->data.getID().c_str()) > \
        //         atoi(y->data.getID().c_str());
        res = x->data.getID() > y->data.getID();
    }
    else if (key == "name")
    {
        res = x->data.getName() > y->data.getName();
    }
    else if (key == "address")
    {
        res = x->data.getAddress() > y->data.getAddress();
    }
    if (reverse)
    {
        res = (res ^ true);  // '^' 是 '按位异或' 运算符
    }
    return res;
}

void LinkList::sort(const string key, bool reverse)
{
    Node ** temp_arr = new Node* [size];  // 用来对结点指针进行排序
    Node *p = head->next;
    // 冒泡排序
    for (int i = 0; i < size; i++)
    {
        temp_arr[i] = p;
        p = p->next;
    }
    for (int i = 0; i < size - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (cmpfunc(temp_arr[j], temp_arr[j + 1], key, reverse))
            {
                Node *t = temp_arr[j];
                temp_arr[j] = temp_arr[j + 1];
                temp_arr[j + 1] = t;
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
    for (int i = 0; i < size; i++)
    {
        temp_arr[i]->next = temp_arr[i + 1];
    }
    head->next = temp_arr[0];
    tail = temp_arr[size - 1];
    tail->next = nullptr;
    delete [] temp_arr;
}

void LinkList::clean()
{
    Node *p = head->next;
    Node *ptmp;
    while (p)
    {
        ptmp = p;
        p = p->next;
        delete ptmp;
    }
    head->next = nullptr;
    tail = head;
    size = 0;
}

void LinkList::traverse() const
{
    Node *p = head->next;
    for (int i = 0; i < size; i++)
    {
        p->data.show();
        p = p->next;
    }
}

int LinkList::getSize() const
{
    return size;
}

LinkList::PNode LinkList::getNode(int pos) const
{
    if (pos < 1)
    {
        cerr << "查找结点的位置应该大于或等于1!" << endl;
        return nullptr;
    }
    else if (pos > size)
    {
        cerr << "查找结点的位置超出链表长度!" << endl;
        return nullptr;
    }
    PNode p = head->next;
    int i = 1;
    while (i < pos)
    {
        p = p->next;
        ++i;
    }
    return p;
}

LinkList::PNode LinkList::getNode(const string id) const
{
    PNode p = head->next;
    while (p && (p->data.getID() != id))
    {
        p = p->next;
    }
    if (p)
    {
        return p;
    }
    else 
    {
        return nullptr;
    }
}

vector<Student> LinkList::search(string str, string type, bool inverse) const
{
    vector<Item> res_vector;
    vector<Item> res_vector_inverse;
    Node *p = head->next;
    string choice = "idnameaddress";
    if (choice.find(type) == choice.npos)
    {
        cerr << "暂时只支持按学号/姓名/籍贯方式查询!" << endl;
        return res_vector;
    }

    if (type == "id")  
    {
        while (p)
        {
            if (p->data.getID() == str)
            {
                res_vector.push_back(p->data);
                // break;
            }
            else
            {
                res_vector_inverse.push_back(p->data);
            }
            p = p->next;
        }
    }
    else if (type == "name")
    { // 名字可能重名, 所以要遍历整个列表
        while (p)
        {
            if (p->data.getName() == str)
            {
                res_vector.push_back(p->data);
            }
            else
            {
                res_vector_inverse.push_back(p->data);
            }
            p = p->next;
        }
    }
    else if (type == "address")
    { // 名字可能重名, 所以要遍历整个列表
        while (p)
        {
            if (p->data.getAddress() == str)
            {
                res_vector.push_back(p->data);
            }
            else
            {
                res_vector_inverse.push_back(p->data);
            }
            p = p->next;
        }
    }
    // cerr << "未找到\"" << type << ": " << str << "\"!\n";
    if (inverse)
    {
        return res_vector_inverse;
    }
    else
    {
        return res_vector;
    }
}

LinkList & LinkList::operator=(const LinkList &L)
{
    if (this == &L)
    {
        return *this;
    }
    this->clean();  // 清空原来的链表数据
    Node *p = L.head->next;
    int len = L.size;
    for (int i = 0; i < len; i++)
    {
        this->addNode(p->data, "tail");
        p = p->next;
    }
    size = L.size;
    return *this;
}

LinkList operator+(const LinkList &L1, const LinkList &L2)
{
    LinkList res_L = L1;
    LinkList::Node *p = L2.head->next;
    int len = L2.size;
    for (int i = 0; i < len; i++)
    {
        res_L.addNode(p->data, "tail");
        p = p->next;
    }
    res_L.size = L1.size + L2.size;
    return res_L;
}