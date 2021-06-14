# Linux下ARM程序的编译运行及调试

## 安装交叉编译环境`arm-linux-gcc-4.4.3.tar.gz`

1. 下载`arm-linux-gcc-4.4.3.tar.gz`

2. 解压

   ```shell
   sudo tar -xvlf arm-linux-gcc-4.4.3.tar.gz
   ```

3. 配置环境变量PATH 修改`/etc/profile`文件

4. `export PATH=$PATH:/usr/local/arm_4.4.3/bin`, `source /etc/profile`

## qemu的安装

```shell
sudo apt-get install qemu qemu-arm-static qemu-kvm-extras
arm-linux-gcc -o hello-arm hello.c
qemu-arm hello-arm
```

1. `gdb-multiarch`

### arm程序的调试

1. 利用gdb对qemu-arm运行的程序进行gdb远程调试，首先在终端中输入如下指令等待调试

   ```shell
   qemu-arm -g 1234 hello-arm
   ```

2. 再打开另外一个终端，并在其中利用`arm-linux-gdb`进入调试器，并通过端口1234连接到qemu-arm等待调试的程序`gdb-multiarch hello-arm`

3. 