# Frida 入门
* 动态二进制插桩 : 

## 1. 二进制插桩
==动态和静态二进制插桩对比==
1. SBI ： 执行前插入，永久改变可执行文件
2. DBI ： 在程序运行时实时地插入额外代码和数据，对可执行文件没有任何永久改变


## 2. DBI的作用
1. 访问进程内存
2. 应用程序运行时覆盖一些功能
3. 从导入的类中调用函数
4. 在堆上查找对象实例并使用这些对象实例
5. Hook, 跟踪和拦截函数

## 3. 基本使用

#### Frida 工具组成
1. frida CLI

```shell
# 连接frida,注入到chrome应用的进程上
frida -U com.android.chrome

# 将test.js文件注入到设备上的进程里 
frida -U com.android.chrome -l test.js

```

2. frida-ps : 列出进程列表
```shell
# 连接frida到一个USB设备上，同事列出设备上运行的进程
frida-ps -U

# 运行中的程序
frida-ps -Ua

# 安装的程序
frida-ps -Uai

# 连接指定设备
frida-ps -D 0000101011


```


### Java API

```javascript
// 我们的线程附加到Java的虚拟机上，
Java.perform(fn)

Java.use(className)
    $new()
    $dispose()

Java.cast(handle, klass)

```


### 3. Frida Hook实战
1. 信息持久化到本地的拦截
`com.tencent.wcdb.database.SQLiteDatabase`类的`insert()`方法：

编写注入脚本
```js
var SQL = Java.use("com.tencent.wcdb.database.SQLiteDatabase");
var Set = Java.use("java.util.Set");
var ContenValues = Java.use("android.content.ContentValues");


// 替换SQL的insert方法的实现
SQL.insert.implementation= function（arg1, arg2, arg3) {
    this.insert(arg1, arg2, arg3) {
        this.log("[insert] -> arg1: " + arg1 + "\r arg2: " + arg2);

        // 通过Frida得到的都是Object类，所以我们通常都要做一次转换
        var values = Java.cast(arg3, ContentValues);
        var sets = Java.cast(values.keySet(), Set);

        // 先得到ContentValues中所有的key
        var arr = sets.toArray().toString().split(".");
        for (var i = 0; i < arr.length; i++) {
            console.log("[insert] -> key: " + arr[i] + " value:" + values.get(arr[i]));
        }
    }
}
```

然后将手机连接电脑，通过frida将脚本注入到微信中：
```shell
frida -U -l lucymoney.js com.tencent.mm
```

用微信发送任意消息，控制台会出现打印内容
