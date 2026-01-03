/**
* @author: luochenhao
* @email: lch2022fox@163.com
* @time: Sun 28 Dec 2025 17:05:17 CST
* @brief: 
**/

#include <iostream>
#include <unistd.h>
#include "mdrpc_application.h"

// 静态成员变量类外初始化
MdrpcConfig MdrpcApplication::_config;

static void PrintHelp() {
    std::cout << "Usage: ./rpc_callee -i <config_file>" << std::endl;
}

MdrpcApplication& MdrpcApplication::GetInstance() {
    static MdrpcApplication app;
    return app;
}

void MdrpcApplication::Init(int argc, char** argv) {
    // 参数校验
    if (argc <= 0 || argv == nullptr) {
        PrintHelp();
        exit(EXIT_FAILURE); 
    }

    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
            case 'i':
                config_file = std::string(optarg);
                break;
            case '?':
                std::cout << "Unknown option: " << char(optopt) << std::endl;
                PrintHelp();
                exit(EXIT_FAILURE);
            case ':':
                std::cout << "Missing arg for option: " << char(optopt) << std::endl;
                PrintHelp();
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }

    /*
        配置文件加载
        rpcserver_ip=
        rpcserver_port=
        zookeeper_ip=
        zookeeper_port=
    */
    if (!_config.LoadConfigFile(config_file.c_str())) {
        std::cout << "Load config file: " << config_file << " failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    auto ip_opt = _config.Load("rpcserver_ip");
    auto port_opt = _config.Load("rpcserver_port");
    auto zk_ip_opt = _config.Load("zookeeper_ip");
    auto zk_port_opt = _config.Load("zookeeper_port");

    if (ip_opt == std::nullopt ||
        port_opt == std::nullopt ||
        zk_ip_opt == std::nullopt ||
        zk_port_opt == std::nullopt) {
        std::cout << "Config file format error, missing required keys." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "------------------ Config Info ------------------" << std::endl;
    std::cout << "Load config file: " << config_file << " succeed." << std::endl;
    std::cout << "rpcserver_ip: " << ip_opt.value() << std::endl;
    std::cout << "rpcserver_port: " << port_opt.value() << std::endl;
    std::cout << "zookeeper_ip: " << zk_ip_opt.value() << std::endl;
    std::cout << "zookeeper_port: " << zk_port_opt.value() << std::endl;
}
