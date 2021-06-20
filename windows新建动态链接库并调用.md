# Windows新建一个动态链接库

### 导出函数的声明方式

* 在函数声明和函数名之间加上`_declspec(dllexport)`
* 采用模块定义(`.def`)文件声明，需要在库工程中添加模块文件，格式如下：
  * LIBRARY库工程名称
  * EXPORTS导出函数名

### DLL的调用方式

* 静态调用，由编译系统完成对DLL的加载和应用程序结束时DLL的加载。

* 动态调用，由编程者用API函数加载和卸载DLL(DLL加载——DLL函数地址获取——DLL释放)方式。

  如`LoadLibrary`函数，是将指定的可执行模块映射到调用进程的地址空间。

### 使用动态库的过程

提供两个文件：一个引入库（.lib)文件和一个DLL(.dll)文件。引入库文件包含该DLL导出的函数和变量的符号名，而.dll文件包含该DLL实际的函数和数据。

使用动态库的情况下，编译链接可执行文件时，只需要链接该DLL的引入库文件，该DLL中的函数代码和数据并不复制到可执行文件中，直到可执行程序运行时才去加载所需的DLL，将该DLL映射到进程的地址空间中，然后访问DLL中的导出函数。

### 例子

1. 函数——创建动态链接库（MFC规则DLL）

   1. New——Project——MFC AppWizard(dll)——DLL

   2. def文件中添加：函数名（Add_new)

   3. h文件中添加：外部函数声明、求和函数，

      ```c
      extern "C" _declspec(dllexport) int __stdcall Add_new(int a, int b)
      {
          return a+b;
      }
      ```

   4. build —— set active configuration ——win32 release —— ok

      

      #### 调用动态链接库

      

      

   ## 非MFC DLL

   sample.h

   ```c
   #ifndef SAMPLE_H
   #define SAMPLE_H
   extern int dllGlobalVal;
   #endif
   ```

   sample.cpp

   ```cpp
   #include "sample.h"
   #include <windows.h>
   int dllGlobalVar;
   bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
   ```

   