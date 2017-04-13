---
layout: "post"
title: "GithubPages+https"
date: "2017-04-13 18:51"
---

### https 简介

HTTPS（全称：Hyper Text Transfer Protocol over Secure Socket Layer），是以安全为目标的HTTP通道，简单讲是HTTP的安全版。即HTTP下加入SSL层，HTTPS的安全基础是SSL，因此加密的详细内容就需要SSL。https:URL表明它使用了HTTP，但HTTPS存在不同于HTTP的默认端口及一个加密/身份验证层（在HTTP与TCP之间）。

超文本传输协议HTTP协议被用于在Web浏览器和网站服务器之间传递信息。HTTP协议以明文方式发送内容，不提供任何方式的数据加密，如果攻击者截取了Web浏览器和网站服务器之间的传输报文，就可以直接读懂其中的信息，因此HTTP协议不适合传输一些敏感信息，比如信用卡号、密码等。

为了解决 HTTP 协议的这一缺陷，需要使用另一种协议：安全套接字层超文本传输协议HTTPS。为了数据传输的安全，HTTPS在HTTP的基础上加入了SSL协议，SSL依靠证书来验证服务器的身份，并为浏览器和服务器之间的通信加密。

HTTPS和HTTP的区别主要为以下四点：
- https 协议需要到 ca 申请证书，之前免费的证书比较少，所以一般国内只有财大气粗的网站使用该协议，但现在情况不同了，一些网站提供了免费的 HTTPS，可以试用下，个人用户往往功能不全，但是免费的。
- http是超文本传输协议，信息是明文传输，https 则是具有安全性的ssl加密传输协议。
- http和https使用的是完全不同的连接方式，用的端口也不一样，前者是80，后者是443。
- http的连接很简单，是无状态的；HTTPS 协议是由SSL+HTTP协议构建的可进行加密传输、身份认证的网络协议，比 HTTPS 协议安全。

值得注意的是：HTTPS 可能会略微影响你的访问速度，但它足够安全，因此如果可以的话，建议都上 HTTPS，现在的各种流氓运营商恶意软件，往往会篡改 HTTP 页面的内容，如果你使用 HTTP 的话，当你访问京东商城时，可能会遇到京东主页被篡改，一些商品被链接到非官方网站；更有甚者，手机下载 APP 的网站被篡改，意外的下载了病毒软件。

### Github Pages

Github Pages 是面向用户、组织和项目开放的公共静态页面搭建托管服 务，站点可以被免费托管在 Github 上，你可以选择使用 Github Pages 默认提供的域名 github.io 或者自定义域名来发布站点。Github Pages 支持 自动利用 Jekyll 生成站点，也同样支持纯 HTML 文档，将你的 Jekyll 站 点托管在 Github Pages 上是一个不错的选择。一般一个库的最大容量是 500M，如此大的容量写博客的话完全绰绰有余了，和其他方式相比，优点是不需要花钱买 VPS 而且定制性也更强；缺点是公有库的话会让你的内容可以被所有人看到。

原生 Github Pages 可以在线帮你将 jekyll 文件生成 html 文件，而其通过其他方式构建的网站，如 hexo 等则必须本地生成 html 将 html 上传后才可以正常访问，两者各有优缺点：
- jekyll 在线生成速度慢，且缺少比较好看精致的模板。
- hexo 等其他页面可以做出很好的效果，但需要本地生成 html 较为麻烦。

