---
layout: "post"
title: "网络监控工具wireshark"
category: "软件应用"
tags:  
date: "2016-09-12 10:17"
---

### wireshark简介

Wireshark（前称Ethereal）是一个网络封包分析软件。网络封包分析软件的功能是撷取网络封包，并尽可能显示出最为详细的网络封包资料。Wireshark使用WinPCAP作为接口，直接与网卡进行数据报文交换。网络封包分析软件的功能可想像成 "电工技师使用电表来量测电流、电压、电阻" 的工作 - 只是将场景移植到网络上，并将电线替换成网络线。在过去，网络封包分析软件是非常昂贵的，或是专门属于营利用的软件。Ethereal的出现改变了这一切。在GNUGPL通用许可证的保障范围底下，使用者可以以免费的代价取得软件与其源代码，并拥有针对其源代码修改及客制化的权利。Ethereal是目前全世界最广泛的网络封包分析软件之一。

<!-- more -->


### 软件安装

#### linux下的安装

首先，安装只要一个命令行(由于之前装过了，所以没有在安装什么了)：sudo apt-get install wireshark 。已经将wireshark安装完毕，接下来我没就可以通过：终端输入wireshark 用来启动它的图形界面。
然而，dumpcap需要root权限才能使用的,以普通用户打开Wireshark，Wireshark当然没有权限使用dumpcap进行截取封包。虽然可以用:sudo wireshark来完成。但是，以sudo的方式用root打开Wireshark显然是不安全的，也不是很方便，因为得到的封包数据也属于root用户。于是，我们提供下面的方法来完成普通用户下的操作。

- 添加wireshark用户组`sudo groupadd  wireshark`，一般软件安装完成后，可能已经自动帮你生成了这个组。
- 将dumpcap程序更改为所属组为wireshark用户组`sudo chgrp wireshark /usr/bin/dumpcap`
- 让wireshark用户组有root权限使用dumpcap即更改dumpcap的科执行权限，赋予所属组执行权限 `sudo chmod 4755 /usr/bin/dumpcap`
- 将需要使用的普通用户名加入wireshark用户组，我的用户是“demon”（需要根据具体用户名修改！在#前面可以找到哟），则需要使用命令：` sudo gpasswd -a demon wireshark `

通过以上步骤就可以以普通用户登陆打开Wireshark，也会有权限进行抓包了。

### 常规用法




> 参考链接：
> http://fangxin.blog.51cto.com/1125131/735178
> http://blog.sina.com.cn/s/blog_5d527ff00100dwph.html
> https://openmaniak.com/cn/wireshark_filters.php
> http://www.jianshu.com/p/400d4430a74a
> https://wiki.wireshark.org/CaptureSetup/CapturePrivileges
> https://anonscm.debian.org/viewvc/collab-maint/ext-maint/wireshark/trunk/debian/README.Debian?view=markup
> http://jingyan.baidu.com/article/c74d60009d992f0f6a595de6.html
