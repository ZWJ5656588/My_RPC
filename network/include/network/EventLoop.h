#pragma once
/*这个 EventLoop 类实现了一个单线程的 Reactor 模型，
负责管理和分发 I/O 事件。通过回调函数机制，可以灵活地处理不同类型的事件，如读、写、错误等*/
#include <sys/syscall.h>

#include <atomic>
#include <functional>
#include <mutex>
#include <vector>

#include <boost/any.hpp>

#include "network/Callbacks.h"
#include "network/util.h"

namespace network {

class Channel;
class Poller;

///
/// Reactor, at most one per thread.
///
/// This is an interface class, so don't expose too much details.
///
class EventLoop {
 public:
  typedef std::function<void()> Functor;

  // 构造函数，初始化 EventLoop 对象
  EventLoop();
  
  // 析构函数，销毁 EventLoop 对象
  ~EventLoop();  // 强制使用 out-line 析构函数，因为 std::unique_ptr 成员需要

  ///
  /// 无限循环
  ///
  /// 必须在创建对象的同一线程中调用
  ///
  void loop();

  /// 退出循环
  ///
  /// 这不是 100% 线程安全的，如果通过原始指针调用，
  /// 最好通过 shared_ptr<EventLoop> 调用以确保 100% 安全
  void quit();

  // 获取循环的迭代次数
  int64_t iteration() const { return iteration_; }

  /// 在循环线程中立即运行回调
  /// 它会唤醒循环，并运行 cb
  /// 如果在同一循环线程中，cb 在函数内运行
  /// 可以安全地从其他线程调用
  void runInLoop(Functor cb);
  
  /// 在循环线程中排队回调
  /// 在完成轮询后运行
  /// 可以安全地从其他线程调用
  void queueInLoop(Functor cb);

  // 获取队列大小
  size_t queueSize() const;

  // 内部使用
  void wakeup();
  void updateChannel(Channel *channel);
  void removeChannel(Channel *channel);
  bool hasChannel(Channel *channel);

  // 检查是否在循环线程中
  void assertInLoopThread() {
    if (!isInLoopThread()) {
      abortNotInLoopThread();
    }
  }

  // 判断是否在循环线程中
  bool isInLoopThread() { return threadId_ == getThreadId(); }
  
  // 检查是否正在处理事件
  bool eventHandling() const { return eventHandling_; }

  // 设置上下文
  void setContext(const boost::any &context) { context_ = context; }

  // 获取上下文
  const boost::any &getContext() const { return context_; }

  // 获取可变的上下文
  boost::any *getMutableContext() { return &context_; }

  // 获取当前线程的 EventLoop 对象
  static EventLoop *getEventLoopOfCurrentThread();

 private:
  // 如果不在循环线程中，则中止
  void abortNotInLoopThread();
  
  // 处理读事件（唤醒）
  void handleRead();
  
  // 执行待处理的回调函数
  void doPendingFunctors();

  // 打印活跃的通道（用于调试）
  void printActiveChannels() const;  // DEBUG

  typedef std::vector<Channel *> ChannelList;

  // 变量声明
  bool looping_; /* atomic */
  std::atomic<bool> quit_;
  bool eventHandling_;          /* atomic */
  bool callingPendingFunctors_; /* atomic */
  int64_t iteration_;
  pid_t threadId_;
  std::unique_ptr<Poller> poller_;
  int wakeupFd_;
  // 不像在 TimerQueue 中，这是一个内部类，
  // 我们不向客户端公开 Channel
  std::unique_ptr<Channel> wakeupChannel_;
  boost::any context_;

  // 临时变量
  ChannelList activeChannels_;
  Channel *currentActiveChannel_;

  mutable std::mutex mutex_;
  std::vector<Functor> pendingFunctors_;
};

}  // namespace network
