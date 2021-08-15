# Xposed 入门教程
https://www.freebuf.com/articles/terminal/189021.html
## 0x01 Xposed模块编写简介
Xposed 框架的原理就不多说了，它部署在ROOT后的安卓手机上，通过替换/system/bin/app_process程序控制zygote进程，使得app_process在启动过程中会加载XposedBridge.jar这个jar包，从而完成对Zygote进程及其创建的Dalvik虚拟机的劫持。可以让我们在不修改APK源码的情况下，通过自己编写的模块来影响程序运行的框架服务，实现类似于自动抢红包、微信消息自动回复等功能。

其实，从本质上来讲，Xposed 模块也是一个 Android 程序。但与普通程序不同的是，想要让写出的Android程序成为一个Xposed 模块，要额外多完成以下四个硬性任务：

1. 让手机上的xposed框架知道这个模块
2. 模块里要包含有xposed的API的jar包，以实现下一步的hook操作。
3. 这个模块里面要有对目标程序进行hook操作的方法。
4. 要让xposed框架知道，模块里哪一个方法是用来hook的

> 
 1. AndroidManifest.xml
 2. XposedBridgeApi-xx.jar 与 build.gradle
 3. 实现hook操作的具体代码
 4. xposed_Init

## 0x02 第一步，新建项目并编辑AndroidManifest.xml文件

在AndroidManifest.xml指定位置插入以下三段代码：
```shell
<meta-data
android:name="xposedmodule"
android:value="true" />
<meta-data
android:name=>
```

## 0x03 第二步，XposedBridgeApi-xx.jar 与 build.gradle


我们知道，Xposed模块主要功能是用来Hook其他程序的各种函数。但是，如何让前一步中的那个“一穷二白”的模块长本事呢？那就要引入 XposedBridgeApi.jar 这个包，你可以理解为一把兵器，模块有了这把宝刀才能施展出Hook本领。以前，都需要手动下载诸如XposedBridgeApi-54.jar 、 XposedBridgeApi-82.jar 等jar包，然后手工导入到libs目录里，才能走下一步道路。其实在AndroidStudio 3.1里面，我们完全不用这么麻烦，只需要多写一行代码，就让AndroidStuido自动给我们配置XposedBridgeApi.jar ！



在 “项目名称/app/src/main/”目录下找到build.gradle，在图示位置加上：

repositories {

    jcenter()

}

以及

compileOnly 'de.robv.android.xposed:api:82'

compileOnly 'de.robv.android.xposed:api:82:sources'

这句代码是告诉AndroidStuido使用jcenter作为代码仓库，从这个仓库里远程寻找 de.robv.android.xposed:api:82 这个API。这个网上很少有Xposed教程介绍它的！（我们不用自己找XposedBridgeApi.jar了。注意！此处要用compileOnly这个修饰符！网上有些写的是provide ，现在已经停用了！）如图：



## 0x04, 实现hook操作的具体代码

crackme.apk代码
```java
package com.example.root.xposd_hook_new;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private Button button;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, toastMessage(), Toast.LENGTH_SHORT).show();
            }
        });
    }
    public String toastMessage() {
        return "我未被劫持";
    }
}
```


下面编写代码hookMainActivity并修改这个类的toastMesage() Fangf a
让它的返回值为 "你已经被劫持”:

编写Hook.java
```java
package com.example.root.xposd_hook_new;
import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;
public class HookTest implements IXposedHookLoadPackage {
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (loadPackageParam.packageName.equals("com.example.root.xposd_hook_new")) {
            XposedBridge.log(" has Hooked!");
            Class clazz = loadPackageParam.classLoader.loadClass(
                    "com.example.root.xposd_hook_new.MainActivity");
            XposedHelpers.findAndHookMethod(clazz, "toastMessage", new XC_MethodHook() {
                protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                    super.beforeHookedMethod(param);
                    //XposedBridge.log(" has Hooked!");
                }
                protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                    param.setResult("你已被劫持");
                }
            });
        }
    }
}
```

Hook的实现是通过`IXposedHookLoadPackage`接口中的handleLoadPackage方法实现的

代码中`com.example.root.xposed_hook_new`是目标程序的包名，`com.example.root.xposed.MainActivity`想要Hook的类，
`toastMessage`是想要Hook的方法



## 最后，添加一个入口点

main文件夹下，new Folder Assets Folder, 新建assets文件夹

在此文件夹下，新建一个text文件，名字为xposed_init
在其中写上入口类的完整路径
```text
com.example.root.HookTest
```

最后选择禁用`Instant Run` 然后小三角运行
