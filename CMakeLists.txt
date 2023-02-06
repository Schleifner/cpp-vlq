cmake_minimum_required(VERSION 3.0.0)
project(vlq VERSION 0.1.0)


include(CTest)
enable_testing()
add_subdirectory(test)

file(GLOB sources  src/*.cpp src/*.hpp)
file(GLOB HEADER_FILES src/vlq.hpp)

# static lib
add_library(vlq ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# shared lib
add_library(vlq-shared SHARED ${sources})
target_include_directories(vlq-shared PUBLIC ./src)

install(TARGETS vlq-shared LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${HEADER_FILES} DESTINATION include)


