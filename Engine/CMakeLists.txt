cmake_minimum_required (VERSION 3.20)

project ("Engine")

set(RESOURCE "${CMAKE_SOURCE_DIR}/Engine/src/Resources/Engine.rc")

add_executable (${PROJECT_NAME} ${RESOURCE} "src/main.cpp" 
"src/Window/Window.cpp" 
"src/Renderer/Renderer.cpp" 
"src/GameTimer/GameTimer.cpp"
"src/Assets/Model.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Engine/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Third-Party/DirectX/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Third-Party/STBI/include")

target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/Third-Party/DirectX/lib/d3d11.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/Third-Party/DirectX/lib/dxgi.lib")
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/Third-Party/DirectX/lib/d3dcompiler.lib")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)