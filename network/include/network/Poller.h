#pragma once

#include <map>
#include <vector>

#include "network/EventLoop.h"
struct epoll_event;

namespace network {

class Channel;

///
/// 使用 epoll(4) 进行 I/O 多路复用。
///
class Poller {
 public:
  // 定义 ChannelList 类型，为 Channel 指针的向量
  typedef std::vector<Channel *> ChannelList;

  // 构造函数，初始化 Poller 对象
  Poller(EventLoop *loop);

  // 析构函数，销毁 Poller 对象
  ~Poller();

  // 等待事件，并将活跃的通道填充到 activeChannels 中
  void poll(int timeoutMs, ChannelList *activeChannels);

  // 更新通道
  void updateChannel(Channel *channel);

  // 移除通道
  void removeChannel(Channel *channel);

  // 断言在事件循环线程中执行
  void assertInLoopThread() const { ownerLoop_->assertInLoopThread(); }

  // 检查通道是否存在
  bool hasChannel(Channel *channel) const;

 private:
  // 填充活跃的通道
  void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;

  // 更新通道状态
  void update(int operation, Channel *channel);

  // 将操作类型转换为字符串
  static const char *operationToString(int op);

  EventLoop *ownerLoop_; // 拥有该 Poller 的事件循环
  static const int kInitEventListSize = 16; // 初始事件列表大小

  typedef std::vector<struct epoll_event> EventList; // 定义 EventList 类型

  int epollfd_; // epoll 文件描述符
  EventList events_; // 事件列表

  typedef std::map<int, Channel *> ChannelMap; // 定义 ChannelMap 类型
  ChannelMap channels_; // 通道映射表
};

}  // namespace network
