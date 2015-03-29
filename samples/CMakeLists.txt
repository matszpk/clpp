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

ADD_EXECUTABLE(clinfo clinfo.cpp)
TARGET_LINK_LIBRARIES(clinfo ${OPENCL_LIBRARIES})

ADD_EXECUTABLE(clcompiler clcompiler.cpp)
TARGET_LINK_LIBRARIES(clcompiler ${OPENCL_LIBRARIES})

IF(PNG_FOUND)
    ADD_EXECUTABLE(imagegen imagegen.cpp)
    TARGET_LINK_LIBRARIES(imagegen ${OPENCL_LIBRARIES} ${PNG_LIBRARIES})
ENDIF(PNG_FOUND)

ADD_EXECUTABLE(pinnedbuffer pinnedbuffer.cpp)
TARGET_LINK_LIBRARIES(pinnedbuffer ${OPENCL_LIBRARIES})

ADD_EXECUTABLE(vectoradd vectoradd.cpp)
TARGET_LINK_LIBRARIES(vectoradd ${OPENCL_LIBRARIES})
