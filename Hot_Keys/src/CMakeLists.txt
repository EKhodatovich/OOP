cmake_minimum_required(VERSION 3.5)

project(HotKeysSources LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(${PROJECT_NAME}
    command.cpp command.hpp
    command_hash.hpp
    conflicts.hpp
    exceptions.hpp
    hot_key.cpp hot_key.hpp
    hot_keys_map.cpp hot_keys_map.hpp
    hot_key_hash.hpp
    key_command_combination.hpp
    parser.cpp parser.hpp
    string_to_lowercase.hpp
)

target_compile_options (${PROJECT_NAME} PRIVATE -Wall)
