#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

Chatserver::Chatserver(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback(bind(&Chatserver::onConnection, this, _1));

    // 注册消息读写回调
    _server.setMessageCallback(bind(&Chatserver::onMessage, this, _1, _2, _3));

    // 设置线程数量
    _server.setThreadNum(4);
}

//启动服务
void Chatserver::start()
{
    _server.start();
}
// 上报连接相关信息的回调函数
void Chatserver::onConnection(const TcpConnectionPtr &conn)
{
    //用户断开连接  客户端
    if (!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
        // 用户下线
    }
    else
    {
        // 用户上线
    }
}

// 上报读写事件相关信息的回调函数
void Chatserver::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    string buf=buffer->retrieveAllAsString();
    //数据的反序列化
    json js= json::parse(buf);
    //达到的目的：完全解耦网络模块的代码和业务模块的代码
    //通过js["msgid"]获取-》业务处理器
    auto msgHandler=ChatService::instance()->getHandler(js["msgid"].get<int>());
    
    //回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn,js,time);
    
}
