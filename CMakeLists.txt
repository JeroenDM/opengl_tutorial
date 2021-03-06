cmake_minimum_required(VERSION 3.16.0)
project(opengl_tutorial VERSION 0.0.1 LANGUAGES CXX)


add_subdirectory(external/spdlog)

set (CMAKE_CXX_STANDARD 20)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # lots of warnings
    add_compile_options(-Wall -Wextra -pedantic)
endif()

find_package(spdlog)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(ImageMagick REQUIRED)
find_package(glfw3 REQUIRED)

set(ON 1)
find_package(assimp REQUIRED)

include_directories(
    external/spdlog/include
    ${OPENGL_INCLUDE_DIRS}    
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)


set(LIBNAME euclid)
FILE(GLOB_RECURSE EUCLID_SRC "euclid/*.cpp")
add_library(${LIBNAME} SHARED ${EUCLID_SRC})
target_include_directories(${LIBNAME} PUBLIC .)
target_link_libraries(${LIBNAME}
    glfw
    ${GLFW_LIBRARIES}
)
# target_link_libraries(${LIBNAME}
#     spdlog
#     ${OPENGL_LIBRARIES}
#     ${GLEW_LIBRARIES}
#     ${GLUT_LIBRARY}
# )
# message(WARN ${EUCLID_SRC})

add_executable(main main.cpp)
target_link_libraries(main
    ${LIBNAME}
    spdlog
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
    assimp
)

add_executable(test_assimp test_assimp.cpp)
target_link_libraries(test_assimp
    spdlog
    assimp
)

add_executable(noneuclidean noneuclidean.cpp)
target_link_libraries(noneuclidean
    ${LIBNAME}
    spdlog
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
    assimp
)

add_executable(01_empty_window
    tutorials/01_empty_window.cpp
    tutorials/engine.cpp
    tutorials/color.cpp
)
target_link_libraries(01_empty_window
    ${LIBNAME}
    spdlog
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
)

add_executable(glfw_main glfw_version/main.cpp)
target_include_directories(glfw_main PRIVATE
    .
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)
target_link_libraries(glfw_main
    spdlog
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw
    ${GLFW_LIBRARIES}
)


# file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