由于 github pages 的部署并不是特别容易，也相当于一个单独的篇幅，这边不再另做介绍，详细可以参考文章[Github Pages + Jekyll 独立博客一小时快速搭建&上线指南](http://playingfingers.com/2016/03/26/build-a-blog/)和[GithubPage+Hexo搭建博客](https://noparkinghere.top/2016/12/14/2016/2016-12-14-GithubPage+Hexo%E6%90%AD%E5%BB%BA%E5%8D%9A%E5%AE%A2/)。

### https 部署

该部分详细内容可以参考[Secure and fast GitHub Pages with CloudFlare](https://blog.cloudflare.com/secure-and-fast-github-pages-with-cloudflare/)，这边只对这部分内容做个补充说明。

GitHub Pages 不支持上传SSL证书，我们采用 CloudFlare 提供的免费 HTTPS 服务。CloudFlare 是一家CDN提供商，它提供了免费的 HTTPS 服务(但不是应用 SSL 证书)。实现模式就是，用户到CDN服务器的连接为 HTTPS，而 CDN 服务器到 GithubPage 服务器的连接也为 HTTPS，但 GithubPage 服务器上不嵌入证书，我们可以采用如下图的方式 1 和方式 2 。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2017-04-13-githubpage-https/1.png)

详细步骤可以分为以下几部：
- 注册并登录 CloudFlare，并将自己域名下的 name server 修改为 CloudFlare 的 name server，那万网为例，就是在域名管理下，将DNS服务器从万网的地址改为 CloudFlare 提供的地址，例如：`boyd.ns.cloudflare.com` 和 `donna.ns.cloudflare.com`。
- 在 CloudFlare 的 DNS 中设置，因为你不存在 IP 地址，所以这边选用 CNAME，name 中填入你需要显示的域名名称，IPv4 中填入跳转的地址即 github pages 的地址。以上内容基本上任何域名服务网站都一样，不仅限于 CloudFlare。

![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2017-04-13-githubpage-https/2.png)

- 下面正式加入 HTTPS 服务，在 CloudFlare 的 Crypto 设置 SSL 为 Flexible 或者 FULL 均可，注意这边并不是立即生效的，需要等待一段时间。
- 在 CloudFlare 的 Page Rules 中设置路由规则，这边功能就比较多了，我们可以将它理解为一个具备小型功能的服务器，里面一些功能之前是需要通过自己服务器上面设置的。这边只说两种常用功能。其一，设置 `http://yoursite.com/*` 强制使用 HTTPS ，这样的话，所有访问 `http://yoursite.com/*` 的操作都会变为` https://yoursite.com/*` 。其二，可以将目标地址重定向，输入 `http://www.yoursite.com/*` 然后选择 forwarding URL ，选择 301 重定向，下面输入 `https://yoursite.com/*` 。这时，你访问 `http://www.yoursite.com/*` 时将会自动跳转到 `https://yoursite.com/*` 页面。**注意：如果有多个规则的话，强制 HTTPS 的规则要放在第一位。**


![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2017-04-13-githubpage-https/4.png)


![](https://raw.githubusercontent.com/noparkinghere/noparkinghere.github.io/master/img/2017-04-13-githubpage-https/5.png)

注意：以上步骤设置后并非立即生效，需要等待一段时间。

### 其他补充

CNAME 中设置跳转的目标页面，一般 CNAME 设置后，会将你的域名作为主要显示域名，一般网站是不允许这么做的，Github Pages 加入了 CNAME 认证，只有两者一致的话，才会返回结果，否则返回错误页面，大多数网页也都是如此。注意这些设置不是立刻生效，我们可以这么验证，如果 CNAME 设置成功了，则会返回 `Invalid URL`，因为你的域名不被对方认可拒绝访问；而如果 CNAME 没有成功，则会跳出：`This page isn’t working`，代表服务器不响应。

采用 CNAME + CloudFlare 的 Page Rules 可以不需要本地服务器，即可完成域名的跳转，具体方法如下：
- 需要建立一个 CNAME 跳转，名称可以是你需要跳转的地址，因为如果不设置的话，下面步骤可能不会生效。
- 我们只需要设置 Page Rules ，将里面的规则进行更改，如：可以将目标地址重定向，输入 `http://www.yoursite.com/*` 然后选择 forwarding URL ，选择 301 重定向，下面输入 `https://www.qq.com/*`，一般这个不是立刻生效，需要耐心等待，页面如果跳出 CloudFlare 相关信息，很可能是已经设置成功，但还没有生效。


> 参考链接：
> http://baike.baidu.com/link?url=2m1AdjLvBGnRv4lsaPqsNch_ZFdA_jp-YVdn4FBcZhszyRB7naHX2d9mLytRTtgCcv8qLczVjLKxVZJWFnOrmq
> http://blog.csdn.net/u010887744/article/details/50762202
> https://blog.cloudflare.com/secure-and-fast-github-pages-with-cloudflare/
> https://www.seozac.com/seo/301-redirect/
> https://www.zhihu.com/question/20376047?sort=created
> https://pages.github.com/
> http://jekyllcn.com/docs/github-pages/
> http://www.freebuf.com/articles/neopoints/45822.html
