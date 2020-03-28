cmake_minimum_required(VERSION 3.5)

project(CppSnake)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Using Clang")
    if (DEBUG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -gfull -fuse-ld=lld")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++ -Og -gfull -fuse-ld=lld")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fuse-ld=lld -flto=full")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++ -O3 -fuse-ld=lld -flto=full")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld -flto=full")
    endif()
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

file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})