---
layout: post
category: "read"
title:  "linux下的virtualbox安装配置"
tags:   软件安装
date: "2016-07-07 1:12"
---

### 背景分析

随着计算机技术的发展，硬件配置越来越高，跨平台软件，手机以及浏览器越来越强大，目前可以说
linux下除了大型游戏意外，其他的办公学习娱乐基本都可以解决，比如：

<!-- more -->


- 购物可以电脑浏览，手机支付（很多win用户，估计也不怎么用u盾了）。
- 音乐可以使用百度，qq在线音乐。
- 至于编程等开发工具更是齐全。

但仍然难免会有一些windows程序需要用户操心，个人主要需用使用的windows产品有：
*迅雷，百度云，photoshop，illustrator，U盘系统制作工具等*

解决办法主要有：

- wine提供windows的类库，是软件windows软件直接可以在linux上面运行
- 使用虚拟机，在linux上面虚拟一个windows xp出来，提供一定的硬件资源，运行需要使用的软件

**这边我们选择虚拟机virtualbox，主要该软件开源小巧，且现在硬件强大，对资源的开销可以接收，外加wine向来不是太稳定，出现问题的几率高。**

#### 系统环境

- ubuntu 16.04 终端输入： lsb_release -a

```
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 16.04 LTS
Release:	16.04
Codename:	xenial
```

### 具体步骤

步骤如下：

1. 需要安装Oracle Virtualbox

可以使用sudo apt-get install virutalbox 安装

也可以通过官网下载地址：`https://www.virtualbox.org/wiki/Downloads`

安装增强包的方法介绍：`http://gaoke0820.blog.163.com/blog/static/21664965201332802833510/`

2. 安装完之后，U盘识别

*如果如VirtualBox客户机挂载U盘中设置后，linux中还不能挂载u盘，而使用sudo启动virtualbox后里面的客户机可以挂载U盘，原因为 普通用户没有使用USB设备权限。*

2.1 方法1：

让GUEST识别USB设备

```
$ sudo gedit   /etc/fstab

在末尾加上
# the USB group
# 对所有用户开放USB设备的读写权限
none /proc/bus/usb usbfs devmode=666 0 0
然后就可以使用的USB设备了。
```

*但是把USB设备的读写权限开放给所有用户的方式在一些情况下不太安全*


2.2 方法2：

将用户名添加到vboxusers组,重启或注销后即可解决.

```
sudo adduser usrname vboxusers

然后再输入：cat /etc/group |grep vboxusers
这时可以看到显示：
vboxusers:x:129:demon,hello
```

*该方法使用后，基本能够使用，但使用之前每次需要手动添加设备*

2.3 方法3：

```
增加用户组usbfs
$sudo groupadd usbfs

查看usbfs用户组的gid
$ cat /etc/group | grep usbfs
usbfs:x:1002:

把当前用户增加到usbfs组
sudo adduser demon usbfs
```

为USB设备重新设置权限,编辑/etc/fstab文件，添加下面两行，注意你的gid可能不是1002

```
 $   sudo gedit /etc/fstab
在末尾加上
# 1002 is the USB group IDI
none /proc/bus/usb usbfs devgid=1002,devmode=774 0 0
```

重新启动后，应该就可以在客户机中使用USB设备了。

方法：插入一个USB设备后，如U盘、鼠标，右键点击虚拟机里右下脚的USB图标，选择已经识别的U盘，就可以正常使用了。
注意： 在客户机里使用USB设备前要先在主机里卸载。

﻿



3. 在virtualbox里启动USB控制器




4. 打开虚拟机，这时在虚拟机的设备-分配USB设备中就可以看到USB设备了



> 相关参考：
> http://blog.csdn.net/rongyongfeikai2/article/details/21795741
> http://www.linuxidc.com/Linux/2012-01/52502.htm
> http://xuantan.iteye.com/blog/1130808
> http://www.iteedu.com/os/linux/mklinuxdiary/ch1tools/2.php
