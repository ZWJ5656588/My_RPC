#include "RpcServer.h"

#include <cassert>

#include <glog/logging.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/service.h>

#include "RpcChannel.h"

using namespace network;

 // 设置连接回调函数，绑定RpcServer的onConnection方法
RpcServer::RpcServer(EventLoop *loop, const InetAddress &listenAddr)
    : server_(loop, listenAddr, "RpcServer") {
  server_.setConnectionCallback(std::bind(&RpcServer::onConnection, this, _1));
}

void RpcServer::registerService(google::protobuf::Service *service) {
  // 获取服务的描述符
  const google::protobuf::ServiceDescriptor *desc = service->GetDescriptor();
  // 将服务注册到services_映射中，键是服务的全名
  services_[desc->full_name()] = service;
}

// 启动TCP服务器
void RpcServer::start() {  server_.start(); }

void RpcServer::onConnection(const TcpConnectionPtr &conn) {
  LOG(INFO) << "RpcServer - " << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");
  if (conn->connected()) {
    RpcChannelPtr channel(new RpcChannel(conn));
    channel->setServices(&services_);
    conn->setMessageCallback(
        std::bind(&RpcChannel::onMessage, get_pointer(channel), _1, _2));
    conn->setContext(channel);
  } else {
    conn->setContext(RpcChannelPtr());
    // FIXME:
  }
}
