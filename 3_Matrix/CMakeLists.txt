cmake_minimum_required(VERSION 3.5)

project(Matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()


add_executable(${PROJECT_NAME}
    main.cpp
    Matrix.hpp Matrix.cpp
    Single_Element_Tests.cpp
    Static_Members_Tests.cpp
    Vector_Tests.cpp
    Matrix_Tests.cpp
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
install(TARGETS Matrix
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
