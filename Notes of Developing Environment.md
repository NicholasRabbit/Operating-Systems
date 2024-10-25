#### 1, Create Environment for labs of 6.S081

1) Install Ubuntu 20.04 on WSL or VM. 
    The version must be 20.04. 

​    Check the version of it.

```shell
lab_release -a
# Notice the codename which should be match version of the mirrors in Aliyun.
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 20.04.6 LTS
Release:        20.04
Codename:       focal
```

2) Change the mirror of `source.list` in Ubuntu to domestic servers in China.

   2.1 Backup `source.list` in `/etc/apt/`

```shell
cp /etc/apt/source.list /etc/apt/source.list.bak
```

   2.2  Replace the mirrors with the following sites.

Notice that the distributed version and the`Codename` of mirrors must be matched your Ubuntu OS.

"ubuntu 20.04 LTS (focal) "

```txt
deb https://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse

deb https://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse

deb https://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse

# deb https://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
# deb-src https://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse

deb https://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
```

 From  [Aliyun mirrors of Ubuntu](https://developer.aliyun.com/mirror/ubuntu)

2.3 Update `apt`

```shell
sudo apt update
sudo apt upgrade
```

3) Then install tools for the labs follow the instruction of [the official website](https://pdos.csail.mit.edu/6.828/2021/tools.html).

```shell
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
```

**N.B. The reason that I couldn't install the tools is the Ubuntu official server is not  connected in China.**

Other: 

If the version of `Qemu` is not suitable for labs, you should uninstall `Qemu`  and install the proper version of it.

```shell
sudo apt-get remove qemu-system-misc
sudo apt-get install qemu-system-misc=1:4.2-3ubuntu6
```



#### 2, Test

```shell
riscv64-unknown-elf-gcc --version 
# riscv64-unknown-elf-gcc (GCC) 10.1.0
qemu-system-riscv64 --version
# QEMU emulator version 5.1.0
git clone git://g.csail.mit.edu/xv6-labs-2020 
# N.B. the repository is "xv6-labs-2020"
cd xv6-labs-2020
# there must be a branch named "util"
checkout until  # switch the the branch name "util"
make qemu
# run the above command in the "until" branch of the repository 
```

Note: run `make qemu` at `git://g.csail.mit.edu/xv6-labs-2020 `.The `xv6 directory` is root directory of the repository.

<img src="note-images/1728728662500.png" alt="1728728662500" style="zoom: 80%;" />



