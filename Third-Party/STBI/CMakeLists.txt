cmake_minimum_required (VERSION 3.20)

project ("STBImage")

add_library(${PROJECT_NAME} "src/stb_image.cpp")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)