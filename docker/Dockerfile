FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
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
    python3 \
    python3-pip \
    nlohmann-json3-dev \ 
    python3-dev \
    && apt-get clean

# Upgrade pip and install required Python packages
RUN python3 -m pip install --upgrade pip && \
    pip3 install ultralytics opencv-python

# Set working directory
WORKDIR /app

# Default shell
CMD ["/bin/bash"]
