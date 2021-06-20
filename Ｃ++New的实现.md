# Ｃ++New的实现

new 和delete最终调用malloc 和 free

## malloc和free

```c
int main()
{
    char* p = (char*)malloc(32);
    free(p);
    return 0;
}

```

**malloc和free的debug和release版本实现各不相同，相差较大**

### Debug版本的malloc

malloc需要分配的内存会比实际的size多36byte,最终分配的内存块包括三个部分。

`_CrtMemBlockHeader结构体`、用户请求内存、4字节校验位

其中`_CrtMemBlockHeader`是一个双向链表结构，定义如下：

```c
<pre name="code" class="cpp">typedef struct _CrtMemBlockHeader
{
	struct _CrtMemBlockHeader *pBlockHeaderNext;	//下次分配的内存块
	struct _CrtMemBlockHeader *pBlockHeaderPrev;	//上次分配的内存块
	char *szFileName;				//分配内存代码的文件名
	int nLine;					//分配内存代码的行号
	size_t nDataSize;				//请求的大小，如实例中的32
	int nBlockUse;					//请求的内存类型，如实例中的user类型
	long lRequest;					//请求id，每次请求都会被记录
	unsigned char gap[nNoMansLandSize];		//4字节校验位
} _CrtMemBlockHeader;
```

用户请求内存前后分别有4字节的校验位，分配内存后都会被初始化为0xFD。如果这8个字节被改写，free时就会触发断言失败。
而请求的32字节会被初始化为0xCC（和栈的初始化一样）。
系统通过记录这些信息就能显示的给出错误。比如越界访问请求的内存在debug下会断言失败，release下面则不会，从而这会给程序埋下巨大的隐患。很多在release下偶发的错误就是这样产生的。
_CrtMemBlockHeader总共32字节，加上用户请求的32字节及最后4字节校验位是68字节。最终调用系统的API请求内存。比如Windows下面是HeapAlloc。

如果内存分配失败，malloc不像new那样可以调用new_handler来处理，它直接返回NULL。

free则是对_CrtMemBlockHeader的信息做清理操作，检查校验位等等。最终调用系统API释放内存。比如Windows下面是HeapFree。 

实际分配的内存等于请求的内存大小。malloc和free只是在系统API之上做了些判断操作。  



**总结**

C语言是跨平台的，最终的内存处理都会交给系统API完成。系统会记录每一块分配内存的地址，大小，释放情况等等。所以free时只需要传入一个地址的参数就可以了。而且同一个地址不能释放两次。



## new

