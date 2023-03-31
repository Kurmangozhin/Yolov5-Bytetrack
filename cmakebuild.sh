#!/bin/bash
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
mkdir models
cp ../opt.json .
cp ../models/* models
echo "Inference Video"
./yolo_track ../v.mp4