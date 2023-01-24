# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

# Include sub-projects.
add_subdirectory ("Third-Party/DirectX")
add_subdirectory ("Engine")