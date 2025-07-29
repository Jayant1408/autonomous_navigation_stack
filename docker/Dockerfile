FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    unzip \
    libopencv-dev \
    libgtk2.0-dev \
    pkg-config \
    libeigen3-dev \
    libyaml-cpp-dev \
    && apt-get clean

# Set working directory
WORKDIR /app

# Default shell
CMD ["/bin/bash"]
