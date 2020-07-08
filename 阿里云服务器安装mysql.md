安装新版mysql前，先将系统自带的mariadb-lib卸载，先查找mariadb的版本：

```bash
rpm -qa|grep mariadb
```

结果为：

```bash
mariadb-libs-5.5.65-1.el7.x86_64
```

下载并安装MySQL官方的 Yum Repository：

```bash
wget -i -c http://dev.mysql.com/get/mysql57-community-release-el7-10.noarch.rpm
yum -y install mysql57-community-release-el7-10.noarch.rpm
```

安装MySQL服务器：

```bash
yum -y install mysql-community-server
```

同时会安装依赖：

```bash
libaio
mysql-community-client
mysql-community-common
mysql-community-libs
```

启动MySQL：

```bash
systemctl start mysqld.service
```

查看MySQL运行状态：

```bash
systemctl status mysqld.service
```

 此时MySQL已经开始正常运行，不过要想进入MySQL还得先找出此时root用户的密码，通过如下命令可以在日志文件中找出密码：

```bash
grep "password" /var/log/mysqld.log
```

记住初始密码，登录数据库：

```bash
mysql -uroot -p
```

输入刚才的初始密码即可进入，但此时不能做任何事情，因为MySQL默认必须修改密码之后才能操作数据库：

```mysql
ALTER USER 'root'@'localhost' IDENTIFIED BY 'MySQLPassword_2020';
```

记得密码要足够复杂，大小写、标点符号、数字等。



应该会提示：

```
/usr/bin/ld: cannot find -lmysqlclient
```

接下来应该建立软连接。



此时还有一个问题，就是因为安装了Yum Repository，以后每次yum操作都会自动更新，需要把这个卸载掉：

```bash
yum -y remove mysql57-community-release-el7-10.noarch
```





















