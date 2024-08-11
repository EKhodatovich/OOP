cmake_minimum_required(VERSION 3.5)

project(DoubleLinkedList LANGUAGES C)

add_executable(DoubleLinkedList
    dlist.c dlist.h
    main.c
)


include(GNUInstallDirs)
install(TARGETS DoubleLinkedList
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
