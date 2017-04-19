---
layout: "post"
title: "VPS : shadowsocks"
category: "软件应用"
tags: 
date: "2016-11-25 09:30"
---

日常生活中，由于GFW的强大，很多学习资料等内容我们无法获取或者检索，因此科学上网往往相当重要，本文章使用 VPS 搭建 shadowsocks 服务让安全的科学上网成为可能，需要注意的是 VPS 必须是境外服务器，推荐 vultr 搬瓦工等廉价vpn。另外你也可以访问[shadowsocks 官网](https://shadowsocks.org/en/index.html)查看详细的教程和下载软件。

### 工作原理

**这边可以参考[原文博客](http://vc2tea.com/whats-shadowsocks/)，以下只是简单罗列一些原理：**

- 早期互联网用户访问网站时，用户的请求通过互联网发送到服务提供方，服务提供方直接将信息反馈给用户： 

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/ss1.png)

- GFW 出现后，每当用户需要获取信息，都经过了 GFW，GFW将它不喜欢的内容统统过滤掉，于是客户当触发 GFW 的过滤规则的时候，就会收到 Connection Reset 这样的响应内容，而无法接收到正常的内容 

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/ss2.png)

- 为了绕过GFW的过滤（包含了各种HTTP代理服务、Socks服务、VPN服务等等），以 ssh tunnel 的方法为例：1) 首先用户和境外服务器基于 ssh 建立起一条加密的通道 2-3) 用户通过建立起的隧道进行代理，通过 ssh server 向真实的服务发起请求 4-5) 服务通过 ssh server，再通过创建好的隧道返回给用户。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/ss3.png)

**由于 ssh 本身就是基于 RSA 加密技术，所以 GFW 无法从数据传输的过程中的加密数据内容进行关键词分析，避免了被重置链接的问题，但由于创建隧道和数据传输的过程中，ssh 本身的特征是明显的，所以 GFW 一度通过分析连接的特征进行干扰，导致 ssh 存在被定向进行干扰的问题**

- shadowsocks 是将原来 ssh 创建的 Socks5 协议拆开成 server 端和 client 端，所以下面这个原理图基本上和利用 ssh tunnel 大致类似:1、6) 客户端发出的请求基于 Socks5 协议跟 ss-local 端进行通讯，由于这个 ss-local 一般是本机或路由器或局域网的其他机器，不经过 GFW，所以解决了上面被 GFW 通过特征分析进行干扰的问题 2、5) ss-local 和 ss-server 两端通过多种可选的加密方法进行通讯，经过 GFW 的时候是常规的TCP包，没有明显的特征码而且 GFW 也无法对通讯数据进行解密 3、4) ss-server 将收到的加密数据进行解密，还原原来的请求，再发送到用户需要访问的服务，获取响应原路返回:

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/ss4.png)


- GFW 就出现了，他像一个收过路费的强盗一样夹在了在用户和服务之间，每当用户需要获取信息，都经过了 GFW，GFW将它不喜欢的内容统统过滤掉，于是客户当触发 GFW 的过滤规则的时候，就会收到 Connection Reset 这样的响应内容，而无法接收到正常的内容 

### 软件简介：

#### shadowsocks:

