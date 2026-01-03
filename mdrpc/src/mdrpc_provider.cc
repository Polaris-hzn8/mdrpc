/**
* @author: luochenhao
* @email: lch2022fox@163.com
* @time: Sun 28 Dec 2025 17:05:31 CST
* @brief: 
**/

#include <functional>
#include "mdrpc_provider.h"
#include "mdrpc_application.h"

void MdrpcProvider::RegisterService(google::protobuf::Service* service) {
    
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