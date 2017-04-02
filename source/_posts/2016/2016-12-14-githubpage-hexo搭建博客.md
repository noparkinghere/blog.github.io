---
layout: "post"
title: "GithubPage+Hexo搭建博客"
category: "软件应用"
tags:
date: "2016-12-14 19:01"
---


个人博客是使用 githubpage+jekyll 搭建的，且博客已经工作有半年了，但由于期初的模板没有找好，加上一些其他的问题，导致博客看起来比较凌乱，这边给出另外一个 GithubPage+Hexo 的博客搭建方法供大家参考，本文操作系统主要使用的是 ubuntu 16.04，使用其他 linux 发行版的用户，可以参考本文。附上最终效果图如下：

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-14-githubpage-hexo搭建博客/1.png)

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2016-12-14-githubpage-hexo搭建博客/2.png)

<!-- more -->

### 安装步骤

#### 安装 node.js

Node.js 是一个开放源代码、跨平台的、可用于服务器端和网络应用的运行环境，该应用由 C++ 语言写成，在 Node.js 运行时运行。Node.js 提供事件驱动和非阻塞 I/O API，可优化应用程序的吞吐量和规模。这些技术通常被用于实时应用程序。并且它是采用 Google 的 V8 引擎来执行代码，它的大部分基本模块都是用 JavaScript 写成的，包含有一系列内置模块，使得程序可以作为独立服务器运行，从而脱离 Apache HTTP Server 或 IIS 运行。npm 也即 Node包管理器（Node Package Manager），它是一个以 Javascript 编写的软件包管理系统，默认环境为 Node.js 。

- 安装 nodejs ： sudo apt-get install nodejs , 注意 ubuntu 16.04 使用：sudo apt install nodejs
- 安装 npm ： sudo apt-get install npm ， 注意 ubuntu 16.04 使用：sudo apt install npm

需要安装 nrm ， nrm 是 npm 的资源管理器，借助各个工具可以方便快捷地对 npm 的源进行管理。另外，由于国内网络环境原因在使用 npm 默认下载源的时候不仅速度非常慢而且常常会超时，因此这里还手动指定了从淘宝源下载。`sudo npm install nrm -g --registry https://registry.npm.taobao.org`，`nrm use taobao`（如果出现无法找到 node 则执行： `sudo  ln -s /usr/bin/nodejs /usr/bin/node` ）




#### 安装 git

这边步骤在多篇博文中都有详细描述，这边就不再累述了，可以直接搜索引擎搜索，或者在本博客的其他文章中找到。


#### 安装 Hexo

