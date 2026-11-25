FROM debian:trixie

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gdb \
    libssl-dev \
    zlib1g-dev \
    libopus-dev \
    pkg-config \
    curl \
    && rm -rf /var/lib/apt/lists/*

COPY dpp.deb /tmp/dpp.deb
RUN apt-get update && apt-get install -y /tmp/dpp.deb \
    && rm -rf /var/lib/apt/lists/* /tmp/dpp.deb

WORKDIR /workspace

CMD ["/bin/bash"]