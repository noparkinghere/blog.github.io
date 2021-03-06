---
layout: post
title:  "u盘安装XP系统"
category: "软件应用"
date: "2016-06-30 18:12"
---

> **如果仅需要优盘安装XP可以直接查看Windows XP安装部分**

### 1.Why XP?

windows XP 这个系统微软早已停止服务了，一般现在也不再会有人会想着安装这个系统了。作为已经安装过各种系统多次的人而言，老实说我也只有最初不太懂电脑的中学时候用过XP，自从09年win7出来后，就开始转战 win7 了，个人写这篇文章主要出于以下几种原因：
- 这个系统相当稳定，占用资源很少，可以作为老旧机器的不二选择。
- 个人工作学习完全使用 Ubuntu 系统了，时不时会用 windows 平台下面的软件如：迅雷，百度云，photoshop 等，现在机器性能强劲，virtualbox 下的 xp 运行这些中小型软件完全没任何问题。
- XP 安装与其他软件比较为特殊，通过文章的总结，下次便于参考。

<!-- more -->

#### windows XP简介：
Windows XP，是微软公司（Microsoft）推出的供个人电脑使用的操作系统，包括商用及家用的台式电脑等。Windows XP率先使用双列菜单，为之后的Windows 版本的开始菜单提供了基础。其名字 "XP" 的意思是英文中的 "体验（Experience）"，现已退役，如果你在结束支持后继续使用 Windows XP，那么你的电脑仍可工作，但它可能更容易受到安全风险与病毒的攻击。

*我们这边以纯净版的sp3中文专业版为例。*

### 2.常规系统安装方法

#### 2.1光驱安装

以往的系统安装大多使用光驱安装，而电脑的 BIOS 引导项也都有光驱引导，但随着上网本，超极本等的流行，越来越多的电脑为了节省空间将光驱给去掉了。

事实也是如此，光驱读取速度慢，且网络如此发达，现在很多厂家现在也都不再提供光盘，而是通过官方网站自行获取相关软件及驱动程序，或者直接提供优盘（优盘越来越廉价）。

*光盘安装简单，但不作为本文的重点，以下将不会再涉及。*

#### 2.2优盘安装

##### 2.2.1windows下的PE安装方式

大多数 windows 的产品都可以将优盘制作成一个 PE 启动盘，然后通过这个启动程序，引导需要安装的 ISO 文件，最终完成安装。

###### 优点：

- 通过 pe，在安装系统之前，可以执行相关备份，分区等操作。
- 一次 pe 制作，下次可以重复反复使用，pe 一般通过软件制作在优盘中，很多都形成单独分区，不会影响优盘的正常使用。
- 通过 pe 可以执行一些辅助的操作，可以将 pe 作为一个系统软件，即便不需要安装系统，可以通过 pe 做一些事情。

###### 缺点：

- 不同的 windows 系统，对应的 pe 不一样！！！没错确确实实不一样，例如： xp 的 pe 就基本上不可能帮你安装 win7 ，同样 win7 的 pe 也不可能让你安装的上 win10 或者 winXP 。
- 现在 pe 越做越复杂，对于只需要安装系统的新手来说，弄清楚里面 ghost 安装，原版安装，优盘一键安装这都很费力。

###### 小结：

- pe 安装虽然可以解决大多数问题，但毕竟太过冗余，而且不同的系统安装还需要不同的PE，另外对于linux等其他系统也完全没办法解决。


##### 2.2.2ultraISO制作u盘安装盘

注意 ultraISO 并非一个免费的软件，且免费版本的功能极为有限，这边提供ultraISO大容量版安装程序：`http://pan.baidu.com/s/1hrXbQ7q`

### 3.Windows XP安装

xp的安装同以上安装略有不同，原因根据查找可能是xp本身系统是不完全支持优盘引导的，所以在制作优盘XP引导时，如果仅仅使用ultraISO是很可能无法成功的。如下图：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/1.jpg)


为了解决这个问题，我们通过另外一个软件 WinSetupFromUSB 来制作 XP 优盘引导。

使用 WinSetupFromUSB 只需要下载一个 6.5MB 的绿色软件就可以制作好 windowsXP 的安装U盘，方便简捷。WinSetupFromUSB 不仅支持 WindowsXP 的，还支持 Win7/Vista 安装U盘的制作。

#### 3.1准备工具：

- 1G 以上 U 盘一枚，XP安装程序约为700M
- WinSetupFromUSB 1.0 beta7：
`http://pan.baidu.com/s/1geXdWyR`
`http://download.csdn.net/detail/littlefang/3664196`
- 下载 Windows XP 安装光盘或镜像：
`http://pan.baidu.com/s/1bNeMp4`


#### 3.2制作步骤：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/2.gif)



![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/3.gif)


- 在 3 BootOption 栏目中选择 XP/BartPE bootable[NTLDR]，在 4 FILESYSTEM and OVERRIDES中选择 NTFS和BOOT as HDD，然后点击 6 Prepare Drive

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/4.gif)


- 开始写入引导文件

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/5.gif)


![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/6.gif)


- 待窗口关闭后返回 RMPrepUSB 界面，点击 exit 退出

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/7.gif)


- 指定安装文件路径回到 WinSetupFromUSB 主界面，选中 Windows 2000/XP/2003 Setup，指定安装盘所在盘符（I386文件夹的父目录），我使用虚拟光驱把xp的镜像加载到E盘。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/8.gif)


- 等待启动 U 盘制作完毕，这个过程极为漫长，参考资料说 10 分钟，但实际用了 40 分钟左右。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/9.gif)


- 完毕就绪

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/10.gif)


#### 3.3安装步骤：

- 开始安装系统，相关 bios 设置这边不详细列出，电脑的厂家不一样，设置也不相同，快速设置功能未必打开，全功能的 bios 设置一般台式机为 delete 按键，笔记本可能是 F2,F10,F12 等根据主板型号而定，修改 bios 主要是为了修改引导方式，电脑一般加载系统会从硬盘进行引导，如果你想从优盘或者光盘引导系统的话，就需要在 boot 中将优盘或者光盘放在最高的优先级（第一位）。这边我们因为使用优盘安装，所以将优盘放在最上面即可。注意：如果你电脑打开了快速设置，一般可以直接选择优盘进行引导，而如果你的电脑是 Lenovo 等在主板中启用了安全功能，则需要讲该功能关闭才可以修改 bios 的引导方式，另外 UEFI 模式这边也需要改成 BIOS/legacy 模式。

- XP安装界面，如果是全新硬盘，需要分区等操作，先使用 winPE 等工具，安装位置选择 C 盘（主分区）默认选项安装即可。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-06-30-windowsXP纯净版安装/11.gif)


- 现在 CPU 和硬盘普遍读取速度快，XP 可能显示需要安装 30 分钟以上，但实际一个固态硬盘 +intel i5 以上的处理体只需要5分钟左右即可安装完毕。

#### 3.4后续补充：
- 因为安装的是纯净版的 XP，因此极有可能会缺少相关驱动程序，尤其是网卡驱动，因此建议系统安装完毕后，使用驱动精灵（网卡版）将网卡驱动补全，进一步将所有需要的驱动下载安装，如果比较冷门的旧机器建议可以去官网下载驱动，主要需要安装的是网卡，intel 相关和显卡驱动，其他驱动程序不会有太大的影响。


> 参考链接：
> http://blog.csdn.net/littlefang/article/details/6851864
> http://jingyan.baidu.com/article/ca2d939df51697eb6d31ce10.html
> http://blog.sina.com.cn/s/blog_4a22a65a0101e0tz.html
