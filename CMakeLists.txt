project(opengl_tutorial)
cmake_minimum_required(VERSION 3.16)

set (CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}    
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

add_executable(main main.cpp)
target_link_libraries(main
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
)

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})