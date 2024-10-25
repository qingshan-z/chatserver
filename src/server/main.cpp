#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace std;

//处理服务器ctrl+c结束后，重置user的状态信息
void resethandler(int sig){
    ChatService::instance()->reset();
    exit(0);
}
int main(int argc, char** argv){

    if(argc < 3){
        cerr<<"command invalid! ./ChatServer ip port"<<endl;
        exit(-1);
    }
    char *ip = argv[1];
    uint16_t port=atoi(argv[2]);
    //定义一个信号处理函数
    signal(SIGINT, resethandler);
    EventLoop loop;
    InetAddress addr(ip, port);
    Chatserver server(&loop, addr,"chatserver");

    server.start();
    loop.loop();

    return 0;
}