cmake_minimum_required(VERSION 3.10)
project(JPEG_cmprsn)

set(CMAKE_CXX_STANDARD 17)

# Add Homebrew OpenCV path
set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.11.0/include/opencv4/)
find_package(OpenCV REQUIRED)

if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV using 'brew install opencv'")
endif()

# Add include directory explicitly
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create a list of source files
set(SOURCES
        src/dct.cpp
        src/quantization.cpp
        src/image_utils.cpp
        main.cpp
)

# Create executable
add_executable(jpeg_compression ${SOURCES})

# Link OpenCV libraries
target_link_libraries(jpeg_compression ${OpenCV_LIBS})

# Set include directories using target_include_directories
target_include_directories(jpeg_compression
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)