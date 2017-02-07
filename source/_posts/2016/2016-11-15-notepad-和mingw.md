---
layout: "post"
title: "notepad++和MinGW"
date: "2016-11-15 16:16"
---

今天写一个换算的小程序，但无奈手头没有编译工具，归根结底为何如此麻烦还是因为windows下的开发不友好不自带常规编译器所决定的，一个简单的程序编译需要你去安装庞大的IDE等。以前用windows偶尔弄点c代码编译或者查看一些文件都是使用notepad++的，有算是比较长的一段时间了，但不久前重装了系统，notepad++虽然仅仅需要选几个皮肤，简单配置作为文本编辑器即可，但无奈MinGW如何调用已经忘了，本文列出个简要步骤，以便下次查看。


### 实际需求

Windows下编写C语言程序，使用如VS2010之类的IDE往往显得大材小用，并且这些集成开发环境都占用了大量的系统和硬件资源，且不如Notepad++之类的编辑器简单易用、定制性强大。最重要的一点在于学习编程的话，建议不要怕麻烦还是从最基础的学起，IDE往往屏蔽了很多的细节，并不利于初学者的学习。Linux下写C推荐可以研习emacs、vim配gcc。起初是想从网上直接找个教程按部就班执行，轻松配置完成的，但看了几个教程都不尽如人意，通过自己多次尝试最终找到了较为满意的解决方法，文章列出了部分参考网络教程的链接，下面对此详细阐述。而MinGW (Minimalist GNU for Windows)听名字就只是很强大，因为gcc的使用广泛和强大，无疑这个套件是编译的理想选择。


### 软件安装

[notepad++](https://pan.baidu.com/s/1slNDMtn)只是一个文本编辑器，本身没有编译C/C++的功能。所以要想先配置，就要先装上一个编译器。MinGW是GNU开源社区面向windows用户提供的一个集成了个编译环境的软件包。一般可以通过搜索MinGW直接去官网下载安装，但官网貌似是在线安装，因此我从其他网站下载了[MinGW-5.1.6](https://pan.baidu.com/s/1bFK8TC)离线包，安装步骤很简单，这边不具体阐述。

<!-- more -->


### 相关配置


#### MinGW

环境变量，简而言之就是在终端中直接输入名称，系统能够识别，且运行的一些可执行文件名称。在（我的电脑右击－－>系统属性－－>高级－－>环境变量－－>系统变量 中）（以下目录都根据自己的电脑MinGW所在位置不同而改变）在PATH的值中加入“D:\MinGW\bin”（如果没有就新建一个PATH）。如果PATH中还有其他内容，需要用英文状态下使用分号进行分割。这是寻找gcc编译器的路径。（这一步中PATH的值根据你的MinGW安装的路径设定，要能够访问的gcc编译器，也就是MInGW安装目录里面的bin文件夹）

下面两步作为可选步骤，如果有确切需求可以添加：新建LIBRARY_PATH变量，在其值中加入“D:\MinGW\lib”。这是标准库存放的路径。新建C_INCLUDE_PATH变量，在其值中加入“D:\MinGW\include”。这是Include查找头文件的路径。

设置结束之后，在cmd控制台窗口下面，输入gcc -v。若已经成功安装好，会显示gcc的版本信息。比如说我的：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-15-notepad-%E5%92%8Cmingw/2.png)

测试一下：
随便找个c文件，你也可以自己写个。使用命令提示符cd到c文件保存的目录，然后：输入`gcc -o test.exe (你的c文件名).c`如果有提示语法错误或者在当前目录生成了test.exe那说明gcc可用了，如果提示 'gcc' 不是内部或外部命令，也不是可运行的程序或批处理文件。说明环境MinGW的环境变量未设置成功。


#### notepad++

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-11-15-notepad-%E5%92%8Cmingw/1.png)

如上图，选用自己喜欢的风格模式，对里面的一些背景参数适当的设置，将行号等常用的功能打开，可以隐藏一些不需要的工具栏，菜单中列出了可以执行的一些操作，适当借用于快捷键可以更快的编写代码。

由于这边主要是让notepad++可以一键编译c程序，所以为其加上编译，运行。

- 编译：按F5输入`cmd /k gcc -o "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" "$(FULL_CURRENT_PATH)" & PAUSE & EXIT` 点保存，设置快捷键为F9
- 运行：按F5输入`cmd /k "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" & PAUSE & EXIT`保存，设置快捷键为Ctrl+F9

上述两步，环境搭建完成，当你用N++编写程序时，先保存再按F9可编译，然后再按Ctrl+F9开看到运行结果。

熟练习惯后，可以将编译运行一起使用：`cmd /k gcc -std=c99 -o "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" "$(FULL_CURRENT_PATH)" & cmd /k "$(CURRENT_DIRECTORY)\$(NAME_PART).exe"& PAUSE & EXIT`或者`cmd /k gcc -std=c99 -o "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" "$(FULL_CURRENT_PATH)" & pause & "$(CURRENT_DIRECTORY)\$(NAME_PART).exe"& PAUSE & EXIT`保存，设置快捷键为Ctrl+F5。



**关键字说明：**

```sh
引号的使用是为了适用于文件名或者路径中带有空格的情况，一定不能省略。
& PAUSE 含义是命令运行后暂停等待键盘操作
& EXIT 含义是完成后退出运行窗口，回到notepad++
$(NAME_PART) 代表当前正操作的文件的文件名，不含后缀；
$(FULL_CURRENT_PATH) 代表当前正操作的文件的完整路径，包括盘符、路径、文件名、后缀；
$(CURRENT_DIRECTORY) 代表当前文件所在的目录路径；
通过以上三个环境变量可以很容易的理解上面一段指令的含义。
至于gcc，-o参数就是将一个c文件编译成exe文件。gcc的bin目录已经之前在系统环境变量中进行过设定，否则需要补全gcc命令的绝对路径。(很简单，将"g++.exe"换成"D:\MinGW\bin\g++.exe",还是要参照你安装的路径）
```

***

> 参考链接：
> http://jingyan.baidu.com/article/9989c7461dc55ff648ecfe12.html
