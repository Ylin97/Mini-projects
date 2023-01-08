#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <iomanip>
#include "calculator.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::ios_base;

// 表达式是否正确
int expr_isright = EXPR_RIGHT;
// 打印结果的小数位数, 默认是 -1 表示由系统决定
int scale = -1;
// 关闭自动科学计数法
bool nosci = false;

string string_strip(string s){
    size_t n = s.find_last_not_of(" \r\n\t\"");
    if (n != string::npos){
        s.erase(n + 1, s.size() - n);
    }
    n = s.find_first_not_of(" \r\n\t\"");
    if (n != string::npos){
        s.erase(0, n);
    }
    return s;
}

std::string which_operator(const string &expr, size_t idx)
{   
    string op;
    bool isfound = false;

    for (int i = 0; i < OPTR_NUM; ++i)
    {
        if (expr.find(OPSET[i], idx) == idx)
        {
            op = OPSET[i];
            isfound = true;
        }
    }

    if (!isfound)
    {
        // cerr << "表达式有误!\n" << endl;
        expr_isright = EXPR_ERROR;
    }
    return op;
}

int get_operator_position(const string &op)
{
    int i;
    for (i = 0; i < OPTR_NUM; ++i)
    {
        if (op == string(OPSET[i]))
            break;
    }
    return i;
}

char get_operator_prior(int i, int j)
{
    return Prior[i][j];
}

void expr_parse(const string &origin_expr, CalcList &nifix_expr)
{
    int sign = 1;
    size_t i = 0;
    string expr = origin_expr;
    // 删除 expr 首尾的空白字符
    expr = string_strip(expr);
    size_t len = expr.size();

    if ('=' == expr[len - 1])  // 忽略表达式末尾的 '=' 号
        --len;  
    
    while (i < len && expr_isright) 
    {
        char num[MAXNUM_LEN] {};  // 存放数字字符串
        string op;
        size_t j;
        for (j = 0; i < len;)
        {
            if (isspace(expr[i]))
            {
                ++i;
            }
            else if (isdigit(expr[i]) || '.' == expr[i])
            {
                num[j] = expr[i];
                ++j;
                ++i;
            }
            else if ('-' == expr[i] 
                      && (0 == i || std::strchr("(gnst/*^+", expr[i - 1])))
            {
                sign *= -1;
                ++i;
            }
            else if ((op = which_operator(expr, i)), !op.empty())
            {
                // 操作数存入链表
                if (num[0] != '\0')
                {
                    num[j] = '\0';
                    Node *pnode_num = new Node;
                    set_num_node(pnode_num, num, sign);
                    list_push_back(nifix_expr, pnode_num);
                    num[0] = '\0';  // 表示数据已经存储

                    // 处理 2log20, 2sin1 等情况
                    if (std::strchr("lscts", expr[i]))
                    {
                        // 操作符存入链表
                        Node *pnode_op1 = new Node;
                        set_op_node(pnode_op1, "*");
                        list_push_back(nifix_expr, pnode_op1);
                    }
                }
                
                // 操作符存入链表
                Node *pnode_op = new Node;
                set_op_node(pnode_op, op);
                list_push_back(nifix_expr, pnode_op);
                i += op.size();
                break;
            }
            else
            {
                cerr << "表达式有误!\n" << endl;
                expr_isright = EXPR_ERROR;
                return;
            }
        }
        if (num[0] != '\0')
        {
            num[j] = '\0';
            Node *pnode_num = new Node;
            set_num_node(pnode_num, num, sign);
            list_push_back(nifix_expr, pnode_num);
            num[0] = '\0';  // 表示数据已经存储
        }
        sign = 1;
    }
}

void trans_postfix_expr(CalcList &nifix_expr, CalcList &postfix_expr)
{
    Node *curr = nifix_expr.head->next;
    int op_stack[100] {};  // 存储操作符在 OPSET 中的下标
    int top = 0;
    for (int i = 0; i < nifix_expr.length; ++i)
    {
        Node *pnode_num = nullptr;
        Node *pnode_op = nullptr;
        int curr_pos = 0;
        switch (curr->type)
        {
        case NUMBER: 
            pnode_num = new Node;
            list_copy_node(curr, pnode_num);
            list_push_back(postfix_expr, pnode_num);
            break;
        case OPERATOR:
            if (0 == top)
            {
                op_stack[top++] = get_operator_position(curr->op);
            }
            else
            {
                curr_pos = get_operator_position(curr->op);
                while (top > 0 
                        && get_operator_prior(op_stack[top - 1], curr_pos) != '<')
                {
                    --top;
                    if ("(" == OPSET[op_stack[top]])
                    {
                        break;
                    }
                    pnode_op = new Node;
                    set_op_node(pnode_op, OPSET[op_stack[top]]);
                    list_push_back(postfix_expr, pnode_op);
                }
                if (curr->op != ")")
                    op_stack[top++] = get_operator_position(curr->op);
            }
            break;
        }
        curr = curr->next;
    }
    // 处理操作符栈里面剩余的操作符
    while (top-- > 0)
    {
        Node *pnode_op = new Node;
        set_op_node(pnode_op, OPSET[op_stack[top]]);
        list_push_back(postfix_expr, pnode_op);
    }
}

