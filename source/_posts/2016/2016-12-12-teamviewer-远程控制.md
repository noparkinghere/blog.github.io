---
layout: "post"
title: "TeamViewer 远程控制"
date: "2016-12-12 11:25"
---

TeamViewer 是一款最流行的远程桌面连接工具，特点：连接稳定，功能强大，跨平台，对网络稳定性要求低等等，几乎集成了市面上大多数远程工具的优点，实时性很强，且资源消耗低，这些都远不是 qq 等国内软件的远程服务可以比拟的。本篇文章就是 windows 远程连接 Ubuntu 桌面编辑完成的。

本文主要介绍如何在局域网内使用 TeamViewer 完成远程桌面的设置。


### 软件安装

这边给出[官方下载地址](https://www.teamviewer.com/zhcn/download/linux/)，可以看到官方提供了目前主流移动端和 PC 端的各个版本的软件。这边根据你自己的平台下载需要的版本。因为平台需要这边我下载的是 windows 版本和 Ubuntu 版本。需要注意的是：下载版本为完整版，而不是缩减版（缩减版中需要联网登录，且不直接存在登录远程功能），图示如下：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-12-teamviewer-%E8%BF%9C%E7%A8%8B%E6%8E%A7%E5%88%B6/1.jpg)

<!-- more -->


### 操作方法

#### 广域网连接

通过ID+密码连接，首先，输入对方的 ID 地址，然后选择下方的远程控制后点击连接到小伙伴，最后输入对方的密码即可完成远程控制。比较诡异的是远程链接到对方的 windows 后，背景图会变成黑色，但这无须担心，退出连接后，会恢复原来主题。另外如果实在看的不舒服，登录后点击“查看”，然后把“删除墙纸”勾掉就可以了。

#### 局域网连接

- 使用局域网链接，需要先配置下本机设置，找开软件后，先要设置允许接入lan（或者叫允许局域网连接），那样的话，ID的地方就显示内网的IP了。如果你的 ID 不能显示自己的 IP 地址，重新启动软件即可。如下图：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-12-teamviewer-%E8%BF%9C%E7%A8%8B%E6%8E%A7%E5%88%B6/2.jpg)


- 局域网内同样需要两边都先打开软件，然后使用 IP 代替伙伴ID输入，后续操作和上面类似，直接点远程控制，输入密码即可。如下图：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-12-teamviewer-%E8%BF%9C%E7%A8%8B%E6%8E%A7%E5%88%B6/3.jpg)


### 小结

TeamViewer 的链接方式稳定，带宽占用资源小，高质量模式下，也仅有 200kb/s 的传输速度，操作也很及时，附带的录屏文件传输等功能强大。但 TeamViewer 并非完全免费的软件，一些附带功能和商业用途需要付费支持，另外 TeamViewer 只能用于远程图形化界面的使用的话，说白了就是只能一个人使用，不能类似于 ssh 可以多人使用登录。





> 参考链接：
> http://www.wuji8.com/meta/864411156.html
> https://zhidao.baidu.com/question/497787316.html
