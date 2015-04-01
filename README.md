# clpp
Lightweight and easy to use the OpenCL C++ wrapper in single file.
This library supports:

* UNIX, Linux, Windows environment
* C++, C++11 language standard
* OpenCL 1.0, 1.1, 1.2, 2.0 (not fully tested)
* OpenCL-OpenGL interoperability

## Installation

Just copy 'clpp.h' file to your '/usr/include' or '/usr/local/include'
(just this is single file!).

## Build samples and tests

Make a building directory, run cmake and make:

    mkdir build
    cd build
    cmake ..      (or cmake .. -DBUILD_TESTS=ON for building tests)
    make
    ctest   (if tests enabled)

Some samples requires libpng library or SDL library. Tests requires SDL library.

## Documentation

Run 'doxygen' in project directory. This will makes 'docs' directory that will contains
documentation for library.

## Important Defines and macros

clpp.h can use an OpenCL functions defined for specified version. Macro \_\_CLPP\_CL\_ABI\_VERSION
defines from what version of OpenCL standard functions will be used by your program.
For example you can use only OpenCL 1.1 functions and in case you define:

    #define __CLPP_CL_ABI_VERSION 101   // 101 is version number
    ....
    #include <clpp.h>

Likewise, \_\_CLPP\_CL\_VERSION defines from what OpenCL standard version features will be used
by clpp.

Other important macros are:

    #define __CLPP_CL_EXT  // enables OpenCL extensions.
    #define __CLPP_CL_GL   // enables OpenCL-OpenGL interoperability support.
    #define __CLPP_CL_GL_EXT   // enables OpenCL-OpenGL interoperability extensions support.
