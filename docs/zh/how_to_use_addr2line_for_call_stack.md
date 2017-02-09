# 如何使用 addr2line 工具获取函数调用栈详细信息

## addr2line 是什么

addr2line （它是标准的 [GNU Binutils](https://www.gnu.org/software/binutils/) 中的一部分）是一个可以将指令的地址和可执行映像转换成文件名、函数名和源代码行数的工具。

## 如何获得 addr2line

Linux 系统一般会集成这个工具，本文重点介绍 Windows 系统下如何获取该工具。方法很多，我这里仅介绍两种方式

- 第一种：安装 MinGW（网上教程很多，自行搜索），安装后在其安装目录的 `bin` 文件夹里会包含 `addr2line.exe` ，此时只用保证环境变量 `path` 中包含该路径即可；
- 第二种（XP 平台除外）：在本项目的 `tools` 文件夹中已存放 `addr2line.exe` ，可以将其直接拷贝至 `C:\Windows` 下，或者将 CmBacktrace 仓库的 `tools` 文件夹路径添加至到环境变量 `path` 中，这样都能保证命令行工具能正常使用 `addr2line` 命令。

## addr2line 如何使用

使用 `addr2line --help` 可以看到如下介绍：

```
$addr2line --help
Usage: addr2line [option(s)] [addr(s)]
 Convert addresses into line number/file name pairs.
 If no addresses are specified on the command line, they will be read from stdin
 The options are:
  @<file>                Read options from <file>
  -a --addresses         Show addresses
  -b --target=<bfdname>  Set the binary file format
  -e --exe=<executable>  Set the input file name (default is a.out)
  -i --inlines           Unwind inlined functions
  -j --section=<name>    Read section-relative offsets instead of addresses
  -p --pretty-print      Make the output easier to read for humans
  -s --basenames         Strip directory names
  -f --functions         Show function names
  -C --demangle[=style]  Demangle function names
  -h --help              Display this information
  -v --version           Display the program's version

addr2line: supported targets: pe-x86-64 pei-x86-64 pe-bigobj-x86-64 elf64-x86-64 elf64-l1om elf64-k1om pe-i386 pei-i386 elf32-i386 elf64-little elf64-big elf32-little elf32-big plugin srec symbolsrec verilog tekhex binary ihex
Report bugs to <http://www.sourceware.org/bugzilla/>
```

这里常用的是以下参数

- `-e` ：指定可执行映像名称
- `-a` ：显示函数地址
- `-f` ：显示函数名称

例如命令 `addr2line -e CmBacktrace.out -f 08000a60 08000141 0800313f` 将会显示名称为 `CmBacktrace.out` 的可执行映像，在地址为 `08000a60` `08000141` `0800313f` 对应的函数名称及源代码信息。执行结果如下：

```
$addr2line -e CmBacktrace.out -a -f 08000a60 08000141 0800313f
fault_test_by_div0
D:\Program\STM32\CmBacktrace\demo\non_os\stm32f10x\app\src/fault_test.c:38
main
D:\Program\STM32\CmBacktrace\demo\non_os\stm32f10x\app\src/app.c:20
_call_main
??:?
```

> 更多使用指南，请 [参考官方说明文档](https://sourceware.org/binutils/docs-2.27/binutils/addr2line.html#addr2line) 。
