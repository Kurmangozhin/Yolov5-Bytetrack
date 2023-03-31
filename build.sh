#!/bin/bash
g++ -I include/ src/main.cpp src/detector.cpp src/util.cpp  src/logs.cpp src/BYTETracker.cpp \
    src/kalmanFilter.cpp src/lapjv.cpp src/STrack.cpp src/utils.cpp -o main -std=c++17 `pkg-config --cflags --libs opencv` -lonnxruntime
echo "build successfully"

