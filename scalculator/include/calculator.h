#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include "calclist.h"
#define MAXNUM_LEN    1000   // 数字的最大长度
#define	OPTR_NUM      14     // 操作符的数目
#define OP_FUNC_NUM   12     // 操作符操作函数数目
#define MAXNUM        100    // 最大操作数数目
#define EXPR_RIGHT    1      // 表达式正确
#define EXPR_ERROR    0      // 表达式有误
#define DEFAULT_SCALE -1     // 默认scale值

// 不采用科学计数法显示的数据范围限制
#define POSITIVE_MAX_NOSCI 999999.0 
#define POSITIVE_MIN_NOSCI 0.0001

// 表达式是否正确
extern int expr_isright;
// 打印结果的小数位数, 默认是 -1 表示由系统决定
extern int scale;
// 关闭自动科学计数法
extern bool nosci;

// 操作符集
const std::string OPSET[OPTR_NUM] = {
    "+", "-", "*", "/", "^", "!", "ln", "log", "sin", "cos", "tan", "sqrt", "(", ")" 
};

// 算符间的优先关系
const char Prior[OPTR_NUM][OPTR_NUM] = { 
   //'+', '-', '*', '/', '^', '!', 'ln','log','sin','cos','tan','sqrt','(', ')'
    {'>', '>', '<', '<', '<', '<', '<',  '<',  '<',  '<',  '<',  '<',  '<', '>'}, //'+'
    {'>', '>', '<', '<', '<', '<', '<',  '<',  '<',  '<',  '<',  '<',  '<', '>'}, //'-'
    {'>', '>', '>', '>', '<', '<', '<',  '<',  '<',  '<',  '<',  '<',  '<', '>'}, //'*'
    {'>', '>', '>', '>', '<', '<', '<',  '<',  '<',  '<',  '<',  '<',  '<', '>'}, //'/'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'^'
    {'>', '>', '>', '>', '>', '>', '>',  '>',  '>',  '>',  '>',  '>',  '>', '>'}, //'!'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'ln'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'log'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'sin'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'cos'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'tan'
    {'>', '>', '>', '>', '>', '<', '>',  '>',  '>',  '>',  '>',  '>',  '<', '>'}, //'sqrt'
    {'<', '<', '<', '<', '<', '<', '<',  '<',  '<',  '<',  '<',  '<',  '<', '='}, //'('
    {'>', '>', '>', '>', '>', '>', '>',  '>',  '>',  '>',  '>',  '>',  ' ', '>'}  //')'
};


// 操作函数结点
struct FuncNode {
    std::string name;
    void *pf;
};

typedef double (*pOPFuncSingle)(double);
typedef double (*pOPFuncDouble)(double, double);

///////////// 函数原型 //////////////

/**
 * @brief 删除字符串首尾的空白字符和英文双引号
 * 
 * @param s 待处理的字符串
 * @return std::string 处理后的字符串
 */
std::string string_strip(std::string s);
/**
 * @brief 查找操作符
 * 
 * @param expr 原始表达式
 * @param idx 开始查找的位置
 * @return std::string 找到的操作符
 */
std::string which_operator(const std::string &expr, std::size_t idx);
/**
 * @brief 获取操作符在操作符集 OPSET 中的位置 (数组下标)
 * 
 * @param op 操作符名
 * @return int 数组下标
 */
int get_operator_position(const std::string &op);
/**
 * @brief 获取两个操作符之间的优先级关系
 * 
 * @param i 第一个操作符在 OPSET 数组中的下标
 * @param j 第二个操作符在 OPSET 数组中的下标
 * @return char 
 */
char get_operator_prior(int i, int j);
/**
 * @brief 查找操作符对应的操作函数 
 * 
 * @param name 操作符名
 * @return void* 操作符对应的函数
 */
void * find_op_func(const std::string name);
/**
 * @brief 设置操作数结点
 * 
 * @param pnode 指向待设置的结点的指针
 * @param num 操作数字符数组
 * @param sign 正负号
 * @return Node* 指向设置后的结点的指针
 */
Node * set_num_node(Node *pnode, char *num, int sign);
/**
 * @brief 设置操作符结点
 * 
 * @param pnode 指向对设置的结点的指针
 * @param op 操作符名
 * @return Node* 指向设置后的结点的指针
 */
