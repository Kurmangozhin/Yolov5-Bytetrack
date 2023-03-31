## Requirements

# Compile library

1. Opencv https://github.com/opencv/opencv C++
2. onnxruntime v 1.10.0 https://github.com/microsoft/onnxruntime C++
3. cmake version 3.25.0
4. sudo apt-get install nlohmann-json-dev Ubuntu 18.04
4. sudo apt-get install nlohmann-json3-dev Ubuntu > 18.04

# Instruction
1. Opencv https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html
2. Onnxruntime (GPU) https://developer.ridgerun.com/wiki/index.php?title=ONNX_simple_sample

# Start app
1. ./cmakebuild.sh 
2. cd build
3. ./yolo_track ../v.mp4
