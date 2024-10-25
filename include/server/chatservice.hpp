#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>

#include "friendmodel.hpp"
#include "UserModel.hpp"
#include "groupmodel.hpp"
#include "json.hpp"
#include "offlinemessagemodel.hpp"
#include "redis.hpp"



using namespace std;
using namespace muduo;
using namespace muduo::net;

using json = nlohmann::json;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;
//聊天服务器业务类
class ChatService
{
private:
    ChatService();
    
    // 存储消息id和对应的处理函数
    unordered_map<int, MsgHandler> _msgHandlerMap; 

    //定义互斥锁，保证_userConnMap线程安全
    mutex _connMutex;

    //存储用户的通信连接,保存登录用户信息
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //数据操作类对象
    UserModel _userModel;
    //离线消息表操作对象
    Offlinemessagemodel _offlineMsgModel;
    //好友表操作对象
    Friendmodel _friendmodel;
    //群组操作对象
    GroupModel _groupmodel;

    //定义redis操作对象，实现用户在线状态、好友变化消息的服务器推送
    Redis _redis;
public:
    //获取单例对象的接口函数
    static ChatService *instance(); // 单例模式
    //处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注册任务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, string message);

    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    //处理客户端异常关闭
    void clientCloseException(const TcpConnectionPtr &conn);

    //服务器异常，业务重置方法
    void reset();
    
    
};
 

#endif