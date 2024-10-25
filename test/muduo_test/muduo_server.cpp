#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <iostream>
#include <functional>
#include <string>
using namespace muduo;
using namespace muduo::net;
using namespace std;
using namespace placeholders;
class ChatServer
{
public:
    // 初始化TcpServer
    ChatServer(muduo::net::EventLoop *loop,
               const muduo::net::InetAddress &listenAddr,
               const string &name)
        : _server(loop, listenAddr, name),_loop(loop)
    {
        // 通过绑定器设置回调函数
        _server.setConnectionCallback(bind(&ChatServer::onConnection,
                                           this, _1));
        _server.setMessageCallback(bind(&ChatServer::onMessage,
                                        this, _1, _2, _3));
        // 设置EventLoop的线程个数
        _server.setThreadNum(10);
    }
    // 启动ChatServer服务
    void start()
    {
        _server.start();
    }

private:
    // TcpServer绑定的回调函数，当有新连接或连接中断时调用
    void onConnection(const muduo::net::TcpConnectionPtr &con)
    {
        if (con->connected())
        {
            cout << "new connection" << endl;
        }else{
            cout << "connection lost" << endl;
        }
    }
    // TcpServer绑定的回调函数，当有新数据时调用
    void onMessage(const muduo::net::TcpConnectionPtr &con,
                   muduo::net::Buffer *buf,
                   muduo::Timestamp time)
    {
        string msg(buf->retrieveAllAsString());
        cout << "message:" << msg << endl;
    }

private:
    TcpServer _server;
    EventLoop *_loop;
};

int main(){
    EventLoop loop;
    InetAddress addr("127.0.0.1",8888);
    ChatServer server(&loop,addr, "chat_server");

    server.start();
    loop.loop();

    return 0;
}