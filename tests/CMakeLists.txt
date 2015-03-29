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

ADD_EXECUTABLE(clpptest clpptest.cpp)
TARGET_LINK_LIBRARIES(clpptest ${SDL_LIBRARIES} ${OPENCL_LIBRARIES})
ADD_TEST(clpptest clpptest)

IF(HAVE_CPP11_FLAG)
    ADD_EXECUTABLE(clpptest_cpp11 clpptest.cpp)
    TARGET_LINK_LIBRARIES(clpptest_cpp11 ${SDL_LIBRARIES} ${OPENCL_LIBRARIES})
    SET_TARGET_PROPERTIES(clpptest_cpp11 PROPERTIES COMPILE_FLAGS "${CPP11_FLAG}"
            LINK_FLAGS "${CPP11_FLAG}")
    ADD_TEST(clpptest_cpp11 clpptest_cpp11)
ENDIF(HAVE_CPP11_FLAG)
