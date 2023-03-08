cmake_minimum_required (VERSION 3.20)

project ("Engine")

set(RESOURCE "${CMAKE_SOURCE_DIR}/Engine/src/Resources/Engine.rc")

add_executable (${PROJECT_NAME} ${RESOURCE} "src/main.cpp" 
"src/Window/Window.cpp"
"src/GameTimer/GameTimer.cpp"
"src/Assets/Model.cpp" 
"src/Graphics/Shader/ShaderObject.cpp"
"src/Graphics/Device/GraphicsDevice.cpp"
"src/Application/GameApp.cpp" "src/GameLogic/GameLogic.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Engine/src")


target_link_libraries(${PROJECT_NAME} "d3d11.lib")
target_link_libraries(${PROJECT_NAME} "dxgi.lib")
target_link_libraries(${PROJECT_NAME} "d3dcompiler.lib")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)