# 聊天服务器

## 1. 简介

    是基于moduo网络库开发，使用json数据格式传输数据，存储数据使用mysql数据库

## 2. 搭建开发环境

### 2.1 jsoncpp 开发环境搭建
```   
sudo apt-get install libjsoncpp-dev
```

### 2.2 moduo 开发环境搭建
```
前提说明：sudo apt install g++ cmake make libboost-dev
下载 https://github.com/chenshuo/muduo.git 的源码
执行里面build.sh 脚本
```
### 2.3 mysql 开发环境搭建

```
sudo apt update
sudo apt install mysql-server
# 启动mysql
sudo systemctl status mysql
# 设置开机自启动
sudo systemctl enable mysql
# 安装mysql开发环境
sudo apt install libmysqlclient-dev


# 登录mysql，在默认安装时如果没有让我们设置密码，则直接回车就能登录成功。
sudo mysql -uroot -p
#配置mysql 登录密码
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '123456';

# 刷新缓存
flush privileges;
```

注意：配置8.0版本参考：我这里通过这种方式没有实现所有IP都能访问；我是通过直接修改配置文件才实现的，MySQL8.0版本把配置文件 my.cnf 拆分成mysql.cnf 和mysqld.cnf，我们需要修改的是mysqld.cnf文件，这里配置需要修改，bind-address，跟mysqlx-bind-address；
```
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf


#修改 bind-address，保存后重启MySQL即可。
bind-address = 0.0.0.0

# 重启mysql
sudo systemctl restart mysql
```

解决wsl连接不上ubuntu 中mysql的问题：

```
sudo mysql -u root -p
 
CREATE USER '新用户名'@'%' IDENTIFIED BY '对应密码';
 
GRANT ALL PRIVILEGES ON *.* TO '新用户名'@'%' WITH GRANT OPTION;
 
FLUSH PRIVILEGES;
```


### 2.4 redis 开发环境搭建

## 3. q111111111

