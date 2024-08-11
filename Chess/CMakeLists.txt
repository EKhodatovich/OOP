cmake_minimum_required(VERSION 3.5)

project(Chess LANGUAGES C)

add_executable(${PROJECT_NAME}
    main.c
    bishop.c bishop.h
    figure.c figure.h
    king.c king.h
    queen.c queen.h
    knight.c knight.h
    new.c new.h
    rook.c rook.h
    read_file.c read_file.h
    figure_list_funcs.c figure_list_funcs.h
    diagonal_and_straight_checks.c diagonal_and_straight_checks.h
)

target_compile_options (${PROJECT_NAME} PRIVATE -Wall)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


