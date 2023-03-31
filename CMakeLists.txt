if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


cmake_minimum_required(VERSION 3.0.0)
project(yolo_track VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)


include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
find_package(Eigen3 ${EIGEN_VERSION} QUIET)
include_directories("include/")
include_directories("/usr/local/include/eigen3")
set(onnxruntime_INCLUDE_DIRS /usr/local/include/onnxruntime)
include_directories(${onnxruntime_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(yolo_track
               src/main.cpp
               src/detector.cpp
               src/util.cpp
               src/logs.cpp
               src/STrack.cpp
               src/utils.cpp
               src/lapjv.cpp
               src/kalmanFilter.cpp
               src/BYTETracker.cpp
                             
               )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} /usr/local/lib/libonnxruntime.so)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
