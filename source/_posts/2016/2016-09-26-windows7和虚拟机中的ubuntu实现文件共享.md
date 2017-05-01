---
layout: "post"
title: "windows和虚拟机中的ubuntu实现文件共享"
category: "软件应用"
tags:   ""
date: "2016-09-26 14:06"
---

### 简介

国内很多用户习惯于使用 windows 系类操作系统，然而其中部分人员需要使用 ubuntu 进行一些开发测试，但他们并不想完全脱离 windows 系统，这时候虚拟机满足了他们的需求，虚拟机以安装配置简单，镜像还原起来方便安全，而被广大学习爱好者所喜爱。但有些时候，需要将真实机中的一些文档或者数据传输到虚拟机中，而如何实现虚拟机同真实机的共享往往是一些初学者头痛的事情。下面我列举出几种方法，可以满足解决这些问题。

*以下的大多数方法，同样不仅适用于虚拟机和真实机之间交换文件，同样适用于同一个交换机/路由器下的不同主机进行通讯。*

### 通过网盘进行传输

首先可以参照我之前写的*桥接、nat、host-only 上网方式的区别*里面介绍了如何配置虚拟机上网，一般虚拟机上方较为方便，如：vmware 或者 virtualbox 之类的都可以一键安装系统，即便手动安装，通过虚拟机拓展工具也都可以补全网卡显示上网的。如果对你所使用的linux发行版不是太熟悉，且极少传输文件的话，可以使用这种方法。推荐使用百度云之类的网盘，先将本地数据文件上传，然后再通过 linux 中的浏览器将数据文件下载下来。这种方式的好处是无需学习，没有门槛，不需要了解任何 linux 的知识，只需要当做一个桌面系统使用即可，坏处显而易见：1.依赖外网，2.机密文件不方便上传，3.必须上传下载，大型文件速度慢。

<!-- more -->

### **进行以下几种方法前建议先关闭 linux 和 windows 的防火墙**

### 通过虚拟机扩展直接拖动

一般虚拟机中的 linux 安装扩展插件就可以直接将 windows 下的文件托进linux去了，或者将 linux 的文件拖到 windows 下，但前提要求是：**需要虚拟机和操作系统的内核版本兼容，各方面切合度高，能够完美支持的情况下，最好使用虚拟机要和两个操作系统都是同一时期发型的，推荐是使用新版 windows，最新版虚拟机还有最新发行版的 linux 系统。**

### 通过scp命令

Linux 与 Linux 之间传送文件，使用 scp 命令，这是一种基于 ssh 的方式，因此**两个系统都必须要支持ssh协议**，安装方式：

- ubuntu：`sudo apt-get install ssh或sudo apt-get install openssh-server`，`sudo /etc/init.d/ssh restart`重启ssh服务，其他发行版该命令未必适用。查看ssh服务是否启动, `ps –e | grep ssh`，响应的sshd和ssh-agent如果未打开则运行指令名字。
- windows系统本身不支持ssh协议，所以，要想上面的命令成功执行，必须在windows客户端安装ssh for windows的客户端软件，比如WinSCP（开源），winsshd，使windows系统支持ssh协议才行。

从linux系统复制文件到windows系统：  
`scp /tmp/a.txt administrator@192.168.3.181:/d:/`

在linux环境下，将windows下的文件复制到linux系统中：  
`scp  administrator@192.168.3.181:/d:/test/config.ips  /tmp`

*。scp的方法于只安装了 CLI 的 linux 版本使用，所有操作无需图形界面，且能够在 linux 下完成。另外该方法也并非任何地方都能够完成，和虚拟机扩展类似，对系统环境有一定要求，尤其是一定要找到可用的 windows 下的 ssh 协议，往往是 linux 的 ssh 完美运行，但无法登陆 windows。*

### 通过 WinSCP 软件

该软件主要就是实现同一网段内的 windows 和 linux 的数据互传，本质上应该和scp命令原理是相同的，好处是图形化界面操作简单，登陆后无需再输入指令。WinSCP 是一个支持 SSH（Secure SHell）的 SCP（Secure CoPy）文件传输软件。只要文件主机支持 SSH 协定，你就可以安心的下载、上传文件。他的操作界面是参考NC（Norton Commander）的双视窗排列方式，使用起来不会有太大的困难。在 WinSCP 中，一般的文件操作都没有问题，如：复制、移动、更名文件或文件夹等。

