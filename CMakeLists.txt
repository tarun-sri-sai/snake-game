cmake_minimum_required(VERSION 3.5)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.1.3
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_executable(SnakeGame ${SRC_FILES} ${HEADER_FILES})

target_include_directories(SnakeGame PRIVATE include)

target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system fmt::fmt)

add_custom_command(TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:SnakeGame>/assets"
)

if (MSVC)
    target_compile_options(SnakeGame PRIVATE /W4)
endif()
