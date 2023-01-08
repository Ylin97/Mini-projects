#include <iostream>
#include <cstring>
#include "calclist.h"
#include "calculator.h"
#include "mainframe.h"
#define NDEBUG

using namespace std;

void test()
{
    // const char *expr = "-1+12+(-333*56/18)+log(10+8/2) +ln(22)+cos(30)  +sqrt(9)";
    // const char *expr = "-3+1+12+ log(100000/100)+2^2+sqrt(9)-4  +sin1+cos(3-1)-5";
    string expr = "12+ 0!^3+sqrt(9)+3!-4";
    CalcList nifix_expr, postfix_expr;

    std::cout << "源表达式: " << std::endl;
    std::cout << '\t' << expr << std::endl;
    list_initialize(nifix_expr);
    list_initialize(postfix_expr);
    expr_parse(expr, nifix_expr);
    std::cout << "中缀表达式: " << std::endl;
    list_display(nifix_expr);
    trans_postfix_expr(nifix_expr, postfix_expr);
    std::cout << "*********************************************************" << std::endl;
    std::cout << "后缀表达式: " << std::endl;
    list_display(postfix_expr);
    std::cout << "*********************************************************" << std::endl;
    std::cout << "计算结果: " << calc_postfix_expr(postfix_expr) << std::endl;

    list_destroy(nifix_expr);
    list_destroy(postfix_expr);

}

int main(int argc, char **argv)
{
    // test();
#if defined(WINDOWS) && defined(NDEBUG)
    system("chcp 65001");  // 更改系统的活动代码页为 utf8
    cout << endl;
#endif
    if (1 == argc)
        cli_main();
    else if (2 == argc 
             && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
        show_help();
    else if (3 == argc && (strcmp(argv[1], "-f") == 0))
        file_main(argv[2]);
    else
        str_main(argc - 1, argv + 1);

    return 0;
}
