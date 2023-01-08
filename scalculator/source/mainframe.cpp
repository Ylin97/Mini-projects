#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include "calculator.h"
#include "mainframe.h"

#ifdef WINDOWS
  std::ostream & operator<<(std::ostream &os, SetColor color)
  {
      HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(handle, (color.back_color << 4) | color.fore_color);
      return os;
  }
#elif __linux__
  std::ostream & operator<<(std::ostream &os, SetColor color)
  {
    if (color.bold && DEFAULT_BACKCOLOR == color.back_color)
        os << "\033[1;" << color.fore_color << 'm';
    else
        os << "\033[" << color.back_color << ';' << color.fore_color << 'm';
    return os;
  }
#endif

void cli_main(void)
{
    std::string expr;
    int count = 1;
    double answer = 0;
    auto origin_prec = std::cout.precision();  // 原始精度值

    CalcList nifix_expr, postfix_expr;
    list_initialize(nifix_expr);
    list_initialize(postfix_expr);
    welcome();
    print_prompt(count);

    while (getline(std::cin, expr))
    {
        expr = string_strip(expr);
        if (tolower(expr[0]) == 'q')
            break;
        if (expr == "cls")  // 清屏
        {
            system(CLS);
            print_prompt(++count);
            continue;
        }
        if (expr.find("scale") == 0)
        {
            int n = get_scale(expr);
            set_scale(n, origin_prec);
            print_prompt(++count);
            continue;
        }
        if (expr == "nosci")
        {
            nosci = true;
            std::cout << "关闭自动科学计数\n" << std::endl;
            print_prompt(++count);
            continue;
        }
        else if (expr == "sci")
        {
            nosci = false;
            set_scale(-1, origin_prec, false);
            std::cout << "开启自动科学计数\n" << std::endl;
            print_prompt(++count);
            continue;
        }

        expr_isright = EXPR_RIGHT;  // 重置表达式正误标志
        answer = 0;

        list_clear(nifix_expr);
        list_clear(postfix_expr);
        expr_parse(expr, nifix_expr);
        if (!expr_isright)
        {
            print_prompt(++count);
            continue;
        }
        trans_postfix_expr(nifix_expr, postfix_expr);
        if (!expr_isright)
        {
            print_prompt(++count);
            continue;
        }
        answer = calc_postfix_expr(postfix_expr);
        if (0 == expr_isright)
        {
            print_prompt(++count);
            continue;
        }
        print_prompt(count, FLAG_OUT);
        show_answer(answer);
        std::cout << '\n' << std::endl;
        print_prompt(++count);
    }
    list_destroy(nifix_expr);
    list_destroy(postfix_expr);
}

void file_main(const char *filename)
{
    std::ifstream fin(filename);
    std::string expr;
    int count = 1;
    double answer = 0;
    auto origin_prec = std::cout.precision();  // 原始精度值

    if (!fin.is_open())
    {
        std::cerr << "不能打开文件'" << filename << "'!\n" << std::endl;
        return;
    }

    CalcList nifix_expr, postfix_expr;
    list_initialize(nifix_expr);
    list_initialize(postfix_expr);

    while (getline(fin, expr))
    {
        expr = string_strip(expr);
        if (expr.empty() || expr == "\r")
            continue;
        if (expr.find("scale") == 0)
        {
            int n = get_scale(expr);
            set_scale(n, origin_prec);
            continue;
        }
        if (expr == "nosci")
        {
            nosci = true;
            std::cout << "关闭自动科学计数\n" << std::endl;
            continue;
        }
        else if (expr == "sci")
        {
            nosci = false;
            set_scale(-1, origin_prec, false);
            std::cout << "开启自动科学计数\n" << std::endl;
            continue;
        }
        
        std::cout << "表达式 [" << count << "]: " << expr << std::endl;
        std::cout << "值: ";
        
        expr_isright = EXPR_RIGHT;  // 重置表达式正误标志
        answer = 0;

        list_clear(nifix_expr);
        list_clear(postfix_expr);
        expr_parse(expr, nifix_expr);
        if (!expr_isright)
        {
            ++count;
            std::cout << std::endl;
            continue;
        }
        trans_postfix_expr(nifix_expr, postfix_expr);
        if (!expr_isright)
        {
            ++count;
            std::cout << std::endl;
            continue;
        }
        answer = calc_postfix_expr(postfix_expr);
        if (!expr_isright)
        {
            ++count;
            std::cout << std::endl;
            continue;
        }
        
        show_answer(answer);
        std::cout << '\n' << std::endl;
        ++count;
    }
    list_destroy(nifix_expr);
    list_destroy(postfix_expr);
    fin.close();
}

