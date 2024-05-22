#include "RpcCodec.h"

#include <zlib.h>  // 用于校验和计算

#include <google/protobuf/message.h>  // protobuf消息相关

#include "network/Endian.h"  // 网络字节序处理
#include "network/TcpConnection.h"  // TCP连接处理

using namespace network;

namespace network {

// 发送protobuf消息，通过TcpConnection发送
void ProtoRpcCodec::send(const TcpConnectionPtr &conn,
                         const ::google::protobuf::Message &message) {
  Buffer buf;
  fillEmptyBuffer(&buf, message);
  conn->send(&buf);
}

// 处理接收到的消息
void ProtoRpcCodec::onMessage(const TcpConnectionPtr &conn, Buffer *buf) {
  // 当缓冲区中的可读字节数大于等于最小消息长度和头部长度之和时
  while (buf->readableBytes() >= static_cast<uint32_t>(kMinMessageLen + kHeaderLen)) {
    const int32_t len = buf->peekInt32();  // 获取消息的长度
    if (len > kMaxMessageLen || len < kMinMessageLen) {
      // 如果消息长度不合法，处理错误
      // errorCallback_(conn, buf, receiveTime, kInvalidLength);
      break;
    } else if (buf->readableBytes() >= size_t(kHeaderLen + len)) {
      // 如果缓冲区中有完整的一条消息
      RpcMessagePtr message(new RpcMessage());
      // 解析消息
      ErrorCode errorCode = parse(buf->peek() + kHeaderLen, len, message.get());
      if (errorCode == kNoError) {
        // 如果解析成功，调用消息回调函数
        messageCallback_(conn, message);
        buf->retrieve(kHeaderLen + len);  // 从缓冲区中移除已处理的消息
      } else {
        // 如果解析失败，处理错误
        // errorCallback_(conn, buf, receiveTime, errorCode);
        break;
      }
    } else {
      // 如果缓冲区中没有完整的一条消息，退出循环
      break;
    }
  }
}

// 从缓冲区中解析protobuf消息
bool ProtoRpcCodec::parseFromBuffer(const void *buf, int len,
                                    google::protobuf::Message *message) {
  return message->ParseFromArray(buf, len);
}

// 将protobuf消息序列化到缓冲区
int ProtoRpcCodec::serializeToBuffer(const google::protobuf::Message &message,
                                     Buffer *buf) {
#if GOOGLE_PROTOBUF_VERSION > 3009002
  int byte_size = google::protobuf::internal::ToIntSize(message.ByteSizeLong());
#else
  int byte_size = message.ByteSize();
#endif
  buf->ensureWritableBytes(byte_size + kChecksumLen);

  uint8_t *start = reinterpret_cast<uint8_t *>(buf->beginWrite());
  uint8_t *end = message.SerializeWithCachedSizesToArray(start);
  if (end - start != byte_size) {
    // 序列化后的大小与预期不符，处理错误（这里省略了具体处理）
  }
  buf->hasWritten(byte_size);
  return byte_size;
}

// 解析消息
ProtoRpcCodec::ErrorCode ProtoRpcCodec::parse(
    const char *buf, int len, ::google::protobuf::Message *message) {
  ErrorCode error = kNoError;

  if (validateChecksum(buf, len)) {
    if (memcmp(buf, tag_.data(), tag_.size()) == 0) {
      // 从缓冲区中解析消息
      const char *data = buf + tag_.size();
      int32_t dataLen = len - kChecksumLen - static_cast<int>(tag_.size());
      if (parseFromBuffer(data, dataLen, message)) {
        error = kNoError;
      } else {
        error = kParseError;
      }
    } else {
      error = kUnknownMessageType;
    }
  } else {
    error = kCheckSumError;
  }

  return error;
}

// 填充空缓冲区
void ProtoRpcCodec::fillEmptyBuffer(Buffer *buf,
                                    const google::protobuf::Message &message) {
  assert(buf->readableBytes() == 0);
  buf->append(tag_);  // 添加消息标识符

  int byte_size = serializeToBuffer(message, buf);  // 序列化消息到缓冲区

  // 计算校验和并添加到缓冲区
  int32_t checkSum = checksum(buf->peek(), static_cast<int>(buf->readableBytes()));
  buf->appendInt32(checkSum);
  assert(buf->readableBytes() == tag_.size() + byte_size + kChecksumLen);
  (void)byte_size;

  // 添加消息的长度（网络字节序）
  int32_t len = sockets::hostToNetwork32(static_cast<int32_t>(buf->readableBytes()));
  buf->prepend(&len, sizeof len);
}

// 将字符数组转换为32位整数
int32_t ProtoRpcCodec::asInt32(const char *buf) {
  int32_t be32 = 0;
  ::memcpy(&be32, buf, sizeof(be32));
  return sockets::networkToHost32(be32);
}

// 计算校验和
int32_t ProtoRpcCodec::checksum(const void *buf, int len) {
  return static_cast<int32_t>(
      ::adler32(1, static_cast<const Bytef *>(buf), len));
}

// 校验校验和
bool ProtoRpcCodec::validateChecksum(const char *buf, int len) {
  // 校验和验证
  int32_t expectedCheckSum = asInt32(buf + len - kChecksumLen);
  int32_t checkSum = checksum(buf, len - kChecksumLen);
  return checkSum == expectedCheckSum;
}

}  // namespace network
