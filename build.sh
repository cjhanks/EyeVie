#!/bin/bash

set -e

g++ \
  -g \
  -std=c++14 \
  -Wall \
  -Wextra \
  -Isrc \
  test/*.cpp \
  -lgtest_main \
  -lgtest \
  -pthread \
  -lglog \
  -o \
  	gtests
