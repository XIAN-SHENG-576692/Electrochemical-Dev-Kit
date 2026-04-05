#!/bin/sh

sudo apt update -y && sudo apt install -y \
    build-essential \
    cmake \
    zip \
    && sudo rm -rf /var/lib/apt/lists/*
