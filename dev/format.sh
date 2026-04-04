#!/bin/sh

find demo -name "*.[c,h]" | xargs clang-format -style=file -i
find src -name "*.[c,h]" | xargs clang-format -style=file -i
find tests -name "*.[c,h]" | xargs clang-format -style=file -i
