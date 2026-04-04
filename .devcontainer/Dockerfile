FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /workspace

RUN apt-get update -y && apt-get install -y \
    build-essential \
    cmake \
    clang \
    clang-format \
    clang-tidy \
    gdb \
    git \
    gh \
    neovim \
    tree \
    && rm -rf /var/lib/apt/lists/*

CMD ["sleep", "infinity"]
