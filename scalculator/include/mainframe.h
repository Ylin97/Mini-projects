#ifndef UI_H
#define UI_H
#include <iostream>
#define FLAG_IN  0
#define FLAG_OUT 1
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>
    #undef WINDOWS
    #define WINDOWS
    #define FORE_PALE_GREEN 10
    #define FORE_SKY_BLUE 9
    #define FORE_RED  12
    #define DEFAULT_FORECOLOR 7
    #define DEFAULT_BACKCOLOR 0
    // #define FOREGROUND_WHITE 7
    #define CLS "cls"
  #elif __linux__
    #define CLS "clear"
    #define FORE_PALE_GREEN 32
    #define FORE_SKY_BLUE 34
    #define FORE_RED 31
    #define DEFAULT_FORECOLOR 0
    #define DEFAULT_BACKCOLOR 0
  #endif
  #if defined(WINDOWS) || defined(__linux__)
    #ifdef WINDOWS
    /**
     * @brief 自定义控制台内容颜色，包括前景色和背景色。颜色值: 
     * 0=黑色, 8=灰色, 1=蓝色, 9=淡蓝色, 2=绿色, 10=淡绿色,
     * 3=浅绿色, 11=淡浅绿色, 4=红色, 12=淡红色, 5=紫色, 13=淡紫色,
     * 6=黄色, 14=淡黄色, 7=白色, 15=亮白色
     * 
     */
      struct SetColor {
        int fore_color;  // 前景色
        int back_color;  // 背景色
        bool bold;       // 是否加粗文本
        /**
         * @brief 设置标准输出的内容颜色
         * 
         * @param fc 前景色
         * @param bc 背景色
         */
        inline SetColor(int fc=DEFAULT_FORECOLOR, int bc=DEFAULT_BACKCOLOR, bool b=false)
              : fore_color(fc), back_color(bc), bold(b) {}
      };
      /**
       * @brief 设置控制台文本颜色。注意! 设置成功后会一直有效, 直到再次调用此函数设置为其他。
       * 
       * @param os std::ostream 类对象
       * @param color SetColor 类对象
       * @return std::ostream&
       */
      std::ostream & operator<<(std::ostream &os, SetColor color);
    #elif __linux__
    /**
    * @brief 前景颜色值: 默认=0, 黑色=30, 红色=31, 绿色=32, 黄色=33, 蓝色=34,
    * 紫色=35, 天蓝色=36,白色=37;
    * 背景颜色值: 默认=0, 黑色=40,
    * 红色=41, 绿色=42, 黄色=43, 蓝色=44, 紫色=45, 天蓝色=46, 白色=47
    * 
    */
      struct SetColor {
        int fore_color;  // 前景色
        int back_color;  // 背景色
        bool bold;       // 是否加粗文本
        /**
         * @brief 设置标准输出的内容颜色
         * 
         * @param fc 前景色
         * @param bc 背景色
         */
        inline SetColor(int fc=DEFAULT_FORECOLOR, int bc=DEFAULT_BACKCOLOR, bool b=false)
              : fore_color(fc), back_color(bc), bold(b) {}
      };
      /**
       * @brief 设置控制台文本颜色。注意! 设置成功后会一直有效, 直到再次调用此函数设置为其他。
       * 
       * @param os std::ostream 类对象
       * @param color SetColor 类对象
       * @return std::ostream&
       */
      std::ostream & operator<<(std::ostream &os, SetColor color);
    #endif
  #endif

/**
 * @brief 命令行交互主函数
 * 
 */
void cli_main(void);
/**
 * @brief 表达式文件操作主函数。从文件中读取表达式，并依次计算表达式。
 * 文件可以包含多个表达式，每个表达式单独占一行，不同表达式之间用空行隔开。
 * 
 * @param filename 文件名
 */
void file_main(const char *filename);
/**
 * @brief 命令行表达式操作主函数。在启动程序时，通过命令行直接给出表达式，不同
 * 表达式之间用空格隔开，如果表达式中本身含有空格，则应该用英文双引号将其引起来。
 * 
 * @param cnt 表达式个数
 * @param exprs 表达式集合
 */
void str_main(const int cnt, char *exprs[]);
/**
 * @brief 命令行交互模式的欢迎界面
 * 
 */
void welcome(void);
/**
 * @brief 显示帮助信息
 * 
 */
void show_help(void);
/**
 * @brief 打印提示符
 * 
 * @param cnt 行数计数
 * @param flag 输入提示(FLAG_IN) 或 输出提示(FLAG_OUT)
 */
void print_prompt(int cnt, int flag=FLAG_IN);
#endif