Node * set_op_node(Node *pnode, const std::string &op);
/**
 * @brief 获取用户定义的 scale 值
 * 
 * @param s 包含 scale 值的字符串
 * @return int scale 值
 */
int get_scale(std::string s);
/**
 * @brief 设置 scale 值
 * 
 * @param n 指定的 scale 值
 * @param origin_prec 默认精度值
 */
void set_scale(int n, std::streamsize origin_prec, bool flag=true);
/**
 * @brief 四舍五入到最近的整数
 * 
 * @param x 操作数
 * @return double 结果值
 */
double round_double(double x);
/**
 * @brief 打印计算结果
 * 
 * @param ans 计算结果
 */
void show_answer(double ans);
/**
 * @brief 是否需要使用科学计数法
 * 
 * @param ans 计算结果
 * @return true 使用科学计数法
 * @return false 不使用科学计数法
 */
bool need_sci(double ans);

/////////// 操作符函数 ///////////

/**
 * @brief 加法操作
 * 
 * @param x 加数1
 * @param y 加数2
 * @return double 两数之和
 */
double add(double x, double y);
/**
 * @brief 减法操作
 * 
 * @param x 被减数
 * @param y 减数
 * @return double 两数之差
 */
double subtract(double x, double y);
/**
 * @brief 乘法操作
 * 
 * @param x 被乘数
 * @param y 乘数
 * @return double 两数之积
 */
double multiply(double x, double y);
/**
 * @brief 除法操作
 * 
 * @param x 被除数
 * @param y 除数
 * @return double 两数之商
 */
double divide(double x, double y);
/**
 * @brief 乘方操作
 * 
 * @param x 底数
 * @param idx 指数
 * @return double 幂值
 */
double power(double x, double idx);
/**
 * @brief 计算阶乘
 * 
 * @param x 操作数
 * @return double 操作数的阶乘值
 */
double calc_factorial(double x);
/**
 * @brief 计算自然对数
 * 
 * @param x 操作数
 * @return double 自然对数值
 */
double calc_ln(double x);
/**
 * @brief 计算以 10 为底的对数
 * 
 * @param x 操作数
 * @return double 以 10 为底的对数值
 */
double calc_log(double x);
/**
 * @brief 计算正弦函数值
 * 
 * @param x 操作数
 * @return double 正弦函数值
 */
double calc_sin(double x);
/**
 * @brief 计算余弦函数值
 * 
 * @param x 操作数
 * @return double 余弦函数值
 */
double calc_cos(double x);
/**
 * @brief 计算正切函数值
 * 
 * @param x 操作数
 * @return double 正切函数值
 */
double calc_tan(double x);
/**
 * @brief 计算平方根
 * 
 * @param x 操作数
 * @return double 平方根值
 */
double calc_sqrt(double x);

////////////// 计算器主要函数 ////////////////

/**
 * @brief 解析表达式，并用将其存储为中缀表达式链表
 * 
 * @param origin_expr 原始表达式字符串
 * @param nifix_expr 目标中缀表达式
 */
void expr_parse(const std::string &origin_expr, CalcList &nifix_expr);
/**
 * @brief 将中缀表达式转换为后缀表达式
 * 
 * @param nifix_expr 原始中缀表达式
 * @param postfix_expr 目标后缀表达式
 */
void trans_postfix_expr(CalcList &nifix_expr, CalcList &postfix_expr);
/**
 * @brief 计算后缀表达式的值
 * 
 * @param postfix_expr 用于计算的后缀表达式
 * @return double 表达式的计算结果
 */
double calc_postfix_expr(const CalcList &postfix_expr);

// 操作数对应的操作函数顺序表
const FuncNode op_funcs[OP_FUNC_NUM] = {
    {"+", (void *)add},
    {"-", (void *)subtract},
    {"*", (void *)multiply},
    {"/", (void *)divide},
    {"^", (void *)power},
    {"!", (void *)calc_factorial},
    {"ln", (void *)calc_ln},
    {"log", (void *)calc_log},
    {"sin", (void *)calc_sin},
    {"cos", (void *)calc_cos},
    {"tan", (void *)calc_tan},
    {"sqrt", (void *)calc_sqrt}
};
#endif