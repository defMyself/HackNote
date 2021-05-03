# GOT和PLT

1. 动态链接库里面函数的地址如何获得？
2. 



Ulrich Drepper的How to write share library

真正动态库中函数地址的解析是第一次调用的时候做的，然后如果再次用到动态库的解析过的函数，就直接用第一次解析的结果。很自然的想法就是，一定有地方存储函数的地址，否则第一次解析出来的结果，第二次调用也没法利用。 这个存储动态库函数的地方就要GOT，Global Offset Table。



延迟绑定的基本原理。假如存在一个bar函数，这个函数在PLT中的条目为bar@plt，在GOT中的条目为bar@got，那么在第一次调用bar函数的时候，首先会跳转到PLT，伪代码如下：

```assembly
bar@plt:

jmp bar@got

patch bar@got
```

这里会从PLT跳转到GOT，如果函数从来没有调用过，那么这时候GOT会跳转回PLT并调用patch bar@got，这一行代码的作用是将bar函数真正的地址填充到bar@got，然后跳转到bar函数真正的地址执行代码。当我们下次再调用bar函数的时候，执行路径就是先后跳转到bar@plt、bar@got、bar真正的地址。

![img](https://img-blog.csdnimg.cn/20191103180842955.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQxMDcxNjQ2,size_16,color_FFFFFF,t_70)

