cmake_minimum_required(VERSION 4.3)
project(Photons LANGUAGES CXX C)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(photons 
    src/main.cpp
)

target_include_directories(photons PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
)

target_link_libraries(photons PUBLIC
    opengl32
    glad
    glfw
)