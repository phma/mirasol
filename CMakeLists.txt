project(mirasol)
cmake_minimum_required(VERSION 3.1.0)
# Copyright 2015,2016,2017 Pierre Abbat.
# This file is part of Mirasol.
# 
# Mirasol is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Mirasol is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Mirasol. If not, see <http://www.gnu.org/licenses/>.

include(TestBigEndian)
include(CheckTypeSize)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(mirasol mirasol.cpp mwidget.cpp dotcanvas.cpp xy.cpp angle.cpp trajectory.cpp dotlist.cpp pattern.cpp random.cpp maction.cpp nearindex.cpp)
add_executable(miratest miratest.cpp xy.cpp angle.cpp trajectory.cpp dotlist.cpp
pattern.cpp random.cpp nearindex.cpp)
target_link_libraries(mirasol Qt5::Widgets Qt5::Core)
target_link_libraries(miratest Qt5::Core)

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
