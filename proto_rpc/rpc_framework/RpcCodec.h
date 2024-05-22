#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

#include "rpc.pb.h"

namespace network {

// 前向声明类和类型定义
class Buffer;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class RpcMessage;
typedef std::shared_ptr<RpcMessage> RpcMessagePtr;
extern const char rpctag[];  // = "RPC0";

// 消息的线格式定义
//
// 字段      长度      内容
//
// size      4字节    N+8
// "RPC0"    4字节
// payload   N字节
// checksum  4字节    "RPC0"+payload的adler32校验和
//

class ProtoRpcCodec {
 public:
  const static int kHeaderLen = sizeof(int32_t);  // 头部长度为4字节
  const static int kChecksumLen = sizeof(int32_t);  // 校验和长度为4字节
  const static int kMaxMessageLen =
      64 * 1024 * 1024;  // 最大消息长度为64MB，与codec_stream.h中的kDefaultTotalBytesLimit相同

  // 错误码定义
  enum ErrorCode {
    kNoError = 0,
    kInvalidLength,
    kCheckSumError,
    kInvalidNameLen,
    kUnknownMessageType,
    kParseError,
  };

  // 类型别名定义
  typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
  typedef std::function<void(const TcpConnectionPtr &, const RpcMessagePtr &)>
      ProtobufMessageCallback;

  typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

  // 构造函数，接收一个消息回调函数
  explicit ProtoRpcCodec(const ProtobufMessageCallback &messageCb)
      : messageCallback_(messageCb) {}
  ~ProtoRpcCodec() {}

  // 发送消息函数
  void send(const TcpConnectionPtr &conn,
            const ::google::protobuf::Message &message);

  // 消息处理函数
  void onMessage(const TcpConnectionPtr &conn, Buffer *buf);

  // 从缓冲区解析消息
  bool parseFromBuffer(const void *buf, int len,
                       google::protobuf::Message *message);

  // 将消息序列化到缓冲区
  int serializeToBuffer(const google::protobuf::Message &message, Buffer *buf);

  // 解析消息
  ErrorCode parse(const char *buf, int len,
                  ::google::protobuf::Message *message);

  // 填充空缓冲区
  void fillEmptyBuffer(Buffer *buf, const google::protobuf::Message &message);

  // 计算校验和
  static int32_t checksum(const void *buf, int len);

  // 校验校验和
  static bool validateChecksum(const char *buf, int len);

  // 将字符数组转换为32位整数
  static int32_t asInt32(const char *buf);

 private:
  ProtobufMessageCallback messageCallback_;  // 消息回调函数
  int kMinMessageLen = 4;  // 最小消息长度
  const std::string tag_ = "RPC0";  // 消息标识符
};

}  // namespace network
