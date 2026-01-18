#!/bin/bash
set -e

cmake --build build --target all
ctest --test-dir build
