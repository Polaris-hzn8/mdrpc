/**
* @author: luochenhao
* @email: lch2022fox@163.com
* @time: Sun 28 Dec 2025 17:05:17 CST
* @brief: 
**/

#include "mdrpc_application.h"

MdrpcApplication::MdrpcApplication() {

}

MdrpcApplication::~MdrpcApplication() {

}

MdrpcApplication& MdrpcApplication::GetInstance() {
    static MdrpcApplication app;
    return app;
}

void MdrpcApplication::Init(int argc, char** argv) {


}