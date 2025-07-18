enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_1v main.cpp
    diffFuncsTests_v1.cpp
    moreArgsTests_v1.cpp
    diffPassingOfArgs_v1.cpp)
target_link_libraries(tests_1v PRIVATE gtest gmock gtest_main)

add_test(NAME MyLibTest_v1 COMMAND tests_1v)

add_executable(tests_2v main.cpp
    diffFuncsTests_v2.cpp
    moreArgsTests_v2.cpp
    diffPassingOfArgs_v2.cpp)
target_link_libraries(tests_2v PRIVATE gtest gmock gtest_main)

add_test(NAME MyLibTest_v2 COMMAND tests_2v)
