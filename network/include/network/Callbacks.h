#pragma once

#include <functional>
#include <memory>

namespace network {

// 引入标准库命名空间中的占位符
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

// 模板函数，用于获取 shared_ptr 和 unique_ptr 的原始指针
// 这些函数应放在 base/Types.h 中，但 <memory> 头文件未包含在内

// 获取 shared_ptr 的原始指针
template <typename T>
inline T *get_pointer(const std::shared_ptr<T> &ptr) {
  return ptr.get();
}

// 获取 unique_ptr 的原始指针
template <typename T>
inline T *get_pointer(const std::unique_ptr<T> &ptr) {
  return ptr.get();
}

// 所有客户端可见的回调函数类型定义都在这里

class Buffer; // 前向声明 Buffer 类
class TcpConnection; // 前向声明 TcpConnection 类

// 定义 TcpConnectionPtr 类型，为 shared_ptr<TcpConnection>
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

// 定义 TimerCallback 类型，为无参数的函数对象
typedef std::function<void()> TimerCallback;

// 定义 ConnectionCallback 类型，为接受 TcpConnectionPtr 的函数对象
typedef std::function<void(const TcpConnectionPtr &)> ConnectionCallback;

// 定义 CloseCallback 类型，为接受 TcpConnectionPtr 的函数对象
typedef std::function<void(const TcpConnectionPtr &)> CloseCallback;

// 定义 WriteCompleteCallback 类型，为接受 TcpConnectionPtr 的函数对象
typedef std::function<void(const TcpConnectionPtr &)> WriteCompleteCallback;

// 定义 HighWaterMarkCallback 类型，为接受 TcpConnectionPtr 和 size_t 的函数对象
typedef std::function<void(const TcpConnectionPtr &, size_t)> HighWaterMarkCallback;

// 定义 MessageCallback 类型，为接受 TcpConnectionPtr 和 Buffer 指针的函数对象
// 数据已经读到 (buf, len)
typedef std::function<void(const TcpConnectionPtr &, Buffer *)> MessageCallback;

// 定义默认的连接回调函数
void defaultConnectionCallback(const TcpConnectionPtr &conn);

// 定义默认的消息回调函数
void defaultMessageCallback(const TcpConnectionPtr &conn, Buffer *buffer);

}  // namespace network
