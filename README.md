# wfrest_netdisk

## 亮点
1. 阿里云对象存储OSS
2. 基于RabbitMQ的消息队列(docker部署)
3. 基于wfrest的API网关
4. 基于srpc框架的微服务(心跳检测)
5. 基于consul的注册中心(docker部署)  
...

## Framework(大致框架,非精确框架)
![Framework](/images/framwork.png)

## 主要功能一览
1. 文件上传至网盘(服务器)
2. 文件上传时备份(阿里云对象存储OSS)
3. 大文件上传的及时响应(消息队列RabbitMQ)
4. 通过"文件列表"页面查询当前用户的文件信息(MySQL)
5. 文件下载(Nginx反向代理)  
...

## 其它功能
1. 用户注册
2. 用户登录
3. 查询用户信息  
...

## Quick start
0. 更改ip, MySQL, OSS账号信息, 配置阿里云AccessKey, 配置Nginx, Consul和RabbitMQ
1. 开启已配置好的Nginx, Consul和RabbitMQ
![Nginx_Consul](/images/ngx_consul_rabbitmq.png)
2. 编译后依次开启3个进程
![run](/images/run.png)
3. 使用浏览器访问注册页面(注意更换为自己的ip)
![signup](/images/signup.png)
4. 登录页面
![signin](/images/signin.png)
5. 用户主页
![home](/images/home.png)
6. 上传页面
![upload](/images/upload.png)
7. 阿里云OSS
![OSS](/images/OSS.png)
8. 下载页面
![download](/images/download.png)

* 其它详情请查看18_final_version中的README.md

## 补充
* 部分README.md可能含有错误信息, 持续更新中...