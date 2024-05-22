#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <cassert>
#include <thread>

#include <glog/logging.h>

// 仿照muduo实现的network
#include "network/EventLoop.h"
#include "network/InetAddress.h"
#include "network/TcpClient.h"
#include "network/TcpConnection.h"
#include "rpc_framework/RpcChannel.h"

#include "monitor.pb.h"

using namespace network;

// RpcClient 类用于与 gRPC 服务器通信，发送监控信息并接收响应
class RpcClient {
 public:
  // 构造函数，初始化 RpcClient 对象
  RpcClient(EventLoop *loop, const InetAddress &serverAddr)
      : loop_(loop),
        client_(loop, serverAddr, "RpcClient"),
        channel_(new RpcChannel),
        stub_(get_pointer(channel_)) {
    // 设置连接回调函数
    client_.setConnectionCallback(
        std::bind(&RpcClient::onConnection, this, std::placeholders::_1));
    // 设置消息回调函数
    client_.setMessageCallback(
        std::bind(&RpcChannel::onMessage, get_pointer(channel_), std::placeholders::_1, std::placeholders::_2));
  }

  // SetMonitorInfo 方法用于发送监控信息的 gRPC 请求并处理响应
  void SetMonitorInfo(const monitor::TestRequest &request) {
    monitor::TestResponse *response = new monitor::TestResponse();

    // 调用存根的 MonitorInfo 方法，发送请求并设置回调函数处理响应
    stub_.MonitorInfo(nullptr, &request, response,
                      NewCallback(this, &RpcClient::closure, response));
  }

  // 连接服务器
  void connect() { client_.connect(); }

 private:
  // 连接回调函数
  void onConnection(const TcpConnectionPtr &conn) {
    if (conn->connected()) {
      // 设置 RPC 通道的连接
      channel_->setConnection(conn);
    } else {
      // 重新连接服务器
      RpcClient::connect();
    }
  }

  // 回调函数，处理 gRPC 响应
  void closure(monitor::TestResponse *resp) {
    LOG(INFO) << "resq:\n" << resp->DebugString();
  }

  EventLoop *loop_; // 事件循环指针
  TcpClient client_; // TCP 客户端对象
  RpcChannelPtr channel_; // RPC 通道指针
  monitor::TestService::Stub stub_; // gRPC 服务存根对象
};

int main(int argc, char *argv[]) {
  // 初始化 Google 日志库
  // google::InitGoogleLogging(argv[0]);

  // 打印当前进程 ID
  LOG(INFO) << "pid = " << getpid();
  if (argc > 1) {
    // 创建事件循环对象
    EventLoop loop;
    // 创建服务器地址对象，端口号为 9981
    InetAddress serverAddr(argv[1], 9981);

    // 创建 RpcClient 对象并连接服务器
    RpcClient rpcClient(&loop, serverAddr);
    rpcClient.connect();

    // 创建一个唯一指针，指向线程对象
    std::unique_ptr<std::thread> thread_ = nullptr;
    int count = 0;
    
    // 创建并启动一个新线程
    thread_ = std::make_unique<std::thread>([&]() {
      while (true) {
        count++;

        // 创建并设置请求消息
        monitor::TestRequest request;
        request.set_name("cpu0");
        request.set_count(count);

        // 发送监控信息请求
        rpcClient.SetMonitorInfo(request);
        // 每隔 3 秒发送一次请求
        std::this_thread::sleep_for(std::chrono::seconds(3));
      }
    });
    
    // 分离线程，使其在后台运行
    thread_->detach();
    // 开始事件循环
    loop.loop();

  } else {
    // 打印使用说明
    printf("Usage: %s host_ip\n", argv[0]);
  }
  // 关闭 Protocol Buffers 库
  google::protobuf::ShutdownProtobufLibrary();
}
