/**
* @author: luochenhao
* @email: lch2022fox@163.com
* @time: Sun 28 Dec 2025 16:57:24 CST
* @brief: 主应用程序类
**/

#pragma once

class MdrpcApplication {
public:
    virtual ~MdrpcApplication();
    static MdrpcApplication& GetInstance();
    static void Init(int argc, char** argv);

private:
    MdrpcApplication();
    MdrpcApplication(const MdrpcApplication&) = delete;
    MdrpcApplication(MdrpcApplication&&) = delete;
    MdrpcApplication& operator=(const MdrpcApplication&) = delete;
};
