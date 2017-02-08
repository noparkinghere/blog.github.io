---
layout: "post"
title: "git submodule 详解"
category: "软件应用"
tags: 
date: "2016-11-23 09:02"
---

使用 git 也有一段时间，但不得不说 git 的功能相当强大和复杂，需要你不断的去摸索学习。这边介绍一个 git 很强大的功能：git submodule 。起初发现这个文件是在我本人 fork 了一个 awesome 的配置文件，用了也蛮久，但最近由于总是出现连接错误，然后手动去更改了一些文件，但意外发现更改的文件无法提交， status 中竟然没有这些文件的信息，另外通过其他官方文档 gitignore 中的几个 ignore 中仔细查看，很确定项目中并没有忽略这些文件，通过排查最后才发现是 .gitmodules 这个文件捣的鬼。仔细研究发现git-submodule是一个十分强大的功能，值得去学习研究。


<!-- more -->



> 参考链接：
> http://www.kafeitu.me/git/2012/03/27/git-submodule.html
> https://git-scm.com/docs/git-submodule
> https://git-scm.com/docs/git-config
> https://git-scm.com/docs/gitignore