[shadowsocks：A secure socks5 proxy,designed to protect your Internet traffic.](https://shadowsocks.org/en/index.html)。

Shadowsocks（中文名称：影梭）是使用Python、C++、C#等语言开发的、基于Apache许可证的开放源代码软件，用于保护网络流量、加密数据传输。Shadowsocks使用Socks5代理方式。Shadowsocks分为服务器端和客户端。在使用之前，需要先将服务器端部署到服务器上面，然后通过客户端连接并创建本地代理。在中国大陆，本工具也被广泛用于突破防火长城（GFW），以浏览被封锁、屏蔽或干扰的内容。在2015年8月22日，Shadowsocks原作者Clowwindy称受到了中国政府的压力，宣布停止维护此项目并移除其用户页面所载的源代码。

Shadowsocks的运行原理与其他代理工具基本相同，使用特定的中转服务器完成数据传输。在服务器端部署完成后，用户需要按照指定的密码、加密方式和端口使用客户端软件与其连接。在成功连接到服务器后，客户端会在用户的电脑上构建一个本地Socks5代理。浏览网络时，网络流量会被分到本地socks5代理，客户端将其加密之后发送到服务器，服务器以同样的加密方式将流量回传给客户端，以此实现代理上网。

- Shadowsocks使用自行设计的协议进行加密通信。[4]加密算法有AES、Blowfish、IDEA、RC4等，除创建TCP连接外无需握手，每次请求只转发一个连接，因此使用起来网速较快，在移动设备上也比较省电。
- 所有的流量都经过算法加密，允许自行选择算法，所以比较安全。
- Shadowsocks通过异步I/O和事件驱动程序运行，响应速度快。
- 客户端覆盖多个主流操作系统和平台，包括Windows，OS X，Android和iOS系统和路由器（OpenWrt）等[5]。
- 专为移动设备和无线网络优化。





#### supervisor:

Linux的后台进程运行有好几种方法，例如nohup，screen等，但是，如果是一个服务程序，要可靠地在后台运行，我们就需要把它做成daemon，最好还能监控进程状态，在意外结束时能自动重启。supervisor就是用Python开发的一套通用的进程管理程序，能将一个普通的命令行进程变为后台daemon，并监控进程状态，异常退出时能自动重启。


### VPS 安装及配置：

#### 软件列表：

- vps（Debian GNU/Linux 7 ），这边采用 Debian 系列linux，ubuntu 应该步骤类似，如果使用 redhat 系列，部分指令需要自行更改，这边不做累述。
- shadowsocks-severs： 注意安装 shadowsocks 的 severs 版本
- supervisor ： 用于Linux后台进程管理的利器

<!-- more -->


#### 详细步骤：

- 安装软件，终端输入：`apt-get install python-pip && pip install shadowsocks`。
- 写 shadowsocks 配置文件： vim /etc/shadowsocks.json ， 具体内容如下：

```sh
{
    "server":"0.0.0.0",
    "server_port":50003,
    "local_address": "127.0.0.1",
    "local_port":1080,
    "password":"123456",
    "timeout":300,
    "method":"aes-256-cfb",
    "fast_open": false
}


说明： 
server 你vps的IP
servier_port 服务端的端口
local_port 本地端口，一般默认1080
password 服务端设置的密码
timeout 超时设置
method 加密方法

如要你需要分享SS服务给朋友或家人，可以配置多个SS账户，具体可以参考下面的代码:
{
    "timeout": 600,
    "method": "aes-256-cfb",
    "port_password":
    {
        "40001": "password1",
        "40002": "password2",
        "40003": "password3"
    },
    "_comment":
    {
        "40001": "xiaoming",
        "40002": "lilei",
        "40003": "mike"
    }
}
```

注意这边 server 的地址可以通过 ipconfig 获取本机地址，如果是一些多层虚拟出来的机器，如果无法获得本机IP，则输入0.0.0.0即可。

- 安装 supervisor： apt-get install supervisor
- 将 shadowsocks 加入到 supervisor 中进行管理：vim /etc/supervisor/supervisord.conf 在末尾加入如下内容：

```sh
[program:shadowsocks]
command=ssserver -c /etc/shadowsocks.json
autostart=true
autorestart=true
user=root
log_stderr=true
logfile=/var/log/shadowsocks.log
```
- 最后让 supervisor 开机自启动：在 `vim /etc/rc.local` 空白行加入 `service supervisor restart` (事实上这一步可以不用加，supervisor 本身就会开机自启动，在 `/etc/rc2.d/` 下 我们可以看到 `lrwxrwxrwx 1 root root  20 Nov 25 11:56 S01supervisor -> ../init.d/supervisor` ，当然如果你的系统没能自动开启 supervisor 守护进程，则需要手动完成上述操作)，重启服务器查看是否配置成功。


*采用 supervisor 的原因很大程度上是：将 `sslocal -c /etc/shadowsocks.json` 放入/etc/rc.local中没法开启自启该服务，有待查找原因。*


**以上内容均为个人总结转述，如果可以访问外网，请参考[官网](https://shadowsocks.org/en/download/servers.html)给出的更加详细的配置步骤。以下为客户端配置，注意只有在完成了服务器端配置或者你已经有一个可以使用的 shadowsocks 服务器，才能够在本地搭建以下服务。**



### 本地 linux 下的安装配置

#### 软件列表：

- linux PC端： shadowsocks ， 本地操作系统 ubuntu 16.04 , 。
- shadowsocks-severs： 注意安装 shadowsocks 的 severs 版本
- supervisor ： 用于Linux后台进程管理的利器
- chrome 插件 SwitchyOmega ：

#### 详细步骤：

- 安装 shadowsocks （我们这边不采用 GUI 软件而直接使用 shadowsocks 命令工具连接 shadowsocks 服务器。）步骤如下：

```sh
sudo apt-get update
sudo apt-get install python-pip
sudo apt-get install python-setuptools m2crypto
pip install shadowsocks

注意： 如果是 ubuntu 16.04 的版本执行完以上命令后可能仍然无法执行 sslocal 命令，需要手动执行 `sudo apt install shadowsocks` （ubuntu16.04 直接可以直接用apt 而不用 apt-get 这是一项改进）。

```

- 配置 Shadowsocks ：同服务器类似， 也是配置 shadowsocks.json 这个文件，可以在你想要指定的目录下新建这个文件如：~/.config/shadowsocks.json ， 编辑该文件：

```sh
{
    "server":"www.baidu.com",
    "server_port":50003,
    "local_port":1080,
    "password":"123456",
    "timeout":600,
    "method":"aes-256-cfb"
}

说明：
server 后面填写你需要链接的服务器地址
server_port 后面填写你 Shadowsocks 服务器配置的 server_port 端口
local_port 无需修改
password 需要和 Shadowsocks 服务器保持一致

```

- 完成以下步骤后，你的浏览器仍然不能浏览网页，Shadowsocks 仅提供了转发服务，而你本地的端口发送的数据还无法和server_port进行链接，这时候，你可以采用全局代理的软件让所有数据帮转发，这边推荐chrome的 SwitchyOmega 插件。可以从Github上直接下载最新版 [SwitchyOmega](https://github.com/FelisCatus/SwitchyOmega/releases/) （这个是chrome的）然后浏览器地址打开chrome://extensions/，将下载的插件托进去安装。安装好之后下面开始设置代理，如下图：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/1.png)

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/2.png)

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/3.png)

上图步骤中注意类型条件中勾选**规则列表规则**， 规则地址： https://raw.githubusercontent.com/gfwlist/gfwlist/master/gfwlist.txt 填入其中。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/4.png)

点击 “应用选项”。然后单击 switchyOmega 图标，选择自动切换，就可以在访问“不存在的网站” 时自动切换到 shadowsocks 代理了。如果遇到某个国外网站无法直接连接或速度太慢时，可以单击 switchyOmega 图标，选择 “添加条件”，情景模式选择 SS，就可以了。这时打开 switchyOmega 选项，在自动切换模式的切换规则中就可以看到刚刚添加的规则。可以在这里管理自定义的规则。

如果换了一台电脑，重新设置一遍 switchyOmega 就太麻烦了。可以在设置好的 switchyOmega 中导出设置文件，在另一个 chrome 浏览器中导入，就可以直接复制原来的设置了。在 switchyOmega 选项的左侧点击 “导入 / 导出”，点击“生成备份文件” 即可生成 switchyOmega 设置备份。点击 “从备份文件恢复” 可以导入备份文件。


- 安装 supervisor： sudo apt-get install supervisor
- 将 shadowsocks 加入到 supervisor 中进行管理：vim /etc/supervisor/supervisor.conf 在末尾加入如下内容，或者在 /etc/supervisor/conf.d 下新建新的文件增加如下内容（注意 shadowsocks.json 文件路径写对）：

```sh
[program:shadowsocks]
command=sslocal -c /home/username/.config/shadowsocks.json
autostart=true
autorestart=true
user=root
log_stderr=true
logfile=/var/log/shadowsocks.log
```

- 最后让 supervisor 开机自启动：在 `sudo vim /etc/rc.local` 空白行加入 `sudo service supervisor restart`。*不知出于什么原因这边 supervisor 必须手动写入 /etc/rc.local 中才会开机自启动* 查看是否配置成功可以重启电脑。

*如果需要让 linux 下其他软件也都可以使用 ss 服务，可以参考我的另外一篇文章：linux-shadowsocks全局代理。*

### 本地 windows 下安装配置

[下载客户端](https://github.com/shadowsocks/shadowsocks-windows/releases/download/3.3.5/Shadowsocks-3.3.5.zip)，作为一个开源软件 GUI 客户端分为多个版本，这边提供了 win 版本，需要安装 微软的库，打开后如下图所示：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/5.png)

这边的服务器 IP 同上面 linux 的类似，填写你的域名或者 IP 即可，密码也要和服务器的 shadowsocks 服务保持一致。值得一提的是 windows 下面的客户端直接可以设置全局代理，右击任务栏的小图标可以设置相关选项。

### 本地 安卓手机端 安装配置

安卓用户这边推荐使用腾讯自家的应用宝，直接搜索 shadowsocks 会看到中文名“影梭”的这个软件(*注意应用宝中的软件版本较老，为 2.8.3 目前最新版本为 3.2.7。*)，设置基本和 windows 的类似，设置完毕后，点击右上角的开启按钮。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-25-vps-shadowsocks/6.png)

其中安卓和苹果的[shadowsocks 官网](https://shadowsocks.org/en/index.html)给出地址都是应用商城地址，用户可以直接去 github 去查找 shadowsocks 库，在 releases 中下载最新的版本。


> 参考链接：
> http://vc2tea.com/whats-shadowsocks/
> https://aitanlu.com/ubuntu-shadowsocks-ke-hu-duan-pei-zhi.html
> https://aitanlu.com/linux-ubuntu-install-shadowsocks.html
> https://php-rmcr7.rhcloud.com/shadowsocks-server/
> http://blog.chinaunix.net/uid-25530360-id-5595974.html
> http://www.liaoxuefeng.com/article/0013738926914703df5e93589a14c19807f0e285194fe84000
> https://zh.wikipedia.org/zh-hans/Shadowsocks
> https://github.com/shadowsocks/shadowsocks/tree/master
> http://webcache.googleusercontent.com/search?q=cache:http://everet.org/shadowsocks.html
