#ifndef CALCLIST_H
#define CALCLIST_H
#define OPERATOR  'o'
#define NUMBER    'n'
#include <string>
// 结点定义
struct Node {
    char type;  // 数据类型, 'OP'为操作符, 'NUM'为操作数
    std::string op;
    double num;
    struct Node *next;
};
// 链表定义
struct CalcList {
    Node *head, *rear;
    size_t length;
};

// 链表操作
/**
 * @brief  初始化链表
 * 
 * @param L 链表
 * @return true  初始化成功
 * @return false 初始化失败
 */
bool list_initialize(CalcList &L);
/**
 * @brief 销毁链表
 * 
 * @param L 链表
 */
void list_destroy(CalcList &L);
/**
 * @brief 清空链表
 * 
 * @param L 链表
 */
void list_clear(CalcList &L);
/**
 * @brief 在链表尾部插入新结点
 * 
 * @param L 链表
 * @param node 待插入的结点 
 */
void list_push_back(CalcList &L, Node *pnode);
/**
 * @brief 显示链表内容
 * 
 * @param L 链表
 */
void list_display(const CalcList &L);
/**
 * @brief 复制结点内容到新结点, 新结点的 next 设置为空
 * 
 * @param pold 源结点
 * @param pnew 新结点
 * @return Node* 指向新结点的指针
 */
Node * list_copy_node(const Node *pold, Node *pnew);
#endif