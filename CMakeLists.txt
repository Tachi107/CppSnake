cmake_minimum_required(VERSION 3.5)

project(CppSnake)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Using Clang")
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -fuse-ld=lld -flto=full")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld -flto=full")
else()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED true)
endif()


set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)


set(HEADER_FILES Apple.hpp IndexBuffer.hpp Quad.hpp Random.hpp Renderer.hpp Shader.hpp Snake.hpp Vertex.hpp VertexArray.hpp VertexBuffer.hpp VertexBufferLayout.hpp)
add_executable("${PROJECT_NAME}" main.cpp ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} glad glfw ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})