cmake_minimum_required (VERSION 3.15)

project ("Application")

set(RESOURCE "${CMAKE_SOURCE_DIR}/Engine/src/Resources/Engine.rc")

add_executable (${PROJECT_NAME} "src/main.cpp" "src/Window/Window.h" "src/Window/Window.cpp" "src/Renderer/Renderer.h" "src/Renderer/Renderer.cpp" "src/Logger/Logger.h" "src/Image Library/stb_image.h" "src/Renderer/DriverTypes.h" ${RESOURCE})

include_directories(${CMAKE_SOURCE_DIR}/Engine/src)

target_link_libraries(${PROJECT_NAME} d3d11.lib)
target_link_libraries(${PROJECT_NAME} dxgi.lib)
target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)
