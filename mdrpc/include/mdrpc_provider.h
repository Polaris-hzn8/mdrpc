/**
* @author: luochenhao
* @email: lch2022fox@163.com
* @time: Sun 28 Dec 2025 16:57:46 CST
* @brief: 框架提供的负责发布rpc服务的网络对象类
**/

#pragma once

#include <memory>
#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <google/protobuf/service.h>

class MdrpcProvider {
public:
    // 发布rpc服务方法
    void RegisterService(google::protobuf::Service* service);
    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();
private:
    // 新连接回调
    void OnConnection(const muduo::net::TcpConnectionPtr& conn);
    // 消息读写回调
    void OnMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buffer,
                   muduo::Timestamp receive_time);
private:
    // eventLoop对象(muduo库提供)
    muduo::net::EventLoop _event_loop;
};

