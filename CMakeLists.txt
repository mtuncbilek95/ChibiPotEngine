# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project("ChibiPot Engine")

# Include sub-projects.
add_subdirectory ("Third-Party/DirectX")
add_subdirectory ("Engine")

