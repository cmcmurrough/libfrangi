cmake_minimum_required(VERSION 2.6)
project(libfrangi)
set(CMAKE_BUILD_TYPE Release)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
	
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


#compile
add_library(frangi SHARED src/frangi.cpp)
add_executable(frangi-bin example/main.cpp)
target_link_libraries(frangi-bin frangi ${OpenCV_LIBS})

#install
install (TARGETS frangi DESTINATION lib)
install (TARGETS frangi-bin DESTINATION bin)
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/frangi.h DESTINATION include)
