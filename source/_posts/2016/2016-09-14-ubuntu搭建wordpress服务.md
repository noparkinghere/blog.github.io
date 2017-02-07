---
layout: "post"
title: "ubuntu搭建wordpress服务"
date: "2016-09-14 09:02"
---


*[wordpress](https://cn.wordpress.org/) 是目前比较流行的博客模板，精美的外观强可定制性收到了国内外很多bloger的亲睐，之前在虚拟机的ubuntu_server上面搭建过这个环境，个人所使用的blog是基于jekyll的静态页面，所以对wordpress不是特别了解，这边以腾讯云的ubuntu服务器为基础搭建自己的wordpress服务，当然现在很多云服务已经支持一键搭建wordpress的功能，但据说“访问速度和灵活性会受到很大影响”，这边有兴趣的朋友可以自己去尝试一下。*

### 简述

- 需要搭建一个服务器，首先需要选定自己使用哪些服务套件，这边我选用LAMP套装，即linux(ubuntu), apache2.0, mysql, php(wordpress)。

<!-- more -->


### 详细安装步骤

#### 1.检查电脑是否安装了这些服务。

```sh
dpkg -l | grep apache
dpkg -l | grep php
dpkg -l | grep mysql
```

#### 2.根据提示信息，如果没有安装则补安装。

```sh
sudo apt-get install apache2 mysql-server php5 libapache2-mod-php5
重启apache服务 `sudo /etc/init.d/apache2 restart`
```

#### 3.让apache、php支持mysql

```sh
sudo apt-get install libapache2-mod-auth-mysql php5-mysql
重启apache服务 `sudo /etc/init.d/apache2 restart`
```

#### 4.安装phpMyAdmin 

```sh
sudo apt-get install phpmyadmin
此时的phpmyadmin文件夹被安装在/usr/share/phpmyadmin下，为了能在浏览器中访问到phpmyadmin，需要在/var/www下做一个软连接到该文件夹。
进入/var/www文件夹，在该目录下执行如下操作:
sudo ln -s /usr/share/phpmyadmin
```

#### 5.[为Wordpress新建mysql数据库](https://codex.wordpress.org/zh-cn:%E5%AE%89%E8%A3%85WordPress#.E7.AC.AC.E4.BA.8C.E6.AD.A5.EF.BC.9A.E5.88.9B.E5.BB.BAWordPress.E6.95.B0.E6.8D.AE.E5.BA.93.E5.92.8C.E4.B8.80.E4.B8.AA.E7.94.A8.E6.88.B7)

```sh
$ mysql -u root -p	// 登陆管理数据库
Enter password:
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 5340 to server version: 3.23.54
 
Type 'help;' or '\h' for help. Type '\c' to clear the buffer.
 
mysql> CREATE DATABASE blog;	// 创建数据库名称
Query OK, 1 row affected (0.00 sec)
 
mysql> GRANT ALL PRIVILEGES ON blog.* TO "demon"@"hostname" // 受理权限
    -> IDENTIFIED BY "password";
Query OK, 0 rows affected (0.00 sec)
  
mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0.01 sec)

mysql> EXIT
Bye
$ 
```

***

to be continued...


> 参考链接：
> https://codex.wordpress.org/zh-cn:%E5%AE%89%E8%A3%85WordPress#.E6.AD.A5.E9.AA.A43:.E8.AE.BE.E7.BD.AEwp-config.php
> http://www.jianshu.com/p/7e6566b613a7
> http://www.jianshu.com/p/26d9e752994e
