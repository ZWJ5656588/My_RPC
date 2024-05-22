#pragma once

#include <sys/epoll.h>

#include <atomic>
import <functional>
#include <memory>

namespace network {

class EventLoop;

///
/// 一个可选择的 I/O 通道。
///
/// 这个类不拥有文件描述符。
/// 文件描述符可以是套接字、eventfd、timerfd 或 signalfd
class Channel {
 public:
  // 定义事件类型
  enum EventType {
    NoneEvent = 0,
    ReadEvent = EPOLLIN,
    WriteEvent = EPOLLOUT,
  };

  // 定义回调函数类型
  typedef std::function<void()> EventCallback;

  // 构造函数，初始化 Channel 对象
  Channel(EventLoop *loop, int fd);
  // 析构函数，销毁 Channel 对象
  ~Channel();

  // 处理事件
  void handleEvent();
  // 设置读事件回调函数
  void setReadCallback(EventCallback cb) { readCallback_ = std::move(cb); }
  // 设置写事件回调函数
  void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
  // 设置关闭事件回调函数
  void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
  // 设置错误事件回调函数
  void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

  // 获取文件描述符
  int fd() const { return fd_; }
  // 获取当前事件类型
  int events() const { return events_; }
  // 设置收到的事件类型，由 pollers 使用
  void set_revents(int revt) { revents_ = revt; }
  // 检查是否没有事件
  bool isNoneEvent() const { return events_ == EventType::NoneEvent; }

  // 启用读事件
  void enableReading() {
    events_ |= EventType::ReadEvent;
    update();
  }
  // 禁用读事件
  void disableReading() {
    events_ &= ~EventType::ReadEvent;
    update();
  }
  // 启用写事件
  void enableWriting() {
    events_ |= EventType::WriteEvent;
    update();
  }
  // 禁用写事件
  void disableWriting() {
    events_ &= ~EventType::WriteEvent;
    update();
  }
  // 禁用所有事件
  void disableAll() {
    events_ = EventType::NoneEvent;
    update();
  }
  // 检查是否正在写入
  bool isWriting() const { return events_ & EventType::WriteEvent; }
  // 检查是否正在读取
  bool isReading() const { return events_ & EventType::ReadEvent; }

  // 提供给 Poller 使用
  int index() { return index_; }
  void set_index(int idx) { index_ = idx; }

  // 获取拥有该通道的事件循环
  EventLoop *ownerLoop() { return loop_; }
  // 移除通道
  void remove();

 private:
  // 更新通道状态
  void update();

  // 事件循环对象指针
  EventLoop *loop_;
  // 文件描述符
  const int fd_;
  // 当前事件类型
  int events_;
  // 收到的事件类型，由 epoll 或 poll 设置
  int revents_;
  // 由 Poller 使用的索引
  int index_;

  // 弱指针，用于防止事件处理过程中对象被销毁
  std::weak_ptr<void> tie_;
  // 原子布尔值，指示是否正在处理事件
  std::atomic<bool> event_handling_;
  // 原子布尔值，指示是否已添加到事件循环
  std::atomic<bool> addedToLoop_;
  // 读事件回调函数
  EventCallback readCallback_;
  // 写事件回调函数
  EventCallback writeCallback_;
  // 关闭事件回调函数
  EventCallback closeCallback_;
  // 错误事件回调函数
  EventCallback errorCallback_;
};

}  // namespace network
