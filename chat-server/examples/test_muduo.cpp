/**
 * @file   : test_muduo.cpp
 * @author : wangdong (wangdong1328@163.com)
 * @brief  :
 * @version: 0.1
 * @date   : 2025-04-16
 *
 * @copyright Copyright (c) 2025
 *
 * **********************************************************
 * @Attention   :
 * @修改日志:
 * <table>
 * <tr><th>Date         <th>Version   <th>Author    <th>Description
 * <tr><td>2025-04-16   <td>0.1       <td>wangdong  <td>创建初始版本
 * </table>
 *
 */

#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>

using namespace std;

// 使用muduo开发回显服务器
class EchoServer
{
public:
    EchoServer(muduo::net::EventLoop *loop,
               const muduo::net::InetAddress &listenAddr);

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr &conn);

    void onMessage(const muduo::net::TcpConnectionPtr &conn,
                   muduo::net::Buffer *buf,
                   muduo::Timestamp time);

    muduo::net::TcpServer server_;
};

EchoServer::EchoServer(muduo::net::EventLoop *loop,
                       const muduo::net::InetAddress &listenAddr)
    : server_(loop, listenAddr, "EchoServer")
{
    server_.setConnectionCallback(bind(&EchoServer::onConnection, this, placeholders::_1));
    server_.setMessageCallback(bind(&EchoServer::onMessage, this, placeholders::_1, placeholders::_2, placeholders::_3));
}

void EchoServer::start()
{
    server_.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");
}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr &conn,
                           muduo::net::Buffer *buf,
                           muduo::Timestamp time)
{
    // 接收到所有的消息，然后回显
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
             << "data received at " << time.toString();
    conn->send(msg);
}

int main()
{
    LOG_INFO << "pid = " << getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(8888);
    EchoServer server(&loop, listenAddr);
    server.start();
    loop.loop();
}
