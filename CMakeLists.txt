###
#  clpp.h - An OpenCL C++/C++11 wrapper
#  Copyright (C) 2015 Mateusz Szpakowski
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
###

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CLPP)

ENABLE_LANGUAGE(CXX)

INCLUDE(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" HAVE_CPP11_FLAG)
if(HAVE_CPP11_FLAG)
    set(CPP11_FLAG "-std=c++11")
endif(HAVE_CPP11_FLAG)

SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -DDEBUG=1")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")

IF(${PROJECT_SOURCE_DIR} MATCHES ${PROJECT_BINARY_DIR})
    MESSAGE("Please do an out-of-tree build:")
    MESSAGE("rm -f CMakeCache.txt; mkdir -p default; cd default; cmake ..; make")
    MESSAGE(FATAL_ERROR "in-tree-build detected")
ENDIF(${PROJECT_SOURCE_DIR} MATCHES ${PROJECT_BINARY_DIR})

FIND_PACKAGE(SDL)
FIND_PACKAGE(PNG)

###n#
# OpenCL find
####
SET(OPENCL_DIST_DIR "" CACHE PATH "OpenCL Distribution directory")

IF(NOT OPENCL_DIST_DIR)
    IF(EXISTS /opt/AMDAPP)
        SET(OPENCL_DIST_DIR "/opt/AMDAPP")
        MESSAGE(STATUS "OpenCL AMDAPP found")
    ELSEIF(EXISTS /usr/include/CL)
        SET(OPENCL_DIST_DIR "/usr")
        MESSAGE(STATUS "Standard OpenCL found.")
    ENDIF(EXISTS /opt/AMDAPP)
ENDIF(NOT OPENCL_DIST_DIR)

IF (OPENCL_DIST_DIR)
    SET(OPENCL_LIBRARY_DIRS "")
    SET(OPENCL_INCLUDE_DIRS "${OPENCL_DIST_DIR}/include")
    SET(OPENCL_LIBRARIES "OpenCL")
    SET(HAVE_OPENCL 1)
ENDIF(OPENCL_DIST_DIR)

IF(HAVE_OPENCL)
    MESSAGE(STATUS "OpenCL found")
    MESSAGE(STATUS "OpenCL library dirs: " ${OPENCL_LIBRARY_DIRS})
    MESSAGE(STATUS "OpenCL libraries: " ${OPENCL_LIBRARIES})
    MESSAGE(STATUS "OpenCL CFLAGS: " ${OPENCL_CFLAGS})
ELSE(HAVE_OPENCL)
    MESSAGE(FATAL_ERROR "OpenCL not found")
ENDIF(HAVE_OPENCL)

IF(BUILD_TESTS)
    ENABLE_TESTING()
ENDIF(BUILD_TESTS)

ADD_DEFINITIONS(${PNG_DEFINITIONS} ${SDL_DEFINITIONS})

LINK_DIRECTORIES(${OPENCL_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} ${OPENCL_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS}
        ${SDL_INCLUDE_DIRS})
IF (BUILD_TESTS)
    ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/tests)
ENDIF(BUILD_TESTS)
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/samples)
