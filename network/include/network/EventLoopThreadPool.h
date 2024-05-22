#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace network {

class EventLoop;
class EventLoopThread;

///
/// EventLoopThreadPool 类用于管理多个 EventLoopThread 线程池。
///
class EventLoopThreadPool {
 public:
  // 定义线程初始化回调函数类型
  typedef std::function<void(EventLoop *)> ThreadInitCallback;

  // 构造函数，初始化 EventLoopThreadPool 对象
  EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg);
  
  // 析构函数，销毁 EventLoopThreadPool 对象
  ~EventLoopThreadPool();

  // 设置线程数量
  void setThreadNum(int numThreads) { numThreads_ = numThreads; }

  // 启动线程池
  void start(const ThreadInitCallback &cb = ThreadInitCallback());

  // 在调用 start() 之后有效
  /// 轮询选择下一个 EventLoop
  EventLoop *getNextLoop();

  /// 使用相同的哈希码，总是返回相同的 EventLoop
  EventLoop *getLoopForHash(size_t hashCode);

  // 获取所有的 EventLoop
  std::vector<EventLoop *> getAllLoops();

  // 检查线程池是否已启动
  bool started() const { return started_; }

  // 获取线程池名称
  const std::string &name() const { return name_; }

 private:
  EventLoop *baseLoop_; // 基础事件循环
  std::string name_; // 线程池名称
  bool started_ = false; // 标识线程池是否已启动
  int numThreads_; // 线程数量
  int next_; // 用于轮询选择 EventLoop 的索引
  std::vector<std::unique_ptr<EventLoopThread>> threads_; // 事件循环线程列表
  std::vector<EventLoop *> loops_; // 事件循环列表
};

}  // namespace network
