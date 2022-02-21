#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置线程数量
    _server.setThreadNum(2);
}

void ChatServer::start() { _server.start(); }

// 上报连接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    // 客户端断开连接
    if (!conn->connected())
    {
        // 断开连接的话 clientCloseException做的事情是 删除内存中的连接 _userConnMap上的连接 修改数据库中状态为offline
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

// 上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 数据的反序列化
    json js = json::parse(buf);
    // 达到的目的：完全解耦网络模块的代码和业务模块的代码
    // 通过js["msgid"]获取->业务处理器handler->conn js time
    // function<void(const TcpConnectionPtr &, json &, Timestamp)> msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());    // json的get方法将msgid转为int
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>()); // json的get方法将msgid转为int
    // 回调消息绑定好的事件处理器 来执行相应的业务处理
    msgHandler(conn, js, time);
}