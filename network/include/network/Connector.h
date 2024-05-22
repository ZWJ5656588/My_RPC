#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include "network/InetAddress.h"

namespace network {

class Channel;
class EventLoop;

///
/// Connector 类负责管理客户端与服务器之间的连接。
///
class Connector {
 public:
  // 定义新的连接回调函数类型
  typedef std::function<void(int sockfd)> NewConnectionCallback;

  // 构造函数，初始化 Connector 对象
  Connector(EventLoop *loop, const InetAddress &serverAddr);
  // 析构函数，销毁 Connector 对象
  ~Connector();

  // 设置新的连接回调函数
  void setNewConnectionCallback(const NewConnectionCallback &cb) {
    newConnectionCallback_ = cb;
  }

  // 启动连接，可以在任何线程中调用
  void start();
  // 重新启动连接，必须在事件循环线程中调用
  void restart();
  // 停止连接，可以在任何线程中调用
  void stop();

  // 获取服务器地址
  const InetAddress &serverAddress() const { return serverAddr_; }

 private:
  // 定义连接状态枚举
  enum States { kDisconnected, kConnecting, kConnected };
  // 最大重试延迟时间，单位为毫秒
  static const int kMaxRetryDelayMs = 30 * 1000;
  // 初始重试延迟时间，单位为毫秒
  static const int kInitRetryDelayMs = 500;

  // 设置连接状态
  void setState(States s) { state_ = s; }
  // 在事件循环中启动连接
  void startInLoop();
  // 在事件循环中停止连接
  void stopInLoop();
  // 发起连接
  void connect();
  // 设置状态为连接中并创建通道
  void connecting(int sockfd);
  // 处理写事件
  void handleWrite();
  // 处理错误事件
  void handleError();
  // 重试连接
  void retry(int sockfd);
  // 移除并重置通道
  int removeAndResetChannel();
  // 重置通道
  void resetChannel();

  // 事件循环对象指针
  EventLoop *loop_;
  // 服务器地址
  InetAddress serverAddr_;
  // 连接标志
  bool connect_;  // atomic
  // 连接状态
  States state_;  // FIXME: use atomic variable
  // 通道对象
  std::unique_ptr<Channel> channel_;
  // 新的连接回调函数
  NewConnectionCallback newConnectionCallback_;
  // 重试延迟时间，单位为毫秒
  int retryDelayMs_;
};

}  // namespace network
