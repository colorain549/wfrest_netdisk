# wfrest快速搭建http服务器
* wfrest是 c++异步web框架
* wfrest是 基于C++ Workflow 开发的
* C++ Workflow是 基于Proactor的
* C++ Workflow是 异步+回调的
* C++ Workfow是 基于任务流的

## 进度
0. 测试官方示例(wfrest)
1. 服务器的command line输出响应(track()和list_routes())
2. 面向对象编程
3. 替换等待请求的响应
4. 等待线程终止
5. 实现注册功能, 并将用户信息写入数据库(MySQL)
6. 实现登录功能 
7. 实现LocalStorage功能
8. 加载用户信息
9. 实现上传功能
10. 实现查询功能
11. 实现下载功能
12. 使用阿里云对象存储OSS进行备份(阿里云对象存储OSS)
13. 使用消息队列, 以减少上传大文件时的等待时间, 提高的交互体验(RabbitMQ)
14. 测试proto
15. 测试srpc
16. 使用srpc改造注册功能
17. 实现API网关, 以查询注册中心, 获得服务的IP和端口(consul)

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

## proto
生成.h和.cc文件
```
protoc --cpp_out=./ user.proto
```
编译
```
g++ testUser.cc -lprotobuf
```

## srpc
生成.h和.cc文件
```
protoc --cpp_out=./ user.proto
```
生成client, service 和user.srpc.h
```
srpc_generator protobuf user.proto ./
```

## 注册中心consul

consul的部署

1. 启动consul服务器
```
// HTTP:8500 LAN:8301 WAN:8302 DNS:8600
sudo docker run --hostname consulsvr1 --name consul_node_1 -d -p 8500:8500 -p 8301:8301 -p  8302:8302 -p 8600:8600 consul agent -server -bootstrap-expect 2 -ui -bind=0.0.0.0 -client=0.0.0.0
```

2. 查看分配的IP地址  
```
sudo docker inspect --format '{{.NetworkSettings.IPAddress}}' consul_node_1
```

3. 启动另外两个节点, 加入集群(注意与2的IP地址保持一致)
```
sudo docker run --hostname consulsvr2 --name consul_node_2 -d -p 8501:8500 consul agent -server -ui -bind=0.0.0.0 -client=0.0.0.0 -join 172.17.0.3

sudo docker run --hostname consulsvr3 --name consul_node_3 -d -p 8502:8500 consul agent -server -ui -bind=0.0.0.0 -client=0.0.0.0 -join 172.17.0.3
```

4. 查看集群状态
```
sudo docker exec -t consul_node_1 consul members
```

5. 测试  
开启16_srpc中的服务器后  
ui http://192.168.253.131:8500/ui/dc1/services  
ip和port http://192.168.253.131:8500/v1/agent/services  

## 补充
1. 智能指针
2. 右值绑定
3. *boost库
4. *模板