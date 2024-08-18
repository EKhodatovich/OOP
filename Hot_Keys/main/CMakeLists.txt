cmake_minimum_required(VERSION 3.5)

project(HotKeysMain LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(${PROJECT_NAME}
    main.cpp
    writer.cpp writer.hpp
)

include_directories(../src)

target_link_libraries(${PROJECT_NAME}
    HotKeysSources
)

target_compile_options (${PROJECT_NAME} PRIVATE -Wall)
