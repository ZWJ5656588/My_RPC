#pragma once

#include <functional>
#include "network/Channel.h"
#include "network/Socket.h"

namespace network {

class EventLoop;
class InetAddress;

///
/// Acceptor of incoming TCP connections.
/// 负责接收传入的TCP连接。
///
class Acceptor {
 public:
  // 定义一个函数类型，用于处理新的连接
  typedef std::function<void(int sockfd, const InetAddress &)>
      NewConnectionCallback;

  // 构造函数，初始化 Acceptor 对象
  Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
  
  // 析构函数，销毁 Acceptor 对象
  ~Acceptor();

  // 设置新的连接回调函数
  void setNewConnectionCallback(const NewConnectionCallback &cb) {
    newConnectionCallback_ = cb;
  }

  // 开始监听传入连接
  void listen();

  // 检查是否正在监听
  bool listening() const { return listening_; }

  // 已弃用的方法，使用上面正确拼写的方法
  // 保留这个错误拼写的方法以便于查找错误信息
  // bool listenning() const { return listening(); }

 private:
  // 处理可读事件，接收新的连接
  void handleRead();

  EventLoop *loop_; // 事件循环对象的指针
  Socket acceptSocket_; // 套接字对象，用于接收连接
  Channel acceptChannel_; // 通道对象，绑定到 acceptSocket_ 上
  NewConnectionCallback newConnectionCallback_; // 新连接回调函数
  bool listening_; // 标识是否正在监听
  int idleFd_; // 空闲文件描述符，用于处理文件描述符耗尽的情况
};

}  // namespace network
