#pragma once

#include <assert.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <vector>

#include "network/Endian.h"
// #include <unistd.h>  // ssize_t

namespace network {

/// 一个缓冲区类，模仿 org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
class Buffer {
 public:
  // 缓冲区前置字节数
  static const size_t kCheapPrepend = 8;
  // 缓冲区初始大小
  static const size_t kInitialSize = 1024 * 4;

  // 构造函数，初始化缓冲区
  explicit Buffer(size_t initialSize = kInitialSize)
      : buffer_(kCheapPrepend + initialSize),
        readerIndex_(kCheapPrepend),
        writerIndex_(kCheapPrepend) {
    assert(readableBytes() == 0);
    assert(writableBytes() == initialSize);
    assert(prependableBytes() == kCheapPrepend);
  }

  // 读取缓冲区中可读字节数
  size_t readableBytes() const { return writerIndex_ - readerIndex_; }

  // 读取缓冲区中可写字节数
  size_t writableBytes() const { return buffer_.size() - writerIndex_; }

  // 读取缓冲区中前置字节数
  size_t prependableBytes() const { return readerIndex_; }

  // 获取可读数据的起始地址
  const char *peek() const { return begin() + readerIndex_; }

  // 从缓冲区中检索数据
  void retrieve(size_t len) {
    assert(len <= readableBytes());
    if (len < readableBytes()) {
      readerIndex_ += len;
    } else {
      retrieveAll();
    }
  }

  // 检索并忽略缓冲区中的 int64_t 类型数据
  void retrieveInt64() { retrieve(sizeof(int64_t)); }

  // 检索并忽略缓冲区中的 int32_t 类型数据
  void retrieveInt32() { retrieve(sizeof(int32_t)); }

  // 检索并忽略缓冲区中的 int16_t 类型数据
  void retrieveInt16() { retrieve(sizeof(int16_t)); }

  // 检索并忽略缓冲区中的 int8_t 类型数据
  void retrieveInt8() { retrieve(sizeof(int8_t)); }

  // 检索并忽略缓冲区中的所有数据
  void retrieveAll() {
    readerIndex_ = kCheapPrepend;
    writerIndex_ = kCheapPrepend;
  }

  // 将缓冲区中的所有数据作为字符串检索
  std::string retrieveAllAsString() {
    return retrieveAsString(readableBytes());
  }

  // 将缓冲区中的指定长度数据作为字符串检索
  std::string retrieveAsString(size_t len) {
    assert(len <= readableBytes());
    std::string result(peek(), len);
    retrieve(len);
    return result;
  }

  // 向缓冲区追加字符串数据
  void append(const std::string &str) { append(str.data(), str.size()); }

  // 向缓冲区追加字符数据
  void append(const char * /*restrict*/ data, size_t len) {
    ensureWritableBytes(len);
    std::copy(data, data + len, beginWrite());
    hasWritten(len);
  }

  // 向缓冲区追加任意类型数据
  void append(const void * /*restrict*/ data, size_t len) {
    append(static_cast<const char *>(data), len);
  }

  // 确保缓冲区有足够的空间写入数据
  void ensureWritableBytes(size_t len) {
    if (writableBytes() < len) {
      makeSpace(len);
    }
    assert(writableBytes() >= len);
  }

  // 获取可写入数据的起始地址
  char *beginWrite() { return begin() + writerIndex_; }

  // 获取可写入数据的起始地址（const 版本）
  const char *beginWrite() const { return begin() + writerIndex_; }

  // 标记已写入的字节数
  void hasWritten(size_t len) {
    assert(len <= writableBytes());
    writerIndex_ += len;
  }

  // 回退写入指针
  void unwrite(size_t len) {
    assert(len <= readableBytes());
    writerIndex_ -= len;
  }

  // 使用网络字节序追加 int64_t 类型数据
  void appendInt64(int64_t x) {
    int64_t be64 = sockets::hostToNetwork64(x);
    append(&be64, sizeof be64);
  }

  // 使用网络字节序追加 int32_t 类型数据
  void appendInt32(int32_t x) {
    int32_t be32 = sockets::hostToNetwork32(x);
    append(&be32, sizeof be32);
  }

  // 使用网络字节序追加 int16_t 类型数据
  void appendInt16(int16_t x) {
    int16_t be16 = sockets::hostToNetwork16(x);
    append(&be16, sizeof be16);
  }

