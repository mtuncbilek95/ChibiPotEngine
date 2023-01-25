cmake_minimum_required (VERSION 3.20)

project ("Application")

set(RESOURCE "${CMAKE_SOURCE_DIR}/Engine/src/Resources/Engine.rc")

add_executable (${PROJECT_NAME} ${RESOURCE} "src/main.cpp" 
"src/Window/Window.h" "src/Window/Window.cpp" 
"src/Renderer/Renderer.h" "src/Renderer/Renderer.cpp" 
"src/Logger/Logger.h" 
"src/Renderer/DriverTypes.h" 
"src/GameTimer/GameTimer.h" "src/GameTimer/GameTimer.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine/src)

target_link_libraries(${PROJECT_NAME} d3d11.lib)
target_link_libraries(${PROJECT_NAME} dxgi.lib)
target_link_libraries(${PROJECT_NAME} d3dcompiler.lib)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)