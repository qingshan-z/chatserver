#ifndef CHATSERVER_H
#define CHATSERVER_H
#include "chatservice.hpp"
#include "chatserver.hpp"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

//聊天服务器的主类
class Chatserver
{
private:
    TcpServer _server;//组合muduo库，实现服务器功能的类对象
    EventLoop *_loop;//指向事件循环对象的指针

    //上报连接相关信息的回调函数
    void onConnection(const TcpConnectionPtr& conn);

    //上报读写事件相关信息的回调函数
    void onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time);
public:
    //初始化聊天服务器对象
    Chatserver(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg);
    //启动服务器
    void start();

};




#endif