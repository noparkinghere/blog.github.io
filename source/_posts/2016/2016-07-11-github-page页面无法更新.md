---
layout: "post"
title: "GitHub_Page页面无法更新"
tags: "问题总结"
category: "read"
date: "2016-07-11 1:00"
---

### 详细问题：
- 文章会在github的工程目录中出现，但github page中首页和存档都无法显示。
- 仔细查看过套用的html等模板，未能发现有问题。
- 连续多次都是某一次推送下，突然问题就解决了。
- 通过github page提供的jekyll服务进行更新文章时，经常会出现文章已经上传到了github的远程库中，但github page却无法显示内容出来，这样的问题出现了很多差，但不断的上传或者某一次传输一个文章，突然就成功了。

<!-- more -->


### 具体原因：

GitHub_Page 使用的是jekyll服务生成page页面的。由于jekyll 3（github目前的jekyll版本）默认对于认定为"未来"的post，是不生成的，详情可以参考[Future posts - Jekyll](http://jekyllrb.com/docs/upgrading/2-to-3/#future-posts)。这极有可能与github服务在美国有关,本人使用的是VPN在美国，不知道是否对此也有影响。

### 解决方法：

- 网上说可以修改feed.xml文件，具体看参考链接。（本人没有实验成功）
- 我使用的方法改写时间：

```sh
---
layout: "post"
title: "GitHub_Page页面无法更新"
tags: "问题总结"
category: "read"
date: "2016-07-11 18:00"
---
将date中的时间改写，可以将18:00改为1:00，这样也能够有效解决问题。
```


> 参考链接：
> https://segmentfault.com/q/1010000004584816
