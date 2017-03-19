#!/bin/bash

set -e

g++ \
  -g \
  -std=c++14 \
  -Wall \
  -Wextra \
  -Wno-deprecated-declarations \
  -IIV \
  -I/usr/include/eigen3 \
  test/*.cpp \
  -lgtest_main \
  -lgtest \
  -pthread \
  -lglog \
  -DHAS_EIGEN3 \
  -DUINT128_DEFINED \
  -o \
  	gtests
