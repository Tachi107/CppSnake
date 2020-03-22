cmake_minimum_required(VERSION 3.5)

project(CppSnake)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Using Clang")
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -std=c++17 -fuse-ld=lld -flto=full")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17 -fuse-ld=lld -flto=full")
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED true)
endif()

set(HEADER_FILES Apple.hpp IndexBuffer.hpp Quad.hpp Random.hpp Renderer.hpp Shader.hpp Snake.hpp Vertex.hpp VertexArray.hpp VertexBuffer.hpp VertexBufferLayout.hpp)

target_include_directories(${PROJECT_NAME} vendor/glad/include)

add_executable("${PROJECT_NAME}" main.cpp ${HEADER_FILES})

add_subdirectory(vendor/glad/)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} dl)
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} GL)