double calc_postfix_expr(const CalcList &postfix_expr)
{
    double stack[MAXNUM] {};
    int top = 0;
    Node *curr = postfix_expr.head->next;
    double answer = 0, tmp_val;
    pOPFuncSingle calc_func_s;
    pOPFuncDouble calc_func_d;

    while (curr && expr_isright)
    {
        switch (curr->type)
        {
        case NUMBER:
            stack[top++] = curr->num;
            break;
        case OPERATOR:
            if ("ln" == curr->op || "log" == curr->op
                || "sin" == curr->op || "cos" == curr->op 
                || "tan" == curr->op || "sqrt" == curr->op || "!" == curr->op
            )
            {
                calc_func_s = (pOPFuncSingle)find_op_func(curr->op);
                tmp_val = calc_func_s(stack[--top]);
                stack[top++] = tmp_val;
            }
            else if (top >= 2)
            {
                calc_func_d = (pOPFuncDouble)find_op_func(curr->op);
                tmp_val = calc_func_d(stack[top - 2], stack[top - 1]);
                top -= 2;
                stack[top++] = tmp_val;
            }
            else
            {
                std::cout << "表达式有误!\n" << std::endl;
                expr_isright = EXPR_ERROR;
                return 0;
            }
            break;
        }
        curr = curr->next;
    }
    return stack[0];
}

void * find_op_func(const string name)
{
    int i;
    for (i = 0; i < OP_FUNC_NUM; ++i)
    {
        if (op_funcs[i].name == name)
            break;
    }
    return op_funcs[i].pf;
}

Node * set_num_node(Node *pnode, char *num, int sign)
{
    double val;
    val = atof(num) * sign;
    pnode->num = val;
    pnode->type = NUMBER;
    pnode->next = nullptr;
    return pnode;
}

Node * set_op_node(Node *pnode, const string &op)
{
    pnode->op = op;
    pnode->type = OPERATOR;
    pnode->next = nullptr;
    return pnode;
}

int get_scale(std::string s)
{
    char *nospace = new char[s.size() + 1];
    int i, j, prec;
    // 去除字符串中的空白字符
    for (i = 0, j = 0; i < s.size(); ++i)
        if (!std::isspace(s[i]))
            nospace[j++] = s[i];
    nospace[j] = '\0';
    std::string s2(nospace);
    if (s2 == "scale")
        prec = -1;
    else if (s2.find('=') == 5 && s2.substr(0, 5) == "scale")
    {
        std::string num_str = s2.substr(6);
        for (auto x : num_str)
            if (!std::isdigit(x))
                return DEFAULT_SCALE;
        prec = std::stoi(num_str);
    }
    if (prec < 0)
        prec = DEFAULT_SCALE;
    delete [] nospace;
    return prec;
}

void set_scale(int new_scale, std::streamsize origin_prec, bool flag)
{
    scale = new_scale;
    if (scale == -1)
    {
        std::cout.precision(origin_prec);
        std::cout.unsetf(ios_base::floatfield);
        if (flag)
            std::cout << "已设置精度值为: " << "默认" << '\n' << std::endl;
    }
    else
    {
        std::cout.precision(scale);
        std::cout.setf(ios_base::fixed, ios_base::floatfield);
        std::cout << "已设置精度值为: " << scale << '\n' << std::endl;
    }
}

double round_double(double x)
{
    return (x > 0.0) ? floor(x + 0.5) : ceil(x - 0.5);
}

void show_answer(double ans)
{
    double ans_abs = fabs(ans);
    if (0 == scale)
    {
        if (need_sci(ans))
        {
            cout << round_double(ans) << " (输入 nosci 可关闭自动科学计数)";
        }
        else if (ans_abs > POSITIVE_MAX_NOSCI || ans_abs < POSITIVE_MIN_NOSCI)
        {
            cout << std::fixed << round_double(ans) << " (输入 sci 可开启自动科学计数法)";
            cout.unsetf(ios_base::floatfield);
        }
        else
        {
            cout << round_double(ans);
        }
    }
    else if (need_sci(ans))
    {
        cout << ans << " (输入 nosci 可关闭自动科学计数)";
    }
    else if (ans_abs > POSITIVE_MAX_NOSCI 
             || (ans_abs < POSITIVE_MIN_NOSCI && ans_abs != 0))
    {
        cout << std::fixed << ans << " (输入 sci 可开启自动科学计数)";
        cout.unsetf(ios_base::floatfield);
    }
    else
    {
        cout << ans;
    }
}

bool need_sci(double ans)
{
    double ans_abs = fabs(ans);
    if (nosci | scale != -1)
        return false;
    else if (ans_abs > POSITIVE_MAX_NOSCI 
             || (ans_abs < POSITIVE_MIN_NOSCI && ans_abs != 0)) 
        return true;
    return false;
}

double add(double x, double y)
{
    return x + y;
}

double subtract(double x, double y)
{
    return x - y;
}

double multiply(double x, double y)
{
    return x * y;
}

double divide(double x, double y)
{
    return x / y;
}

double power(double x, double idx)
{
    return pow(x, idx);
}

double calc_factorial(double x)
{
    long long x2 = (long long)x;
    long long res = 1;
    if (x2 < 0)
        return 0;
    if (0 == x2)
        return 1;
    for (long long i = 1; i <= x2; ++i)
        res *= i;
    return (double)res;
}

double calc_ln(double x)
{
    return log(x);
}

double calc_log(double x)
{
    return log10(x);
}

double calc_sin(double x)
{
    return sin(x);
}

double calc_cos(double x)
{
    return cos(x);
}

double calc_tan(double x)
{
    return tan(x);
}

double calc_sqrt(double x)
{
    return sqrt(x);
}