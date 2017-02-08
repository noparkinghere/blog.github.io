---
layout: "post"
title: "Caps_Lock与右Ctrl互换"
category: "推荐配置"
tags:  
date: "2016-07-14 08:59"
---

*实现该功能的目的主要是切换中英文输入法，在使用 ctrl 或者 shift 切换时，很明显这两个键的位置远不如caps按起来方便，且 shift 往往作为大小写功能使用，用来作为切换中英文输入会恨混乱，而 caps 作为大小写时用起来相当罕见，作为中文输入来说更可以说完全是鸡肋的功能。大写完全可以用 shift 代替的用户群中，无疑是占用了一个最好的位置，却几乎完全被遗忘的一个按键。下面将会总结一个既保留 Caps_Lock 键功能，又可以充分利用这个最好位置的按键映射方法。*

### linux系统下的实现

#### 按键值查询

linux 下可以通过命令小程序对绝大多数按键值进行查找，要想修改键值映射, 先要知道按键的键值. 用如下命令查看: `xev | grep keycode`。

同时我们可以查看需要映射的按键的映射名称：

```sh
例如, 执行命令查看 Menu 键相关的按键名:

xmodmap -pke | grep menu -i
显示结果为:

keycode 135 = Menu NoSymbol Menu
keycode 147 = XF86MenuKB NoSymbol XF86MenuKB

```

比如想把键盘的右边的 Alt 改为 Menu : `xmodmap -e "keycode 108=Menu"`，简而言之 xmodmap 程序就是用来控制系统按键的，需要详细了解这个软件的操作，可以查看帮助文档。

<!-- more -->


#### 将Caps_Lock和键盘右边的Ctrl调换
在当前的用户根目录下～创建 .Xmodmap 文件(尤其注意:这边名称是Xmodmap首字母大写,很多教程都忽略了这个问题,往往导致配置出来有问题)，书写内容如下：

```sh
remove Lock = Caps_Lock
remove Control = Control_R
keysym Control_R = Caps_Lock
keysym Caps_Lock = Control_R
add Lock = Caps_Lock
add Control = Control_R
```

这样，caps lock 和 ctrl 就都是 ctrl 的功能。执行下`xmodmap ~/.Xmodmap  2>/dev/null`即可立即生效。实际上，每次开机启动后，系统会通过 xmodmap 程序自动加载 .Xmodmap 程序，也就是一次创建更改 .Xmodmap 文件，终身配置有效。

**注意:完成上述步骤即可，以下步骤为最初设置时,出现的问题,可以忽略不看。**

#### 加入开机自启
同大多数开机自启并没有太大区别，将`xmodmap ~/.xmodmap  2>/dev/null`写入到 /etc/rc.local 中即可。该方法经常失效，不是太灵验，因此我设置了快捷键 ctrl+space ，每次按下这个快捷键时，会自动执行`xmodmap ~/.xmodmap  2>/dev/null`。

解决:由于上面命名错误, .Xmodmap 文件的首字母是大写，因此加载总是出错，另外使用 `xmodmap ~/.Xmodmap  2>/dev/null` 命令后，每次无需再加入启动项了，一次配置成功即可。


### windows下的更换按键

打开注册表，在运行（win+R）中输入 regedit ，注册表位置：[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Keyboard Layout]  （注意： KeyBoard Layout, 而不是 KeyBoard Layouts）如果没有此键，就新建一个二进制值的 Key，名叫： Scancode Map（注意名称不能够写错，错一个字母都没法实现功能）。

```sh
输入如下的值：
　　00,00,00,00
　　00,00,00,00
　　03,00,00,00
　　3A,00,1D,E0
　　1D,E0,3A,00
　　00,00,00,00
```

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-07-14-Caps_Lock%E4%B8%8E%E5%8F%B3Ctrl%E4%BA%92%E6%8D%A2/BaiduShurufa_2016-8-10_14-5-24.png)

#### windows 各个键位值的参考：

```sh
　　Escape 01 00
　　Tab 0F 00
　　Caps Lock 3A 00
　　Left Alt 38 00
　　Left Ctrl 1D 00
　　Left Shift 2A 00
　　Left Windows 5B E0
　　Right Alt 38 E0
　　Right Ctrl 1D E0
　　Right Shift 36 00
　　Right Windows 5C E0
　　Backspace 0E 00
　　Delete 53 E0
　　Enter 1C 00
　　Space 39 00
　　Insert 52 E0
　　HOME 47 E0
　　End 4F E0
　　Num Lock 45 00
　　Page Down 51 E0
　　Page Up 49 E0
　　Scroll Lock 46 00
```

以上 windows 的按键更改仅在 windows 7 下实验过，其他系统有待验证。



> 参考链接：
> http://www.cnblogs.com/xiaobaibuhei/p/3629133.html
> http://hanjc.me/post/2015-09-14-win7-exchange-capslock-and-ctrl/
> http://www.mikewootc.com/wiki/linux/usage/linux_xmodmap_change_keyboard_map.html
> http://baohaojun.github.io/blog/2015/01/12/0-How-to-swap-Escape-and-Caps-Lock-on-mainstream-PCs.html
> http://www.xiaozhou.net/exchange_ctrl_and_capslock_key-2012-07-20.html
> http://xahlee.info/kbd/linux_make_capslock_esc_key.html