  // 追加 int8_t 类型数据
  void appendInt8(int8_t x) { append(&x, sizeof x); }

  // 从网络字节序读取 int64_t 类型数据
  int64_t readInt64() {
    int64_t result = peekInt64();
    retrieveInt64();
    return result;
  }

  // 从网络字节序读取 int32_t 类型数据
  int32_t readInt32() {
    int32_t result = peekInt32();
    retrieveInt32();
    return result;
  }

  // 从网络字节序读取 int16_t 类型数据
  int16_t readInt16() {
    int16_t result = peekInt16();
    retrieveInt16();
    return result;
  }

  // 从网络字节序读取 int8_t 类型数据
  int8_t readInt8() {
    int8_t result = peekInt8();
    retrieveInt8();
    return result;
  }

  // 查看网络字节序中的 int64_t 类型数据
  int64_t peekInt64() const {
    assert(readableBytes() >= sizeof(int64_t));
    int64_t be64 = 0;
    ::memcpy(&be64, peek(), sizeof be64);
    return sockets::networkToHost64(be64);
  }

  // 查看网络字节序中的 int32_t 类型数据
  int32_t peekInt32() const {
    assert(readableBytes() >= sizeof(int32_t));
    int32_t be32 = 0;
    ::memcpy(&be32, peek(), sizeof be32);
    return sockets::networkToHost32(be32);
  }

  // 查看网络字节序中的 int16_t 类型数据
  int16_t peekInt16() const {
    assert(readableBytes() >= sizeof(int16_t));
    int16_t be16 = 0;
    ::memcpy(&be16, peek(), sizeof be16);
    return sockets::networkToHost16(be16);
  }

  // 查看 int8_t 类型数据
  int8_t peekInt8() const {
    assert(readableBytes() >= sizeof(int8_t));
    int8_t x = *peek();
    return x;
  }

  // 使用网络字节序预置 int64_t 类型数据
  void prependInt64(int64_t x) {
    int64_t be64 = sockets::hostToNetwork64(x);
    prepend(&be64, sizeof be64);
  }

  // 使用网络字节序预置 int32_t 类型数据
  void prependInt32(int32_t x) {
    int32_t be32 = sockets::hostToNetwork32(x);
    prepend(&be32, sizeof be32);
  }

  // 使用网络字节序预置 int16_t 类型数据
  void prependInt16(int16_t x) {
    int16_t be16 = sockets::hostToNetwork16(x);
    prepend(&be16, sizeof be16);
  }

  // 预置 int8_t 类型数据
  void prependInt8(int8_t x) { prepend(&x, sizeof x); }

  // 预置数据
  void prepend(const void * /*restrict*/ data, size_t len) {
    assert(len <= prependableBytes());
    readerIndex_ -= len;
    const char *d = static_cast<const char *>(data);
    std::copy(d, d + len, begin() + readerIndex_);
  }

  // 获取缓冲区的内部容量
  size_t internalCapacity() const { return buffer_.capacity(); }

  // 直接将数据读取到缓冲区中
  ssize_t readFd(int fd, int *savedErrno);

 private:
  // 获取缓冲区的起始地址
  char *begin() { return &*buffer_.begin(); }

  // 获取缓冲区的起始地址（const 版本）
  const char *begin() const { return &*buffer_.begin();}

    // 确保有足够的空间写入数据
  void makeSpace(size_t len) {
    if (writableBytes() + prependableBytes() < len + kCheapPrepend) {
      // 如果当前可写空间和前置空间不足以容纳新数据，则扩展缓冲区
      buffer_.resize(writerIndex_ + len);
    } else {
      // 将可读数据移动到缓冲区前面，腾出空间
      assert(kCheapPrepend < readerIndex_);
      size_t readable = readableBytes();
      std::copy(begin() + readerIndex_, begin() + writerIndex_,
                begin() + kCheapPrepend);
      readerIndex_ = kCheapPrepend;
      writerIndex_ = readerIndex_ + readable;
      assert(readable == readableBytes());
    }
  }

 private:
  std::vector<char> buffer_; // 缓冲区数据存储
  size_t readerIndex_; // 读指针索引
  size_t writerIndex_; // 写指针索引

  static const char kCRLF[]; // CRLF 字符常量，用于标识行结束
};

}  // namespace network
