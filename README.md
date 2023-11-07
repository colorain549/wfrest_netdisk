# wfrest_netdisk

## 亮点
1. 采用了阿里云对象存储OSS
2. 采用了RabbitMQ
3. 采用了基于srpc框架的微服务, 以及注册中心consul

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
* 请查看18_final_version中的README.md

## 补充
* 部分README.md可能含有错误信息, 持续更新中...