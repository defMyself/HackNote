# Frida 入门及介绍

Frida是一款基于Python + Javascript的hook与调试框架

Frida是一款易用的跨平台Hook工具，Java层到Native层的Hook无所不能，是一种动态的插桩工具，可以插入代码到原生App的内存空间，动态的去监视和修改行为，原生平台包括Win、Mac、Linux、Android、iOS全平台

* 静态二进制插桩：在程序执行前插入额外的代码数据，生成一个永久改变的可执行文件。
* 动态二进制插桩：在程序运行时实时地插入额外代码和数据，对可执行文件没有任何永久改变。

Frida的功能如同油猴插件

Frida通过使用Python注入JavaScript脚本，通过JS脚本来操作设备上的Java代码

持久化Hook需要Xposed等框架



*Frida大致原理，在手机端安装一个server程序，然后把手机端的端口转到PC端，PC端写python脚本惊醒通信，而python脚本中需要hook的代码采用Javascript语言*

1. Xposed的优缺点

   优点：在编写Java层hook插件的时候非常好用，这一点完全优越于Frida和SubstrateCydia，Xposed是一个Android项目，可以直接编写Java代码调用各类api进行操作。可以安装到手机上直接使用。

   缺点：配置安装环境繁琐，兼容性差，Hook底层时无助

2. Frida的优缺点

   优点：配置环境简单，操作便捷，对破解开发者非常好用。支持Java层和Native层hook,

   在Native层Hook非基本类型较为麻烦

   缺点：没法像Xposed用于实践生产

**各大APP越来越注重安全性，NDK所编译出来的so库逆向难度明显高于Java代码产生的dex文件**

**敏感的加密算法与数据需要用NDK进行开发**



### Frida的用途

* 访问进程的内存
* 应用程序运行时覆盖功能
* 从导入的类调用函数
* 动态Hook跟踪，拦截函数等



Frida拦截微信消息

```python
import frida, sys

def on_message(message, data):
    if message['type'] == 'send':
        print("[*] {0}".format(message['payload']))
    else:
        print(message)

jscode = """
Java.perform(function () {
    // Hook插入数据库
    var SQLiteDatabase = Java.use('com.tencent.wcdb.database.SQLiteDatabase');
    var Set = Java.use("java.util.Set");
    var ContentValues = Java.use("android.content.ContentValues");
    SQLiteDatabase.insert.implementation = function (arg1,arg2,arg3) {

        this.insert.call(this, arg1, arg2, arg3);
        console.log("[insert] -> arg1:" + arg1 + "\t arg2:" + arg2);
        var values = Java.cast(arg3, ContentValues);
        var sets = Java.cast(values.keySet(), Set);
        
        var arr = sets.toArray().toString().split(",");
        for (var i = 0; i < arr.length; i++){
            console.log("[insert] -> key:" + arr[i] + "\t value:" + values.get(arr[i]));
        }
    };
});
"""

rdev = frida.get_remote_device()
session = rdev.attach("com.tencent.mm")		 # 获取指定APP
script = session.create_script(jscode)
# script.on('message', on_message)

print('[*] Running')
script.load()
sys.stdin.read()

```



