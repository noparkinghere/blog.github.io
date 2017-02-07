---
layout: "post"
title: "PuTTY + Xming 远程使用 Linux GUI"
date: "2016-12-01 12:11"
---

就目前而言，将 linux 作为个人电脑操作系统使用的人还比较少，而 linux 也一直以来因为其占用资源少，系统稳定，强大的 CLI 而闻名于世。因此显而易见，广大用户一般都是通过 ssh 等方式登录连接 linux ，然后使用 CLI 完成需要的操作，而使用 linux GUI 用户较少，甚至可以被忽略，但出于个人的需要，本人需要通过 windows 远程登录 linux 然后通过 chrome 等


### 操作系统：

- windows 7 x64 中文旗舰版
- ubuntu 16.04 

<!-- more -->


### 软件配置：

#### Xming ：

Xming是一个在 Microsoft Windows 操作系统上运行 X Window System 的自由软件。其主要功能是通过在Linux平台上通过交叉编译的方法，实现了跨越操作系统对X GUI的表现。

正常安装该软件：这边使用过的是： Xming-6-9-0-31-setup.exe 的版本，正常安装过，一般都没有问题，设置按照下图选择不安装 ssh client。 Display 设置按照个人习惯进行设置，如果仅是打开个别 GUI 窗口的话，建议采用 Multiple windows ，可以讲所有的 GUI 窗口作为一个个应用进行打开。接下来按照默认设置进行下一步即可，另外最后一步可以保存当前设置作为一个快捷方式，下次直接打开即可。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-01-putty-xming-%E8%BF%9C%E7%A8%8B%E4%BD%BF%E7%94%A8-linux-gui/1.png)

#### putty :

PuTTY是一个Telnet、SSH、rlogin、纯TCP以及串行接口连接软件。较早的版本仅支持Windows平台，在最近的版本中开始支持各类Unix平台，并打算移植至Mac OS X上。自带SSH Forwarding的功能，包括X11 Forwarding。

- 输入需要拨号的地址（这边注意本机和目标机器在同一个网段）

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-01-putty-xming-%E8%BF%9C%E7%A8%8B%E4%BD%BF%E7%94%A8-linux-gui/2.png)

- 设置拨号的账户名，方便下次登录

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-01-putty-xming-%E8%BF%9C%E7%A8%8B%E4%BD%BF%E7%94%A8-linux-gui/3.png)

- 一定要打开 X11 转发模式，可以让 ssh 图形化转发给 Xming 进行工作。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-01-putty-xming-%E8%BF%9C%E7%A8%8B%E4%BD%BF%E7%94%A8-linux-gui/4.png)

#### SecureCRT 方式（可以跳过）

这边补充 SecureCRT 这个软件的方式，原理和 putty 类似，得益于 SecureCRT 在用户界面上面更加友好方便，常常用作远程管理使用，如果已经使用了 putty 的这边可以跳过，两种方式选其一即可。

SecureCRT 同 putty 类似，设置时，需要在 session options -> connection -> port forwarding -> remote/x11 中勾选 x11 forwarding 下面的 forward x11 packets 和 enforce x11 authentication 。注意：不需要添加 remotely forwarded connections 中的内容。

#### linux端设置

- 要允许Linux主机上的SSH X转发，查看 /etc/ssh/sshd_config 文件，加入以下一行，`X11Forwrding yes` 至此配置完成。
- 保证 linux 端至少要有多个可以访问的用户。

#### 工作运行

- 上述部分 putty 设置完成后，开始登录，注意使用不同于 linux 上已经登录图形界面的账户登录 putty 。
- 在 windows 上使用 PuTTY 连接到 linux ，输入 xclock & ，可以看到一个图形化时钟出现了，说明图形化转发已经成功了。
- 输入 `google-chrome` 则可以在 xming 中打开 chrome 浏览器进行需要的操作了。
- 输入 `gnome-session` 则可以远程打开 GUI 交互环境。

**这边要注意的是：如果 putty 和 linux GUI 登录了同一个账号，则输入相关命令可能会无法打开相关 GUI，检查发现事实上，你要打开的窗口在 linux 主机上面被打开了，因此最好的办法是登录一个新的账号，进行相关的图形化操作。**


#### 小结

通过步骤可以发现，PuTTY + Xming 或 SecureCRT + Xming 的配置较为简单，但效率较低，即便传输速率达到 4mb/s 图像依然刷新较慢，体验效果很差。可能是 ssh 的直接访问方式，没有对视频等多媒体进行过优化，推荐可以采用其他方式进行远程桌面连接，这边可以参考博客中另外一篇文章 *TeamViewer 远程控制*。




> 参考链接：
> http://www.zw1840.com/blog/zw1840/2008/10/putty-xming-linux-gui.html
