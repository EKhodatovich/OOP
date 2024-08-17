cmake_minimum_required(VERSION 3.5)

project(WaveAlgorithmSources LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(${PROJECT_NAME}
    main.cpp
    cells_table.cpp cells_table.hpp
    cell_position.hpp
    cell_type.hpp
    cell_types_convertor.hpp
    exceptions.hpp
    maze.cpp maze.hpp
    parser.cpp parser.hpp
    path.hpp
    path_finder.cpp path_finder.hpp
    start_finish_to_empty_space_convertor.cpp start_finish_to_empty_space_convertor.hpp
    start_finish_to_wall_convertor.cpp start_finish_to_wall_convertor.hpp
)

target_compile_options (${PROJECT_NAME} PRIVATE -Wall)
