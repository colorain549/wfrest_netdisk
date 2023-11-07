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

## 环境
* 已安装 workflow
* 已安装 wfrest

## 编译
```
$ g++ server.cc -o server -lworkflow -lwfrest
```

## 测试
* 请使用浏览器访问 http://192.168.253.131:8888/hello
* 温馨提醒: 记得更换成自己的 ip !!!

## 参考
https://github.com/wfrest/wfrest/blob/main/README_cn.md

## track() 
* 当前请求的响应

## list_routes()
* 等待请求的响应