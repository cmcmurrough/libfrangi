cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(libfrangi)

# set build type to release
set(CMAKE_BUILD_TYPE "Release")

# explicitly set c++14
set(CMAKE_CXX_STANDARD 14)
	
# configure OpenCV
# workaround for -lopencv_dep_cudart linker error when using CUDA
# NOTE: if linker error occurs, run cmake again with existing cache before build
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
# workaround for findOpenCV.cmake set to not found error
set(OpenCV_DIR "/usr/local/share/OpenCV")
# workaround for libatomic
set(CMAKE_CXX_FLAGS "-Wl,-latomic")
# find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# build the application
add_executable(frangi_demo frangi_demo.cpp)
target_link_libraries(frangi_demo ${OpenCV_LIBS})

