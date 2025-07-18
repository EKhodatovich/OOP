cmake_minimum_required(VERSION 3.5)

project(WaveAlgorithmTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(../src)

add_executable(${PROJECT_NAME}
    main.cpp
    cells_table_tests.cpp
    cell_position_tests.cpp
    cell_types_convertor_tests.cpp
    maze_tests.cpp
    parser_test.cpp
    path_finder_tests.cpp
    main.cpp
)

target_compile_options (${PROJECT_NAME} PRIVATE -Wall)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

target_link_libraries(
  ${PROJECT_NAME}
  WaveAlgorithmSources
  GTest::gtest_main
)


