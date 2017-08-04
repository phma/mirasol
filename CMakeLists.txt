project(mirasol)
cmake_minimum_required(VERSION 3.1.0)

include(TestBigEndian)
include(CheckTypeSize)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(mirasol mirasol.cpp mwidget.cpp dotcanvas.cpp xy.cpp angle.cpp trajectory.cpp dotlist.cpp pattern.cpp random.cpp maction.cpp)
add_executable(miratest miratest.cpp xy.cpp angle.cpp trajectory.cpp dotlist.cpp
pattern.cpp random.cpp)
target_link_libraries(mirasol Qt5::Widgets Qt5::Core)
target_link_libraries(miratest Qt5::Core)

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
