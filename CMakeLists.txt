cmake_minimum_required(VERSION 3.23)
project(ImageStitching CXX)
find_package(Eigen3 REQUIRED)
find_path(STB_IMAGE_INCLUDE_DIR "stb_image.h" PATH_SUFFIXES "stb")

set(CMAKE_BUILD_TYPE Debug)

add_library(stb::image INTERFACE IMPORTED)
add_executable(ImageStitching)

target_sources(ImageStitching
    PRIVATE
        src/main.cpp
        src/image.cpp
        src/harrisCorner.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            src
        FILES
            src/image.h
            src/harrisCorner.h

)

target_include_directories(stb::image INTERFACE ${STB_IMAGE_INCLUDE_DIR})
target_link_libraries(ImageStitching
    PRIVATE
        Eigen3::Eigen
        stb::image
)   
