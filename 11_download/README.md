# wfrest快速搭建http服务器
* wfrest是 c++异步web框架
* wfrest是 基于C++ Workflow 开发的
* C++ Workflow是 基于Proactor的
* C++ Workflow是 异步+回调的
* C++ Workfow是 基于任务流的

## 进度
0. 测试官方示例
1. 服务器的command line输出响应
2. 面向对象编程
3. 替换等待请求的响应
4. 等待线程终止
5. 实现注册功能, 并将用户信息写入数据库
6. 实现登录功能 
7. 实现LocalStorage功能
8. 加载用户信息
9. 实现上传功能
10. 实现查询功能
11. 实现下载功能

## 环境
* 已安装 workflow
* 已安装 wfrest

## 编译
```
$ g++ server.cc -o server -lworkflow -lwfrest
```

## 测试
* 请使用浏览器访问 http://192.168.253.131:8888/user/signup
* 温馨提醒: 记得更换成自己的 ip !!!

## 参考
https://github.com/wfrest/wfrest/blob/main/README_cn.md

## track() 
* 当前请求的响应

## list_routes()
* 等待请求的响应

## Nginx
配置文件
```
cd /usr/local/nginx/conf
sudo cp nginx.conf 11_download.conf
sudo vi 11_download.conf
```
修改配置文件
```
user root;
worker_processes  1;
error_log  logs/error11.log;
pid        logs/nginx11.pid;
events {
    worker_connections  1024;
}

http {
    #include       mime.types;
    default_type  application/octet-stream;

    log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';

    access_log  logs/access.log  main;

    sendfile        on;
    keepalive_timeout  65;
    server {
        listen       8868;
        server_name  localhost;

        location / {
        root /home/lam/myproject/11_download/tmp;
        }
    }
}

```

启动服务器
```
cd /usr/local/nginx
sudo sbin/nginx -c conf/11_download.conf
```

查看端口
```
sudo netstat -ntlp | grep 8868
```