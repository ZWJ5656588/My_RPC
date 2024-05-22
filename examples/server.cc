#include <unistd.h>
#include <cassert>
#include <glog/logging.h>
#include "network/EventLoop.h"
#include "rpc_framework/RpcServer.h"
#include "monitor.pb.h"

using namespace network;

namespace monitor {

// TestServiceImpl 类实现了 TestService 服务，处理 MonitorInfo RPC 请求
class TestServiceImpl : public TestService {
 public:
  // MonitorInfo 方法处理客户端发送的监控信息请求并返回响应
  virtual void MonitorInfo(::google::protobuf::RpcController *controller,
                           const ::monitor::TestRequest *request,
                           ::monitor::TestResponse *response,
                           ::google::protobuf::Closure *done) override {
    // 打印请求消息
    LOG(INFO) << " req:\n" << request->DebugString();
    // 设置响应消息的状态
    response->set_status(true);
    // 设置响应消息的 CPU 信息
    std::string c = "hight_" + std::to_string(request->count());
    response->set_cpu_info(c);
    // 运行回调函数，表示响应已准备好
    done->Run();
  }
};

}  // namespace monitor

int main(int argc, char *argv[]) {
  // 初始化 Google 日志库
  // google::InitGoogleLogging(argv[0]);
  // 打印当前进程 ID
  LOG(INFO) << "pid = " << getpid();

  // 创建事件循环对象
  EventLoop loop;
  // 创建监听地址对象，端口号为 9981
  InetAddress listenAddr(9981);

  // 创建 TestServiceImpl 对象
  monitor::TestServiceImpl impl;

  // 创建 RpcServer 对象
  RpcServer server(&loop, listenAddr);

  // 注册服务实现到服务器
  server.registerService(&impl);

  // 启动服务器
  server.start();

  // 开始事件循环
  loop.loop();

  // 关闭 Protocol Buffers 库
  google::protobuf::ShutdownProtobufLibrary();
}