void str_main(const int cnt, char *exprs[])
{
    std::string expr;
    int count = 1;
    double answer = 0;
    auto origin_prec = std::cout.precision();  // 原始精度值

    CalcList nifix_expr, postfix_expr;
    list_initialize(nifix_expr);
    list_initialize(postfix_expr);
    
    for (int i = 0; i < cnt; ++i)
    {
        expr = string_strip(exprs[i]);
        if (expr.empty())
            continue;
        if (expr.find("scale") == 0)
        {
            int n = get_scale(expr);
            set_scale(n, origin_prec);
            continue;
        }
        if (expr == "nosci")
        {
            nosci = true;
            std::cout << "关闭自动科学计数\n" << std::endl;
            continue;
        }
        else if (expr == "sci")
        {
            nosci = false;
            set_scale(-1, origin_prec, false);
            std::cout << "开启自动科学计数\n" << std::endl;
            continue;
        }

        std::cout << "表达式 [" << count << "]: " << expr << std::endl;
        std::cout << "值: ";

        expr_isright = EXPR_RIGHT;  // 重置表达式正误标志
        answer = 0;

        list_clear(nifix_expr);
        list_clear(postfix_expr);
        expr_parse(expr, nifix_expr);
        if (!expr_isright)
        {
            ++count;
            std::cout << std::endl;
            continue;
        }
        trans_postfix_expr(nifix_expr, postfix_expr);
        if (!expr_isright)
        {
            ++count;
            std::cout << std::endl;
            continue;
        }
        answer = calc_postfix_expr(postfix_expr);
        if (!expr_isright)
        {
            ++count;
            std::cout << std::endl;
            continue;
        }
        show_answer(answer);
        std::cout << '\n' << std::endl;
        ++count;
    }
    list_destroy(nifix_expr);
    list_destroy(postfix_expr);
}

void welcome(void)
{
    std::cout << "---------------------------------------------------" << '\n';
    std::cout << "    ____      _            _       _                " << '\n'
              << "   / ___|__ _| | ___ _   _| | __ _| |_ ___  _ __    " << '\n'
              << "  | |   / _` | |/ __| | | | |/ _` | __/ _ \\| '__|   " << '\n'
              << "  | |__| (_| | | (__| |_| | | (_| | || (_) | |     " << '\n'
              << "   \\____\\__,_|_|\\___|\\__,_|_|\\__,_|\\__\\___/|_|" << '\n'
              << "                                                   " << '\n';
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << '\n';
    std::cout << "支持的运算符: + - * / ^ ! ln log sin cos tan sqrt ( )\n";
    std::cout << "提示: 输入 scale=n 指定精度为 n; 输入 scale 或 scale=-1 重置精度为默认值\n";
    std::cout << "      输入 cls 清屏\n";
    std::cout << "      输入 q 退出\n";
    std::cout << std::endl;
}

void show_help(void)
{
    std::cout << "用法: scalculator [expr...] [-h | --help] [-f <filename>]\n\n";
    std::cout << "程序有三种输入模式: 1)交互式读取 2)从命令行参数中读取 3)从文件中读取\n"
              << "无命令行参数时, 将打开交互式输入界面。\n\n";
    std::cout << "选项:\n";
    std::cout << "\texpr...,        表达式，即从命令行参数中读取表达式。可以给出多个表达式，不同\n"
              << "\t                表达式之间用空格隔开，如果表达式中本身含有空格, 则整个表达式\n"
              << "\t                应该用 \"\" 引起来\n"
              << "\t-h, --help      显示帮助信息\n"
              << "\t-f <filename>   从<filename>参数指定的文件中读取表达式。文件可以表达式单独占\n"
              << "\t                一行，不同表达式之间用空行隔开\n";
    std::cout << std::endl;
}

void print_prompt(int cnt, int flag)
{
    if (FLAG_IN == flag){
        std::cout << SetColor(FORE_PALE_GREEN) << "In ["
                  << SetColor(FORE_SKY_BLUE, DEFAULT_BACKCOLOR, true) << cnt
                  << SetColor(FORE_PALE_GREEN) << "]: ";
    } else if (FLAG_OUT == flag) {
        std::cout << SetColor(FORE_RED) << "Out["
                  << SetColor(FORE_SKY_BLUE, DEFAULT_BACKCOLOR, true) << cnt
                  << SetColor(FORE_RED) << "]: ";
    }
    std::cout<< SetColor(DEFAULT_FORECOLOR);
}