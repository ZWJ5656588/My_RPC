#pragma once

#include <cassert>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace network {

class EventLoop;

///
/// EventLoopThread 类用于在单独的线程中运行 EventLoop。
///
class EventLoopThread {
 public:
  // 定义线程初始化回调函数类型
  typedef std::function<void(EventLoop *)> ThreadInitCallback;

  // 构造函数，初始化 EventLoopThread 对象
  EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(),
                  const std::string &name = std::string());
  
  // 析构函数，销毁 EventLoopThread 对象
  ~EventLoopThread();

  // 启动事件循环线程并返回 EventLoop 指针
  EventLoop *startLoop();

 private:
  // 线程函数，在新线程中运行事件循环
  void threadFunc();

  EventLoop *loop_; // 指向事件循环对象的指针
  bool exiting_; // 标识是否正在退出
  std::unique_ptr<std::thread> thread_; // 线程对象
  std::mutex mutex_; // 互斥锁
  std::condition_variable cv_; // 条件变量
  ThreadInitCallback callback_; // 线程初始化回调函数
};

}  // namespace network