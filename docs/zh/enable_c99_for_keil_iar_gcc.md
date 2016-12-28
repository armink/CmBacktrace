# 一步开启 Keil/IAR/GCC 的 C99 支持

## 背景

C99 标准于 1999 年发布，至今（2016-12-28）将近 20 年的时间，相比早期的 C89 ，C99 有如下新特性（摘自 [维基百科](https://zh.wikipedia.org/wiki/C%E8%AF%AD%E8%A8%80#C99)）：

- 增加了对编译器的限制，比如源程序每行要求至少支持到 4095 字节，变量名函数名的要求支持到 63 字节（extern 要求支持到 31）。
- 增强了预处理功能。例如：
    - 宏支持取可变参数 #define Macro(...) `__VA_ARGS__`
    - 使用宏的时候，允许省略参数，被省略的参数会被扩展成空串。
    - 支持 // 开头的单行注释（这个特性实际上在C89的很多编译器上已经被支持了）
- 增加了新关键字 restrict, inline, _Complex, _Imaginary, _Bool
    - 支持 long long, long double _Complex, float _Complex 等类型
- 支持不定长的数组，即数组长度可以在运行时决定，比如利用变量作为数组长度。声明时使用 int a[var] 的形式。不过考虑到效率和实现，不定长数组不能用在全局，或 struct 与 union 里。
- 变量声明不必放在语句块的开头，for 语句提倡写成 for(int i=0;i<100;++i) 的形式，即i 只在 for 语句块内部有效。
- 允许采用（type_name）{xx,xx,xx} 类似于 C++ 的构造函数的形式构造匿名的结构体。
- 初始化结构的时候允许对特定的元素赋值，形式为：
    - `struct test{int a[3]，b;} foo[] =  { [0].a = {1}, [1].a = 2 };`
    - `struct test{int a, b, c, d;} foo =  { .a = 1, .c = 3, 4, .b = 5 };  // 3,4 是对 .c,.d 赋值的`
- 格式化字符串中，利用 \u 支持 unicode 的字符。
- 支持 16 进制的浮点数的描述。
- printf scanf 的格式化串增加了对 long long int 类型的支持。
- 浮点数的内部数据描述支持了新标准，可以使用 #pragma 编译器指令指定。
- 除了已有的 `__line__` `__file__` 以外，增加了 `__func__` 得到当前的函数名。
- 允许编译器化简非常数的表达式。
- 修改了 / % 处理负数时的定义，这样可以给出明确的结果，例如在C89中-22 / 7 = -3, -22 % 7 = -1，也可以-22 / 7= -4, -22 % 7 = 6。 而C99中明确为 -22 / 7 = -3, -22 % 7 = -1，只有一种结果。
- 取消了函数返回类型默认为 int 的规定。
- 允许在 struct 的最后定义的数组不指定其长度，写做 [](flexible array member)。
- const const int i 将被当作 const int i 处理。
- 增加和修改了一些标准头文件，比如定义 bool 的 <stdbool.h> ，定义一些标准长度的 int 的 <inttypes.h> ，定义复数的 <complex.h> ，定义宽字符的 <wctype.h> ，类似于泛型的数学函数 <tgmath.h>， 浮点数相关的 <fenv.h>。 在<stdarg.h> 增加了 va_copy 用于复制 ... 的参数。<time.h> 里增加了 struct tmx ，对 struct tm 做了扩展。
- 输入输出对宽字符以及长整数等做了相应的支持。

> C99 提供了众多的便利，也提高了程序开发的效率，但是一些嵌入式工具链并不是默认开启 C99，接下来将会针对不同的工具链，介绍如何开启 C99 模式。

## Keil 4

![keil4_enable_c99](https://raw.githubusercontent.com/armink/CmBacktrace/master/docs/zh/images/keil4_enable_c99.jpg)

## Keil 5

![keil5_enable_c99](https://raw.githubusercontent.com/armink/CmBacktrace/master/docs/zh/images/keil5_enable_c99.jpg)

## IAR

IAR 新建完的工程，默认开启 C99 ，如果工程没有开启，请使用下面的方法

![iar_enable_c99](https://raw.githubusercontent.com/armink/CmBacktrace/master/docs/zh/images/iar_enable_c99.png)

## GCC

在编译配置中增加 `-std=c99` 即可