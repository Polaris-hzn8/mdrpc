/**
* @author: luochenhao
* @email: lch2022fox@163.com
* @time: Sun 28 Dec 2025 17:05:31 CST
* @brief: 
**/

#include <iostream>
#include <functional>
#include "mdrpc_provider.h"
#include "mdrpc_application.h"

// 注册发布rpc服务方法
void MdrpcProvider::RegisterService(google::protobuf::Service* service) {
    ServiceInfo service_info;
    service_info._service = service;
    service_info._method_map.clear();

    // 服务描述符
    const google::protobuf::ServiceDescriptor* sd = service->GetDescriptor();
    // 服务名称
    std::string service_name = sd->name();
    // 服务方法数量
    int method_count = sd->method_count();
    for (int i = 0; i < method_count; ++i) {
        // 服务方法描述符
        const google::protobuf::MethodDescriptor* md = sd->method(i);
        // 方法名称
        std::string method_name = md->name();
        // 存储服务方法名称和方法描述符的映射
        service_info._method_map.insert({method_name, md});
        std::cout << "Register method: " << method_name << " for service: " << service_name << std::endl;
    }
    _service_map.insert({service_name, service_info});
    std::cout << "Register service: " << service_name << " with " << method_count << " methods." << std::endl;
}

void MdrpcProvider::Run() {
    // RPC服务节点ip和port端口数据获取
    MdrpcConfig& config = MdrpcApplication::GetConfig();
    auto ip_opt = config.Load("rpcserver_ip");
    auto port_opt = config.Load("rpcserver_port");
    if (ip_opt == std::nullopt || port_opt == std::nullopt) {
        std::cerr << "rpcserver_ip or rpcserver_port is not configured!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string ip = ip_opt.value();
    uint16_t port = static_cast<uint16_t>(std::stoi(port_opt.value()));
    
    muduo::net::InetAddress address(ip, port);

    // 创建tcpServer
    muduo::net::TcpServer tcp_server(&_event_loop, address, "MdrpcProvider");
    tcp_server.start();
    // 绑定连接回调和消息读写回调方法
    // 分离网络代码与业务代码
    tcp_server.setConnectionCallback(std::bind(&MdrpcProvider::OnConnection, this, std::placeholders::_1));
    tcp_server.setMessageCallback(std::bind(&MdrpcProvider::OnMessage, this,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3));
    // 设置muduo库的线程数量(基于Reactor模型的服务器：EPOLL + 线程池)
    tcp_server.setThreadNum(4);
    // 启动网络服务
    tcp_server.start();
    std::cout << "MdrpcProvider start service at " << ip << ":" << port << std::endl;
    // 事件循环epoll_wait
    _event_loop.loop();
}

void MdrpcProvider::OnConnection(const muduo::net::TcpConnectionPtr& conn) {

}

void MdrpcProvider::OnMessage(
    const muduo::net::TcpConnectionPtr& conn,
    muduo::net::Buffer* buffer,
    muduo::Timestamp receive_time) {
    
    
    
}