[Hexo](https://hexo.io/zh-cn/) 是一个快速、简洁且高效的博客框架。Hexo 使用 Markdown（或其他渲染引擎）解析文章，在几秒内，即可利用靓丽的主题生成静态网页。接下来我们开始使用 Hexo 搭建博客。

- sudo npm install hexo-cli -g 或者 sudo npm install -g hexo
- 如果以上命令遇到错误或者警告，则更新 npm 版本，`sudo npm i npm -g`
- 创建并进入目录 Hexo ：`mkdir Hexo && cd Hexo`
- 使用 hexo 生成博客框架。依次执行如下命令(hexo init blog 过程可能会比较慢，需要耐心等待。)：
```sh
$ hexo init blog
$ cd blog
$ npm install
$ hexo generate (hexo generate 为我们生成了静态文件存储于 public 文件夹之下，并且在一开始默认情况下执行这句将会为我们生成一个 Hello World 的页面。)
$ hexo server (通过 hexo server 运行起 hexo 内置的服务器。这时候就可以开始在本地访问了，默认地址为 localhost:4000 。)
```
注意：hexo 中的 generate, server, dpoly 等操作都可以简写为首字母，所以 hexo generate 等同于 hexo g ，hexo server 等同于 hexo s，。


### 模块简介
通过 tree | less 可以查看以下 blog 的目录结构，主要的几个文件和目录的作用分别如下：
- _config.yml ：配置文件，可以修改网站的主题、标题、作者等信息。
- public ：由 hexo 根据 source 文件夹中的资源进行渲染生成的文件夹，里边存储着最终的静态网页文件。
- scaffolds/ ：模板文件，当要给博客添加新文章的时候，将根据对应的模板进行创建。
- source/ ：用于存储用户资源，比如文章与新页面等。其中以 _ 开头的文件夹中除了 _posts 文件夹中的 markdown 或 HTML 文件会在执行 generate 操作的时候被渲染添加到 public 文件夹中之外，其他均被忽略。而且在初始化博客的过程中 _posts 目录底会自带一个 hello-world.md 的文件。
- themes/ ：主题文件，自带默认主题 landscape 。

### 操作指导

#### 文章创建

`hexo new [layout] <filename>` 其中 layout 为可选参数，指定了新创建的文件布局，默认为 post 文件。 filename 为必填参数，指定了文件名，如果文件名中有空格则需要把文件名用引号"" 包裹起来。例如： 终端输入：  `hexo new "我的第一篇文章"` ，这时候我们发现 hexo 在 source/_post 目录之下创建了一个 我的第一篇文章.md 的文件。打开该文件进行编辑。我们也可以通过 atom 等常用的 markdown 编辑工具直接在 source/_post 目录下创建文章进行编辑即可。刷新浏览器就可以看到我们博客更新的内容了。

至此我们基本配置好了本地 hexo 服务，能够自己写点内容了。

#### 插入图片

- 在 hexo/source 目录下新建一个img文件夹，将图片放入该文件夹下，插入图片时链接即为https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/图片名称。 注意目录必须为 hexo/source，且图片文件夹为 img ，否则通过 hexo generate 可能无法生成目标图片。
- 也可以使用[图床](http://tc.ffsky.net/)外链来存储图片。

### 部署到 github page

访问 github，创建库 `git账户名.github.io` ， 这一这个名字是固定的，一般的库没法修改跳转地址，只能显示为 github page 。

将远程库同步到本地，`git clone [你的仓库的 url]`，本地会多出一个 `git账户名.github.io` 的文件夹，然后把 public 文件目录下的博客文件都复制到你的本地仓库中，并将本地仓库 push 到 github 仓库上。这样当其他人访问你的博客链接的时候 github 将会自动将该仓库中的相应文件展示出来。

#### 方法1
由于访问网页最终都是访问的 html 文件，因此这边需要通过本地 hexo generate 工具生成所需的 html 页面代码，然后每次将你的 html 页面覆盖到 github 的项目中去。

执行如下命令：
```sh
	hexo g
	cp -R public/* [你的仓库名]
	cd [你的仓库名]
	git add .
	git commit -m 'update blog'
	git push
```

#### 方法2

注意，实际上 github page 是可以自己按照 jekyll 的方式将源码生成 html 文件的，但是 对于 hexo 等其他源码，如果需要展示出来，则必须本地生成 html 代码，然后把生成的代码部署到服务器上面才行，这边我们可以使用如上面的方式（将 public 目录下面生成的 html 文件直接复制到服务器的根目录下）， hexo 提供了更加人性化的方式，通过 hexo deploy 可以一键完成部署（无需在通过 push 手动推送了），每次部署的步骤，可按以下两步：

- 修改 该配置文件：vim _config.yml，执行如下命令才能使用 git 部署 `npm install hexo-deployer-git --save`
```sh
deploy:
  type: git
  repository: https://github.com/username/username.github.io.git
  branch: master
```
*注：type: git 老版本可能是 github，repository 后也可以采用 ssh 的地址，https 每次需要输入密码，而 ssh 需要配置好公钥私钥免密码。*

- 执行以下命令无需手动将代码 push 上去
```sh
hexo clean
hexo generate
hexo deploy
```

以上步骤虽然看起来貌似繁琐，但实际可以写成 bash 脚本，这样每次就会自动生成 public 自动复制以及上传了。

#### CNAME 配置

github page 可以使用上面提供的网址也可以让每次访问时跳转自己的域名地址，一般 github page 需要在根目录下新建一个 CNAME 文件，其中写下你的域名地址如：`www.google.com`。

因为 hexo 每次需要生成好文件再上传，这边将 CNAME 文件放入 source 目录下，每次 hexo g && hexo generate 后则会上传 CNAME 到 github page了。


### 扩展补充

上述虽然配置完成了 hexo 博客，但博客功能过于简单，使用起来不方便，可以添加图片，摘要，标签页与分类页等内容。

#### 主题配置

下载并解压缩 [NexT 主题](https://github.com/iissnan/hexo-theme-next)

`wget http://labfile.oss.aliyuncs.com/courses/700/next.zip && unzip next.zip`

需要将主题文件放入 Hexo/blog/themes 下，打开 ../blog/_config.yml 修改 theme 后的内容就可以更改主题了。这会博客就套上了我们的新模板了。但是我们发现博客菜单上的文字是英文的于是我们还要重新配置以下，让主题以中文的方式显示。再次编辑 _config.yml 文件，将 language 项设置为 zh-Hans 。

注意更改主题后每次需要重启 `hexo server` 服务才可以刷新网页。

*到 github 上面搜索，可以找到更多出色的主题，这儿给出一个[主题汇总](https://www.zhihu.com/question/24422335)。*


### 小结

hexo 比 jekyll 布局更简单，更加容易操作，但每次需要本地生成 html 然后上传同步，虽然这不是问题，可以用脚本实现，但对于图片等内容，需要依赖第三方图床就显得很是无奈了。


> 参考链接：
> http://behappyli.cn/2015/12/05/hexo%E6%95%99%E7%A8%8B/
> http://www.runoob.com/w3cnote/git-guide.html
> http://baixin.io/2015/08/HEXO%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2/
> http://blog.csdn.net/u012307002/article/details/51298705
> https://www.zhihu.com/question/24422335
> http://www.jianshu.com/p/1d427e888dda
> http://www.jianshu.com/p/f4dce0e76886
> http://baixin.io/2015/08/HEXO%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2/
> http://www.jianshu.com/p/2b9f202c13fd
> http://c4fun.cn/blog/2014/03/03/use-hexo-blog/
> http://www.cnfeat.com/blog/2014/05/10/how-to-build-a-blog/
