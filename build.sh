#!/bin/bash

set -e

g++ \
  -g \
  -std=c++14 \
  -Wall \
  -Wextra \
  -Werror \
  -Isrc \
  test/*.cpp \
  -lgtest_main \
  -lgtest \
  -pthread \
  -lglog \
  -DUINT128_DEFINED \
  -o \
  	gtests
