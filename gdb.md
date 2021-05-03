# GDB 程序交互调试

```gdb 
gdb proc
break main
run
next
print var1
list
info b
nm 列出目标文件的符号清单
size 命令 程序运行时各个段的实际内存占用
string
fuser
xxd 以十六进制方式显示文件， 只显示文本信息

```

* A 绝对
* B BSS段中的符号
* C 表示引用未初始化的数据的一般符号





*pstatck工具*

功能：跟踪栈空间，显示每个的进程的栈跟踪

*strace*分析系统调用

```shell
strace -o output.txt -t -tt -e trace=all -p 28979

```

跟踪28979进程的所有系统调用, 并统计系统调用的时间

```shell
strace -p pid
```

查看进程在做什么

