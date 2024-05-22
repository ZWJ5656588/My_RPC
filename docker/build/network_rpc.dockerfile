FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get clean && \
    apt-get autoclean

#docker环境中进行装配置
RUN apt update && \
    apt install -y \
    vim \
    htop \
    apt-utils \
    curl \
    cmake \
    net-tools \
    gdb  gcc g++ \
    libboost-all-dev \
    libgoogle-glog-dev     


COPY install/abseil /tmp/install/abseil
RUN /tmp/install/abseil/install_abseil.sh

COPY install/protobuf /tmp/install/protobuf
RUN /tmp/install/protobuf/install_protobuf.sh


WORKDIR /work
 
