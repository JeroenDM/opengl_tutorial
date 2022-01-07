cmake_minimum_required(VERSION 3.16.0)
project(opengl_tutorial VERSION 0.0.1 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

add_subdirectory(external/spdlog)

find_package(spdlog)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

set(ON 1)
find_package(assimp REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}    
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)


set(LIBNAME euclid)
FILE(GLOB_RECURSE EUCLID_SRC "euclid/*.cpp")
add_library(${LIBNAME} SHARED ${EUCLID_SRC})
target_include_directories(${LIBNAME} PUBLIC .)
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


# file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})