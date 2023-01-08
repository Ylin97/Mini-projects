#include <iostream>
#include "calclist.h"

bool list_initialize(CalcList &L)
{
    // 分配头结点
    L.head = new Node;
    if (!L.head)
        return false;
    L.head->type = '\0';
    L.head->num = 0;
    // L.head->op = "";
    L.head->next = nullptr;
    L.rear = L.head;
    L.length = 0;
    return true;
}

void list_destroy(CalcList &L)
{
    Node *p = L.head->next;
    
    while (p)
    {
        delete L.head;
        L.head = p;
        p = p->next;
    }
    delete L.head;
}

void list_clear(CalcList &L)
{
    if (0 == L.length)
        return;
    Node *p = L.head->next;
    Node *q = p->next;
    while (q)
    {
        delete p;
        p = q;
        q = q->next;
    }
    delete p;
    L.head->next = nullptr;
    L.rear = L.head;
    L.length = 0;
}

void list_push_back(CalcList &L, Node *pnode)
{
    L.rear->next = pnode;
    L.rear = L.rear->next;
    ++L.length;
}

void list_display(const CalcList &L)
{
    Node *p = L.head->next;
    std::cout << '\t';
    for (int i = 0;  i < L.length; ++i)
    {
        // std::cout << "Node" << i + 1 << ": " << "type:" << p->type;
        switch (p->type)
        {
            case NUMBER:
                std::cout << p->num << " ";
                break;
            case OPERATOR:
                std::cout << p->op << " ";
                break;
        }
        p = p->next;
    }
    std::cout << std::endl;
}

Node * list_copy_node(const Node *pold, Node *pnew)
{
    pnew->num = pold->num;
    pnew->op = pold->op;
    pnew->type = pold->type;
    pnew->next = nullptr;
    return pnew;
}