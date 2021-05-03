# C++ 虚表gdb分析

```c++
#include <stdio.h>
#include <string.h>

class BaseClass
{
    private:
    	char Buffer[32];
    public:
        void SetBuffer(char *String)
        {
            strcpy(Buffer, String);
        }
    virtual void PrintBuffer()
    {
        printf("%s\n", Buffer);
    }
};

class MyClass1 : public BaseClass
{
    public:
    	void PrintBuffer()
        {
            printf("MyClass1: ");
            BaseClass::PrintBuffer();
        }
};

class MyClass2 : public BaseClass
{
    public:
    	void PrintBuffer()
        {
            printf("MyClass2: ");
            BaseClass::PrintBuffer();
        }
};

int main()
{
    BaseClass *Object[2];
    
    Object[0] = new MyClass1;
    Object[1] = new MyClass2;
    
    Object[0]->SetBuffer("string1");
    Object[1]->SetBuffer("string2");
    Object[0]->PrintBuffer();
    Object[1]->PrintBuffer();
}
```