输入主机名，用户名，密码，点击保存。通过下图中的界面，实现登陆：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-09-26-windows7%E5%92%8C%E8%99%9A%E6%8B%9F%E6%9C%BA%E4%B8%AD%E7%9A%84ubuntu%E5%AE%9E%E7%8E%B0%E6%96%87%E4%BB%B6%E5%85%B1%E4%BA%AB/1.jpg)

*第一登陆的时候，会告诉你服务器的主秘钥不再缓存中，确认修改后，即可远程登陆，另外如果使用root用户的话，新安装的ubuntu系统需要设置 root 密码，以及修改ssh的配置文件：`sudo vi /etc/ssh/sshd-config`，将 PermitRootLogin 修改为 yes。重启ssh服务：`sudo /etc/init.d/ssh restart`*

文件的上传与下载跟 Windows 的资源管理器差不多了，如果要编辑目录或文件，只要右键就会出相应的可选的项目。下图为登陆后的资源管理界面：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-09-26-windows7%E5%92%8C%E8%99%9A%E6%8B%9F%E6%9C%BA%E4%B8%AD%E7%9A%84ubuntu%E5%AE%9E%E7%8E%B0%E6%96%87%E4%BB%B6%E5%85%B1%E4%BA%AB/2.jpg)


### 通过虚拟机共享文件夹的方式

#### 安装 VMware tools 或者 virtualboxaddition 等工具

- 在VMware 虚拟机界面，点 VM->Install VMware Tools。之后，点击 Ubuntu 窗口中主文件 按钮然后再左边会看见设备里有 VMware tools 文件夹，双击之，并且解压其中的压缩文件，把它拷贝到主文件夹
- 打开 Terminal 终端，进入解压的文件夹中，输入以下命令：

```
sudo tar zxf VMwareTools-xxx.tar.gz (注：xxx为版本号)
cd /vmware-tools-distrib
sudo ./vmware-install.pl
安装过程中一直按enter即可，或者输入【】提示yes和no，直到安装完毕。
```

- 查看结果：lsmod | grep vmblock

#### 设置共享文件夹的目录

- 将 Ubuntu 关机（power off），否则不能添加共享文件夹
- 在 VMware 虚拟机窗口，选择VM->Settings->Options->Shared Folders
- 点右边的 Add，点Next->选择 Win7 共享目录的路径，然后点 Next-> 选中 Enable this share->Finish
- 在 VM->Settings->Options->Shared Folders 窗口的右边，Folder sharing 栏里选择 Always enabled
- 点 OK 确定退出

#### 在 Ubuntu 虚拟机下安装插件

- 执行 sudo apt-get install open-vm-dkms (注：如果无法查到open-vm-dkms，则可能更名为：open-vm-tools-dkms)
- 执行 sudo mount -t vmhgfs .host:/ /mnt/hgfs 
- cd /mnt/hgfs

注意：即便完成了这个方法的所有步骤也未必能够完成共享文件夹，同虚*拟机扩展直接拖动*类似，该方法对系统和虚拟机切合度要求较高，vmtools 和 ubuntu 内核存在版本不兼容的问题，mount 经常支持不够好。也就是说同样的方法，相同的步骤，有的人轻松就可以实现，有的需要不断的去修补 linux 的脚本头文件等，当然解决是一定可以解决，但往往较为麻烦，如果该方法不行，建议尝试其他方法。

### 总结：

*通过 scp 命令*和*通过虚拟机共享文件夹的方式*并不推荐，建议首先尝试安装虚拟机扩展工具，如果可以直接拖拽文件则问题已解决，无需参考文章中的方法，如果不行的话，推荐通过 WinSCP 软件来操作，适用的场景多且不容易出错，本人尝试过如 centos 6.5，ubuntu 16.04 等多个主流操作系统，均可以实现传输。


***

> 参考链接：
> http://huangfuff.blog.51cto.com/2632203/1604500
> https://my.oschina.net/u/811744/blog/179229
> https://www.centos.bz/2011/03/windows-linux-transfer-data-tool-winscp/
> http://blog.csdn.net/warringah1/article/details/8927437
> http://fancyseeker.github.io/2013/12/31/ssh_connect/
> http://blog.csdn.net/lulitianyu/article/details/50446015
