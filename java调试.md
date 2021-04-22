# Java代码调试

```java
public class HelloJDB {
	public static void main(String[] args) {
		int i = 5;
		int j = 6;
		int sum = add(i, j);
		System.out.println(sum);
		
		sum = 0;
		for(i=0; i<100; i++) {
			sum += 1;
		}
		System.out.println(sum);
	}
	
	public static int add(int augend, int addend) {
		int sum = augend + addend;
		return sum;
	}
}
```

调试命令
```shell
javac -g -d bin src/HelloJDB.java
```

```shell
jdb -classpath .:./bin HelloJDB
```

## 调试基础
* 方法断点
* 行断点
* 条件断点
* 临时断点

`jdb -h`帮助命令

在`main`方法开始处设置断点
```shell
stop in HelloJDB.main
```
`run`命令 程序会在`main()`的开始处停下
此时可以使用`local`命令查看变量
用`step`命令运行下一行代码

`list` 命令查看运行到了源代码的什么位置
```use ./src```
当`HelloJDB.java`和`HelloJDB.class`不在同一目录时使用

*调试遇到方法调用，先看调用结果对不对*
`next`将方法执行完
`step`进入方法内部
`step up` 方法执行完， 返回到调用处
`cont` 运行到下一个断点
`stop` 查看断点集合

*JDB不支持条件断点和临时断点*

`where` 显示栈帧

## 递归调试
## 多线程调试
## GDB调试Java程序

