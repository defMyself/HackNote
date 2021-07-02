# C++学习感悟

* 面向对象
* lambda函数
* 异常
* 二进制可执行文件
* 目标文件
* 静态链接库
* 动态链接库
* 资源申请与释放
* 缓存，分支预测，内存顺序
* 段错误
* 静态分派，动态分派
* 泛型编程

```c++
class Teacher {
private:
    std::string name;
    std::string position;
public:
    Teacher(const std::string& n, const std::string& p)
        :name(n), position(p) {}
    
    Teacher(std::string&& n, std::string&& p)
        : name(std::move(n)), position(std::move(p)) {}
    
    Teacher(const std::string&& n, const std::string& p)
        : name(std::move(n)), position(std::move(p)) {}
    
    Teacher(const std::string& n, const std::string&& p)
        : name(n), position(std::move(p)) {}
}
```



```c++
class Teacher {
private:
    std::string name;
    std::string position;
public:
    template <typename S1, typename S2>
    Teacher(S1&&n, S2&& p)
    	: name(std::forward<S1>(n)), position(std::forward<S2>(p)) {};
}
```



```c++
class Teacher {
private:
    std::string name;
    std::string position;
public:
    template <typename S1, typename S2>
    typename = std::enable_if_t<!std::is_name_v<S1, Teacher>>>
    Teacher(S1&&n, S2&& p)
    	: name(std::forward<S1>(n)), position(std::forward<S2>(p)) {};
}
```



