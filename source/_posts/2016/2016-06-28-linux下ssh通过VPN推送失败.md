---
layout: post
title:  linux下ssh通过VPN推送失败
category: "问题总结"
date: "2016-06-28 12:12"
---

本文主要用于解决 VPN 和 SSH 两者冲突不兼容的问题。


### VPN

虚拟专用网络的功能是：在公用网络上建立专用网络，进行加密通讯。在企业网络中有广泛应用。VPN网关通过对数据包的加密和数据包目标地址的转换实现远程访问。VPN有多种分类方式，主要是按协议进行分类。VPN可通过服务器、硬件、软件等多种方式实现。

VPN属于远程访问技术，简单地说就是利用公用网络架设专用网络。例如某公司员工出差到外地，他想访问企业内网的服务器资源，这种访问就属于远程访问。让外地员工访问到内网资源，利用VPN的解决方法就是在内网中架设一台VPN服务器。外地员工在当地连上互联网后，通过互联网连接VPN服务器，然后通过VPN服务器进入企业内网。为了保证数据安全，VPN服务器和客户机之间的通讯数据都进行了加密处理。有了数据加密，就可以认为数据是在一条专用的数据链路上进行安全传输，就如同专门架设了一个专用网络一样，但实际上VPN使用的是互联网上的公用链路，因此VPN称为虚拟专用网络，其实质上就是利用加密技术在公网上封装出一个数据通讯隧道。有了VPN技术，用户无论是在外地出差还是在家中办公，只要能上互联网就能利用VPN访问内网资源，这就是VPN在企业中应用得如此广泛的原因。

VPN的协议分类主要有三种，PPTP、L2TP和IPSec，其中PPTP和L2TP协议工作在OSI模型的第二层，又称为二层隧道协议；IPSec是第三层隧道协议。

### SSH

SSH 为 Secure Shell 的缩写，由 IETF 的网络小组（Network Working Group）所制定；SSH 为建立在应用层基础上的安全协议。SSH 是目前较可靠，专为远程登录会话和其他网络服务提供安全性的协议。利用 SSH 协议可以有效防止远程管理过程中的信息泄露问题。SSH最初是UNIX系统上的一个程序，后来又迅速扩展到其他操作平台。SSH在正确使用时可弥补网络中的漏洞。SSH客户端适用于多种平台。几乎所有UNIX平台—包括HP-UX、Linux、AIX、Solaris、Digital UNIX、Irix，以及其他平台，都可运行SSH。windows 通过安装 putty等软件可以帮助安装 ssh 协议。

<!-- more -->

### 在VPN下使用SSH服务

#### github使用ssh协议：#

- 我们可以本地推送而免输入账户名密码，这里不作为本文重点，相关网址教程如下：

  > http://playingfingers.com/2016/03/26/build-a-blog/
  > http://beiyuu.com/github-pages
  > http://www.cnblogs.com/ayseeing/p/3572582.html
  > http://blog.csdn.net/renfufei/article/details/37725057/


#### SSH无法推送: #

- 当一切操作就绪后，会偶然出现无法通过SSH推送：

  > 等待很长时间后，显示超时！

#### 原理及方案： #

- **通过排查发现主要是由于链接的VPN引起的，SSH协议和VPN本身存在不兼容，要想解决可以通过底层设置让需要使用SSH协议的IP地址不经过VPN服务器，由电脑主机网卡直接访问。**


#### 具体步骤：  #

- 查看网卡情况

```
输入指令：ifconfig
下面出现的ppp0就是虚拟出来的VPN网卡。
```
![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-28-linux下ssh通过VPN推送失败/2016-06-23-remarkable-install.png)



- 查看ip列表,查看有哪些设置过了的IP地址

```
ip route list
```
![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-28-linux下ssh通过VPN推送失败/DeepinScrot-3457.png)


- 获取目标网站IP地址

*最简单的可以通过ping命令如下*

ping www.github.com 终端返回：64 bytes from github.com (192.30.252.131): icmp_seq=1 ttl=54 time=210 ms，一般来说192.30.252.131 则为我们目标IP地址。但可能push的地址不一定是同一个地址。即便通过`nslookup + 详细网址`也未必能够获取真正推送的ip地址。最终通过谷歌搜索[网站](https://help.github.com/articles/what-ip-addresses-does-github-use-that-i-should-whitelist/)查看到github实际推送过程中ip地址为：192.30.252.0/22，（这边另外推荐可以使用wireshark进行抓包查看网络服务）

- 将目标域名的IP地址加入到主机网卡中， 192.168.18.1为路由器网关的地址，通过上面ifconfig可以看到本机被路由器分配的ip地址为192.168.18.60，而eno1为计算机在访问外网中的实体网卡。


```
sudo ip route add 192.30.252.0/22 via 192.168.18.1 dev eno1
```

- 再次查看ip列表,查看有哪些设置过了的IP地址

```
ip route list
```

- 最终完成推送
![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-28-linux下ssh通过VPN推送失败/DeepinScrot-3044.png)



***

> 参考网址：
> https://help.github.com/articles/what-ip-addresses-does-github-use-that-i-should-whitelist/
