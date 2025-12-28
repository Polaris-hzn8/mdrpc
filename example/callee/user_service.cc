
#include <string>
#include <iostream>
#include "user.pb.h"

class UserService {
public:
    bool Login(const std::string& uid, const std::string& password) {
        // 远程方法执行的具体逻辑
        // 1. 获取数据库连接
        // 2. 查询用户名和密码
        // 3. 如果用户名和密码正确，返回true
        // 4. 如果用户名和密码不正确，返回false
        std::cout << "callee do service rpc function: login" << std::endl;
        std::cout << "uid: " << uid << std::endl;
        std::cout << "password: " << password << std::endl;
        return true;
    }
};

// int main() {
//     // 调用远程方法
//     UserService user_service;
//     user_service.Login("luochenhao", "123456");
// }

