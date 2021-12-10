cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project (${ProjectId})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -static")


add_executable(${ProjectId}
    main.cpp
    
    GLDebug.h
    GLDebug.cpp
    
    VertexBuffer.h
    VertexBuffer.cpp
    
    IndexBuffer.h
    IndexBuffer.cpp
    
    VertexBufferLayout.h
    VertexBufferLayout.cpp
    
    VertexArray.h
    VertexArray.cpp
    
    Shader.h
    Shader.cpp
)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${ProjectId} glfw)

add_subdirectory(external/glad)
target_link_libraries(${ProjectId} glad)