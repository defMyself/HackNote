# pwntools教程

> `pwntools`既是一个CTF工具框架也是一个漏洞利用开发库。使用Python开发，目的是使得利用脚本尽可能的简单

## 认识Pwntools

### 关于pwntools

> `pwntools`2.0 有两个不同的模块构成
>
> * `pwnlib` python module
> * `pwn` CTF中使用

#### `pwn` -- CTF效率提升工具

#### `pwnlib` -- 普通的pyton模块

#### Binutils





## 基本使用

### 1. 建立连接

`pwnlib.tubes.remote`

```shell
conn = remote('ftp.ubuntu.com', 21)
conn.recvline()
conn.send(b'USER anonymous\r\n')
conn.recvuntil(b' ', drop=True)
conn.recvline()
conn.close90
```

监听

```shell
l = listen()
r = remote('localhost', l.port)
c = l.wait_for_connection()
r.send(b'hello')
c.recv()
```

使用`pwnlib.tubes.process`与进程交互

```shell
sh = process('/bin/sh')
sh.sendline(b'sleep 3; echo hello world;')
sh.recvline(timeout=1)
sh.recvline(timeout=5)
sh.close()

# 手工交互
sh.interactive()

# ssh 模块
shell = ssh('bandit0', 'bandit.lab.overthewire.org', password='bandit0', prt=2220)
shell['whoami']
shell.download_file('/etc/motd')
sh = shell.run('sh')
sh.sendline(b.'sleep 3; echo hello world;‘ )
```

### 2 打包整数

```python
import struct
p32(0xdeadbeef) == struct.pack('I', 0xdeadbeef)
leet = unhex('37130000')
u32(b'abcd') == struct.unpack('I', b'abcd')[0]
u8(b'A') == 0x41
```

设置体系结构和OS

```python
asm('nop')
asm('nop', arch='arm')
```

#### 3 汇编和反汇编

`pwnlib.asm`

```python
enhex(asm('mov eax, 0'))
print(disasm(unhex('6a0258cd80ebf9')))
```

pwnlib.cyclic

#### 5 ELF操作

```python
e = ELF('/bin/cat')
print(hex(e.address))
print(hex(e.symbols['write']))

```

```python
e.read(e.address, 4)
e.asm(e.address, 'ret')
e.save('/tmp/quiet-cat')
disasm(open('/tmp/quiet-cat', 'rb').read(1))
```







