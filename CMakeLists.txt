project(mirasol)
cmake_minimum_required(VERSION 2.8.11)
add_executable(mirasol mirasol.cpp mwidget.cpp dotcanvas.cpp)
#target_link_libraries(mirasol Qt4::QtGui)
target_link_libraries(mirasol Qt5::Widgets)

include(TestBigEndian)
include(CheckTypeSize)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#find_package(Qt4)
find_package(Qt5Widgets)

set(CMAKE_CXX_FLAGS "-std=c++11")
install(TARGETS mirasol DESTINATION bin)

test_big_endian(BIGENDIAN)

set(MIRASOL_MAJOR_VERSION 0)
set(MIRASOL_MINOR_VERSION 1)
set(MIRASOL_PATCH_VERSION 0)
set(MIRASOL_VERSION ${MIRASOL_MAJOR_VERSION}.${MIRASOL_MINOR_VERSION}.${MIRASOL_PATCH_VERSION})

include_directories(${PROJECT_BINARY_DIR})
configure_file (config.h.in config.h)

set(CPACK_PACKAGE_VERSION_MAJOR ${MIRASOL_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${MIRASOL_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${MIRASOL_PATCH_VERSION})
set(CPACK_SOURCE_IGNORE_FILES /\\\\.git;.*~)
include(CPack)
