#!/bin/bash

cmake --build build --target all
ctest --test-dir build
