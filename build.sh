#!/bin/bash
set -e

g++ \
  -std=c++14 \
  -O3 \
  -g \
  -Wall \
  -Wextra \
  -Isrc \
  main.cpp
