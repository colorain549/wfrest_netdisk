# 使用说明
至此, 需启用3个进程, 以获得完整服务

## 准备

## 16_srpc_signup
* 微服务, 注册功能
```
$ make
$ ./rpc_server
```

## 17_srpc_signup
* 消息队列, 阿里云对象存储OSS
```
$ g++ consumer.cc -o consumer -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl -lcrypto -lpthread -lwfrest -lworkflow -lssl -lcrypto -lcrypt -lSimpleAmqpClient
$ ./consumer
```

## 17_srpc_signup
* 主程序
```
$ make
$ ./wfrest_server.exe
```