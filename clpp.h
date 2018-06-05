/*
 *  clpp.h - An OpenCL C++/C++11 wrapper
 *  Copyright (C) 2015 Mateusz Szpakowski
 *  Contributors:
 *  Lukasz Towarek (ltowarek)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
/*! \file clpp.h
 * \brief OpenCL C++/C++11 wrapper
 */

#ifndef __CLPP_H__
#define __CLPP_H__

#ifndef __CLPP_CL_ABI_VERSION
#    define __CLPP_CL_ABI_VERSION __CLPP_CL_VERSION
#endif

#if __CLPP_CL_ABI_VERSION==100
#   define CL_USE_DEPRECATED_OPENCL_2_1_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_2_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_1_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_0_APIS 1
#endif
#if __CLPP_CL_ABI_VERSION==101
#   define CL_USE_DEPRECATED_OPENCL_2_1_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_2_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_1_APIS 1
#endif
#if __CLPP_CL_ABI_VERSION==102
#   define CL_USE_DEPRECATED_OPENCL_2_1_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_2_APIS 1
#endif
#if __CLPP_CL_ABI_VERSION==200
#   define CL_USE_DEPRECATED_OPENCL_2_1_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#endif
#if __CLPP_CL_ABI_VERSION==201
#   define CL_USE_DEPRECATED_OPENCL_2_1_APIS 1
#endif

/// clpp major version number
#define __CLPP_MAJOR_VERSION 0
/// clpp minor version number
#define __CLPP_MINOR_VERSION 3
/// clpp version string
#define __CLPP_VERSION_STRING "0.3"

#include <cstdio>
#include <exception>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <string>
#include <utility>
#if __cplusplus > 199711L
#   define __CLPP_CPP0X
#   include <initializer_list>
/// noexcept/throw macro
#   define __CLPP_NOEXCEPT noexcept
#else
/// noexcept/throw macro
#   define __CLPP_NOEXCEPT throw()
#endif
#ifdef __APPLE__
#   include <OpenCL/cl.h>
#else
#   include <CL/cl.h>
#endif

#ifdef _WIN32
#pragma push_macro("max")
#undef max
#endif

// only for generating Doxygen documentation
#ifdef __CLPP_DOXYGEN
    /// determines what OpenCL version standard will be used.
    /** Version is in format: 100*major_version+minor_version. */
    #define __CLPP_CL_VERSION
    
    /// determines from what OpenCL version functions will be used
    /** Version is in format: 100*major_version+minor_version.
     * This macros will be useful to create portable programs between various systems.
     * Various vendors provides various an OpenCL versions. For example NVIDIA drivers
     * provides only OpenCL 1.1 version. To create compliant binaries you must
     * use only OpenCL 1.1 functions and this macro inform about what functions from what
     * OpenCL version can be used.
     */
    #define __CLPP_CL_ABI_VERSION
    
    /// enables OpenCL extensions (device fission, migrate mem object)
    #define __CLPP_CL_EXT
    
    /// enables OpenCL GL Interoperability
    #define __CLPP_CL_GL
    
    /// enables OpenCL GL Interoperability extensions
    #define __CLPP_CL_GL_EXT
#endif

#if (defined(CL_VERSION_2_0) || defined(CL_VERSION_1_2)) && __CLPP_CL_ABI_VERSION==100
extern "C"
{
extern CL_API_ENTRY cl_int CL_API_CALL
clSetCommandQueueProperty(cl_command_queue              /* command_queue */,
                cl_command_queue_properties   /* properties */, 
                cl_bool                        /* enable */,
                cl_command_queue_properties * /* old_properties */)
                CL_API_SUFFIX__VERSION_1_0;
};
#endif

#if defined(CL_VERSION_2_2)
#    if (!defined(__CLPP_CL_ABI_VERSION) || __CLPP_CL_ABI_VERSION>202)
#       define __CLPP_CL_ABI_VERSION (202U)
#    endif
#elif defined(CL_VERSION_2_1)
#    if (!defined(__CLPP_CL_ABI_VERSION) || __CLPP_CL_ABI_VERSION>201)
#       define __CLPP_CL_ABI_VERSION (201U)
#    endif
#elif defined(CL_VERSION_2_0)
#    if (!defined(__CLPP_CL_ABI_VERSION) || __CLPP_CL_ABI_VERSION>200)
#       define __CLPP_CL_ABI_VERSION (200U)
#    endif
#elif defined(CL_VERSION_1_2)
#    if (!defined(__CLPP_CL_ABI_VERSION) || __CLPP_CL_ABI_VERSION>102)
#       define __CLPP_CL_ABI_VERSION (102U)
#    endif
#elif defined(CL_VERSION_1_1)
#    if (!defined(__CLPP_CL_ABI_VERSION) || __CLPP_CL_ABI_VERSION>101)
#       define __CLPP_CL_ABI_VERSION (101U)
#    endif
#elif defined(CL_VERSION_1_0)
#    if (!defined(__CLPP_CL_ABI_VERSION) || __CLPP_CL_ABI_VERSION>100)
#       define __CLPP_CL_ABI_VERSION (100U)
#    endif
#endif

#if defined(CL_VERSION_2_2)
#    if (!defined(__CLPP_CL_VERSION) || __CLPP_CL_VERSION>202)
#       define __CLPP_CL_VERSION (202U)
#    endif
#elif defined(CL_VERSION_2_1)
#    if (!defined(__CLPP_CL_VERSION) || __CLPP_CL_VERSION>201)
#       define __CLPP_CL_VERSION (201U)
#    endif
#elif defined(CL_VERSION_2_0)
#    if (!defined(__CLPP_CL_VERSION) || __CLPP_CL_VERSION>200)
#       define __CLPP_CL_VERSION (200U)
#    endif
#elif defined(CL_VERSION_1_2)
#    if (!defined(__CLPP_CL_VERSION) || __CLPP_CL_VERSION>102)
#       define __CLPP_CL_VERSION (102U)
#    endif
#elif defined(CL_VERSION_1_1)
#    if (!defined(__CLPP_CL_VERSION) || __CLPP_CL_VERSION>101)
#       define __CLPP_CL_VERSION (101U)
#    endif
#elif defined(CL_VERSION_1_0)
#    if (!defined(__CLPP_CL_VERSION) || __CLPP_CL_VERSION>100)
#       define __CLPP_CL_VERSION (100U)
#    endif
#endif

#if __CLPP_CL_ABI_VERSION > __CLPP_CL_VERSION
#   undef __CLPP_CL_VERSION
#   define __CLPP_CL_VERSION __CLPP_CL_ABI_VERSION
#endif

#ifdef __CLPP_CL_EXT
#   ifdef __APPLE__
#       include <OpenCL/cl_ext.h>
#   else
#       include <CL/cl_ext.h>
#   endif
#   if __CLPP_CL_ABI_VERSION<102 && defined(cl_ext_device_fission)
#       define __CLPP_DEVICE_FISSION 1
#   endif
#   if __CLPP_CL_ABI_VERSION<102 && defined(cl_ext_migrate_memobject)
#       define __CLPP_MIGRATE_MEMOBJECT 1
#  endif
#endif

#ifdef __CLPP_CL_GL
#   ifdef __APPLE__
#       include <OpenCL/cl_gl.h>
#   else
#       include <CL/cl_gl.h>
#   endif
#endif

#ifdef __CLPP_CL_GL_EXT
#   ifdef __APPLE__
#       include <OpenCL/cl_gl_ext.h>
#   else
#       include <CL/cl_gl_ext.h>
#   endif
#   ifdef CL_COMMAND_GL_FENCE_SYNC_OBJECT_KHR
#       define __CLPP_EVENT_FROM_GLSYNC 1
#   endif
#endif

/* deprecated definitions */
#if defined(__GNUC__) || defined(__clang__)
/// deprecated macro for deprecated methods and functions
#    define __CLPP_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
/// deprecated macro for deprecated methods and functions
#    define __CLPP_DEPRECATED __declspec(deprecated)
#else
/// deprecated macro for deprecated methods and functions
#    define __CLPP_DEPRECATED
#endif

#if __CLPP_CL_VERSION>=202 && !defined(CL_USE_DEPRECATED_OPENCL_2_1_APIS)
/// deprecated macro for deprecated features in OpenCL 2.2 standard
#    define __CLPP_CL_2_2_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated features in OpenCL 2.2 standard
#    define __CLPP_CL_2_2_DEPRECATED
#endif
#if __CLPP_CL_VERSION>=201 && \
        (!defined(CL_USE_DEPRECATED_OPENCL_2_0_APIS) || !defined(CL_VERSION_2_1))
/// deprecated macro for deprecated features in OpenCL 2.1 standard
#    define __CLPP_CL_2_1_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated features in OpenCL 2.1 standard
#    define __CLPP_CL_2_1_DEPRECATED
#endif
#if __CLPP_CL_VERSION>=200 && \
        (!defined(CL_USE_DEPRECATED_OPENCL_2_0_APIS) || defined(CL_VERSION_2_1)) && \
        (!defined(CL_USE_DEPRECATED_OPENCL_1_2_APIS) || !defined(CL_VERSION_2_1))
/// deprecated macro for deprecated features in OpenCL 2.0 standard
#    define __CLPP_CL_2_0_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated features in OpenCL 2.0 standard
#    define __CLPP_CL_2_0_DEPRECATED
#endif
#if __CLPP_CL_VERSION>=102 && !defined(CL_USE_DEPRECATED_OPENCL_1_1_APIS)
/// deprecated macro for deprecated features in OpenCL 1.2 standard
#    define __CLPP_CL_1_2_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated features in OpenCL 1.2 standard
#    define __CLPP_CL_1_2_DEPRECATED
#endif
#if __CLPP_CL_VERSION>=101 && !defined(CL_USE_DEPRECATED_OPENCL_1_0_APIS)
/// deprecated macro for deprecated features in OpenCL 1.1 standard
#    define __CLPP_CL_1_1_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated features in OpenCL 1.1 standard
#    define __CLPP_CL_1_1_DEPRECATED
#endif

#if __CLPP_CL_ABI_VERSION>=202 && !defined(CL_USE_DEPRECATED_OPENCL_2_1_APIS)
/// deprecated macro for deprecated features in OpenCL 2.2 standard
#    define __CLPP_CL_ABI_2_2_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated features in OpenCL 2.2 standard
#    define __CLPP_CL_ABI_2_2_DEPRECATED
#endif
#if __CLPP_CL_ABI_VERSION>=201 && \
        (!defined(CL_USE_DEPRECATED_OPENCL_2_0_APIS) || !defined(CL_VERSION_2_1))
/// deprecated macro for deprecated functions in OpenCL 2.1 standard
#    define __CLPP_CL_ABI_2_1_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated functions in OpenCL 2.1 standard
#    define __CLPP_CL_ABI_2_1_DEPRECATED
#endif
#if __CLPP_CL_ABI_VERSION>=200 && \
        (!defined(CL_USE_DEPRECATED_OPENCL_2_0_APIS) || defined(CL_VERSION_2_1)) && \
        (!defined(CL_USE_DEPRECATED_OPENCL_1_2_APIS) || !defined(CL_VERSION_2_1))
/// deprecated macro for deprecated functions in OpenCL 2.0 standard
#    define __CLPP_CL_ABI_2_0_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated functions in OpenCL 2.0 standard
#    define __CLPP_CL_ABI_2_0_DEPRECATED
#endif
#if __CLPP_CL_ABI_VERSION>=102 && !defined(CL_USE_DEPRECATED_OPENCL_1_1_APIS)
/// deprecated macro for deprecated functions in OpenCL 1.2 standard
#    define __CLPP_CL_ABI_1_2_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated functions in OpenCL 1.2 standard
#    define __CLPP_CL_ABI_1_2_DEPRECATED
#endif
#if __CLPP_CL_ABI_VERSION>=101 && !defined(CL_USE_DEPRECATED_OPENCL_1_0_APIS)
/// deprecated macro for deprecated functions in OpenCL 1.1 standard
#    define __CLPP_CL_ABI_1_1_DEPRECATED __CLPP_DEPRECATED
#else
/// deprecated macro for deprecated functions in OpenCL 1.1 standard
#    define __CLPP_CL_ABI_1_1_DEPRECATED
#endif

#ifdef __CLPP_EVENT_FROM_GLSYNC
extern "C"
{
/// type of clCreateEventFromGLsyncKHR function
typedef CL_API_ENTRY cl_event CL_API_CALL
(*clCreateEventFromGLsyncKHR_fn)(cl_context           context,
                   cl_GLsync            cl_GLsync,
                   cl_int *             errcode_ret) CL_EXT_SUFFIX__VERSION_1_1;
}
#endif

/// main namespace for clpp
/**
 * This namespace holds any class or functions definitions that can be used by programmer.
 * Almost classes represent an OpenCL object handles (for example, Device, Kernel, Program, etc).
 * These classes automatically manages an underlying OpenCL handles by using references.
 */
namespace clpp
{

/// notify callback type for context notifications
typedef void (CL_CALLBACK *ContextNotifyCallback)(const char *, const void *, size_t, void *);

/// notify callback type for program building
typedef void (CL_CALLBACK *ProgramNotifyCallback)(cl_program, void*);

/// notify callback type for memory
typedef void (CL_CALLBACK *MemoryNotifyCallback)(cl_mem, void*);

/// NativeCallback
typedef void (CL_CALLBACK *NativeCallback)(void*);

/// notify callback type for event
typedef void (CL_CALLBACK* EventCallback)(cl_event, cl_int, void*);

#if __CLPP_CL_ABI_VERSION >= 200U
/// SVM free callback (defined only if OpenCL ABI >= 2.0)
typedef void (CL_CALLBACK* SVMFreeCallback)(cl_command_queue, cl_uint, void**, void*);
#endif

#if __CLPP_CL_ABI_VERSION >= 202U
/// program release callback (defined only if OpenCL ABI >= 2.2)
typedef void (CL_CALLBACK* ProgramReleaseCallback)(cl_program, void*);
#endif

/// error class based on std::exception
class Error: public std::exception
{
private:
    cl_int error;
    std::string name;
    std::string description;
public:
    /// empty constructor
    Error() : error(0)
    { }
    
    /// constructs error from description
    explicit Error(const char* _description) : error(0), name(""), description(_description)
    { }
    
    /// constructs error from errorCode and description
    /**
     * \param _error an OpenCL error code
     * \param _description error description (by what function has been returned)
     */
    Error(cl_int _error, const char* _description) : error(_error)
    {
        char buf[20];
#ifdef _MSC_VER
        _snprintf(buf, 20, "%d", _error);
#else
        snprintf(buf, 20, "%d", _error);
#endif
        name = code_to_name(_error);

        description = "Error code: ";
        description += buf;
        description += " (";
        description += name;
        description += "), Desc: ";
        description += _description;
    }
    
    /// destructor
    virtual ~Error() __CLPP_NOEXCEPT
    { }
    
    /// what method
    const char* what() const __CLPP_NOEXCEPT
    { return (!description.empty()) ? description.c_str() : "No error!"; }

    /// converts error code to error name
    /**
     * \param _error an OpenCL error code
     */
    std::string code_to_name(cl_int _error)
    {
        std::string _name = "Unknown error code";
        if (_error == CL_SUCCESS) _name = "CL_SUCCESS";
        else if (_error == CL_DEVICE_NOT_FOUND) _name = "CL_DEVICE_NOT_FOUND";
        else if (_error == CL_DEVICE_NOT_FOUND) _name = "CL_DEVICE_NOT_FOUND";
        else if (_error == CL_DEVICE_NOT_AVAILABLE) _name = "CL_DEVICE_NOT_AVAILABLE";
        else if (_error == CL_COMPILER_NOT_AVAILABLE) _name = "CL_COMPILER_NOT_AVAILABLE";
        else if (_error == CL_MEM_OBJECT_ALLOCATION_FAILURE) _name = "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        else if (_error == CL_OUT_OF_RESOURCES) _name = "CL_OUT_OF_RESOURCES";
        else if (_error == CL_OUT_OF_HOST_MEMORY) _name = "CL_OUT_OF_HOST_MEMORY";
        else if (_error == CL_PROFILING_INFO_NOT_AVAILABLE) _name = "CL_PROFILING_INFO_NOT_AVAILABLE";
        else if (_error == CL_MEM_COPY_OVERLAP) _name = "CL_MEM_COPY_OVERLAP";
        else if (_error == CL_IMAGE_FORMAT_MISMATCH) _name = "CL_IMAGE_FORMAT_MISMATCH";
        else if (_error == CL_IMAGE_FORMAT_NOT_SUPPORTED) _name = "CL_IMAGE_FORMAT_NOT_SUPPORTED";
        else if (_error == CL_BUILD_PROGRAM_FAILURE) _name = "CL_BUILD_PROGRAM_FAILURE";
        else if (_error == CL_MAP_FAILURE) _name = "CL_MAP_FAILURE";
#if __CLPP_CL_VERSION >= 101U
        else if (_error == CL_MISALIGNED_SUB_BUFFER_OFFSET) _name = "CL_MISALIGNED_SUB_BUFFER_OFFSET";
        else if (_error == CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST) _name = "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
#endif
#if __CLPP_CL_VERSION >= 102U
        else if (_error == CL_COMPILE_PROGRAM_FAILURE) _name = "CL_COMPILE_PROGRAM_FAILURE";
        else if (_error == CL_LINKER_NOT_AVAILABLE) _name = "CL_LINKER_NOT_AVAILABLE";
        else if (_error == CL_LINK_PROGRAM_FAILURE) _name = "CL_LINK_PROGRAM_FAILURE";
        else if (_error == CL_DEVICE_PARTITION_FAILED) _name = "CL_DEVICE_PARTITION_FAILED";
        else if (_error == CL_KERNEL_ARG_INFO_NOT_AVAILABLE) _name = "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
#endif
        else if (_error == CL_INVALID_VALUE) _name = "CL_INVALID_VALUE";
        else if (_error == CL_INVALID_DEVICE_TYPE) _name = "CL_INVALID_DEVICE_TYPE";
        else if (_error == CL_INVALID_PLATFORM) _name = "CL_INVALID_PLATFORM";
        else if (_error == CL_INVALID_DEVICE) _name = "CL_INVALID_DEVICE";
        else if (_error == CL_INVALID_CONTEXT) _name = "CL_INVALID_CONTEXT";
        else if (_error == CL_INVALID_QUEUE_PROPERTIES) _name = "CL_INVALID_QUEUE_PROPERTIES";
        else if (_error == CL_INVALID_COMMAND_QUEUE) _name = "CL_INVALID_COMMAND_QUEUE";
        else if (_error == CL_INVALID_HOST_PTR) _name = "CL_INVALID_HOST_PTR";
        else if (_error == CL_INVALID_MEM_OBJECT) _name = "CL_INVALID_MEM_OBJECT";
        else if (_error == CL_INVALID_IMAGE_FORMAT_DESCRIPTOR) _name = "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        else if (_error == CL_INVALID_IMAGE_SIZE) _name = "CL_INVALID_IMAGE_SIZE";
        else if (_error == CL_INVALID_SAMPLER) _name = "CL_INVALID_SAMPLER";
        else if (_error == CL_INVALID_BINARY) _name = "CL_INVALID_BINARY";
        else if (_error == CL_INVALID_BUILD_OPTIONS) _name = "CL_INVALID_BUILD_OPTIONS";
        else if (_error == CL_INVALID_PROGRAM) _name = "CL_INVALID_PROGRAM";
        else if (_error == CL_INVALID_PROGRAM_EXECUTABLE) _name = "CL_INVALID_PROGRAM_EXECUTABLE";
        else if (_error == CL_INVALID_KERNEL_NAME) _name = "CL_INVALID_KERNEL_NAME";
        else if (_error == CL_INVALID_KERNEL_DEFINITION) _name = "CL_INVALID_KERNEL_DEFINITION";
        else if (_error == CL_INVALID_KERNEL) _name = "CL_INVALID_KERNEL";
        else if (_error == CL_INVALID_ARG_INDEX) _name = "CL_INVALID_ARG_INDEX";
        else if (_error == CL_INVALID_ARG_VALUE) _name = "CL_INVALID_ARG_VALUE";
        else if (_error == CL_INVALID_ARG_SIZE) _name = "CL_INVALID_ARG_SIZE";
        else if (_error == CL_INVALID_KERNEL_ARGS) _name = "CL_INVALID_KERNEL_ARGS";
        else if (_error == CL_INVALID_WORK_DIMENSION) _name = "CL_INVALID_WORK_DIMENSION";
        else if (_error == CL_INVALID_WORK_GROUP_SIZE) _name = "CL_INVALID_WORK_GROUP_SIZE";
        else if (_error == CL_INVALID_WORK_ITEM_SIZE) _name = "CL_INVALID_WORK_ITEM_SIZE";
        else if (_error == CL_INVALID_GLOBAL_OFFSET) _name = "CL_INVALID_GLOBAL_OFFSET";
        else if (_error == CL_INVALID_EVENT_WAIT_LIST) _name = "CL_INVALID_EVENT_WAIT_LIST";
        else if (_error == CL_INVALID_EVENT) _name = "CL_INVALID_EVENT";
        else if (_error == CL_INVALID_OPERATION) _name = "CL_INVALID_OPERATION";
        else if (_error == CL_INVALID_GL_OBJECT) _name = "CL_INVALID_GL_OBJECT";
        else if (_error == CL_INVALID_BUFFER_SIZE) _name = "CL_INVALID_BUFFER_SIZE";
        else if (_error == CL_INVALID_MIP_LEVEL) _name = "CL_INVALID_MIP_LEVEL";
        else if (_error == CL_INVALID_GLOBAL_WORK_SIZE) _name = "CL_INVALID_GLOBAL_WORK_SIZE";
#if __CLPP_CL_VERSION >= 101U
        else if (_error == CL_INVALID_PROPERTY) _name = "CL_INVALID_PROPERTY";
#endif
#if __CLPP_CL_VERSION >= 102U
        else if (_error == CL_INVALID_IMAGE_DESCRIPTOR) _name = "CL_INVALID_IMAGE_DESCRIPTOR";
        else if (_error == CL_INVALID_COMPILER_OPTIONS) _name = "CL_INVALID_COMPILER_OPTIONS";
        else if (_error == CL_INVALID_LINKER_OPTIONS) _name = "CL_INVALID_LINKER_OPTIONS";
        else if (_error == CL_INVALID_DEVICE_PARTITION_COUNT) _name = "CL_INVALID_DEVICE_PARTITION_COUNT";
#endif
#if __CLPP_CL_VERSION >= 200U
        else if (_error == CL_INVALID_PIPE_SIZE) _name = "CL_INVALID_PIPE_SIZE";
        else if (_error == CL_INVALID_DEVICE_QUEUE) _name = "CL_INVALID_DEVICE_QUEUE";
#endif
#if __CLPP_CL_VERSION >= 201U
        else if (_error == CL_INVALID_SPEC_ID) _name = "CL_INVALID_SPEC_ID";
        else if (_error == CL_MAX_SIZE_RESTRICTION_EXCEEDED) _name = "CL_MAX_SIZE_RESTRICTION_EXCEEDED";
#endif
#if defined(__CLPP_DEVICE_FISSION)
        else if (_error == CL_DEVICE_PARTITION_FAILED_EXT) _name = "CL_DEVICE_PARTITION_FAILED_EXT";
        else if (_error == CL_INVALID_PARTITION_COUNT_EXT) _name = "CL_INVALID_PARTITION_COUNT_EXT";
        else if (_error == CL_INVALID_PARTITION_NAME_EXT) _name = "CL_INVALID_PARTITION_NAME_EXT";
#endif
#if defined(__CLPP_CL_EXT)
        else if (_error == CL_PLATFORM_NOT_FOUND_KHR) _name = "CL_PLATFORM_NOT_FOUND_KHR";
#endif
#if defined(__CLPP_CL_GL)
        else if (_error == CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR) _name = "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
#endif
        return _name;
    }
    
    /// get error code
    int err() const
    { return error; }
    /// get error code
    int code() const
    { return error; }
};

/// container of 3 sizes
struct Size3
{
    /// array of 3 elements
    size_t v[3];
    
    /// empty constructor
    Size3() { v[0] = v[1] = v[2] = 0; }
    
    /// constructor with 1 value
    Size3(size_t v1)
    { v[0] = v1; v[1] = 0; v[2] = 0; }
    /// constructor with 2 values
    Size3(size_t v1, size_t v2)
    { v[0] = v1; v[1] = v2; v[2] = 0; }
    /// constructor with 3 values
    Size3(size_t v1, size_t v2, size_t v3)
    { v[0] = v1; v[1] = v2; v[2] = v3; }
    
    /// constructor with bounded array
    template<typename T>
    Size3(unsigned int n, const T* vp)
    {
        v[0] = n>=1?vp[0]:0;
        v[1] = n>=2?vp[1]:0;
        v[2] = n>=3?vp[2]:0; 
    }
    
    /// constructor with vector
    template<typename T>
    Size3(const std::vector<T>& vp)
    {
        typename std::vector<T>::const_iterator it = vp.begin();
        typename std::vector<T>::const_iterator end = vp.end();
        v[0] = (it!=end)?*it++:0;
        v[1] = (it!=end)?*it++:0;
        v[2] = (it!=end)?*it++:0;
    }
    
    /// constructor with array
    template<typename T>
    Size3(const T* vp)
    { v[0] = vp[0]; v[1] = vp[1]; v[2] = vp[2]; }
#ifdef __CLPP_CPP0X
    /// constructor with initializer list
    template<typename T>
    Size3(std::initializer_list<T> vp)
    {
        auto it = vp.begin();
        auto end = vp.end();
        v[0] = (it!=end)?*it++:0;
        v[1] = (it!=end)?*it++:0;
        v[2] = (it!=end)?*it++:0;
    }
#endif

    /// assign from vector
    template<typename T>
    Size3& operator=(const std::vector<T>& vp)
    {
        typename std::vector<T>::const_iterator it = vp.begin();
        typename std::vector<T>::const_iterator end = vp.end();
        v[0] = (it!=end)?*it++:0;
        v[1] = (it!=end)?*it++:0;
        v[2] = (it!=end)?*it++:0;
        return *this;
    }

#ifdef __CLPP_CPP0X
    /// constructor with initializer list
    template<typename T>
    Size3& operator=(std::initializer_list<T> vp)
    {
        auto it = vp.begin();
        auto end = vp.end();
        v[0] = (it!=end)?*it++:0;
        v[1] = (it!=end)?*it++:0;
        v[2] = (it!=end)?*it++:0;
        return *this;
    }
#endif
    
    /// index operator
    const size_t& operator[](size_t i) const
    { return v[i]; }
    /// index operator
    size_t& operator[](size_t i)
    { return v[i]; }
    
    /// comparison
    bool operator==(const Size3& s) const
    { return v[0]==s.v[0] && v[1]==s.v[1] && v[2]==s.v[2]; }
    /// comparison
    bool operator!=(const Size3& s) const
    { return v[0]!=s.v[0] || v[1]!=s.v[1] || v[2]!=s.v[2]; }
};

/// local object for kernel arguments
struct Local
{
    /// size of local memory
    size_t size;
    
    /// empty constructor
    Local() : size(0) { }
    /// simple constructor
    explicit Local(size_t _size) : size(_size) { }
    
    /// assignment
    Local& operator=(size_t _size)
    { size = _size; return *this; }
};

/// null type for kernel args
struct Null { };

#if __CLPP_CL_ABI_VERSION >= 200U
/// SVM Pointer argument for kernel (defined only if OpenCL ABI >= 2.0)
struct SVMPtr
{
    /// pointer
    void* ptr;
    
    /// empty constructor
    SVMPtr() : ptr(NULL) { }
    
    /// pointer constructor
    explicit SVMPtr(void* _ptr): ptr(_ptr) { }
    
    /// assignment
    SVMPtr& operator=(void* _ptr)
    { ptr = _ptr; return *this; }
};
#endif

/// implementation namespace
namespace impl
{
    /// internal retain routine
    template<typename T>
    inline void retainInternal(const T& object)
    { }
        
    /// internal release routine
    template<typename T>
    inline void releaseInternal(const T& object)
    { }
    
    /// internal retain routine
    inline void retainInternal(cl_device_id object)
    {
        if (object == NULL) return;
#if __CLPP_CL_ABI_VERSION >= 102U
        const cl_int error = clRetainDevice(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainDevice");
#elif defined(__CLPP_DEVICE_FISSION)
        static volatile clRetainDeviceEXT_fn retainDeviceEXT = NULL;
        if (retainDeviceEXT == NULL)
        {
            retainDeviceEXT = reinterpret_cast<clRetainDeviceEXT_fn>(
                        clGetExtensionFunctionAddress("clRetainDeviceEXT"));
            if (retainDeviceEXT == NULL)
                retainDeviceEXT = clRetainDeviceEXT_fn(1);
        }
        if (retainDeviceEXT <= clRetainDeviceEXT_fn(1)) return;
        const cl_int error = retainDeviceEXT(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainDeviceEXT");
#endif
    }
        
    /// internal release routine
    inline void releaseInternal(cl_device_id object)
    {
        if (object == NULL) return;
#if __CLPP_CL_ABI_VERSION >= 102U
        const cl_int error = clReleaseDevice(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseDevice");
#elif defined(__CLPP_DEVICE_FISSION)
        static volatile clReleaseDeviceEXT_fn releaseDeviceEXT = NULL;
        if (releaseDeviceEXT == NULL)
        {
            releaseDeviceEXT = reinterpret_cast<clReleaseDeviceEXT_fn>(
                        clGetExtensionFunctionAddress("clReleaseDeviceEXT"));
            if (releaseDeviceEXT == NULL)
                releaseDeviceEXT = clReleaseDeviceEXT_fn(1);
        }
        if (releaseDeviceEXT <= clReleaseDeviceEXT_fn(1)) return;
        const cl_int error = releaseDeviceEXT(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseDeviceEXT");
#endif
    }
    
    /// internal retain routine
    inline void retainInternal(cl_context object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainContext(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainContext");
    }
    
    /// internal release routine
    inline void releaseInternal(cl_context object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseContext(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseContext");
    }
    
    /// internal retain routine
    inline void retainInternal(cl_mem object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainMemObject(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainMemObject");
    }
    
    /// internal release routine
    inline void releaseInternal(cl_mem object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseMemObject(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseMemObject");
    }
    
    /// internal retain routine
    inline void retainInternal(cl_sampler object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainSampler(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainSampler");
    }
        
    /// internal release routine
    inline void releaseInternal(cl_sampler object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseSampler(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseSampler");
    }
    
    /// internal retain routine
    inline void retainInternal(cl_event object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainEvent(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainEvent");
    }
    
    /// internal release routine
    inline void releaseInternal(cl_event object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseEvent(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseEvent");
    }
    
    /// internal retain routine
    inline void retainInternal(cl_program object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainProgram(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainProgram");
    }
    
    /// internal release routine
    inline void releaseInternal(cl_program object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseProgram(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseProgram");
    }
    
    /// internal retain routine
    inline void retainInternal(cl_kernel object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainKernel(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainKernel");
    }
    
    /// internal release routine
    inline void releaseInternal(cl_kernel object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseKernel(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseKernel");
    }
    
    /// internal retain routine
    inline void retainInternal(cl_command_queue object)
    {
        if (object == NULL) return;
        const cl_int error = clRetainCommandQueue(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clRetainCommandQueue");
    }
    
    /// internal release routine
    inline void releaseInternal(cl_command_queue object)
    {
        if (object == NULL) return;
        const cl_int error = clReleaseCommandQueue(object);
        if (error != CL_SUCCESS)
            throw Error(error, "clReleaseCommandQueue");
    }
    
    /// option enums
    enum {
        PLATOPT_PLATFORM = 0,
        DEVOPT_DEVICE = 0,
        CTXOPT_CONTEXT = 0,
        MEMOPT_MEMORY = 0,
        MEMOPT_IMAGE,
        MEMOPT_PIPE,
        MEMOPT_TEXTUREGL,
        SAMPOPT_SAMPLER = 0,
        PROGOPT_PROGRAM = 0,
        PROGOPT_BUILD,
        KERNOPT_KERNEL = 0,
        KERNOPT_WORKGROUP,
        KERNOPT_ARG,
        KERNOPT_SUBGROUP,
        EVOPT_EVENT = 0,
        EVOPT_PROFILING,
        CMDQOPT_CMDQUEUE = 0,
        GLCOPT_GLCTX = 0
    };
    
    /// internal function to get info about object
    template<typename CLType, typename InfoType, int Option>
    inline void getInfoInternal(CLType obj, InfoType paramName, size_t size, void* infoRet,
                size_t* sizeRet);
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_platform_id, cl_platform_info, PLATOPT_PLATFORM>(
                cl_platform_id obj, cl_platform_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetPlatformInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetPlatformInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_device_id, cl_device_info, DEVOPT_DEVICE>(
                cl_device_id obj, cl_device_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetDeviceInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetDeviceInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_context, cl_context_info, CTXOPT_CONTEXT>(
                cl_context obj, cl_context_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetContextInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetContextInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_mem, cl_mem_info, MEMOPT_MEMORY>(
                cl_mem obj, cl_mem_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetMemObjectInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetMemObjectInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_mem, cl_image_info, MEMOPT_IMAGE>(
                cl_mem obj, cl_image_info paramName, size_t size, void* infoRet,
                size_t* sizeRet)
    {
        const cl_int error = clGetImageInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetImageInfo");
    }
    
#if __CLPP_CL_ABI_VERSION >= 200U
    /// internal function to get info about object (defined only if OpenCL ABI >= 2.0)
    template<>
    inline void getInfoInternal<cl_mem, cl_pipe_info, MEMOPT_PIPE>(
                cl_mem obj, cl_pipe_info paramName, size_t size, void* infoRet,
                size_t* sizeRet)
    {
        const cl_int error = clGetPipeInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetPipeInfo");
    }
#endif
    
#ifdef __CLPP_CL_GL
    /// internal function to get info about object (defined only if __CLPP_CL_GL)
    template<>
    inline void getInfoInternal<cl_mem, cl_gl_texture_info, MEMOPT_TEXTUREGL>(
                cl_mem obj, cl_gl_texture_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetGLTextureInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetGLTextureInfo");
    }
#endif
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_sampler, cl_sampler_info,SAMPOPT_SAMPLER>(
                cl_sampler obj, cl_sampler_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetSamplerInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetSamplerInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_program, cl_program_info, PROGOPT_PROGRAM>(
                cl_program obj, cl_program_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetProgramInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetProgramInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<std::pair<cl_program, cl_device_id>,
                cl_program_build_info, PROGOPT_BUILD>(std::pair<cl_program, cl_device_id> obj,
                cl_program_build_info paramName, size_t size, void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetProgramBuildInfo(obj.first, obj.second, paramName,
                    size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetProgramBuildInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_kernel, cl_kernel_info, KERNOPT_KERNEL>(
                cl_kernel obj, cl_kernel_info paramName, size_t size, void* infoRet,
                size_t* sizeRet)
    {
        const cl_int error = clGetKernelInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetKernelInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<std::pair<cl_kernel, cl_device_id>, cl_kernel_work_group_info,
                KERNOPT_WORKGROUP>(std::pair<cl_kernel, cl_device_id> obj,
                cl_kernel_work_group_info paramName, size_t size, void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetKernelWorkGroupInfo(obj.first, obj.second, paramName,
                        size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetKernelWorkGroupInfo");
    }
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// internal function to get info about object (defined only if OpenCL ABI >= 1.2)
    template<>
    inline void getInfoInternal<std::pair<cl_kernel, cl_uint>, cl_kernel_arg_info, KERNOPT_ARG>(
                std::pair<cl_kernel, cl_uint> obj, cl_kernel_arg_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetKernelArgInfo(obj.first, obj.second, paramName,
                        size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetKernelArgInfo");
    }
#endif

#if __CLPP_CL_ABI_VERSION >= 201U
    struct SubGroupObj
    {
        cl_kernel kernel;
        cl_device_id device;
        size_t inputSize;
        const void* input;
        
        SubGroupObj() { }
        
        SubGroupObj(cl_kernel k, cl_device_id d, size_t is, const void* i)
                : kernel(k), device(d), inputSize(is), input(i)
        { }
    };
    
    /// internal function to get info about object (defined only if OpenCL ABI >= 2.1)
    template<>
    inline void getInfoInternal<SubGroupObj, cl_kernel_sub_group_info, KERNOPT_SUBGROUP>(
                SubGroupObj obj, cl_kernel_sub_group_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetKernelSubGroupInfo(obj.kernel, obj.device, paramName,
                        obj.inputSize, obj.input, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetKernelSubGroupInfo");
    }
#endif
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_event, cl_event_info, EVOPT_EVENT>(
                cl_event obj, cl_event_info paramName, size_t size, void* infoRet,
                size_t* sizeRet)
    {
        const cl_int error = clGetEventInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetEventInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_event, cl_profiling_info, EVOPT_PROFILING>(
                cl_event obj, cl_profiling_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetEventProfilingInfo(obj, paramName, size,
                        infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetEventProfilingInfo");
    }
    
    /// internal function to get info about object
    template<>
    inline void getInfoInternal<cl_command_queue, cl_command_queue_info, CMDQOPT_CMDQUEUE>(
                cl_command_queue obj, cl_command_queue_info paramName, size_t size,
                void* infoRet, size_t* sizeRet)
    {
        const cl_int error = clGetCommandQueueInfo(obj, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetCommandQueueInfo");
    }

#ifdef __CLPP_CL_GL
    /// internal function to get info about object (defined only if __CLPP_CL_GL)
    template<>
    inline void getInfoInternal<const cl_context_properties *, cl_gl_context_info,
                GLCOPT_GLCTX>(const cl_context_properties* props,
                cl_gl_context_info paramName, size_t size, void* infoRet, size_t* sizeRet)
    {
#   if __CLPP_CL_ABI_VERSION >= 102U
        /* slow but sure */
        cl_platform_id platform = NULL;
        if (props != NULL)
            for (const cl_context_properties* p = props; *p != 0; p+=2)
                if (*p == CL_CONTEXT_PLATFORM) // get platform
                    platform = cl_platform_id(p[1]);
        if (platform == NULL)
            throw Error("Null platform for clGetExtensionFunctionAddressForPlatform");
        clGetGLContextInfoKHR_fn getGLContextInfoKHR =
            reinterpret_cast<clGetGLContextInfoKHR_fn>(
                clGetExtensionFunctionAddressForPlatform(platform, "clGetGLContextInfoKHR"));
#   else
        static volatile clGetGLContextInfoKHR_fn getGLContextInfoKHR = NULL;
        if (getGLContextInfoKHR == NULL)
        {
            getGLContextInfoKHR = reinterpret_cast<clGetGLContextInfoKHR_fn>(
                    clGetExtensionFunctionAddress("clGetGLContextInfoKHR"));
            if (getGLContextInfoKHR == NULL)
                getGLContextInfoKHR = clGetGLContextInfoKHR_fn(1);
        }
#   endif
        if (getGLContextInfoKHR <= clGetGLContextInfoKHR_fn(1))
            throw Error("Unsupported clGetGLContextInfoKHR");
        const cl_int error = getGLContextInfoKHR(props, paramName, size, infoRet, sizeRet);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetGLContextInfoKHR");
    }
#endif
    
    /// class that holds static methods to getting info
    template<typename CLType, typename InfoType, typename T, int Option = 0>
    struct GetInfoHelper
    {
        /// get info
        static T getInfo(CLType object, InfoType paramName)
        {
            T value;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, sizeof(T),
                        &value, NULL);
            return value;
        }
        
        /// get info
        static void getInfo(CLType object, InfoType paramName, T& value)
        {
            getInfoInternal<CLType, InfoType, Option>(object, paramName, sizeof(T),
                        &value, NULL);
        }
        
        /// get info as vector
        static std::vector<T> getInfoVector(CLType object, InfoType paramName)
        {
            size_t size;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, 0, NULL, &size);
            const size_t outNum = size / sizeof(T);
            std::vector<T> vector(outNum);
            getInfoInternal<CLType, InfoType, Option>(object, paramName, outNum*sizeof(T),
                        &(vector[0]), NULL);
            return vector;
        }
    };
    
    /// get info helper that handles reference counting (retain/release)
    template<typename CLType, typename InfoType, typename T, int Option = 0>
    struct GetInfoRefHelper
    {
        /// internal OpenCL type
        typedef typename T::cl_type cl_type;
        
        /// get info
        static T getInfo(CLType object, InfoType paramName)
        {
            T value;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, sizeof(T),
                        &value, NULL);
            retainInternal((cl_type)value);
            return value;
        }
        
        /// get info
        static void getInfo(CLType object, InfoType paramName, T& value)
        {
            T tmpValue;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, sizeof(T),
                        &tmpValue, NULL);
            value = tmpValue;
            retainInternal((cl_type)value);
        }
        
        /// get info as vector
        static std::vector<T> getInfoVector(CLType object, InfoType paramName)
        {
            size_t outNum;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, 0, NULL, &outNum);
            outNum /= sizeof(T);
            std::vector<T> vector(outNum);
            if (outNum == 0) return vector;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, outNum*sizeof(T),
                        &(vector[0]), NULL);
            for (size_t i = 0; i < vector.size(); i++)
                retainInternal((cl_type)vector[i]);
            return vector;
        }
    };
    
    /// class that holds statics method to getting string infos
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, std::string, Option>
    {
        /// get info
        static std::string getInfo(CLType object, InfoType paramName)
        {
            size_t infoSize;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, 0, NULL, &infoSize);
            std::vector<char> cvalue(infoSize);
            getInfoInternal<CLType, InfoType, Option>(object, paramName, infoSize,
                        &cvalue[0], NULL);
            return std::string(&cvalue[0]);
        }
        
        /// get info
        static void getInfo(CLType object, InfoType paramName, std::string& value)
        { value = getInfo(object, paramName); }
    };
    
    /// class that holds statics method to getting string infos
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, bool, Option>
    {
        /// get info
        static bool getInfo(CLType object, InfoType paramName)
        {
            cl_bool value;
            getInfoInternal<CLType, InfoType, Option>(object, paramName, sizeof(cl_bool),
                    &value, NULL);
            return value;
        }
        
        /// get info
        static void getInfo(CLType object, InfoType paramName, bool& value)
        { value = getInfo(object, paramName); }
    };
}

#ifdef __CLPP_CL_GL
/// get GL context info
template<typename T>
inline T getGLContextInfo(const cl_context_properties* props, cl_gl_context_info paramName)
{ return impl::GetInfoHelper<const cl_context_properties*, cl_gl_context_info, T>::getInfo(
            props, paramName); }

/// get GL context info
template<typename T>
inline void getGLContextInfo(const cl_context_properties* props,
            cl_gl_context_info paramName, T& value)
{ impl::GetInfoHelper<const cl_context_properties*, cl_gl_context_info, T>::getInfo(
            props, paramName, value); }

/// get GL context info as vector
template<typename T>
inline std::vector<T> getGLContextInfoVector(const cl_context_properties* props,
            cl_gl_context_info paramName)
{ return impl::GetInfoHelper<const cl_context_properties*, cl_gl_context_info, T>
            ::getInfoVector(props, paramName); }
#endif

class Platform;

/// OpenCL Device wrapper
/** This class holds a OpenCL device handle. */
class Device
{
private:
    cl_device_id device;
public:
    /// internal OpenCL type
    typedef cl_device_id cl_type;
    
    /// empty constructor
    Device() : device(NULL)
    { }
    
    /// copy-constructor
    Device(const Device& _device) : device(_device.device)
    { impl::retainInternal(device); }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Device(Device&& _device) noexcept
            : device(_device.device)
    { _device.device = NULL; }
#endif
    
    /// copy-assignment
    Device& operator=(const Device& _device)
    {
        if (device == _device.device)
            return *this;
        impl::releaseInternal(device);
        device = _device.device;
        impl::retainInternal(device);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Device& operator=(Device&& _device)
    {
        impl::releaseInternal(device);
        device = _device.device;
        _device.device = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Device()
    { impl::releaseInternal(device); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(device); device = NULL; }
    
    /// logical negation
    bool operator!() const
    { return device==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return device!=NULL; }
    
    /// get (convert) cl_device_id
    cl_device_id operator()() const
    { return device; }
    
    /// convert to cl_device_id
    operator cl_device_id() const
    { return device; }
    
    /// comparison operator
    bool operator==(const Device& d2) const
    { return device==d2.device; }
    /// comparison operator
    bool operator!=(const Device& d2) const
    { return device!=d2.device; }
    
    /// create device from cl object
    static Device from(cl_device_id clobj, bool retain = true)
    {
        Device device;
        device.device = clobj;
        if (retain) impl::retainInternal(clobj);
        return device;
    }
    
    /// get device info
    template<typename T>
    T getInfo(cl_device_info paramName) const
    { return impl::GetInfoHelper<cl_device_id, cl_device_info, T>::getInfo(
                device, paramName); }
    
    /// get device info
    template<typename T>
    void getInfo(cl_device_info paramName, T& value) const
    { impl::GetInfoHelper<cl_device_id, cl_device_info, T>::getInfo(
                device, paramName, value); }
    
    /// get device info
    std::string getInfoString(cl_device_info paramName) const
    { return impl::GetInfoHelper<cl_device_id, cl_device_info, std::string>::getInfo(
                device, paramName); }
    
    /// get device info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_device_info paramName) const
    { return impl::GetInfoHelper<cl_device_id, cl_device_info, T>::getInfoVector(
                device, paramName); }
    
    /// get device type
    cl_device_type getType() const
    { return getInfo<cl_device_type>(CL_DEVICE_TYPE); }
    
    /// get device vendor id
    cl_uint getVendorId() const
    { return getInfo<cl_uint>(CL_DEVICE_VENDOR_ID); }
    
    /// get maximum compute units for device
    cl_uint getMaxComputeUnits() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS); }
    
    /// get maximum work item dimensions
    cl_uint getMaxWorkItemDims() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS); }
    
    /// get maximum work item sizes
    Size3 getMaxWorkItemSizes() const
    { return getInfo<Size3>(CL_DEVICE_MAX_WORK_ITEM_SIZES); }
    
    /// get maximum work group size
    size_t getMaxWorkGroupSize() const
    { return getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE); }
    
    /// get preferred vector width for char type
    cl_uint getPreferredVectorWidthChar() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR); }
    /// get preferred vector width for short type
    cl_uint getPreferredVectorWidthShort() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT); }
    /// get preferred vector width for int type
    cl_uint getPreferredVectorWidthInt() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT); }
    /// get preferred vector width for long type
    cl_uint getPreferredVectorWidthLong() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG); }
    /// get preferred vector width for float type
    cl_uint getPreferredVectorWidthFloat() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT); }
    /// get preferred vector width for double type
    cl_uint getPreferredVectorWidthDouble() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE); }
#if __CLPP_CL_VERSION >= 101U
    /// get preferred vector width for half type (defined only if OpenCL >= 1.1)
    cl_uint getPreferredVectorWidthHalf() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF); }
#endif
#if __CLPP_CL_VERSION >= 102U
    /// get native vector width for char type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthChar() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR); }
    /// get native vector width for short type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthShort() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT); }
    /// get native vector width for int type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthInt() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT); }
    /// get native vector width for long type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthLong() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG); }
    /// get native vector width for float type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthFloat() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT); }
    /// get native vector width for double type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthDouble() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE); }
    /// get native vector width for half type (defined only if OpenCL >= 1.2)
    cl_uint getNativeVectorWidthHalf() const
    { return getInfo<cl_uint>(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF); }
#endif
    
    /// get maximum clock frequency for device
    cl_uint getMaxClockFrequency() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY); }
    
    /// get number of bits for address (address space size)
    cl_uint getAddressBits() const
    { return getInfo<cl_uint>(CL_DEVICE_ADDRESS_BITS); }
    
    /// get maximum allocation size for device
    cl_ulong getMaxMemAllocSize() const
    { return getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE); }
    
    /// check whether device supports OpenCL images
    bool isImageSupport() const
    { return getInfo<cl_bool>(CL_DEVICE_IMAGE_SUPPORT); }
    
    /// get maximum number of arguments of read only images
    cl_uint getMaxReadImageArgs() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_READ_IMAGE_ARGS); }
    
    /// get maximum number of arguments of write only images
    cl_uint getMaxWriteImageArgs() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_WRITE_IMAGE_ARGS); }
    
#if __CLPP_CL_VERSION >= 200U
    /// get maximum number of arguments of read-write images (defined only if OpenCL >= 2.0)
    cl_uint getMaxReadWriteImageArgs() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS); }
#endif
    
    /// get maximum width for 2D image in pixels
    size_t getImage2DMaxWidth() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_WIDTH); }
    
    /// get maximum height for 2D image in pixels
    size_t getImage2DMaxHeight() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_HEIGHT); }
    
    /// get maximum sizes (width,height) for 2D image in pixels
    /**
     * \param width output max width
     * \param height output max height
     */
    void getImage2DMaxSizes(size_t& width, size_t& height) const
    {
        getInfo(CL_DEVICE_IMAGE2D_MAX_WIDTH, width);
        getInfo(CL_DEVICE_IMAGE2D_MAX_HEIGHT, height);
    }
    
    /// get maximum sizes (width,height) for 2D image in pixels
    Size3 getImage2DMaxSizes() const
    {
        Size3 sizes;
        getInfo(CL_DEVICE_IMAGE2D_MAX_WIDTH, sizes[0]);
        getInfo(CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizes[1]);
        return sizes;
    }
    
    /// get maximum width for 3D image in pixels
    size_t getImage3DMaxWidth() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_WIDTH); }
    
    /// get maximum height for 3D image in pixels
    size_t getImage3DMaxHeight() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_HEIGHT); }
    
    /// get maximum height for 3D image in pixels
    size_t getImage3DMaxDepth() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_DEPTH); }
    
    /// get maximum sizes (width,height,depth) for 3D image in pixels
    /**
     * \param width output max width
     * \param height output max height
     * \param depth output max depth
     */
    void getImage3DMaxSizes(size_t& width, size_t& height, size_t& depth) const
    {
        getInfo(CL_DEVICE_IMAGE3D_MAX_WIDTH, width);
        getInfo(CL_DEVICE_IMAGE3D_MAX_HEIGHT, height);
        getInfo(CL_DEVICE_IMAGE3D_MAX_DEPTH, depth);
    }
    
    /// get maximum sizes (width,height,depth) for 3D image in pixels
    Size3 getImage3DMaxSizes() const
    {
        Size3 sizes;
        getInfo(CL_DEVICE_IMAGE3D_MAX_WIDTH, sizes[0]);
        getInfo(CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizes[1]);
        getInfo(CL_DEVICE_IMAGE3D_MAX_DEPTH, sizes[2]);
        return sizes;
    }
    
#if __CLPP_CL_VERSION >= 102U
    /// get maximum buffer size for image buffers in pixels (defined only if OpenCL >= 1.2)
    size_t getImageMaxBufferSize() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE_MAX_BUFFER_SIZE); }
    /// get maximum number of images in image array (defined only if OpenCL >= 1.2)
    size_t getImageMaxArraySize() const
    { return getInfo<size_t>(CL_DEVICE_IMAGE_MAX_ARRAY_SIZE); }
    
    /// get image row pitch alignment size in pixels (defined only if OpenCL >= 1.2)
    cl_uint getImagePitchAlign() const
    { return getInfo<cl_uint>(CL_DEVICE_IMAGE_PITCH_ALIGNMENT); }
    
    /// get image base address alignment size in pixels (defined only if OpenCL >= 1.2)
    cl_uint getImageBaseAddrAlign() const
    { return getInfo<cl_uint>(CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT); }
#endif

#if __CLPP_CL_VERSION >= 200U
    /// get maximum number of pipe in kernel arguments (defined only if OpenCL >= 2.0)
    cl_uint getMaxPipeArgs() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_PIPE_ARGS); }
    
    /// get maximum number of active pipe reservations (defined only if OpenCL >= 2.0)
    cl_uint getPipeMaxActiveReservations() const
    { return getInfo<cl_uint>(CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS); }
    
    /// get maximum pipe packet size in bytes (defined only if OpenCL >= 2.0)
    cl_uint getPipeMaxPacketSize() const
    { return getInfo<cl_uint>(CL_DEVICE_PIPE_MAX_PACKET_SIZE); }
#endif
    
    /// get base address alignment in bits
    cl_uint getMemBaseAddrAlign() const
    { return getInfo<cl_uint>(CL_DEVICE_MEM_BASE_ADDR_ALIGN); }
    
    /// get minimum data type alignment size in bytes (deprecated in OpenCL >= 1.2)
     __CLPP_CL_1_2_DEPRECATED cl_uint getMinDataTypeAlignSize() const
    { return getInfo<cl_uint>(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE); }
    
    /// get maximum samplers that can be used by kernel
    cl_uint getMaxSamplers() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_SAMPLERS); }
    
    /// get maximum parameter size for device in bytes
    size_t getMaxParameterSize() const
    { return getInfo<size_t>(CL_DEVICE_MAX_PARAMETER_SIZE); }
    
    /// get single precision floating point configuration
    cl_device_fp_config getSingleFPConfig() const
    { return getInfo<cl_device_fp_config>(CL_DEVICE_SINGLE_FP_CONFIG); }
    
#if __CLPP_CL_VERSION >= 102U || defined(__CLPP_CL_EXT)
    /// get double precision floating point configuration (defined if OpenCL >= 1.2 or _CLPP_CL_EXIT)
    cl_device_fp_config getDoubleFPConfig() const
    { return getInfo<cl_device_fp_config>(CL_DEVICE_DOUBLE_FP_CONFIG); }
#endif
#ifdef __CLPP_CL_EXT
    /// get half precision floating point configuration (defined only if __CLPP_CL_EXT)
    cl_device_fp_config getHalfFPConfig() const
    { return getInfo<cl_device_fp_config>(CL_DEVICE_HALF_FP_CONFIG); }
#endif
    
    /// get cache type for global memory
    cl_device_mem_cache_type getGlobalMemCacheType() const
    { return getInfo<cl_device_mem_cache_type>(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE); }
    
    /// get cache line size for global memory in bytes
    cl_uint getGlobalMemCacheLineSize() const
    { return getInfo<cl_uint>(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE); }
    
    /// get cache size for global memory in bytes
    cl_ulong getGlobalMemCacheSize() const
    { return getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE); }
    
    /// get current global memory size for device in bytes
    cl_ulong getGlobalMemSize() const
    { return getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_SIZE); }
    
    /// get maximum constant buffer size in bytes
    cl_ulong getMaxConstantBufferSize() const
    { return getInfo<cl_ulong>(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE); }
    
    /// get maximum number of constant arguments
    cl_uint getMaxConstantArgs() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_CONSTANT_ARGS); }
    
#if __CLPP_CL_VERSION >= 200U
    /// get maximum global variable size in bytes (defined only if OpenCL >= 2.0)
    size_t getMaxGlobalVariableSize() const
    { return getInfo<size_t>(CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE); }
    
    ///get maximum preferred total size in bytes of all program variables (defined only if OpenCL >= 2.0)
    size_t getGlobalVariablePreferredTotalSize() const
    { return getInfo<size_t>(CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE); }
#endif
    
    /// get local memory type
    cl_device_local_mem_type getLocalMemType() const
    { return getInfo<cl_device_local_mem_type>(CL_DEVICE_LOCAL_MEM_TYPE); }
    
    /// get local memory size
    cl_ulong getLocalMemSize() const
    { return getInfo<cl_ulong>(CL_DEVICE_LOCAL_MEM_SIZE); }
    
    /// check whether device supports error correction
    bool isErrorCorrectionSupport() const
    { return getInfo<cl_bool>(CL_DEVICE_ERROR_CORRECTION_SUPPORT); }
#if __CLPP_CL_VERSION >= 101U
    /// check whether device supports host unified memory (defined only if OpenCL >= 1.1) (deprecated in OpenCL >= 2.0)
     __CLPP_CL_2_0_DEPRECATED bool isHostUnifiedMemory() const
    { return getInfo<cl_bool>(CL_DEVICE_HOST_UNIFIED_MEMORY); }
#endif
    
    /// get profiling timer resolution of device
    size_t getProfilingTimerResolution() const
    { return getInfo<size_t>(CL_DEVICE_PROFILING_TIMER_RESOLUTION); }
    
    /// check whether device is little-endian
    bool isEndianLittle() const
    { return getInfo<cl_bool>(CL_DEVICE_ENDIAN_LITTLE); }
    
    /// check whether device is available
    bool isAvailable() const
    { return getInfo<cl_bool>(CL_DEVICE_AVAILABLE); }
    
    /// check whether compiler is available for device
    bool isCompilerAvailable() const
    { return getInfo<cl_bool>(CL_DEVICE_COMPILER_AVAILABLE); }
    
#if __CLPP_CL_VERSION >= 102U
    /// check whether linker is available for device (defined only if OpenCL >= 1.2)
    bool isLinkerAvailable() const
    { return getInfo<cl_bool>(CL_DEVICE_LINKER_AVAILABLE); }
#endif
    
    /// get device execution capabilities
    cl_device_exec_capabilities getExecCapabilities() const
    { return getInfo<cl_device_exec_capabilities>(CL_DEVICE_EXECUTION_CAPABILITIES); }
    
    /// get supported queue properties (deprecated in OpenCL >= 2.0)
     __CLPP_CL_2_0_DEPRECATED cl_command_queue_properties getQueueProperties() const
    { return getInfo<cl_command_queue_properties>(CL_DEVICE_QUEUE_PROPERTIES); }
    
#if __CLPP_CL_VERSION >= 200U
    /// get supported queue properties on the host (defined only if OpenCL >= 2.0)
    cl_command_queue_properties getQueueOnHostProperties() const
    { return getInfo<cl_command_queue_properties>(CL_DEVICE_QUEUE_ON_HOST_PROPERTIES); }
    
    /// get supported queue properties on the device (defined only if OpenCL >= 2.0)
    cl_command_queue_properties getQueueOnDeviceProperties() const
    { return getInfo<cl_command_queue_properties>(CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES); }
    
    /// get preferred queue size on device in bytes (defined only if OpenCL >= 2.0)
    cl_uint getQueueOnDevicePreferredSize() const
    { return getInfo<cl_uint>(CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE); }
    
    /// get maximum size for queue on device in bytes (defined only if OpenCL >= 2.0)
    cl_uint getQueueOnDeviceMaxSize() const
    { return getInfo<cl_uint>(CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE); }
    
    /// get maximum number of queues on device (defined only if OpenCL >= 2.0)
    cl_uint getMaxOnDevicesQueues() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_ON_DEVICE_QUEUES); }
    
    /// get maximum number of events on device (defined only if OpenCL >= 2.0)
    cl_uint getMaxOnDevicesEvents() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_ON_DEVICE_EVENTS); }
#endif
    
#if __CLPP_CL_VERSION >= 102U
    /// get bult-in kernels available for device (defined only if OpenCL >= 1.2)
    std::string getBuilInKernels() const
    { return getInfoString(CL_DEVICE_BUILT_IN_KERNELS); }
#endif
    
    /// get device platform
    Platform getPlatform() const;
    
    /// get device name
    std::string getName() const
    { return getInfoString(CL_DEVICE_NAME); }
    
    /// get device vendor
    std::string getVendor() const
    { return getInfoString(CL_DEVICE_VENDOR); }
    
    /// get device profile
    std::string getProfile() const
    { return getInfoString(CL_DEVICE_PROFILE); }
    
    /// get device driver version
    std::string getDriverVersion() const
    { return getInfoString(CL_DRIVER_VERSION); }
    
    /// get device version
    std::string getVersion() const
    { return getInfoString(CL_DEVICE_VERSION); }
    
#if __CLPP_CL_VERSION >= 101U
    /// get OpenCL C version supported by device (defined only if OpenCL >= 1.1)
    std::string getOpenCLCVersion() const
    { return getInfoString(CL_DEVICE_OPENCL_C_VERSION); }
#endif

    /// get device extensions
    std::string getExtensions() const
    { return getInfoString(CL_DEVICE_EXTENSIONS); }
    
#if __CLPP_CL_VERSION >= 102U
    /// get printf buffer size (defined only if OpenCL >= 1.2)
    size_t getPrintfBufferSize() const
    { return getInfo<size_t>(CL_DEVICE_PRINTF_BUFFER_SIZE); }
    
    /// check whether preferred interop user sync (defined only if OpenCL >= 1.2)
    bool isPreferredInterOpUserSync() const
    { return getInfo<cl_bool>(CL_DEVICE_PREFERRED_INTEROP_USER_SYNC); }
    
    /// get parent device (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    Device getParentDevice() const
    { return getInfo<Device>(CL_DEVICE_PARENT_DEVICE); }
    
    /// get maximum sub devices when device is partitioned (defined only if OpenCL >= 1.2)
    cl_uint getPartitionMaxSubDevices() const
    { return getInfo<cl_uint>(CL_DEVICE_PARTITION_MAX_SUB_DEVICES); }
    
    /// get list of partition properties for device (defined only if OpenCL >= 1.2)
    std::vector<cl_device_partition_property> getPartitionProperties() const
    { return getInfoVector<cl_device_partition_property>(CL_DEVICE_PARTITION_PROPERTIES); }
    
    /// get affinity domains supported by device (defined only if OpenCL >= 1.2)
    cl_device_affinity_domain getPartitionAffinityDomain() const
    { return getInfo<cl_device_affinity_domain>(CL_DEVICE_PARTITION_AFFINITY_DOMAIN); }
    
    /// get list of partition properties for device (defined only if OpenCL >= 1.2)
    std::vector<cl_device_partition_property> getPartitionType() const
    { return getInfoVector<cl_device_partition_property>(CL_DEVICE_PARTITION_TYPE); }
    
    /// returns reference count for this device (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_DEVICE_REFERENCE_COUNT); }
#endif

#if __CLPP_CL_VERSION >= 201U
    /// get IL version supported by device (defined only if OpenCL >= 2.1)
    std::string getILVersion() const
    { return getInfoString(CL_DEVICE_IL_VERSION); }
    
    /// get max number of subgroups
    cl_uint getMaxNumSubGroups() const
    { return getInfo<cl_uint>(CL_DEVICE_MAX_NUM_SUB_GROUPS); }
    
    /// is if this device supports independent forward progress of sub- groups
    bool isSubGroupIndependentForwardProgress() const
    { return getInfo<cl_bool>(CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS); }
#endif

#if defined(__CLPP_DEVICE_FISSION) || defined(__CLPP_DOXYGEN)
    /// get parent device (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    Device getParentDevice() const
    { return getInfo<Device>(CL_DEVICE_PARENT_DEVICE_EXT); }
    
    /// get partition types supported by device (defined if __CLPP_DEVICE_FISSION)
    std::vector<cl_device_partition_property_ext> getPartitionTypes() const
    { return getInfoVector<cl_device_partition_property_ext>(CL_DEVICE_PARTITION_TYPES_EXT); }
    
    /// get affinity domains supported by device (defined if __CLPP_DEVICE_FISSION)
    std::vector<cl_device_partition_property_ext> getAffinityDomains() const
    { return getInfoVector<cl_device_partition_property_ext>(CL_DEVICE_AFFINITY_DOMAINS_EXT); }
    
    /// get partition style supported by device (defined if __CLPP_DEVICE_FISSION)
    std::vector<cl_device_partition_property_ext> getPartitionStyle() const
    { return getInfoVector<cl_device_partition_property_ext>(CL_DEVICE_PARTITION_STYLE_EXT); }
    
    /// returns reference count for this device (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_DEVICE_REFERENCE_COUNT_EXT); }
#endif

#if __CLPP_CL_VERSION >= 200U
    /// get SVM capabilities (defined only if OpenCL >= 2.0)
    cl_device_svm_capabilities getSVMCapabilities() const
    { return getInfo<cl_device_svm_capabilities>(CL_DEVICE_SVM_CAPABILITIES); }
    
    /// get preferred atomic alignment for fine-grain SVM atomics in bytes (defined only if OpenCL >= 2.0)
    cl_uint getPreferredPlatformAtomicAlign() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT); }
    
    /// get preferred atomic alignment for atomics to global memory in bytes (defined only if OpenCL >= 2.0)
    cl_uint getPreferredGlobalAtomicAlign() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT); }
    
    /// get preferred atomic alignment for atomics to local memory in bytes (defined only if OpenCL >= 2.0)
    cl_uint getPreferredLocalAtomicAlign() const
    { return getInfo<cl_uint>(CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT); }
#endif
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// create sub devices (defined only if OpenCL ABI >= 1.2)
    std::vector<Device> createSubDevices(const cl_device_partition_property* properties) const
    {
        cl_uint numSubDevs;
        cl_int error = clCreateSubDevices(device, properties, 0, NULL, &numSubDevs);
        if (error != CL_SUCCESS)
            throw Error(error, "clCreateSubDevices");
        std::vector<Device> outDevices(numSubDevs);
        error = clCreateSubDevices(device, properties, numSubDevs,
                            &(outDevices[0].device), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clCreateSubDevices");
        return outDevices;
    }
    
    /// create subdevices equally (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevicesEqually(cl_uint computeUnits) const
    {
        const cl_device_partition_property props[3] = {
                CL_DEVICE_PARTITION_EQUALLY, cl_device_partition_property(computeUnits), 0 };
        return createSubDevices(props);
    }
    
private:
    static std::vector<cl_device_partition_property> propsByCounts(size_t listSize,
            const cl_uint* computeUnitsList)
    {
        std::vector<cl_device_partition_property> props(listSize+3);
        props[0] = CL_DEVICE_PARTITION_BY_COUNTS;
        for (size_t i = 0; i < listSize; i++)
            props[i+1] = computeUnitsList[i];
        props[listSize+1] = CL_DEVICE_PARTITION_BY_COUNTS_LIST_END;
        props[listSize+2] = 0;
        return props;
    }
public:
    
    /// create subdevices by counts (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    /**
     * \param listSize list size in elems
     * \param computeUnitsList computeUnits per device list
     * \return number of output devices
     */
    std::vector<Device> createSubDevicesByCounts(size_t listSize,
            const cl_uint* computeUnitsList) const
    {
        std::vector<cl_device_partition_property> props = propsByCounts(
                    listSize, computeUnitsList);
        return createSubDevices(&props[0]);
    }
    
    /// create subdevices by affinity domain (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevicesByAffinityDomain(
                cl_device_partition_property affinityDomain) const
    {
        const cl_device_partition_property props[3] = {
                CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN, affinityDomain, 0 };
        return createSubDevices(props);
    }
#endif
#if defined(__CLPP_DEVICE_FISSION) || defined(__CLPP_DOXYGEN)
private:
    cl_int createSubDevicesInternal(const cl_device_partition_property_ext* properties,
                cl_uint maxDevices, cl_device_id* outDevices, cl_uint* numDevices) const
    {
        static volatile clCreateSubDevicesEXT_fn createSubDevicesEXT = NULL;
        if (createSubDevicesEXT == NULL)
        {
            createSubDevicesEXT = reinterpret_cast<clCreateSubDevicesEXT_fn>(
                    clGetExtensionFunctionAddress("clCreateSubDevicesEXT"));
            if (createSubDevicesEXT == NULL)
                createSubDevicesEXT = clCreateSubDevicesEXT_fn(1);
        }
        if (createSubDevicesEXT <= clCreateSubDevicesEXT_fn(1))
            throw Error("Unsupported clCreateSubDevicesEXT");
        return createSubDevicesEXT(device, properties, maxDevices, outDevices, numDevices);
    }
public:
    /// create subdevices (defined only if __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevices(const cl_device_partition_property_ext* properties) const
    {
        cl_uint numSubDevs;
        cl_int error = createSubDevicesInternal(properties, 0, NULL, &numSubDevs);
        if (error != CL_SUCCESS)
            throw Error(error, "clCreateSubDevicesEXT");
        std::vector<Device> outDevices(numSubDevs);
        error = createSubDevicesInternal(properties, numSubDevs, &(outDevices[0].device), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clCreateSubDevicesEXT");
        return outDevices;
    }
    
    /// create subdevices equally (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevicesEqually(cl_uint computeUnits) const
    {
        const cl_device_partition_property_ext props[3] = {
                CL_DEVICE_PARTITION_EQUALLY_EXT,
                cl_device_partition_property_ext(computeUnits), CL_PROPERTIES_LIST_END_EXT };
        return createSubDevices(props);
    }
private:
    static std::vector<cl_device_partition_property_ext> propsByCounts(size_t listSize,
            const cl_uint* computeUnitsList)
    {
        std::vector<cl_device_partition_property_ext> props(listSize+3);
        props[0] = CL_DEVICE_PARTITION_BY_COUNTS_EXT;
        for (size_t i = 0; i < listSize; i++)
            props[i+1] = computeUnitsList[i];
        props[listSize+1] = CL_PARTITION_BY_COUNTS_LIST_END_EXT;
        props[listSize+2] = CL_PROPERTIES_LIST_END_EXT;
        return props;
    }
    
    static std::vector<cl_device_partition_property_ext> propsByNames(size_t listSize,
            const cl_uint* namesList)
    {
        std::vector<cl_device_partition_property_ext> props(listSize+3);
        props[0] = CL_DEVICE_PARTITION_BY_NAMES_EXT;
        for (size_t i = 0; i < listSize; i++)
            props[i+1] = namesList[i];
        props[listSize+1] = CL_PARTITION_BY_NAMES_LIST_END_EXT;
        props[listSize+2] = CL_PROPERTIES_LIST_END_EXT;
        return props;
    }
public:

    /// create subdevices by counts (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevicesByCounts(size_t listSize,
            const cl_uint* computeUnitsList) const
    {
        std::vector<cl_device_partition_property_ext> props = propsByCounts(
                listSize, computeUnitsList);
        return createSubDevices(&props[0]);
    }
    
    /// create subdevices by names (defined if __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevicesByNames(size_t listSize,
            const cl_uint* namesList) const
    {
        std::vector<cl_device_partition_property_ext> props = propsByNames(
                listSize, namesList);
        return createSubDevices(&props[0]);
    }
    
    /// create subdevices by affinity domain (defined if OpenCL >= 1.2 or __CLPP_DEVICE_FISSION)
    std::vector<Device> createSubDevicesByAffinityDomain(
                cl_device_partition_property_ext affinityDomain) const
    {
        const cl_device_partition_property_ext props[3] = {
                CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN_EXT, affinityDomain,
                CL_PROPERTIES_LIST_END_EXT };
        return createSubDevices(props);
    }
#endif

#if __CLPP_CL_ABI_VERSION >= 201U
    void getDeviceAndHostTimer(cl_ulong& deviceTimer, cl_ulong& hostTimer) const
    {
        const cl_int error = clGetDeviceAndHostTimer(device, &deviceTimer, &hostTimer);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetDeviceAndHostTimer");
    }
    
    cl_ulong getHostTimer() const
    {
        cl_ulong t;
        const cl_int error = clGetHostTimer(device, &t);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetHostTimer");
        return t;
    }
#endif
};

#if __CLPP_CL_ABI_VERSION >= 102U
namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Device, Option>:
            GetInfoRefHelper<CLType, InfoType, Device, Option>
    { };
}
#endif

#if __CLPP_CL_ABI_VERSION <= 101U || defined(CL_USE_DEPRECATED_OPENCL_1_1_APIS)
/// get function address
__CLPP_CL_1_2_DEPRECATED void* getExtensionFunctionAddress(const char* funcname)
{ return getExtensionFunctionAddress(funcname); }
#endif

/// OpenCL Platform object wrapper
class Platform
{
private:
    cl_platform_id platform;
public:
    /// internal OpenCL type
    typedef cl_platform_id cl_type;
    
    /// empty constructor
    Platform() : platform(NULL)
    { }
    
    /// get (convert) to cl_platform_id
    cl_platform_id operator()() const
    { return platform; }
    
    /// convert to cl_platform_id
    operator cl_platform_id() const
    { return platform; }
    
    /// logical negation
    bool operator!() const
    { return platform==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return platform!=NULL; }
    
    /// comparison operator
    bool operator==(const Platform& p2) const
    { return platform==p2.platform; }
    /// comparison operator
    bool operator!=(const Platform& p2) const
    { return platform!=p2.platform; }
    
    /// create platform from cl object
    static Platform from(cl_platform_id clobj)
    {
        Platform platform;
        platform.platform = clobj;
        return platform;
    }
    
    /// get all platforms
    static std::vector<Platform> get()
    {
        cl_uint numPlatforms;
        cl_int error = clGetPlatformIDs(0, NULL, &numPlatforms);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetPlatformIDs");
        std::vector<Platform> platforms(numPlatforms);
        error = clGetPlatformIDs(numPlatforms, &(platforms[0].platform), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetPlatformIDs");
        return platforms;
    }
    
    /// get all platforms
    static cl_uint get(cl_uint maxNumPlatforms, Platform* platforms)
    {
        cl_uint outNum;
        const cl_int error = clGetPlatformIDs(maxNumPlatforms,
                            &(platforms[0].platform), &outNum);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetPlatformIDs");
        return outNum;
    }
    
    /// get platform info
    template<typename T>
    T getInfo(cl_platform_info paramName) const
    { return impl::GetInfoHelper<cl_platform_id, cl_platform_info, T>::getInfo(
                platform, paramName); }
    
    /// get platform info
    template<typename T>
    void getInfo(cl_platform_info paramName, T& value) const
    { impl::GetInfoHelper<cl_platform_id, cl_platform_info, T>::getInfo(
                platform, paramName, value); }
    
    /// get platform info
    std::string getInfoString(cl_platform_info paramName) const
    { return impl::GetInfoHelper<cl_platform_id, cl_platform_info, std::string>::getInfo(
                platform, paramName); }
    
    /// get platform info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_platform_info paramName) const
    { return impl::GetInfoHelper<cl_platform_id, cl_platform_info, T>::getInfoVector(
                platform, paramName); }
    
    /// get platform name
    std::string getName() const
    { return getInfoString(CL_PLATFORM_NAME); }
    
    /// get platform version
    std::string getVersion() const
    { return getInfoString(CL_PLATFORM_VERSION); }
    
    /// get platform profile
    std::string getProfile() const
    { return getInfoString(CL_PLATFORM_PROFILE); }
    
    /// get platform vendor
    std::string getVendor() const
    { return getInfoString(CL_PLATFORM_VENDOR); }
    
    /// get platform extensions
    std::string getExtensions() const
    { return getInfoString(CL_PLATFORM_EXTENSIONS); }
    
#if __CLPP_CL_VERSION >= 201U
    /// get host timer resolution
    cl_ulong getHostTimerResolution() const
    { return getInfo<cl_ulong>(CL_PLATFORM_HOST_TIMER_RESOLUTION); }
#endif
    
    /// get devices with specified type
    std::vector<Device> getDevices(cl_device_type type) const
    {
        cl_uint numDevices;
        cl_int error = clGetDeviceIDs(platform, type, 0, NULL, &numDevices);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetDeviceIDs");
        std::vector<Device> devices(numDevices);
        error = clGetDeviceIDs(platform, type, numDevices,
                reinterpret_cast<cl_device_id*>(&devices[0]), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetDeviceIDs");
        return devices;
    }
    
    /// get all devices from platform (excepts custom devices)
    std::vector<Device> getAllDevices() const
    { return getDevices(CL_DEVICE_TYPE_ALL); }
    /// get GPU devices from platform
    std::vector<Device> getGPUDevices() const
    { return getDevices(CL_DEVICE_TYPE_GPU); }
    /// get CPU devices from platform
    std::vector<Device> getCPUDevices() const
    { return getDevices(CL_DEVICE_TYPE_CPU); }
    /// get accelerator devices from platform
    std::vector<Device> getAccDevices() const
    { return getDevices(CL_DEVICE_TYPE_ACCELERATOR); }
    
    /// get default device in the system (should not be used in production apps)
    Device getDefaultDevice() const
    { return getDevices(CL_DEVICE_TYPE_DEFAULT)[0]; }
    
#if __CLPP_CL_VERSION >= 102U
    /// get custom devices from platform (defined only if OpenCL >= 1.2)
    std::vector<Device> getCustomDevices() const
    { return getDevices(CL_DEVICE_TYPE_CUSTOM); }
    /// get extension function address
    void* getExtensionFunctionAddress(const char* funcname) const
    { return clGetExtensionFunctionAddressForPlatform(platform, funcname); }
#endif
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// unload platform compiler (defined only for OpenCL ABI >= 1.2)
    void unloadCompiler() const
    { 
        const cl_int error = clUnloadPlatformCompiler(platform);
        if (error != CL_SUCCESS)
            throw Error(error, "clUnloadPlatformCompiler");
    }
#endif

#ifdef __CLPP_CL_GL
    /// get all OpenCL devices associated with OpenGL
    std::vector<Device> getDevicesForGL(cl_context_properties handleType,
                cl_context_properties glContext) const
    {
        cl_context_properties props[5] = { CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform, handleType,
            (cl_context_properties)glContext, 0 };
        return getGLContextInfoVector<Device>(props, CL_DEVICES_FOR_GL_CONTEXT_KHR);
    }
    
    /// get current OpenCL device associated with OpenGL
    Device getCurrentDeviceForGL(cl_context_properties handleType,
                cl_context_properties glContext) const
    {
        cl_context_properties props[5] = { CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform, handleType,
            (cl_context_properties)glContext, 0 };
        return getGLContextInfo<Device>(props, CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR);
    }
#endif
};

/// get device platform
inline Platform Device::getPlatform() const
{ return getInfo<Platform>(CL_DEVICE_PLATFORM); }

/// ImageFormat class
struct ImageFormat: cl_image_format
{
    /// empty constructor
    ImageFormat() { };
    /// constructor
    ImageFormat(cl_channel_order order, cl_channel_type type)
    {
        image_channel_order = order;
        image_channel_data_type = type;
    }
    
    /// accessor for order (value)
    const cl_channel_order& order() const
    { return image_channel_order; }
    /// accessor for order (reference)
    cl_channel_order& order()
    { return image_channel_order; }
    
    /// accessor for type (value)
    const cl_channel_order& type() const
    { return image_channel_data_type; }
    /// accessor for type (reference)
    cl_channel_type& type()
    { return image_channel_data_type; }
};

#if __CLPP_CL_VERSION >= 102U
/// ImageDesc class (defined only if OpenCL >= 1.2)
struct ImageDesc: cl_image_desc
{
    /// constructor
    ImageDesc(cl_mem_object_type type, size_t imageWidth, size_t imageHeight = 0,
            size_t imageDepth = 0, size_t arraySize = 0, size_t rowPitch = 0,
            size_t slicePitch = 0, cl_mem buffer = NULL)
    {
        image_type = type;
        image_width = imageWidth;
        image_height = imageHeight;
        image_depth = imageDepth;
        image_array_size = arraySize;
        image_row_pitch = rowPitch;
        image_slice_pitch = slicePitch;
        num_mip_levels = num_samples = 0;
        this->buffer = buffer;
    }
};
#endif

class CommandQueue;

/// OpenCL Context object wrapper
class Context
{
private:
    cl_context context;
public:
    /// internal OpenCL type
    typedef cl_context cl_type;
    
    /// empty constructor
    Context() : context(NULL)
    { }
    
    /// create context from single device
    /**
     * \param device device for context
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    explicit Context(const Device& device,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        context = clCreateContext(NULL, 1, reinterpret_cast<const cl_device_id*>(&device),
                    notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContext");
    }
    
    /// create context from devices
    /**
     * \param devices devices for context
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    explicit Context(const std::vector<Device>& devices, ContextNotifyCallback notify = NULL,
            void* userData = NULL)
    {
        cl_int error;
        context = clCreateContext(NULL, devices.size(),
                    reinterpret_cast<const cl_device_id*>(&devices[0]),
                    notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContext");
    }
    
    /// create context from single device with properties
    /**
     * \param properties properties for context creation
     * \param device device for context
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    Context(const cl_context_properties* properties, const Device& device,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        context = clCreateContext(properties, 1, reinterpret_cast<const cl_device_id*>(&device),
                    notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContext");
    }
    
    /// create context from devices with properties
    /**
     * \param properties properties for context creation
     * \param devices devices for context
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    Context(const cl_context_properties* properties, const std::vector<Device>& devices,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        context = clCreateContext(properties, devices.size(),
                reinterpret_cast<const cl_device_id*>(&devices[0]), notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContext");
    }
    
    /// create context from type
    explicit Context(cl_device_type deviceType, ContextNotifyCallback notify = NULL,
            void* userData = NULL)
    {
        cl_int error;
        context = clCreateContextFromType(NULL, deviceType, notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContextFromType");
    }
    
    /// create context from type with properties
    /**
     * \param properties properties for context creation
     * \param deviceType device type
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    explicit Context(const cl_context_properties* properties, cl_device_type deviceType,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        context = clCreateContextFromType(properties, deviceType, notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContextFromType");
    }
    
    /// create context from type with platform
    /**
     * \param platform platform for context
     * \param deviceType device type
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    Context(const Platform& platform, cl_device_type deviceType,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        const cl_context_properties props[3] = { CL_CONTEXT_PLATFORM,
                    (cl_context_properties)platform(), 0 };
        context = clCreateContextFromType(props, deviceType, notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContextFromType");
    }
    
#ifdef __CLPP_CL_GL
    /// create GL context (defined only if __CLPP_CL_GL)
    /**
     * \param handleType type of handle of GL context
     * \param glContext gl context
     * \param platform platform for context
     * \param device device for context
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    Context(cl_context_properties handleType, cl_context_properties glContext,
            const Platform& platform, const Device& device,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_context_properties props[5] = { CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform(), handleType,
            (cl_context_properties)glContext, 0 };
        cl_int error;
        context = clCreateContext(props, 1, reinterpret_cast<const cl_device_id*>(&device),
                    notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContext");
    }
    /// create GL context (defined only if __CLPP_CL_GL)
    /**
     * \param handleType type of handle of GL context
     * \param glContext gl context
     * \param platform platform for context
     * \param devices devices for context
     * \param notify notify callback pointer
     * \param userData user data pointer for notify callback
     */
    Context(cl_context_properties handleType, cl_context_properties glContext,
            const Platform& platform, const std::vector<Device>& devices,
            ContextNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_context_properties props[5] = { CL_CONTEXT_PLATFORM,
            (cl_context_properties)platform(), handleType,
            (cl_context_properties)glContext, 0 };
        cl_int error;
        context = clCreateContext(props, devices.size(),
                reinterpret_cast<const cl_device_id*>(&devices[0]), notify, userData, &error);
        if (context==NULL)
            throw Error(error, "clCreateContext");
    }
#endif
    
    /// copy-constructor
    Context(const Context& _context) : context(_context.context)
    { impl::retainInternal(context); }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Context(Context&& _context) noexcept
            : context(_context.context)
    { _context.context = NULL; }
#endif
    
    /// copy-assignment
    Context& operator=(const Context& _context)
    {
        if (context == _context.context)
            return *this;
        impl::releaseInternal(context);
        context = _context.context;
        impl::retainInternal(context);
        return *this;
    }
    
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Context& operator=(Context&& _context)
    {
        impl::releaseInternal(context);
        context = _context.context;
        _context.context = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Context()
    { impl::releaseInternal(context); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(context); context = NULL; }
    
    /// logical negation
    bool operator!() const
    { return context==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return context!=NULL; }
    
    /// get (convert) cl_context
    cl_context operator()() const
    { return context; }
    
    /// convert to cl_context
    operator cl_context() const
    { return context; }
    
    /// comparison operator
    bool operator==(const Context& c2) const
    { return context==c2.context; }
    /// comparison operator
    bool operator!=(const Context& c2) const
    { return context!=c2.context; }
    
    /// create context from cl object
    static Context from(cl_context clobj, bool retain = true)
    {
        Context context;
        context.context = clobj;
        if (retain) impl::retainInternal(clobj);
        return context;
    }
    
    /// get context info
    template<typename T>
    T getInfo(cl_context_info paramName) const
    { return impl::GetInfoHelper<cl_context, cl_context_info, T>::getInfo(
                context, paramName); }
    
    /// get context info
    template<typename T>
    void getInfo(cl_context_info paramName, T& value) const
    { impl::GetInfoHelper<cl_context, cl_context_info, T>::getInfo(
                context, paramName, value); }
    
    /// get context info
    std::string getInfoString(cl_context_info paramName) const
    { return impl::GetInfoHelper<cl_context, cl_context_info, std::string>::getInfo(
                context, paramName); }
    
    /// get context info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_context_info paramName) const
    { return impl::GetInfoHelper<cl_context, cl_context_info, T>::getInfoVector(
                context, paramName); }
    
    /// returns reference count for this context
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_CONTEXT_REFERENCE_COUNT); }
    
    /// get number of devices
    cl_uint getNumDevices() const
    {
#if __CLPP_CL_VERSION >= 101U
        return getInfo<cl_uint>(CL_CONTEXT_NUM_DEVICES);
#else
        size_t devicesNum;
        impl::getInfoInternal<cl_context, cl_context_info, impl::CTXOPT_CONTEXT>(
                    context, CL_CONTEXT_DEVICES, 0, NULL, &devicesNum);
        return devicesNum/sizeof(cl_device_id);
#endif
    }
    
    /// get devices of context
    std::vector<Device> getDevices() const
    { return getInfoVector<Device>(CL_CONTEXT_DEVICES); }
    
    /// get properties of context
    std::vector<cl_context_properties> getProperties() const
    { return getInfoVector<cl_context_properties>(CL_CONTEXT_PROPERTIES); }
    
    /// get supported image formats
    /**
     * \param memFlags flags for memory creation
     * \param objType object type
     * \return output list
     */
    std::vector<ImageFormat> getSupportedImageFormats(cl_mem_flags memFlags,
            cl_mem_object_type objType) const
    {
        cl_uint outNum;
        cl_int error = clGetSupportedImageFormats(context, memFlags, objType,
                        0, NULL, &outNum);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetSupportedImageFormats");
        std::vector<ImageFormat> out(outNum);
        error = clGetSupportedImageFormats(context, memFlags, objType, outNum, &out[0], NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetSupportedImageFormats");
        return out;
    }
    /// get supported image formats
    /**
     * \param memFlags flags for memory creation
     * \param objType object type
     * \param numFormats maximum elements number of list
     * \param formats output
     * \return number of output image formats
     */
    cl_uint getSupportedImageFormats(cl_mem_flags memFlags, cl_mem_object_type objType,
            cl_uint numFormats, ImageFormat* formats) const
    {
        cl_uint outNum;
        cl_int error = clGetSupportedImageFormats(context, memFlags, objType,
                        numFormats, formats, &outNum);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetSupportedImageFormats");
        return outNum;
    }

#if __CLPP_CL_ABI_VERSION >= 200U
    /// allocate shared virtual memory (defined only if OpenCL ABI >= 2.0)
    /**
     * \param flags shared virtual memory flags
     * \param size size in bytes
     * \param alignment in bytes
     */
    void* SVMAlloc(cl_svm_mem_flags flags, size_t size, cl_uint alignment = 0) const
    { return clSVMAlloc(context, flags, size, alignment); }
    
    /// free shared virtual memory
    void SVMFree(void* ptr) const
    { clSVMFree(context, ptr); }
#endif
    /// create command queues for all context devices
    std::vector<CommandQueue> createCommandQueues(cl_command_queue_properties props = 0) const;
    
#if __CLPP_CL_ABI_VERSION >= 200U
    /// create command queues for all context devices (defined only if OpenCL ABI >= 2.0)
    std::vector<CommandQueue> createCommandQueues(cl_command_queue_properties props,
                size_t size) const;
    
    /// create command queues for all context devices (defined only if OpenCL ABI >= 2.0)
    std::vector<CommandQueue> createCommandQueues(const cl_queue_properties* props) const;
#endif
    
#if __CLPP_CL_ABI_VERSION >= 201U
    /// set default device command queue
    void setDefaultDeviceCommandQueue(const Device& device,
                        const CommandQueue& cmdQueue) const;
#endif
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Context, Option>:
            GetInfoRefHelper<CLType, InfoType, Context, Option>
    { };
}

/// OpenCL Memory object wrapper
class Memory
{
protected:
    /// memory object
    cl_mem memory;
public:
    /// internal OpenCL type
    typedef cl_mem cl_type;
    
    /// empty constructor
    Memory() : memory(NULL)
    { }
    
    /// copy-constructor
    Memory(const Memory& _memory) : memory(_memory.memory)
    { impl::retainInternal(memory); }
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Memory(Memory&& _memory) noexcept
            : memory(_memory.memory)
    { _memory.memory = NULL; }
#endif
    
    /// copy-assignment
    Memory& operator=(const Memory& _memory)
    {
        if (memory == _memory.memory)
            return *this;
        impl::releaseInternal(memory);
        memory = _memory.memory;
        impl::retainInternal(memory);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Memory& operator=(Memory&& _memory)
    {
        impl::releaseInternal(memory);
        memory = _memory.memory;
        _memory.memory = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Memory()
    { impl::releaseInternal(memory); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(memory); memory = NULL; }
    
    /// logical negation
    bool operator!() const
    { return memory==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return memory!=NULL; }
    
    /// get (convert) cl_context
    cl_mem operator()() const
    { return memory; }
    
    /// convert to cl_context
    operator cl_mem() const
    { return memory; }
    
    /// comparison operator
    bool operator==(const Memory& m2) const
    { return memory==m2.memory; }
    /// comparison operator
    bool operator!=(const Memory& m2) const
    { return memory!=m2.memory; }
    
    /// create memory object from cl object
    static Memory from(cl_mem clobj, bool retain = true)
    {
        Memory memory;
        memory.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return memory;
    }
    
    /// cast this object to other class
    template<typename T>
    T& cast()
    { return reinterpret_cast<T&>(*this); }
    
    /// cast this object to other class
    template<typename T>
    const T& cast() const
    { return reinterpret_cast<const T&>(*this); }
    
    /// get memory info
    template<typename T>
    T getInfo(cl_mem_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_mem_info, T>::getInfo(memory, paramName); }
    
    /// get memory info
    template<typename T>
    void getInfo(cl_mem_info paramName, T& value) const
    { impl::GetInfoHelper<cl_mem, cl_mem_info, T>::getInfo(memory, paramName, value); }
    
    /// get memory info
    std::string getInfoString(cl_mem_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_mem_info, std::string>::getInfo(
                memory, paramName); }
    
    /// get memory info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_mem_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_mem_info, T>::getInfoVector(memory, paramName); }
    
    /// get memory type
    cl_mem_object_type getType() const
    { return getInfo<cl_mem_object_type>(CL_MEM_TYPE); }
    
    /// get memory flags
    cl_mem_flags getFlags() const
    { return getInfo<cl_mem_flags>(CL_MEM_FLAGS); }
    
    /// get memory size in bytes
    size_t getSize() const
    { return getInfo<size_t>(CL_MEM_SIZE); }
    
    /// get memory host pointer
    void* getHostPointer() const
    { return getInfo<void*>(CL_MEM_HOST_PTR); }
    
    /// get memory map count
    cl_uint getMapCount() const
    { return getInfo<cl_uint>(CL_MEM_MAP_COUNT); }
    
    /// get memory context
    Context getContext() const
    { return getInfo<Context>(CL_MEM_CONTEXT); }
    
    /// returns reference count for this memory
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_MEM_REFERENCE_COUNT); }
    
#if __CLPP_CL_VERSION >= 101U
    /// get associated memory object (defined only if OpenCL >= 1.1)
    Memory getAssociatedMemObject() const
    { return getInfo<Memory>(CL_MEM_ASSOCIATED_MEMOBJECT); }
    
    /// get associated memory object (defined only if OpenCL >= 1.1)
    Memory getAssociatedMemory() const
    { return getInfo<Memory>(CL_MEM_ASSOCIATED_MEMOBJECT); }
    
    /// get memory offset in bytes (defined only if OpenCL >= 1.1)
    size_t getOffset() const
    { return getInfo<size_t>(CL_MEM_OFFSET); }
#endif

#if __CLPP_CL_VERSION >= 200U
    /// check whether memory uses SVM pointer (defined only if OpenCL >= 2.0)
    bool isUsesSVMPointer() const
    { return getInfo<cl_bool>(CL_MEM_USES_SVM_POINTER); }
#endif

#if __CLPP_CL_VERSION >= 101U
    /// set memory destructor callback
    void setDestructorCallback(MemoryNotifyCallback notify, void* userData = NULL) const
    {
        const cl_int error = clSetMemObjectDestructorCallback(memory, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetMemObjectDestructorCallback");
    }
#endif
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Memory, Option>:
            GetInfoRefHelper<CLType, InfoType, Memory, Option>
    { };
}

/// OpenCL Buffer
class Buffer: public Memory
{
public:
    /// empty constructor
    Buffer()
    { }
    
    /// constructor
    /**
     * \param context context for buffer
     * \param flags flags for memory creation
     * \param size size of buffer
     * \param hostPtr pointer to host data
     */
    Buffer(const Context& context, cl_mem_flags flags, size_t size, void* hostPtr = NULL)
    {
        cl_int error;
        memory = clCreateBuffer(context, flags, size, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateBuffer");
    }
    
    /// constructor
    /**
     * \param context context for buffer
     * \param readOnly if true constructs read only buffer
     * \param useHostPtr if true uses hostPtr during construct buffer
     * \param size size of buffer
     * \param hostPtr pointer to host data
     */
    Buffer(const Context& context, bool readOnly, bool useHostPtr, size_t size,
                void* hostPtr = NULL)
    {
        cl_int error;
        const cl_mem_flags flags = ((readOnly)? CL_MEM_READ_ONLY : CL_MEM_READ_WRITE) |
            ((useHostPtr) ? CL_MEM_USE_HOST_PTR : 0);
        memory = clCreateBuffer(context, flags, size, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateBuffer");
    }
    
    /// copy-constructor
    Buffer(const Buffer& _buffer) : Memory(_buffer)
    { }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Buffer(Buffer&& _buffer) noexcept : Memory(std::forward<Buffer>(_buffer))
    { }
#endif
    
    /// copy-assignment
    Buffer& operator=(const Buffer& _buffer)
    { Memory::operator=(_buffer); return *this; }    
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Buffer& operator=(Buffer&& _buffer)
    { Memory::operator=(std::forward<Buffer>(_buffer)); return *this; }
#endif

    /// create buffer from cl object
    static Buffer from(cl_mem clobj, bool retain = true)
    {
        Buffer buffer;
        buffer.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return buffer;
    }
    
#if __CLPP_CL_ABI_VERSION >= 101U
    /// create subbuffer (defined only if OpenCL ABI >= 1.1)
    /**
     * \param flags flags for buffer creation
     * \param createType type of subbuffer creation
     * \param bufCreateInfo information about subbuffer creation
     * \return output subbuffer
     */
    Buffer createSubBuffer(cl_mem_flags flags, cl_buffer_create_type createType,
                const void* bufCreateInfo) const
    {
        cl_int error;
        const cl_mem subBuf = clCreateSubBuffer(memory, flags, createType,
                            bufCreateInfo, &error);
        if (subBuf == NULL)
            throw Error(error, "clCreateSubBuffer");
        Buffer out;
        out.memory = subBuf;
        return out;
    }
    
    /// create subbuffer (defined only if OpenCL >= 1.1)
    /**
     * \param flags flags for buffer creation
     * \param region subbuffer region
     * \return output subbuffer
     */
    Buffer createSubBuffer(cl_mem_flags flags, const cl_buffer_region& region) const
    { return createSubBuffer(flags, CL_BUFFER_CREATE_TYPE_REGION, &region); }
    
    /// create subbuffer (defined only if OpenCL >= 1.1)
    /**
     * \param flags flags for buffer creation
     * \param origin subbuffer origin
     * \param size subbuffer size
     * \return output subbuffer
     */
    Buffer createSubBuffer(cl_mem_flags flags, size_t origin, size_t size) const
    {
        const cl_buffer_region region = { origin, size };
        return createSubBuffer(flags, CL_BUFFER_CREATE_TYPE_REGION, &region);
    }
#endif
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Buffer, Option>:
            GetInfoRefHelper<CLType, InfoType, Buffer, Option>
    { };
}

#ifdef __CLPP_CL_GL
/// buffer from OpenGL
class BufferGL: public Buffer
{
public:
    /// empty constructor
    BufferGL()
    { }
    
    /// BufferGL constructor
    BufferGL(const Context& context, cl_mem_flags flags, cl_GLuint bufobj)
    {
        cl_int error;
        memory = clCreateFromGLBuffer(context, flags, bufobj, &error);
        if (memory == NULL)
            throw Error(error, "clCreateFromGLBuffer");
    }
    /// copy-constructor
    BufferGL(const BufferGL& _buffer) : Buffer(_buffer)
    { }
    
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    BufferGL(BufferGL&& _buffer) noexcept : Buffer(std::forward<BufferGL>(_buffer))
    { }
#   endif
    
    /// copy-assignment
    BufferGL& operator=(const BufferGL& _buffer)
    { Buffer::operator=(_buffer); return *this; }
    
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    BufferGL& operator=(BufferGL&& _buffer)
    { Buffer::operator=(std::forward<BufferGL>(_buffer)); return *this; }
#    endif
    
    /// create bufferGL from cl object
    static BufferGL from(cl_mem clobj, bool retain = true)
    {
        BufferGL buffer;
        buffer.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return buffer;
    }
    
    /// get object info
    void getGLObjectInfo(cl_gl_object_type* type, cl_GLuint* name) const
    {
        const cl_int error = clGetGLObjectInfo(memory, type, name);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetGLObjectInfo");
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, BufferGL, Option>:
            GetInfoRefHelper<CLType, InfoType, BufferGL, Option>
    { };
}
#endif

#if __CLPP_CL_ABI_VERSION >= 200U
/// OpenCL Pipe (defined only if OpenCL ABI >= 2.0)
class Pipe: public Memory
{
public:
    /// empty constructor
    Pipe()
    { }
    
    /// constructor
    /**
     * \param context context for pipe
     * \param flags flags for memory creation
     * \param pipePacketSize size of pipe packet
     * \param pipeMaxPackets number of max packets
     * \param properties properties for pipe
     */
    Pipe(const Context& context, cl_mem_flags flags, cl_uint pipePacketSize,
                cl_uint pipeMaxPackets, const cl_pipe_properties* properties = NULL)
    {
        cl_int error;
        memory = clCreatePipe(context, flags, pipePacketSize, pipeMaxPackets, properties,
                    &error);
        if (memory == NULL)
            throw Error(error, "clCreatePipe");
    }
    
    /// copy-constructor
    Pipe(const Pipe& _pipe) : Memory(_pipe)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Pipe(Pipe&& _pipe) noexcept : Memory(std::forward<Pipe>(_pipe))
    { }
#   endif
    
    /// copy-assignment
    Pipe& operator=(const Pipe& _pipe)
    { Memory::operator=(_pipe); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Pipe& operator=(Pipe&& _pipe)
    { Memory::operator=(std::forward<Pipe>(_pipe)); return *this; }
#   endif
    
    /// create pipe from cl object
    static Pipe from(cl_mem clobj, bool retain = true)
    {
        Pipe pipe;
        pipe.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return pipe;
    }
    
    /// get pipe info
    template<typename T>
    T getPipeInfo(cl_pipe_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_pipe_info, T, impl::MEMOPT_PIPE>::getInfo(
                memory, paramName); }
    
    /// get pipe info
    template<typename T>
    void getPipeInfo(cl_pipe_info paramName, T& value) const
    { impl::GetInfoHelper<cl_mem, cl_pipe_info, T, impl::MEMOPT_PIPE>::getInfo(
                memory, paramName, value); }
    
    /// get pipe info
    std::string getPipeInfo(cl_pipe_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_pipe_info, std::string,
                impl::MEMOPT_PIPE>::getInfo(memory, paramName); }
    
    /// get pipe info as vector
    template<typename T>
    std::vector<T> getPipeInfoVector(cl_pipe_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_pipe_info, T, impl::MEMOPT_PIPE>::getInfoVector(
                memory, paramName); }
    
    /// get pipe packet size
    cl_uint getPacketSize() const
    { return getPipeInfo<cl_uint>(CL_PIPE_PACKET_SIZE); }
    
    /// get pipe number of maximum packets
    cl_uint getMaxPackets() const
    { return getPipeInfo<cl_uint>(CL_PIPE_MAX_PACKETS); }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Pipe, Option>:
            GetInfoRefHelper<CLType, InfoType, Pipe, Option>
    { };
}
#endif

/// OpenCL Image object wrapper
class Image: public Memory
{
public:
    /// empty constructor
    Image()
    { }
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// general constructor with image descriptor (defined only if OpenCL ABI >= 1.2)
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param imgDesc image descriptor
     * \param hostPtr host data
     */
    Image(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
                const cl_image_desc& imgDesc, void* hostPtr = NULL)
    {
        cl_int error;
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
    }
#endif
    /// constructor for 1D/2D/3D image
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param height image height
     * \param depth image depth
     * \param rowPitch size of row in bytes
     * \param slicePitch size of slice in bytes
     * \param hostPtr host data
     */
    Image(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, size_t height = 0, size_t depth = 0, size_t rowPitch = 0,
          size_t slicePitch = 0, void* hostPtr = NULL)
    {
        cl_int error;
#if __CLPP_CL_ABI_VERSION >= 102U
        const cl_mem_object_type type = (depth != 0) ? CL_MEM_OBJECT_IMAGE3D : 
            (height != 0) ? CL_MEM_OBJECT_IMAGE2D : CL_MEM_OBJECT_IMAGE1D;
        cl_image_desc imgDesc = { type, width, height, depth, 0, rowPitch, slicePitch, 0, 0 };
        imgDesc.buffer = NULL; // clang++ warning fix
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
#else
        if (depth != 0)
        {
            memory = clCreateImage3D(context, memFlags, &imgFormat, width, height, depth,
                        rowPitch, slicePitch, hostPtr, &error);
            if (memory == NULL)
                throw Error(error, "clCreateImage3D");
        }
        else
        {
            memory = clCreateImage2D(context, memFlags, &imgFormat, width, height,
                        rowPitch, hostPtr, &error);
            if (memory == NULL)
                throw Error(error, "clCreateImage2D");
        }
#endif
    }
    
    /// copy-constructor
    Image(const Image& _image) : Memory(_image)
    { }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image(Image&& _image) noexcept : Memory(std::forward<Image>(_image))
    { }
#endif
    
    /// copy-assignment
    Image& operator=(const Image& _image)
    { Memory::operator=(_image); return *this; }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image& operator=(Image&& _image)
    { Memory::operator=(std::forward<Image>(_image)); return *this; }
#endif
    
    /// create image from cl object
    static Image from(cl_mem clobj, bool retain = true)
    {
        Image image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
    
    /// get image info
    template<typename T>
    T getImageInfo(cl_image_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_image_info, T, impl::MEMOPT_IMAGE>::getInfo(
                memory, paramName); }
    
    /// get image info
    template<typename T>
    void getImageInfo(cl_image_info paramName, T& value) const
    { impl::GetInfoHelper<cl_mem, cl_image_info, T, impl::MEMOPT_IMAGE>::getInfo(
                memory, paramName, value); }
    
    /// get image info
    std::string getImageInfo(cl_image_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_image_info, std::string, impl::MEMOPT_IMAGE>::
                getInfo(memory, paramName); }
    
    /// get image info as vector
    template<typename T>
    std::vector<T> getImageInfoVector(cl_image_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_image_info, T, impl::MEMOPT_IMAGE>::
                getInfoVector(memory, paramName); }
    
    /// get image format
    cl_image_format getFormat() const
    { return getImageInfo<cl_image_format>(CL_IMAGE_FORMAT); }
    
    /// get image element size
    size_t getElementSize() const
    { return getImageInfo<size_t>(CL_IMAGE_ELEMENT_SIZE); }
    
    /// get image row pitch
    size_t getRowPitch() const
    { return getImageInfo<size_t>(CL_IMAGE_ROW_PITCH); }
    
    /// get image slice pitch
    size_t getSlicePitch() const
    { return getImageInfo<size_t>(CL_IMAGE_SLICE_PITCH); }
    
    /// get image width
    size_t getWidth() const
    { return getImageInfo<size_t>(CL_IMAGE_WIDTH); }
    
    /// get image height
    size_t getHeight() const
    { return getImageInfo<size_t>(CL_IMAGE_HEIGHT); }
    
    /// get image depth
    size_t getDepth() const
    { return getImageInfo<size_t>(CL_IMAGE_DEPTH); }
    
    /// get 2D image sizes
    void get2DSizes(size_t& width, size_t& height) const
    { getImageInfo(CL_IMAGE_WIDTH, width);
      getImageInfo(CL_IMAGE_HEIGHT, height); }
      
    /// get 2D image sizes
    Size3 get2DSizes() const
    {
        Size3 sizes;
        getImageInfo(CL_IMAGE_WIDTH, sizes[0]);
        getImageInfo(CL_IMAGE_HEIGHT, sizes[1]);
        return sizes;
    }
    
    /// get 3D image sizes
    void get3DSizes(size_t& width, size_t& height, size_t& depth) const
    {
        getImageInfo(CL_IMAGE_WIDTH, width);
        getImageInfo(CL_IMAGE_HEIGHT, height);
        getImageInfo(CL_IMAGE_DEPTH, depth);
    }
    /// get 3D image sizes
    Size3 get3DSizes() const
    {
        Size3 sizes;
        getImageInfo(CL_IMAGE_WIDTH, sizes[0]);
        getImageInfo(CL_IMAGE_HEIGHT, sizes[1]);
        getImageInfo(CL_IMAGE_DEPTH, sizes[2]);
        return sizes;
    }
    
#if __CLPP_CL_VERSION >= 102U
    /// get image array size (defined if only OpenCL >= 1.2)
    size_t getArraySize() const
    { return getImageInfo<size_t>(CL_IMAGE_ARRAY_SIZE); }
    
    /// get image buffer (defined if only OpenCL >= 1.2) (deprecated if OpenCL >= 2.0)
     __CLPP_CL_2_0_DEPRECATED Buffer getBuffer() const
    { return getImageInfo<Buffer>(CL_IMAGE_BUFFER); }
    
    /// get image number of mip levels (defined if only OpenCL >= 1.2)
    cl_uint getNumMipLevels() const
    { return getImageInfo<cl_uint>(CL_IMAGE_NUM_MIP_LEVELS); }
    
    /// get image number of samples (defined if only OpenCL >= 1.2)
    cl_uint getNumSamples() const
    { return getImageInfo<cl_uint>(CL_IMAGE_NUM_SAMPLES); }
#endif
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image, Option>:
            GetInfoRefHelper<CLType, InfoType, Image, Option>
    { };
}
#if __CLPP_CL_ABI_VERSION >= 102U
/// OpenCL Image1D object wrapper (defined only if OpenCL ABI >= 1.2)
class Image1D: public Image
{
public:
    /// empty constructor
    Image1D()
    { }
    
    /// constructor for 1D image
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param hostPtr host data
     */
    Image1D(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, void* hostPtr = NULL)
    {
        cl_int error;
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE1D, width, 0, 0, 0, 0, 0, 0, 0 };
        imgDesc.buffer = NULL; // clang++ warning fix
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
    }
    
    /// copy-constructor
    Image1D(const Image1D& _image) : Image(_image)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image1D(Image1D&& _image) noexcept : Image(std::forward<Image1D>(_image))
    { }
#   endif
    
    /// copy-assignment
    Image1D& operator=(const Image1D& _image)
    { Image::operator=(_image); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image1D& operator=(Image1D&& _image)
    { Image::operator=(std::forward<Image1D>(_image)); return *this; }
#    endif
    
    /// create image from cl object
    static Image1D from(cl_mem clobj, bool retain = true)
    {
        Image1D image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image1D, Option>:
            GetInfoRefHelper<CLType, InfoType, Image1D, Option>
    { };
}

/// OpenCL Image1DArray object wrapper (defined only if OpenCL >= 1.2)
class Image1DArray: public Image
{
public:
    /// empty constructor
    Image1DArray()
    { }
    
    /// constructor for 1D image array
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param arraySize array size
     * \param rowPitch size of row in bytes
     * \param hostPtr host data
     */
    Image1DArray(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, size_t arraySize, size_t rowPitch = 0, void* hostPtr = NULL)
    {
        cl_int error;
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE1D_ARRAY, width, 0, 0, arraySize,
                    rowPitch, 0 /* calculated as rowPitch */, 0, 0 };
        imgDesc.buffer = NULL;
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
    }
    
    /// copy-constructor
    Image1DArray(const Image1DArray& _image) : Image(_image)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image1DArray(Image1DArray&& _image) noexcept : Image(std::forward<Image1DArray>(_image))
    { }
#   endif
    
    /// copy-assignment
    Image1DArray& operator=(const Image1DArray& _image)
    { Image::operator=(_image); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image1DArray& operator=(Image1DArray&& _image)
    { Image::operator=(std::forward<Image1DArray>(_image)); return *this; }
#    endif
    
    /// create image from cl object
    static Image1DArray from(cl_mem clobj, bool retain = true)
    {
        Image1DArray image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image1DArray, Option>:
            GetInfoRefHelper<CLType, InfoType, Image1DArray, Option>
    { };
}

/// OpenCL Image1DBuffer object wrapper (defined only if OpenCL >= 1.2)
class Image1DBuffer: public Image
{
public:
    /// empty constructor
    Image1DBuffer()
    { }
    
    /// constructor for 1D image buffer
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param imgMem memory buffer for image
     */
    Image1DBuffer(const Context& context, cl_mem_flags memFlags,
            const cl_image_format& imgFormat, size_t width, const Memory& imgMem)
    {
        cl_int error;
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE1D_BUFFER, width, 0, 0, 0, 0, 0, 0, 0 };
        imgDesc.buffer = imgMem; // fix for clang++
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, NULL, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
    }
    
    /// copy-constructor
    Image1DBuffer(const Image1DBuffer& _image) : Image(_image)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image1DBuffer(Image1DBuffer&& _image) noexcept : Image(std::forward<Image1DBuffer>(_image))
    { }
#   endif
    
    /// copy-assignment
    Image1DBuffer& operator=(const Image1DBuffer& _image)
    { Image::operator=(_image); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image1DBuffer& operator=(Image1DBuffer&& _image)
    { Image::operator=(std::forward<Image1DBuffer>(_image)); return *this; }
#    endif
    
    /// create image from cl object
    static Image1DBuffer from(cl_mem clobj, bool retain = true)
    {
        Image1DBuffer image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image1DBuffer, Option>:
            GetInfoRefHelper<CLType, InfoType, Image1DBuffer, Option>
    { };
}
#endif

/// OpenCL Image2D object wrapper
class Image2D: public Image
{
public:
    /// empty constructor
    Image2D()
    { }
    
    /// constructor for 2D image
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param height image height
     * \param rowPitch size of row in bytes
     * \param hostPtr host data
     */
    Image2D(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, size_t height, size_t rowPitch = 0, void* hostPtr = NULL)
    {
        cl_int error;
#if __CLPP_CL_ABI_VERSION >= 102U
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE2D, width, height, 0, 0,
                    rowPitch, 0, 0, 0 };
        imgDesc.buffer = NULL; // fix for clang++
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
#else
        memory = clCreateImage2D(context, memFlags, &imgFormat, width, height,
                    rowPitch, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage2D");
#endif
    }
    
#if __CLPP_CL_VERSION >= 200U
    /// constructor for 2D image with memobject (defined if only OpenCL >= 2.0)
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param height image height
     * \param memObject memory to associate
     */
    Image2D(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, size_t height, const Memory& memObject)
    {
        cl_int error;
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE2D, width, height, 0, 0,
                    0, 0, 0, 0 };
        imgDesc.buffer = memObject; // fix for clang++
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, NULL, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
    }
#endif
    
    /// copy-constructor
    Image2D(const Image2D& _image) : Image(_image)
    { }
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image2D(Image2D&& _image) noexcept : Image(std::forward<Image2D>(_image))
    { }
#endif
    
    /// copy-assignment
    Image2D& operator=(const Image2D& _image)
    { Image::operator=(_image); return *this; }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image2D& operator=(Image2D&& _image)
    { Image::operator=(std::forward<Image2D>(_image)); return *this; }
#endif
    
    /// create image from cl object
    static Image2D from(cl_mem clobj, bool retain = true)
    {
        Image2D image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image2D, Option>:
            GetInfoRefHelper<CLType, InfoType, Image2D, Option>
    { };
}

#ifdef __CLPP_CL_GL
/// renderbuffer GL  object wrapper (defined if only __CLPP_CL_GL)
class RenderbufferGL: public Image2D
{
public:
    /// empty constructor
    RenderbufferGL()
    { }
    
    /// constructor
    RenderbufferGL(const Context& context, cl_mem_flags flags, cl_GLuint bufobj)
    {
        cl_int error;
        memory = clCreateFromGLRenderbuffer(context, flags, bufobj, &error);
        if (memory == NULL)
            throw Error(error, "clCreateFromGLRenderbuffer");
    }
    
    /// copy-constructor
    RenderbufferGL(const RenderbufferGL& _image) : Image2D(_image)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    RenderbufferGL(RenderbufferGL&& _image) noexcept :
            Image2D(std::forward<RenderbufferGL>(_image))
    { }
#   endif
    
    /// copy-assignment
    RenderbufferGL& operator=(const RenderbufferGL& _image)
    { Image2D::operator=(_image); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    RenderbufferGL& operator=(RenderbufferGL&& _image)
    { Image2D::operator=(std::forward<RenderbufferGL>(_image)); return *this; }
#   endif
    
    /// create renderbufferGL from cl object
    static RenderbufferGL from(cl_mem clobj, bool retain = true)
    {
        RenderbufferGL image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
    
    /// get object info
    void getGLObjectInfo(cl_gl_object_type* type, cl_GLuint* name) const
    {
        const cl_int error = clGetGLObjectInfo(memory, type, name);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetGLObjectInfo");
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, RenderbufferGL, Option>:
            GetInfoRefHelper<CLType, InfoType, RenderbufferGL, Option>
    { };
}

/// TextureGL object wrapper (defined if only __CLPP_CL_GL)
class TextureGL: public Image
{
public:
    /// empty constructor
    TextureGL()
    { }
    
    /// constructor
    TextureGL(const Context& context, cl_mem_flags flags, cl_GLenum target,
              cl_GLint miplevel, cl_GLuint texture, bool _3D = false)
    {
        cl_int error;
#if __CLPP_CL_ABI_VERSION >= 102U
        memory = clCreateFromGLTexture(context, flags, target, miplevel,
                        texture, &error);
        if (memory == NULL)
            throw Error(error, "clCreateFromGLTexture");
#else
        if (_3D)
        {
            memory = clCreateFromGLTexture3D(context, flags, target, miplevel,
                            texture, &error);
            if (memory == NULL)
                throw Error(error, "clCreateFromGLTexture3D");
        }
        else
        {
            memory = clCreateFromGLTexture2D(context, flags, target, miplevel,
                            texture, &error);
            if (memory == NULL)
                throw Error(error, "clCreateFromGLTexture2D");
        }
#endif
    }
    
    /// copy-constructor
    TextureGL(const TextureGL& _image) : Image(_image)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    TextureGL(TextureGL&& _image) noexcept : Image(std::forward<TextureGL>(_image))
    { }
#   endif
    
    /// copy-assignment
    TextureGL& operator=(const TextureGL& _image)
    { Image::operator=(_image); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    TextureGL& operator=(TextureGL&& _image)
    { Image::operator=(std::forward<TextureGL>(_image)); return *this; }
#   endif
    
    /// create texture gl from cl object
    static TextureGL from(cl_mem clobj, bool retain = true)
    {
        TextureGL image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
    
    /// get object info
    void getGLObjectInfo(cl_gl_object_type* type, cl_GLuint* name) const
    {
        const cl_int error = clGetGLObjectInfo(memory, type, name);
        if (error != CL_SUCCESS)
            throw Error(error, "clGetGLObjectInfo");
    }
    
    /// get gl_texture info
    template<typename T>
    T getGLTextureInfo(cl_gl_texture_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_gl_texture_info, T,
                impl::MEMOPT_TEXTUREGL>::getInfo(memory, paramName); }
    
    /// get gl_texture info
    template<typename T>
    void getGLTextureInfo(cl_gl_texture_info paramName, T& value) const
    { impl::GetInfoHelper<cl_mem, cl_gl_texture_info, T, impl::MEMOPT_TEXTUREGL>::getInfo(
                memory, paramName, value); }
    
    /// get gl_texture info
    std::string getGLTextureInfoString(cl_gl_texture_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_gl_texture_info, std::string,
                impl::MEMOPT_TEXTUREGL>::getInfo( memory, paramName); }
    
    /// get gl_texture info as vector
    template<typename T>
    std::vector<T> getGLTextureInfoVector(cl_gl_texture_info paramName) const
    { return impl::GetInfoHelper<cl_mem, cl_gl_texture_info, T, impl::MEMOPT_TEXTUREGL>::
                getInfoVector(memory, paramName); }
    
    /// get GL texture target
    cl_GLenum getGLTextureTarget() const
    { return getGLTextureInfo<cl_GLenum>(CL_GL_TEXTURE_TARGET); }
    
    /// get GL mipmap level
    cl_GLint getGLMipMapLevel() const
    { return getGLTextureInfo<cl_GLint>(CL_GL_MIPMAP_LEVEL); }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, TextureGL, Option>:
            GetInfoRefHelper<CLType, InfoType, TextureGL, Option>
    { };
}
#endif

#if __CLPP_CL_ABI_VERSION >= 102U
/// OpenCL Image2DArray object wrapper (defined only if OpenCL ABI >= 1.2)
class Image2DArray: public Image
{
public:
    /// empty constructor
    Image2DArray()
    { }
    
    /// constructor for 2D image array
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param height image height
     * \param arraySize array size
     * \param rowPitch size of row in bytes
     * \param slicePitch size of slice in bytes
     * \param hostPtr host data
     */
    Image2DArray(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, size_t height, size_t arraySize, size_t rowPitch = 0,
          size_t slicePitch = 0, void* hostPtr = NULL)
    {
        cl_int error;
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE2D_ARRAY, width, height, 0, arraySize,
                    rowPitch, slicePitch, 0, 0 };
        imgDesc.buffer = NULL; // fix for clang++
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
    }
    
    /// copy-constructor
    Image2DArray(const Image2DArray& _image) : Image(_image)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image2DArray(Image2DArray&& _image) noexcept : Image(std::forward<Image2DArray>(_image))
    { }
#   endif
    
    /// copy-assignment
    Image2DArray& operator=(const Image2DArray& _image)
    { Image::operator=(_image); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image2DArray& operator=(Image2DArray&& _image)
    { Image::operator=(std::forward<Image2DArray>(_image)); return *this; }
#   endif
    
    /// create image from cl object
    static Image2DArray from(cl_mem clobj, bool retain = true)
    {
        Image2DArray image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image2DArray, Option>:
            GetInfoRefHelper<CLType, InfoType, Image2DArray, Option>
    { };
}
#endif

/// OpenCL Image3D object wrapper
class Image3D: public Image
{
public:
    /// empty constructor
    Image3D()
    { }
    
    /// constructor for 3D image
    /**
     * \param context context
     * \param memFlags flags for creating memory object
     * \param imgFormat image format
     * \param width image width
     * \param height image height
     * \param depth image depth
     * \param rowPitch size of row in bytes
     * \param slicePitch size of slice in bytes
     * \param hostPtr host data
     */
    Image3D(const Context& context, cl_mem_flags memFlags, const cl_image_format& imgFormat,
          size_t width, size_t height, size_t depth,
          size_t rowPitch = 0, size_t slicePitch = 0, void* hostPtr = NULL)
    {
        cl_int error;
#if __CLPP_CL_ABI_VERSION >= 102U
        cl_image_desc imgDesc = { CL_MEM_OBJECT_IMAGE3D, width, height, depth, 0,
                    rowPitch, slicePitch, 0, 0 };
        imgDesc.buffer = NULL; // fix for clang++
        memory = clCreateImage(context, memFlags, &imgFormat, &imgDesc, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage");
#else
        memory = clCreateImage3D(context, memFlags, &imgFormat, width, height, depth,
                    rowPitch, slicePitch, hostPtr, &error);
        if (memory == NULL)
            throw Error(error, "clCreateImage3D");
#endif
    }
    
    /// copy-constructor
    Image3D(const Image3D& _image) : Image(_image)
    { }
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Image3D(Image3D&& _image) noexcept : Image(std::forward<Image3D>(_image))
    { }
#endif
    
    /// copy-assignment
    Image3D& operator=(const Image3D& _image)
    { Image::operator=(_image); return *this; }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Image3D& operator=(Image3D&& _image)
    { Image::operator=(std::forward<Image3D>(_image)); return *this; }
#endif
    
    /// create image from cl object
    static Image3D from(cl_mem clobj, bool retain = true)
    {
        Image3D image;
        image.memory = clobj;
        if (retain) impl::retainInternal(clobj);
        return image;
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Image3D, Option>:
            GetInfoRefHelper<CLType, InfoType, Image3D, Option>
    { };
}

/// OpenCL Sampler object wrapper
class Sampler
{
private:
    cl_sampler sampler;
public:
    /// internal OpenCL type
    typedef cl_sampler cl_type;
    
    /// empty constructor
    Sampler() : sampler(NULL)
    { }
    
    /// constructor with params
    /**
     * \param context context for sampler
     * \param normalizedCoords normalized coordinates
     * \param addrMode addressing mode
     * \param filterMode filter mode
     */
    Sampler(const Context& context, bool normalizedCoords, cl_addressing_mode addrMode,
            cl_filter_mode filterMode)
    {
        cl_int error;
#if __CLPP_CL_ABI_VERSION >= 200U
        const cl_sampler_properties props[7] = {
            CL_SAMPLER_NORMALIZED_COORDS, cl_uint(normalizedCoords),
            CL_SAMPLER_ADDRESSING_MODE, addrMode,
            CL_SAMPLER_FILTER_MODE, filterMode, 0
        };
        sampler = clCreateSamplerWithProperties(context, props, &error);
        if (sampler == NULL)
            throw Error(error, "clCreateSamplerWithProperties");
#else
        sampler = clCreateSampler(context, normalizedCoords, addrMode, filterMode, &error);
        if (sampler == NULL)
            throw Error(error, "clCreateSampler");
#endif
    }

#if __CLPP_CL_ABI_VERSION >= 200U
    /// constructor with properties (defined only if OpenCL ABI >= 2.0)
    /**
     * \param context context for sampler
     * \param properties list of properties
     */
    Sampler(const Context& context, const cl_sampler_properties* properties)
    {
        cl_int error;
        sampler = clCreateSamplerWithProperties(context, properties, &error);
        if (sampler == NULL)
            throw Error(error, "clCreateSamplerWithProperties");
    }
#endif
    
    /// copy-constructor
    Sampler(const Sampler& _sampler) : sampler(_sampler.sampler)
    { impl::retainInternal(sampler); }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Sampler(Sampler&& _sampler) noexcept
            : sampler(_sampler.sampler)
    { _sampler.sampler = NULL; }
#endif
    
    /// copy-assignment
    Sampler& operator=(const Sampler& _sampler)
    {
        if (sampler == _sampler.sampler)
            return *this;
        impl::releaseInternal(sampler);
        sampler = _sampler.sampler;
        impl::retainInternal(sampler);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Sampler& operator=(Sampler&& _sampler)
    {
        impl::releaseInternal(sampler);
        sampler = _sampler.sampler;
        _sampler.sampler = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Sampler()
    { impl::releaseInternal(sampler); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(sampler); sampler = NULL; }
    
    /// logical negation
    bool operator!() const
    { return sampler==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return sampler!=NULL; }
    
    /// get (convert) cl_sampler
    cl_sampler operator()() const
    { return sampler; }
    
    /// convert to cl_sampler
    operator cl_sampler() const
    { return sampler; }
    
    /// comparison operator
    bool operator==(const Sampler& s2) const
    { return sampler==s2.sampler; }
    /// comparison operator
    bool operator!=(const Sampler& s2) const
    { return sampler!=s2.sampler; }
    
    /// create sampler from cl object
    static Sampler from(cl_sampler clobj, bool retain = true)
    {
        Sampler sampler;
        sampler.sampler = clobj;
        if (retain) impl::retainInternal(clobj);
        return sampler;
    }
    
    /// get sampler info
    template<typename T>
    T getInfo(cl_sampler_info paramName) const
    { return impl::GetInfoHelper<cl_sampler, cl_sampler_info, T>::getInfo(
                sampler, paramName); }
    
    /// get sampler info
    template<typename T>
    void getInfo(cl_sampler_info paramName, T& value) const
    { impl::GetInfoHelper<cl_sampler, cl_sampler_info, T>::getInfo(
                sampler, paramName, value); }
    
    /// get sampler info
    std::string getInfoString(cl_sampler_info paramName) const
    { return impl::GetInfoHelper<cl_sampler, cl_sampler_info, std::string>::getInfo(
                sampler, paramName); }
    
    /// get sampler info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_sampler_info paramName) const
    { return impl::GetInfoHelper<cl_sampler, cl_sampler_info, T>::getInfoVector(
                sampler, paramName); }
    
    /// get context
    Context getContext() const
    { return getInfo<Context>(CL_SAMPLER_CONTEXT); }
    
    /// check whether is normalized coords
    bool isNormalizedCoords() const
    { return getInfo<cl_bool>(CL_SAMPLER_NORMALIZED_COORDS); }
    
    /// get addressing mode
    cl_addressing_mode getAddressingMode() const
    { return getInfo<cl_addressing_mode>(CL_SAMPLER_ADDRESSING_MODE); }
    
    /// get filter mode
    cl_filter_mode getFilterMode() const
    { return getInfo<cl_filter_mode>(CL_SAMPLER_FILTER_MODE); }
    
    /// get reference count for this sampler
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_SAMPLER_REFERENCE_COUNT); }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Sampler, Option>:
                GetInfoRefHelper<CLType, InfoType, Sampler, Option>
    { };
}

class Kernel;

/// OpenCL Program object wrapper
class Program
{
private:
    cl_program program;
public:
    /// internal OpenCL type
    typedef cl_program cl_type;
    
    /// Source element (first - pointer to C string, second - optional size)
    typedef std::pair<const char*, size_t> Source;
    /// Binary element (first - pointer to data, second - size)
    typedef std::pair<const void*, size_t> Binary;
#if __CLPP_CL_ABI_VERSION >= 201U
    /// IL element (first - pointer to data, second - size)
    typedef std::pair<const void*, size_t> IL;
#endif
    /// sources type
    typedef std::vector<Source> Sources;
    /// binaries type
    typedef std::vector<Binary> Binaries;
    
    /// empty constructor
    Program() : program(NULL)
    { }
    
    /// constructor for program with source
    /**
     * \param context context
     * \param source pointer to source string
     * \param length optional length of string
     */
    Program(const Context& context, const char* source, size_t length = 0)
    {
        cl_int error;
        program = clCreateProgramWithSource(context, 1, &source, &length, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithSource");
    }
    
    /// constructor for program with source
    /**
     * \param context context
     * \param source source string
     */
    Program(const Context& context, const std::string& source)
    {
        cl_int error;
        const char* sourceCStr = source.c_str();
        program = clCreateProgramWithSource(context, 1, &sourceCStr, NULL, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithSource");
    }
    
    /// constructor for program with source
    /**
     * \param context context
     * \param sources pointers to source string
     */
    Program(const Context& context, const std::vector<const char*>& sources)
    {
        cl_int error;
        program = clCreateProgramWithSource(context, sources.size(),
                    const_cast<const char**>(&sources[0]), NULL, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithSource");
    }
    
    /// constructor for program with source
    /**
     * \param context context
     * \param sources strings of sources
     */
    Program(const Context& context, const std::vector<std::string>& sources)
    {
        cl_int error;
        std::vector<const char*> sourcePtrs(sources.size());
        for (cl_uint i = 0; i < sources.size(); i++)
            sourcePtrs[i] = sources[i].c_str();
        program = clCreateProgramWithSource(context, sources.size(),
                    const_cast<const char**>(&sourcePtrs[0]), NULL, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithSource");
    }
    
    /// constructor for program with source
    /**
     * \param context context
     * \param source source element
     */
    Program(const Context& context, const Source& source)
    {
        cl_int error;
        program = clCreateProgramWithSource(context, 1,
                    const_cast<const char**>(&source.first), &source.second, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithSource");
    }
    
    /// constructor for program with sources
    /**
     * \param context context
     * \param sources vector of source elements
     */
    Program(const Context& context, const std::vector<Source>& sources)
    {
        cl_int error;
        std::vector<size_t> lengths(sources.size());
        std::vector<const char*> sourcePtrs(sources.size());
        for (cl_uint i = 0; i < sources.size(); i++)
        {
            sourcePtrs[i] = sources[i].first;
            lengths[i] = sources[i].second;
        }
        program = clCreateProgramWithSource(context, sources.size(),
                    &sourcePtrs[0], &lengths[0], &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithSource");
    }
    
    /// constructor for program witn binary
    /**
     * \param context context
     * \param device device on which binaries will be loaded
     * \param length length of binary
     * \param binary binary data
     * \param binaryStatus status of loading
     */
    Program(const Context& context, const Device& device, size_t length,
            const unsigned char* binary, cl_int* binaryStatus = NULL)
    {
        cl_int error;
        program = clCreateProgramWithBinary(context, 1,
                reinterpret_cast<const cl_device_id*>(&device), &length, &binary,
                binaryStatus, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithBinary");
    }
    
    /// constructor for program witn binary
    Program(const Context& context, const Device& device, const Binary& binary,
                cl_int* binaryStatus = NULL)
    {
        cl_int error;
        program = clCreateProgramWithBinary(context, 1,
                reinterpret_cast<const cl_device_id*>(&device), &binary.second,
                (const unsigned char**)(&binary.first), binaryStatus, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithBinary");
    }
    
    /// constructor for program witn binary
    Program(const Context& context, const std::vector<Device>& devices,
            const std::vector<Binary>& binaries, std::vector<cl_int>* binaryStatuses = NULL)
    {
        cl_int error;
        binaryStatuses->resize(devices.size());
        std::vector<size_t> lengths(devices.size());
        std::vector<const unsigned char*> datas(devices.size());
        for (size_t i = 0; i < devices.size(); i++)
        {
            datas[i] = reinterpret_cast<const unsigned char*>(binaries[i].first);
            lengths[i] = binaries[i].second;
        }
        program = clCreateProgramWithBinary(context, devices.size(),
                reinterpret_cast<const cl_device_id*>(&devices[0]), &lengths[0],
                &datas[0], (binaryStatuses!=NULL)?&(*binaryStatuses)[0]:NULL, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithBinary");
    }
    
#if __CLPP_CL_ABI_VERSION >= 201U
    /// constructor for program with IL
    /**
     * \param context context
     * \param IL IL element
     */
    Program(const Context& context, const IL& il)
    {
        cl_int error;
        program = clCreateProgramWithIL(context, il.first, il.second, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithIL");
    }
#endif
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// constructor for builtin kernels (defined only if OpenCL ABI >= 1.2)
    /**
     * \param context context
     * \param device devices on whose binaries will be loaded
     * \param kernelNames kernel names to load
     */
    Program(const Context& context, const Device& device, const char* kernelNames)
    {
        cl_int error;
        program = clCreateProgramWithBuiltInKernels(context, 1,
                reinterpret_cast<const cl_device_id*>(&device), kernelNames, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithBuiltInKernels");
    }
    
    /// constructor for builtin kernels (defined only if OpenCL ABI >= 1.2)
    Program(const Context& context, const std::vector<Device>& devices,
            const char* kernelNames)
    {
        cl_int error;
        program = clCreateProgramWithBuiltInKernels(context, devices.size(),
                reinterpret_cast<const cl_device_id*>(&devices[0]), kernelNames, &error);
        if (program == NULL)
            throw Error(error, "clCreateProgramWithBuiltInKernels");
    }
#endif
    
    /// copy-constructor
    Program(const Program& _program) : program(_program.program)
    { impl::retainInternal(program); }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Program(Program&& _program) noexcept
            : program(_program.program)
    { _program.program = NULL; }
#endif
    
    /// copy-assignment
    Program& operator=(const Program& _program)
    {
        if (program == _program.program)
            return *this;
        impl::releaseInternal(program);
        program = _program.program;
        impl::retainInternal(program);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Program& operator=(Program&& _program)
    {
        impl::releaseInternal(program);
        program = _program.program;
        _program.program = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Program()
    { impl::releaseInternal(program); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(program); program = NULL; }
    
    /// logical negation
    bool operator!() const
    { return program==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return program!=NULL; }
    
    /// get (convert) cl_program
    cl_program operator()() const
    { return program; }
    
    /// convert to cl_program
    operator cl_program() const
    { return program; }
    
    /// comparison operator
    bool operator==(const Program& p2) const
    { return program==p2.program; }
    /// comparison operator
    bool operator!=(const Program& p2) const
    { return program!=p2.program; }
    
    /// create program from cl object
    static Program from(cl_program clobj, bool retain = true)
    {
        Program program;
        program.program = clobj;
        if (retain) impl::retainInternal(clobj);
        return program;
    }
    
    /// get program info
    template<typename T>
    T getInfo(cl_program_info paramName) const
    { return impl::GetInfoHelper<cl_program, cl_program_info, T>::getInfo(
                program, paramName); }
    
    /// get program info
    template<typename T>
    void getInfo(cl_program_info paramName, T& value) const
    { impl::GetInfoHelper<cl_program, cl_program_info, T>::getInfo(
                program, paramName, value); }
    
    /// get program info
    std::string getInfoString(cl_program_info paramName) const
    { return impl::GetInfoHelper<cl_program, cl_program_info, std::string>::getInfo(
                program, paramName); }
    
    /// get program info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_program_info paramName) const
    { return impl::GetInfoHelper<cl_program, cl_program_info, T>::getInfoVector(
                program, paramName); }
    
    /// get context
    Context getContext() const
    { return getInfo<Context>(CL_PROGRAM_CONTEXT); }
    
    /// get number of devices
    cl_uint getNumDevices() const
    { return getInfo<cl_uint>(CL_PROGRAM_NUM_DEVICES); }
    
    /// get devices of program
    std::vector<Device> getDevices() const
    { return getInfoVector<Device>(CL_PROGRAM_DEVICES); }
    
    /// get program source
    std::string getSource() const
    { return getInfoString(CL_PROGRAM_SOURCE); }
    
    /// get binary sizes
    std::vector<size_t> getBinarySizes() const
    { return getInfoVector<size_t>(CL_PROGRAM_BINARY_SIZES); }
    
    /// get binaries
    std::vector<std::vector<unsigned char> > getBinaries() const
    {
        const cl_uint numDevices = getNumDevices();
        std::vector<std::vector<unsigned char> > out(numDevices);
        std::vector<size_t> sizes = getBinarySizes();
        std::vector<unsigned char*> pointers(numDevices);
        for (cl_uint i = 0; i < numDevices; i++)
        {
            out[i].resize(sizes[i]);
            pointers[i] = (sizes[i]!=0)? &out[i][0] : NULL;
        }
        impl::getInfoInternal<cl_program, cl_program_info, impl::PROGOPT_PROGRAM>(
                    program, CL_PROGRAM_BINARIES, sizeof(unsigned char*)*numDevices,
                    &pointers[0], NULL);
        return out;
    }
    /// get binaries (warning: always free data pointers!)
    /** this method allocates space for program binaries and gets binaries from program object.
     * You must manually free allocated spaces after using! */
    void getBinaries(std::vector<unsigned char*>& out) const
    {
        const cl_uint numDevices = getNumDevices();
        std::vector<unsigned char*> tmpOut(numDevices, (unsigned char*)NULL);
        std::vector<size_t> sizes = getBinarySizes();
        try
        {
            for (cl_uint i = 0; i < numDevices; i++)
                if (sizes[i] != 0)
                    tmpOut[i] = new unsigned char[sizes[i]];
                else
                    tmpOut[i] = NULL;
            impl::getInfoInternal<cl_program, cl_program_info, impl::PROGOPT_PROGRAM>(
                    program, CL_PROGRAM_BINARIES, sizeof(unsigned char*)*numDevices,
                    &tmpOut[0], NULL);
            out = tmpOut;
        }
        catch(...)
        {   // free allocated areas for binaries
            for (cl_uint i = 0; i < numDevices; i++)
                if (tmpOut[i] != NULL) delete[] tmpOut[i];
            throw;
        }
    }
    
    /// get binaries to pointers allocated by caller
    void getBinariesToPtrs(const std::vector<unsigned char*>& out) const
    { impl::getInfoInternal<cl_program, cl_program_info, impl::PROGOPT_PROGRAM>(program,
                CL_PROGRAM_BINARIES, sizeof(unsigned char*)*out.size(),
                const_cast<unsigned char**>(&out[0]), NULL); }
    
#if __CLPP_CL_VERSION >= 102U
    /// get number of kernels (defined only if OpenCL 1.2)
    size_t getNumKernels() const
    { return getInfo<size_t>(CL_PROGRAM_NUM_KERNELS); }
    
    /// get kernel names (defined only if OpenCL 1.2)
    std::string getKernelNames() const
    { return getInfoString(CL_PROGRAM_KERNEL_NAMES); }
#endif

#if __CLPP_CL_VERSION >= 201U
    /// get program IL
    std::vector<unsigned char> getIL() const
    { return getInfoVector<unsigned char>(CL_PROGRAM_IL); }
#endif

#if __CLPP_CL_VERSION >= 202U
    /// is program have non-trivial global scope constructors (defined only if OpenCL 2.2)
    bool isScopeGlobalCtorsPresent() const
    { return getInfo<cl_bool>(CL_PROGRAM_SCOPE_GLOBAL_CTORS_PRESENT); }
    
    /// is program have non-trivial global scope destructors (defined only if OpenCL 2.2)
    bool isScopeGlobalDtorsPresent() const
    { return getInfo<cl_bool>(CL_PROGRAM_SCOPE_GLOBAL_DTORS_PRESENT); }
#endif
    
    /// get refererence count for this program
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_PROGRAM_REFERENCE_COUNT); }
    
    /// get program build info
    template<typename T>
    T getBuildInfo(const Device& device, cl_program_build_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_program, cl_device_id>, cl_program_build_info, T,
                impl::PROGOPT_BUILD>::getInfo(std::make_pair(program, device()), paramName); }
    
    /// get program build info
    template<typename T>
    void getBuildInfo(const Device& device, cl_program_build_info paramName, T& value) const
    { impl::GetInfoHelper<std::pair<cl_program, cl_device_id>, cl_program_build_info, T,
                impl::PROGOPT_BUILD>::getInfo(std::make_pair(program, device()),
                        paramName, value); }
    
    /// get program build info
    std::string getBuildInfoString(const Device& device, cl_program_build_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_program, cl_device_id>, cl_program_build_info,
                std::string, impl::PROGOPT_BUILD>::getInfo(std::make_pair(program, device()),
                        paramName); }
    
    /// get program build info as vector
    template<typename T>
    std::vector<T> getBuildInfoVector(const Device& device,
                cl_program_build_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_program, cl_device_id>, cl_program_build_info, T,
                impl::PROGOPT_BUILD>::getInfoVector(std::make_pair(program, device()),
                        paramName); }
    
    /// get build status
    cl_build_status getBuildStatus(const Device& device) const
    { return getBuildInfo<cl_build_status>(device, CL_PROGRAM_BUILD_STATUS); }
    
    /// get build options
    std::string getBuildOptions(const Device& device) const
    { return getBuildInfoString(device, CL_PROGRAM_BUILD_OPTIONS); }
    
    /// get build log
    std::string getBuildLog(const Device& device) const
    { return getBuildInfoString(device, CL_PROGRAM_BUILD_LOG); }
    
#if __CLPP_CL_VERSION >= 102U
    /// get build binary type (defined if only OpenCL >= 1.2)
    cl_program_binary_type getBinaryType(const Device& device) const
    { return getBuildInfo<cl_program_binary_type>(device, CL_PROGRAM_BINARY_TYPE); }
#endif

#if __CLPP_CL_VERSION >= 200U
    /// get build global variable total size (defined if only OpenCL >= 2.0)
    size_t getBuildGlobalVariableTotalSize(const Device& device) const
    { return getBuildInfo<size_t>(device, CL_PROGRAM_BUILD_GLOBAL_VARIABLE_TOTAL_SIZE); }
#endif

    /// build program
    /** build program. if notify is not NULL this method may returns immediately and
     * will notifies about building finish by calling notification callback.
     * \param options build options
     * \param notify notification callback
     * \param userData userData for callback
     */
    void build(const char* options = NULL,
               ProgramNotifyCallback notify = NULL, void* userData = NULL) const
    {
        const cl_int error = clBuildProgram(program, 0, NULL, options, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clBuildProgram");
    }

    /// build program
    /** build program. if notify is not NULL this method may returns immediately and
     * will notifies about building finish by calling notification callback.
     * \param device device for which program will be built
     * \param options build options
     * \param notify notification callback
     * \param userData userData for callback
     */
    void build(const Device& device, const char* options = NULL,
               ProgramNotifyCallback notify = NULL, void* userData = NULL) const
    { 
        const cl_int error = clBuildProgram(program, 1,
                reinterpret_cast<const cl_device_id*>(&device), options, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clBuildProgram");
    }
    
    /// build program
    void build(const std::vector<Device>& devices, const char* options = NULL,
               ProgramNotifyCallback notify = NULL, void* userData = NULL) const
    {
        const cl_int error = clBuildProgram(program, devices.size(),
                (!devices.empty())?reinterpret_cast<const cl_device_id*>(&devices[0]):NULL,
                options, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clBuildProgram");
    }
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// compile program (defined only if OpenCL ABI >= 1.2)
    /** compile program. if notify is not NULL this method may returns immediately and
     * will notifies about compilation finish by calling notification callback.
     * \param options compile options
     * \param notify notification callback
     * \param userData userData for callback
     */
    void compile(const char* options = NULL, ProgramNotifyCallback notify = NULL,
                 void* userData = NULL) const
    {
        const cl_int error = clCompileProgram(program, 0, NULL, options,
                0, NULL, NULL, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clCompileProgram");
    }

    /// compile program (defined only if OpenCL ABI >= 1.2)
    /** compile program. if notify is not NULL this method may returns immediately and
     * will notifies about compilation finish by calling notification callback.
     * \param device device for which program will be compiled
     * \param options compile options
     * \param notify notification callback
     * \param userData userData for callback
     */
    void compile(const Device& device, const char* options = NULL,
               ProgramNotifyCallback notify = NULL, void* userData = NULL) const
    {
        const cl_int error = clCompileProgram(program, 1,
                reinterpret_cast<const cl_device_id*>(&device), options,
                0, NULL, NULL, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clCompileProgram");
    }
    
    /// compile program (defined only if OpenCL ABI >= 1.2)
    /** compile program. if notify is not NULL this method may returns immediately and
     * will notifies about compilation finish by calling notification callback. */
    void compile(const std::vector<Device>& devices, const char* options = NULL,
               ProgramNotifyCallback notify = NULL, void* userData = NULL) const
    {
        const cl_int error = clCompileProgram(program, devices.size(),
                (!devices.empty())?reinterpret_cast<const cl_device_id*>(&devices[0]):NULL,
                options, 0, NULL, NULL, notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clCompileProgram");
    }
    
    /// compile program (defined only if OpenCL ABI >= 1.2)
    /** compile program. if notify is not NULL this method may returns immediately and
     * will notifies about compilation finish by calling notification callback. */
    void compile(const std::vector<Program>& headers,
               const std::vector<const char*>& headerNames,
               const char* options = NULL, ProgramNotifyCallback notify = NULL,
               void* userData = NULL) const
    { compile(std::vector<Device>(), headers, headerNames, options, notify, userData); }
    
    /// compile program (defined only if OpenCL ABI >= 1.2)
    /** compile program. if notify is not NULL this method may returns immediately and
     * will notifies about compilation finish by calling notification callback. */
    void compile(const Device& device, const std::vector<Program>& headers,
               const std::vector<const char*>& headerNames,
               const char* options = NULL, ProgramNotifyCallback notify = NULL,
               void* userData = NULL) const
    {
        const cl_int error = clCompileProgram(program, 1,
                reinterpret_cast<const cl_device_id*>(&device), options,
                headers.size(), reinterpret_cast<const cl_program*>(&headers[0]),
                const_cast<const char**>(&headerNames[0]), notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clCompileProgram");
    }
    
    /// compile program (defined only if OpenCL ABI >= 1.2)
    /** compile program. if notify is not NULL this method may returns immediately and
     * will notifies about compilation finish by calling notification callback.
     * \param devices device for which program will be compiled
     * \param headers input headers
     * \param headerNames input header names
     * \param options compile options
     * \param notify notification callback
     * \param userData userData for callback
     */
    void compile(const std::vector<Device>& devices, const std::vector<Program>& headers,
               const std::vector<const char*>& headerNames,
               const char* options = NULL, ProgramNotifyCallback notify = NULL,
               void* userData = NULL) const
    {
        const cl_int error = clCompileProgram(program, devices.size(),
                (!devices.empty())?reinterpret_cast<const cl_device_id*>(&devices[0]):NULL,
                options, headers.size(), reinterpret_cast<const cl_program*>(&headers[0]),
                const_cast<const char**>(&headerNames[0]), notify, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clCompileProgram");
    }
    
    /// link many program object into executable program (defined only if OpenCL ABI >= 1.2)
    /** link program. if notify is not NULL this method may returns immediately and
     * will notifies about linkage finish by calling notification callback. */
    static Program link(const Context& context, const std::vector<Program>& programs,
            const char* options = NULL, ProgramNotifyCallback notify = NULL,
            void* userData = NULL)
    { return link(context, std::vector<Device>(), programs, options, notify, userData); }
                
    /// link many program object into executable program (defined only if OpenCL ABI >= 1.2)
    /** link program. if notify is not NULL this method may returns immediately and
     * will notifies about linkage finish by calling notification callback. */
    static Program link(const Context& context, const Device& device,
            const std::vector<Program>& programs, const char* options = NULL,
            ProgramNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        Program out;
        out.program = clLinkProgram(context, 1, reinterpret_cast<const cl_device_id*>(&device),
                options, programs.size(), reinterpret_cast<const cl_program*>(&programs[0]),
                notify, userData, &error);
        if (!out)
            throw Error(error, "clLinkProgram");
        return out;
    }
    
    /// link many program object into executable program (defined only if OpenCL ABI >= 1.2)
    /** link program. if notify is not NULL this method may returns immediately and
     * will notifies about linkage finish by calling notification callback. */
    static Program link(const Context& context, const std::vector<Device>& devices,
            const std::vector<Program>& programs, const char* options = NULL,
            ProgramNotifyCallback notify = NULL, void* userData = NULL)
    {
        cl_int error;
        Program out;
        out.program = clLinkProgram(context, devices.size(),
                (!devices.empty())?reinterpret_cast<const cl_device_id*>(&devices[0]):NULL,
                options, programs.size(),
                reinterpret_cast<const cl_program*>(&programs[0]), notify, userData, &error);
        if (!out)
            throw Error(error, "clLinkProgram");
        return out;
    }
#endif
    
    /// create kernels in program for all functions
    std::vector<Kernel> createKernels() const;
    
    /// create specified number of kernels
    std::vector<Kernel> kernelCopies(const char* name, cl_uint number) const;
    
#if __CLPP_CL_ABI_VERSION >= 202U
    /// set program specialization constant (defined only if OpenCL ABI >= 2.2)
    void setSpecializationConstant(cl_uint specId,
                        const std::vector<unsigned char>& value) const
    {
        cl_int error;
        error = clSetProgramSpecializationConstant(program, specId, value.size(),
                                (const void*)(&value[0]));
        if (error != CL_SUCCESS)
            throw Error(error, "clSetProgramSpecializationConstant");
    }
    
    /// set program release callback (defined only if OpenCL ABI >= 2.2)
    void setReleaseCallback(ProgramReleaseCallback callback, void* userData = NULL) const
    {
        cl_int error;
        error = clSetProgramReleaseCallback(program, callback, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetProgramReleaseCalback");
    }
#endif
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Program, Option>:
                GetInfoRefHelper<CLType, InfoType, Program, Option>
    { };
}

/// OpenCL Kernel object wrapper
class Kernel
{
private:
    cl_kernel kernel;
public:
    /// internal OpenCL type
    typedef cl_kernel cl_type;
    
    /// empty constructor
    Kernel() : kernel(NULL)
    { }
    
    /// constructor with program and kernelName
    /**
     * \param program program
     * \param kernelName kernel name
     */
    Kernel(const Program& program, const char* kernelName)
    {
        cl_int error;
        kernel = clCreateKernel(program, kernelName, &error);
        if (kernel == NULL)
            throw Error(error, "clCreateKernel");
    }
    
    /// copy-constructor
    Kernel(const Kernel& _kernel) : kernel(_kernel.kernel)
    { impl::retainInternal(kernel); }
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Kernel(Kernel&& _kernel) noexcept
            : kernel(_kernel.kernel)
    { _kernel.kernel = NULL; }
#endif
    
    /// copy-assignment
    Kernel& operator=(const Kernel& _kernel)
    {
        if (kernel == _kernel.kernel)
            return *this;
        impl::releaseInternal(kernel);
        kernel = _kernel.kernel;
        impl::retainInternal(kernel);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Kernel& operator=(Kernel&& _kernel)
    {
        impl::releaseInternal(kernel);
        kernel = _kernel.kernel;
        _kernel.kernel = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Kernel()
    { impl::releaseInternal(kernel); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(kernel); kernel = NULL; }
    
    /// logical negation
    bool operator!() const
    { return kernel==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return kernel!=NULL; }
    
    /// get (convert) cl_kernel
    cl_kernel operator()() const
    { return kernel; }
    
    /// convert to cl_kernel
    operator cl_kernel() const
    { return kernel; }
    
    /// comparison operator
    bool operator==(const Kernel& k2) const
    { return kernel==k2.kernel; }
    /// comparison operator
    bool operator!=(const Kernel& k2) const
    { return kernel!=k2.kernel; }
    
    /// create kernel from cl object
    static Kernel from(cl_kernel clobj, bool retain = true)
    {
        Kernel kernel;
        kernel.kernel = clobj;
        if (retain) impl::retainInternal(clobj);
        return kernel;
    }
    
    /// get kernel info
    template<typename T>
    T getInfo(cl_kernel_info paramName) const
    { return impl::GetInfoHelper<cl_kernel, cl_kernel_info, T>::getInfo(
                kernel, paramName); }
    
    /// get kernel info
    template<typename T>
    void getInfo(cl_kernel_info paramName, T& value) const
    { impl::GetInfoHelper<cl_kernel, cl_kernel_info, T>::getInfo(
                kernel, paramName, value); }
    
    /// get kernel info
    std::string getInfoString(cl_kernel_info paramName) const
    { return impl::GetInfoHelper<cl_kernel, cl_kernel_info, std::string>::getInfo(
                kernel, paramName); }
    
    /// get kernel info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_kernel_info paramName) const
    { return impl::GetInfoHelper<cl_kernel, cl_kernel_info, T>::getInfoVector(
                kernel, paramName); }
    
    /// get function name
    std::string getFunctionName() const
    { return getInfoString(CL_KERNEL_FUNCTION_NAME); }
    
    /// get function name
    std::string getName() const
    { return getInfoString(CL_KERNEL_FUNCTION_NAME); }
    
    /// get kernel number of arguments
    cl_uint getNumArgs() const
    { return getInfo<cl_uint>(CL_KERNEL_NUM_ARGS); }
    
    /// get context
    Context getContext() const
    { return getInfo<Context>(CL_KERNEL_CONTEXT); }
    
    /// get program
    Program getProgram() const
    { return getInfo<Program>(CL_KERNEL_PROGRAM); }
    
    /// get reference count for this kernel
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_KERNEL_REFERENCE_COUNT); }
    
#if __CLPP_CL_VERSION >= 102U
    /// get kernel attributes (defined only if OpenCL >= 1.2)
    std::string getAttributes() const
    { return getInfoString(CL_KERNEL_ATTRIBUTES); }
#endif
    
    /// get kernel work group info
    template<typename T>
    T getWorkGroupInfo(const Device& device, cl_kernel_work_group_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_kernel, cl_device_id>,
                cl_kernel_work_group_info, T, impl::KERNOPT_WORKGROUP>::getInfo(
                        std::make_pair(kernel, device()), paramName); }
    
    /// get kernel work group info
    template<typename T>
    void getWorkGroupInfo(const Device& device,
                cl_kernel_work_group_info paramName, T& value) const
    { impl::GetInfoHelper<std::pair<cl_kernel, cl_device_id>, cl_kernel_work_group_info, T,
                impl::KERNOPT_WORKGROUP>::getInfo(std::make_pair(kernel, device()),
                        paramName, value); }
    
    /// get kernel work group info
    std::string getWorkGroupInfoString(const Device& device,
                cl_kernel_work_group_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_kernel, cl_device_id>, cl_kernel_work_group_info,
                std::string, impl::KERNOPT_WORKGROUP>::getInfo(std::make_pair(kernel, device()),
                        paramName); }
    
    /// get kernel work group info as vector
    template<typename T>
    std::vector<T> getWorkGroupInfoVector(const Device& device,
                cl_kernel_work_group_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_kernel, cl_device_id>,
                cl_kernel_work_group_info, T, impl::KERNOPT_WORKGROUP>::getInfoVector(
                        std::make_pair(kernel, device()), paramName); }
    
#if __CLPP_CL_VERSION >= 102U
    /// get global work size (defined only if OpenCL >= 1.2)
    Size3 getGlobalWorkSize(const Device& device) const
    { return getWorkGroupInfo<Size3>(device, CL_KERNEL_GLOBAL_WORK_SIZE); }
#endif
    
    /// get work group size
    size_t getWorkGroupSize(const Device& device) const
    { return getWorkGroupInfo<size_t>(device, CL_KERNEL_WORK_GROUP_SIZE); }
    
    /// get compiled work group size
    Size3 getCompileWorkGroupSize(const Device& device) const
    { return getWorkGroupInfo<Size3>(device, CL_KERNEL_COMPILE_WORK_GROUP_SIZE); }
    
    /// get local memory size
    cl_ulong getLocalMemSize(const Device& device) const
    { return getWorkGroupInfo<cl_ulong>(device, CL_KERNEL_LOCAL_MEM_SIZE); }
#if __CLPP_CL_VERSION >= 101U
    /// get preferred work group size multiple (defined only if OpenCL >= 1.1)
    size_t getPreferredWorkGroupSizeMultiple(const Device& device) const
    { return getWorkGroupInfo<size_t>(device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE); }
    
    /// get private memory size (defined only if OpenCL >= 1.1)
    cl_ulong getPrivateMemSize(const Device& device) const
    { return getWorkGroupInfo<cl_ulong>(device, CL_KERNEL_PRIVATE_MEM_SIZE); }
#endif
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// get kernel arg info (defined only if OpenCL >= 1.2)
    template<typename T>
    T getArgInfo(cl_uint argIdx, cl_kernel_arg_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_kernel, cl_uint>, cl_kernel_arg_info, T,
                impl::KERNOPT_ARG>::getInfo(std::make_pair(kernel, argIdx), paramName); }
    
    /// get kernel arg info (defined only if OpenCL >= 1.2)
    template<typename T>
    void getArgInfo(cl_uint argIdx, cl_kernel_arg_info paramName, T& value) const
    { impl::GetInfoHelper<std::pair<cl_kernel, cl_uint>, cl_kernel_arg_info, T,
                impl::KERNOPT_ARG>::getInfo(std::make_pair(kernel, argIdx),
                        paramName, value); }
    
    /// get kernel arg info (defined only if OpenCL >= 1.2)
    std::string getArgInfoString(cl_uint argIdx, cl_kernel_arg_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_kernel, cl_uint>, cl_kernel_arg_info,
                std::string, impl::KERNOPT_ARG>::getInfo(std::make_pair(kernel, argIdx),
                        paramName); }
    
    /// get kernel arg info as vector (defined only if OpenCL >= 1.2)
    template<typename T>
    std::vector<T> getArgInfoVector(cl_uint argIdx, cl_kernel_arg_info paramName) const
    { return impl::GetInfoHelper<std::pair<cl_kernel, cl_uint>, cl_kernel_arg_info, T,
                impl::KERNOPT_ARG>::getInfoVector(std::make_pair(kernel, argIdx),
                        paramName); }
    
    /// get argument address qualifier (defined only if OpenCL >= 1.2)
    cl_kernel_arg_address_qualifier getArgAddressQualifier(cl_uint argIdx) const
    { return getArgInfo<cl_kernel_arg_address_qualifier>(argIdx,
                CL_KERNEL_ARG_ADDRESS_QUALIFIER); }
    
    /// get argument access qualifier (defined only if OpenCL >= 1.2)
    cl_kernel_arg_access_qualifier getArgAccessQualifier(cl_uint argIdx) const
    { return getArgInfo<cl_kernel_arg_access_qualifier>(argIdx,
                CL_KERNEL_ARG_ACCESS_QUALIFIER); }
    
    /// get argument type name (defined only if OpenCL >= 1.2)
    std::string getArgTypeName(cl_uint argIdx) const
    { return getArgInfoString(argIdx, CL_KERNEL_ARG_TYPE_NAME); }
    
    /// get argument type qualifier (defined only if OpenCL >= 1.2)
    cl_kernel_arg_type_qualifier getArgTypeQualifier(cl_uint argIdx) const
    { return getArgInfo<cl_kernel_arg_type_qualifier>(argIdx, CL_KERNEL_ARG_TYPE_QUALIFIER); }
    
    /// get argument name (defined only if OpenCL >= 1.2)
    std::string getArgName(cl_uint argIdx) const
    { return getArgInfoString(argIdx, CL_KERNEL_ARG_NAME); }
#endif
    
#if __CLPP_CL_ABI_VERSION >= 201U
    /// get kernel subgroup info (defined only if OpenCL >= 2.1)
    template<typename T>
    T getSubGroupInfo(cl_device_id device, size_t inputSize, const void* input,
                      cl_kernel_arg_info paramName) const
    { return impl::GetInfoHelper<impl::SubGroupObj, cl_kernel_sub_group_info, T,
                impl::KERNOPT_SUBGROUP>::getInfo(
                    impl::SubGroupObj(kernel, device, inputSize, input), paramName); }
    
    /// get kernel subgroup info (defined only if OpenCL >= 2.1)
    template<typename T>
    void getSubGroupInfo(cl_device_id device, size_t inputSize, const void* input,
                    cl_kernel_arg_info paramName, T& value) const
    { impl::GetInfoHelper<impl::SubGroupObj, cl_kernel_sub_group_info, T,
                impl::KERNOPT_SUBGROUP>::getInfo(
                        impl::SubGroupObj(kernel, device, inputSize, input),
                        paramName, value); }
    
    /// get kernel subgroup info (defined only if OpenCL >= 2.1)
    std::string getSubGroupInfoString(cl_device_id device, size_t inputSize,
                        const void* input, cl_kernel_sub_group_info paramName) const
    { return impl::GetInfoHelper<impl::SubGroupObj, cl_kernel_sub_group_info,
                std::string, impl::KERNOPT_SUBGROUP>::getInfo(
                        impl::SubGroupObj(kernel, device, inputSize, input),
                        paramName); }
    
    /// get kernel subgroup info as vector (defined only if OpenCL >= 2.1)
    template<typename T>
    std::vector<T> getSubGroupInfoVector(cl_device_id device, size_t inputSize,
                        const void* input, cl_kernel_sub_group_info paramName) const
    { return impl::GetInfoHelper<impl::SubGroupObj, cl_kernel_sub_group_info, T,
                impl::KERNOPT_SUBGROUP>::getInfoVector(
                        impl::SubGroupObj(kernel, device, inputSize, input),
                        paramName); }
    
    /// get maximum subgroup size for kernel (defined only if OpenCL >= 2.1)
    size_t getMaxSubGroupSizeForNDRange(const Device& device, Size3 input) const
    {
        const size_t inSize = input[2]!=0 ? 3 : input[1]!=0 ? 2 : 1;
        return getSubGroupInfo<size_t>(device, sizeof(size_t)*inSize, &input,
                CL_KERNEL_MAX_SUB_GROUP_SIZE_FOR_NDRANGE);
    }
    
    ///get number of subgroups for given local size (defined only if OpenCL >= 2.1)
    size_t getSubGroupCountForNDRange(const Device& device, Size3 input) const
    {
        const size_t inSize = input[2]!=0 ? 3 : input[1]!=0 ? 2 : 1;
        return getSubGroupInfo<size_t>(device, sizeof(size_t)*inSize, &input,
                CL_KERNEL_SUB_GROUP_COUNT_FOR_NDRANGE);
    }
    
    /// get local size for subgroup count (defined only if OpenCL >= 2.1)
    Size3 getLocalSizeForSubGroupCount(const Device& device, size_t input) const
    { return getSubGroupInfo<Size3>(device, sizeof(size_t), &input,
            CL_KERNEL_LOCAL_SIZE_FOR_SUB_GROUP_COUNT); }
    
    /// get max number of subgroups (defined only if OpenCL >= 2.1)
    size_t getMaxNumSubGroups(const Device& device) const
    { return getSubGroupInfo<size_t>(device, 0, NULL, CL_KERNEL_MAX_NUM_SUB_GROUPS); }
    
    /// get compile number of subgroups (defined only if OpenCL >= 2.1)
    size_t getCompileNumSubGroups(const Device& device) const
    { return getSubGroupInfo<size_t>(device, 0, NULL, CL_KERNEL_COMPILE_NUM_SUB_GROUPS); }
#endif
    /// set kernel argument
    /**
     * \param argIndex argument index
     * \param value value for argument
     */
    template<typename T>
    void setArg(cl_uint argIndex, const T& value) const
    {
        const cl_int error = clSetKernelArg(kernel, argIndex, sizeof(T), &value);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetKernelArg");
    }
    
#if __CLPP_CL_ABI_VERSION >= 200U
    /// set kernel argument as SVM pointer (defined only if OpenCL ABI >= 2.0)
    void setArgSVMPointer(cl_uint argIndex, const void* ptr) const
    {
        const cl_int error = clSetKernelArgSVMPointer(kernel, argIndex, ptr);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetKernelArgSVMPointer");
    }
#endif
    
#ifdef __CLPP_CPP0X
private:
    template<typename T>
    void setArgsInternal(cl_uint argIndex, const T& value) const
    { setArg(argIndex, value); }
    
    template<typename T, typename... Args>
    void setArgsInternal(cl_uint argIndex, const T& value, Args... args) const
    {
        setArg(argIndex, value);
        setArgsInternal(argIndex+1, args...);
    }
public:
    /// set kernel arguments
    template<typename T, typename... Args>
    void setArgs(const T& value, Args... args) const
    { setArgsInternal(0, value, args...); }
#else
    /// set kernel arguments
    template<typename T1>
    void setArgs(const T1& value1) const
    { setArg(0, value1); }
    
    /// set kernel arguments
    template<typename T1, typename T2>
    void setArgs(const T1& value1, const T2& value2) const
    { setArg(0, value1); setArg(1, value2); }
    
    /// set kernel arguments
    template<typename T1, typename T2, typename T3>
    void setArgs(const T1& value1, const T2& value2, const T3& value3) const
    { setArg(0, value1); setArg(1, value2); setArg(2, value3); }
    
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4) const
    { setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4); }
    
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5);
    }
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 6))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 7))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 8))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 9))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 10))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 11))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 12))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 13))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 14))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 15))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 16))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16 value16) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 17))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16 value16, const T17& value17) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 18))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 19))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18, typename T19>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18,
            const T19& value19) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
        setArg(18, value19);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 20))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18, typename T19, typename T20>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18,
            const T19& value19, const T20& value20) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
        setArg(18, value19); setArg(19, value20);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 21))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18, typename T19, typename T20, typename T21>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18,
            const T19& value19, const T20& value20, const T21& value21) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
        setArg(18, value19); setArg(19, value20); setArg(20, value21);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 22))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18, typename T19, typename T20, typename T21, typename T22>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18,
            const T19& value19, const T20& value20, const T21& value21,
            const T22& value22) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
        setArg(18, value19); setArg(19, value20); setArg(20, value21);
        setArg(21, value22);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 23))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18, typename T19, typename T20, typename T21, typename T22,
            typename T23>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18,
            const T19& value19, const T20& value20, const T21& value21,
            const T22& value22, const T23& value23) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
        setArg(18, value19); setArg(19, value20); setArg(20, value21);
        setArg(21, value22); setArg(22, value23);
    }
#   endif
#   if !(defined(_MSC_VER) && defined(_VARIADIC_MAX) && (_VARIADIC_MAX < 24))
    /// set kernel arguments
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6,
            typename T7, typename T8, typename T9, typename T10, typename T11, typename T12,
            typename T13, typename T14, typename T15, typename T16, typename T17,
            typename T18, typename T19, typename T20, typename T21, typename T22,
            typename T23, typename T24>
    void setArgs(const T1& value1, const T2& value2, const T3& value3, const T4& value4,
            const T5& value5, const T6& value6, const T7& value7, const T8& value8,
            const T9& value9, const T10& value10, const T11& value11, const T12& value12,
            const T13& value13, const T14& value14, const T15& value15,
            const T16& value16, const T17& value17, const T18& value18,
            const T19& value19, const T20& value20, const T21& value21,
            const T22& value22, const T23& value23, const T24& value24) const
    {
        setArg(0, value1); setArg(1, value2); setArg(2, value3); setArg(3, value4);
        setArg(4, value5); setArg(5, value6); setArg(6, value7); setArg(7, value8);
        setArg(8, value9); setArg(9, value10); setArg(10, value11); setArg(11, value12);
        setArg(12, value13); setArg(13, value14); setArg(14, value15);
        setArg(15, value16); setArg(16, value17); setArg(17, value18);
        setArg(18, value19); setArg(19, value20); setArg(20, value21);
        setArg(21, value22); setArg(22, value23); setArg(23, value24);
    }
#   endif
#endif
    
#if __CLPP_CL_ABI_VERSION >= 200U
    /// set kernel exec info (defined only if OpenCL ABI >= 2.0)
    /**
     * \param paramName exec info parameter name
     * \param value value to set
     */
    template<typename T>
    void setExecInfo(cl_kernel_exec_info paramName, const T& value) const
    {
        const cl_int error = clSetKernelExecInfo(kernel, paramName, sizeof(T), &value);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetKernelExecInfo");
    }
    
    /// set kernel exec info (defined only if OpenCL ABI >= 2.0)
    template<typename T>
    void setExecInfoVector(cl_kernel_exec_info paramName, const std::vector<T>& vector) const
    {
        const cl_int error = clSetKernelExecInfo(kernel, paramName,
                    sizeof(T)*vector.size(), &vector[0]);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetKernelExecInfo");
    }
    
    /// set exec info SVM pointers (defined only if OpenCL ABI >= 2.0)
    void setSVMPointers(const std::vector<void*>& ptrs) const
    { setExecInfoVector<void*>(CL_KERNEL_EXEC_INFO_SVM_PTRS, ptrs); }
    
    /// set SVM fine-grain system (defined only if OpenCL ABI >= 2.0)
    void setSVMFineGrainSystem(bool fineGrain = true) const
    {
        const cl_bool val = fineGrain;
        setExecInfo<cl_bool>(CL_KERNEL_EXEC_INFO_SVM_FINE_GRAIN_SYSTEM, val);
    }
    
    /// set SVM coarse-grain system (defined only if OpenCL ABI >= 2.0)
    void setSVMCoarseGrainSystem() const
    { setExecInfo<cl_bool>(CL_KERNEL_EXEC_INFO_SVM_FINE_GRAIN_SYSTEM, CL_FALSE); }
#endif

#if __CLPP_CL_ABI_VERSION >= 201U
    Kernel clone() const
    {
        cl_int error;
        Kernel kernel;
        kernel.kernel = clCloneKernel(kernel, &error);
        if (kernel.kernel==NULL)
            throw Error(error, "clCloneKernel");
        return kernel;
    }
#endif
};

/// set kernel argument
template<>
inline void Kernel::setArg(cl_uint argIndex, const Local& value) const
{
    const cl_int error = clSetKernelArg(kernel, argIndex, value.size, NULL);
    if (error != CL_SUCCESS)
        throw Error(error, "clSetKernelArg");
}

/// set kernel argument
template<>
inline void Kernel::setArg(cl_uint argIndex, const Null& value) const
{ }

#if __CLPP_CL_ABI_VERSION >= 200U
/// set kernel argument (defined only if OpenCL ABI >= 2.0)
template<>
inline void Kernel::setArg(cl_uint argIndex, const SVMPtr& value) const
{
    const cl_int error = clSetKernelArgSVMPointer(kernel, argIndex, value.ptr);
    if (error != CL_SUCCESS)
        throw Error(error, "clSetKernelArgSVMPointer");
}

/// set exec info (defined only if OpenCL ABI >= 2.0)
template<>
inline void Kernel::setExecInfo(cl_kernel_exec_info paramName, const bool& value) const
{
    const cl_bool valToSet = value;
    const cl_int error = clSetKernelExecInfo(kernel, paramName, sizeof(cl_bool), &valToSet);
    if (error != CL_SUCCESS)
        throw Error(error, "clSetKernelExecInfo");
}
#endif

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Kernel, Option>:
                GetInfoRefHelper<CLType, InfoType, Kernel, Option>
    { };
}

/// create kernels in program for all functions
inline std::vector<Kernel> Program::createKernels() const
{
    cl_uint outNum;
    cl_int error = clCreateKernelsInProgram(program, 0, NULL, &outNum);
    if (error != CL_SUCCESS)
        throw Error(error, "clCreateKernelsInProgram");
    std::vector<Kernel> outKernels(outNum);
    error = clCreateKernelsInProgram(program, outNum,
                reinterpret_cast<cl_kernel*>(&outKernels[0]), NULL);
    if (error != CL_SUCCESS)
        throw Error(error, "clCreateKernelsInProgram");
    return outKernels;
}

/// create specified number of kernels
inline std::vector<Kernel> Program::kernelCopies(const char* name, cl_uint number) const
{
    std::vector<Kernel> kernels(number);
    for (cl_uint i = 0; i < number; i++)
        kernels[i] = Kernel(*this, name);
    return kernels;
}

#if __CLPP_CL_ABI_VERSION >= 200U
/// SVMAllocator (defined only if OpenCL ABI >= 2.0)
template<typename T>
class SVMAllocator
{
public:
    typedef T value_type;    ///< value
    typedef T* pointer; ///< pointer
    typedef const T* const_pointer;     ///< constant pointer
    typedef T& reference;       ///< reference
    typedef const T& const_reference;   ///< constant reference
    typedef std::size_t size_type;      ///< size type
    typedef std::ptrdiff_t difference_type;     ///< difference type
private:
    template<typename U>
    friend bool operator==(const SVMAllocator<U>& a1, const SVMAllocator<U>& a2);
    template<typename U>
    friend bool operator!=(const SVMAllocator<U>& a1, const SVMAllocator<U>& a2);
    
    Context context;
    cl_svm_mem_flags flags;
    cl_uint alignment;
public:
    /// constructor
    SVMAllocator(const Context& _context, cl_svm_mem_flags _flags, cl_uint _alignment = 0)
            : context(_context), flags(_flags), alignment(_alignment)
    { }
    
    /// convert reference to address
    pointer address(reference x) const
    { return &x; }
    
    /// convert reference to address
    const_pointer address(const_reference x) const
    { return &x; }
    
    /// allocate space
    pointer allocate(size_type n, void* hint = 0)
    {
        if (n > max_size())
            throw std::bad_alloc();
        return static_cast<pointer>(context.SVMAlloc(flags, n*sizeof(value_type), alignment));
    }
    
    /// deallocate space
    void deallocate(pointer p, size_type n)
    { return context.SVMFree(p); }
    
    /// max elements that can be allocated
    size_type max_size() const
    { return std::numeric_limits<size_type>::max()/sizeof(value_type); }

    /// rebind helper
    template< class U > struct rebind
    {   /// other type for rebinding
        typedef SVMAllocator<U> other;
    };
    
#   ifdef __CLPP_CPP0X
    /// construct object
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args)
    { ::new((void *)p) U(std::forward<Args>(args)...); }
    
    /// destroy object
    template<typename U>
    void destroy(U* p) { p->~U(); }
#   else
    /// construct object
    void construct(pointer p, const_reference v) 
    { ::new((void *)p) T(v); }
    
    /// destroy object
    void destroy(pointer p) { p->~T(); }
#   endif
};

/// comparison of allocators
template<typename T1, typename T2>
inline bool operator==(const SVMAllocator<T1>& a1, const SVMAllocator<T2>& a2)
{ return a1.context==a2.context && a1.flags==a2.flags && a1.alignment==a2.alignment; }

/// comparison of allocators
template<typename T1, typename T2>
inline bool operator!=(const SVMAllocator<T1>& a1, const SVMAllocator<T2>& a2)
{ return a1.context!=a2.context || a1.flags!=a2.flags || a1.alignment!=a2.alignment; }
#endif

/// OpenCL Event object wrapper
class Event
{
protected:
    /// OpenCL event object
    cl_event event;
public:
    /// internal OpenCL type
    typedef cl_event cl_type;
    
    /// empty constructor
    Event() : event(NULL)
    { }
    
    /// copy-constructor
    Event(const Event& _event) : event(_event.event)
    { impl::retainInternal(event); }
    
#ifdef __CLPP_EVENT_FROM_GLSYNC
    /// construct event from GLsync (defined if __CLPP_EVENT_FROM_GLSYNC)
    Event(const Context& context, cl_GLsync glsync)
    {
#   if __CLPP_CL_ABI_VERSION >= 102U
        /* slow but sure */
        cl_platform_id platform = NULL;
        std::vector<cl_context_properties> props = context.getProperties();
        if (!props.empty())
            for (std::vector<cl_context_properties>::const_iterator p = props.begin();
                        *p != 0; p += 2)
                if (*p == CL_CONTEXT_PLATFORM) // get platform
                    platform = cl_platform_id(p[1]);
        clCreateEventFromGLsyncKHR_fn createEventFromGLsyncKHR =
            reinterpret_cast<clCreateEventFromGLsyncKHR_fn>(
                clGetExtensionFunctionAddressForPlatform(platform,
                            "clCreateEventFromGLsyncKHR"));
        if (platform == NULL)
            throw Error("Null platform for clGetExtensionFunctionAddressForPlatform");
#   else
        static volatile clCreateEventFromGLsyncKHR_fn createEventFromGLsyncKHR = NULL;
        if (createEventFromGLsyncKHR == NULL)
        {
            createEventFromGLsyncKHR = reinterpret_cast<clCreateEventFromGLsyncKHR_fn>(
                    clGetExtensionFunctionAddress("clCreateEventFromGLsyncKHR"));
            if (createEventFromGLsyncKHR == NULL)
                createEventFromGLsyncKHR = clCreateEventFromGLsyncKHR_fn(1);
        }
#   endif
        cl_int error;
        if (createEventFromGLsyncKHR <= clCreateEventFromGLsyncKHR_fn(1))
            throw Error("Unsupported clCreateEventFromGLsyncKHR");
        event = createEventFromGLsyncKHR(context, glsync, & error);
        if (event == NULL)
            throw Error(error, "clCreateEventFromGLsyncKHR");
    }
#endif
    
#ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    Event(Event&& _event) noexcept
            : event(_event.event)
    { _event.event = NULL; }
#endif
    
    /// copy-assignment
    Event& operator=(const Event& _event)
    {
        if (event == _event.event)
            return *this;
        impl::releaseInternal(event);
        event = _event.event;
        impl::retainInternal(event);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    Event& operator=(Event&& _event)
    {
        impl::releaseInternal(event);
        event = _event.event;
        _event.event = NULL;
        return *this;
    }
#endif
    
    /// destructor
    ~Event()
    { impl::releaseInternal(event); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(event); event = NULL; }
    
    /// logical negation
    bool operator!() const
    { return event==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return event!=NULL; }
    
    /// get (convert) cl_event
    cl_event operator()() const
    { return event; }
    
    /// convert to cl_event
    operator cl_event() const
    { return event; }
    
    /// comparison operator
    bool operator==(const Event& e2) const
    { return event==e2.event; }
    /// comparison operator
    bool operator!=(const Event& e2) const
    { return event!=e2.event; }
    
    /// create event from cl object
    static Event from(cl_event clobj, bool retain = true)
    {
        Event event;
        event.event = clobj;
        if (retain) impl::retainInternal(clobj);
        return event;
    }
    
    /// cast this object to other class
    template<typename T>
    T& cast()
    { return reinterpret_cast<T&>(*this); }
    
    /// cast this object to other class
    template<typename T>
    const T& cast() const
    { return reinterpret_cast<const T&>(*this); }
    
    /// get event info
    template<typename T>
    T getInfo(cl_event_info paramName) const
    { return impl::GetInfoHelper<cl_event, cl_event_info, T>::getInfo(event, paramName); }
    
    /// get event info
    template<typename T>
    void getInfo(cl_event_info paramName, T& value) const
    { impl::GetInfoHelper<cl_event, cl_event_info, T>::getInfo(event, paramName, value); }
    
    /// get event info
    std::string getInfoString(cl_event_info paramName) const
    { return impl::GetInfoHelper<cl_event, cl_event_info, std::string>::getInfo(
                event, paramName); }
    
    /// get event info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_event_info paramName) const
    { return impl::GetInfoHelper<cl_event, cl_event_info, T>::getInfoVector(
                event, paramName); }
    
    /// get command queue for event
    CommandQueue getCommandQueue() const;
    
#if __CLPP_CL_VERSION >= 101U
    /// get context for event
    Context getContext() const
    { return getInfo<Context>(CL_EVENT_CONTEXT); }
#else
    /// get command queue for event
    Context getContext() const
    {
        cl_command_queue cmdQueue;
        impl::getInfoInternal<cl_event, cl_event_info, 0>(event, CL_EVENT_COMMAND_QUEUE,
                sizeof(cl_command_queue), &cmdQueue, NULL);
        if (cmdQueue==NULL)
            return Context();
        Context context;
        impl::getInfoInternal<cl_command_queue, cl_command_queue_info, 0>(cmdQueue,
                    CL_QUEUE_CONTEXT, sizeof(cl_context),
                    reinterpret_cast<cl_context*>(&context), NULL);
        impl::retainInternal(context());
        return context;
    }
#endif
    
    /// get event command type
    cl_command_type getCommandType() const
    { return getInfo<cl_command_type>(CL_EVENT_COMMAND_TYPE); }
    
    /// get event command execution status
    cl_int getCommandExecutionStatus() const
    { return getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS); }
    /// get event command execution status
    cl_int getStatus() const
    { return getInfo<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS); }
    
    /// returns reference count for this event
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_EVENT_REFERENCE_COUNT); }
    
    /// get event profiling info
    template<typename T>
    T getProfilingInfo(cl_profiling_info paramName) const
    { return impl::GetInfoHelper<cl_event, cl_profiling_info, T,
                impl::EVOPT_PROFILING>::getInfo(event, paramName); }
    
    /// get event profiling info
    template<typename T>
    void getProfilingInfo(cl_profiling_info paramName, T& value) const
    { impl::GetInfoHelper<cl_event, cl_profiling_info, T, impl::EVOPT_PROFILING>::getInfo(
                event, paramName, value); }
    
    /// get event profiling info
    std::string getProfilingInfoString(cl_profiling_info paramName) const
    { return impl::GetInfoHelper<cl_event, cl_profiling_info, std::string,
                impl::EVOPT_PROFILING>::getInfo(event, paramName); }
    
    /// get event profiling info as vector
    template<typename T>
    std::vector<T> getProfilingInfoVector(cl_profiling_info paramName) const
    { return impl::GetInfoHelper<cl_event, cl_profiling_info, T, impl::EVOPT_PROFILING>::
                getInfoVector(event, paramName); }
    
    /// get time when command queued
    cl_ulong getProfilingCommandQueued() const
    { return getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_QUEUED); }
    
    /// get time when command submitted
    cl_ulong getProfilingCommandSubmit() const
    { return getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_SUBMIT); }
    
    /// get time when command started
    cl_ulong getProfilingCommandStart() const
    { return getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_START); }
    
    /// get time when command ended
    cl_ulong getProfilingCommandEnd() const
    { return getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_END); }

#if __CLPP_CL_VERSION >= 200U
    /// get time when command completed (defined if only OpenCL >= 2.0)
    cl_ulong getProfilingCommandComplete() const
    { return getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_COMPLETE); }
#endif
    
    /// wait for event
    void wait() const
    {
        const cl_int error = clWaitForEvents(1, &event);
        if (error != CL_SUCCESS)
            throw Error(error, "clWaitForEvents");
    }
    
    /// wait for events
    static void waitForEvents(const std::vector<Event>& events)
    {
        const cl_int error = clWaitForEvents(events.size(), &events[0].event);
        if (error != CL_SUCCESS)
            throw Error(error, "clWaitForEvents");
    }
    
#if __CLPP_CL_ABI_VERSION >= 101U
    /// set event callback (defined only if OpenCL ABI >= 1.1)
    void setCallback(cl_int execType, EventCallback callback, void* userData) const
    {
        const cl_int error = clSetEventCallback(event, execType, callback, userData);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetEventCallback");
    }
#endif
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, Event, Option>:
                GetInfoRefHelper<CLType, InfoType, Event, Option>
    { };
}

#if __CLPP_CL_ABI_VERSION >= 101U
/// OpenCL Event object wrapper (defined only if OpenCL ABI >= 1.1)
class UserEvent:  public Event
{
public:
    /// empty constructor
    UserEvent()
    { }
    
    /// constructor with context
    explicit UserEvent(const Context& context)
    {
        cl_int error;
        event = clCreateUserEvent(context, & error);
        if (event == NULL)
            throw Error(error, "clCreateUserEvent");
    }
    
    /// copy-constructor
    UserEvent(const UserEvent& _event) : Event(_event)
    { }
#   ifdef __CLPP_CPP0X
    /// move-constructor (defined only for C++0x or C++1x)
    UserEvent(UserEvent&& _event) noexcept : Event(std::forward<UserEvent>(_event))
    { }
#   endif
    
    /// copy-assignment
    UserEvent& operator=(const UserEvent& _event)
    { Event::operator=(_event); return *this; }
#   ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    UserEvent& operator=(UserEvent&& _event)
    { Event::operator=(std::forward<UserEvent>(_event)); return *this; }
#   endif
    
    /// create user event from cl object
    static UserEvent from(cl_event clobj, bool retain = true)
    {
        UserEvent event;
        event.event = clobj;
        if (retain) impl::retainInternal(clobj);
        return event;
    }
    
    /// set status for this event
    void setStatus(cl_int status) const
    {
        const cl_int error = clSetUserEventStatus(event, status);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetUserEventStatus");
    }
};

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, UserEvent, Option>:
                GetInfoRefHelper<CLType, InfoType, UserEvent, Option>
    { };
}
#endif

/// OpenCL CommandQueue object wrapper
/** This class holds a OpenCL command queue. Programmer can enqueue command to queue by using
 * enqueue* methods that returns an event that represents command. That event will be used later
 * to wait for a command completion. Correctly written program should get events and wait
 * for completion. Simplest usage is:
 * 
 * \code
 * cmdQueue.enqueue...(....).wait();
 * \endcode
 * 
 * Other methods for reading/writing/mapping without enqueue
 * prefix executes an underlying commands in blocking mode and does not return an event.
 */
class CommandQueue
{
private:
    cl_command_queue queue;
public:
    /// internal OpenCL type
    typedef cl_command_queue cl_type;
    
    /// empty constructor
    CommandQueue() : queue(NULL)
    { }
    
    /// constructor with context and device
    /**
     * \param context context for command queue
     * \param device device for command queue
     * \param properties properties for command queue
     */
    CommandQueue(const Context& context, const Device& device,
            cl_command_queue_properties properties = 0)
    {
        cl_int error;
#if __CLPP_CL_ABI_VERSION >= 200U
        const cl_queue_properties props[3] = { CL_QUEUE_PROPERTIES, properties, 0 };
        queue = clCreateCommandQueueWithProperties(context, device, props, &error);
        if (queue==NULL)
            throw Error(error, "clCreateCommandQueueWithProperties");
#else
        queue = clCreateCommandQueue(context, device, properties, &error);
        if (queue==NULL)
            throw Error(error, "clCreateCommandQueue");
#endif
    }
    
#if __CLPP_CL_ABI_VERSION >= 200U
    /// constructor with context and device (defined only if OpenCL ABI >= 2.0)
    /**
     * \param context context for command queue
     * \param device device for command queue
     * \param properties properties list
     */
    CommandQueue(const Context& context, const Device& device,
            const cl_queue_properties* properties)
    {
        cl_int error;
        queue = clCreateCommandQueueWithProperties(context, device, properties, &error);
        if (queue==NULL)
            throw Error(error, "clCreateCommandQueueWithProperties");
    }
    
    /// constructor with context and device (defined only if OpenCL >= 2.0)
    /**
     * \param context context for command queue
     * \param device device for command queue
     * \param properties properties list
     * \param queueSize queue size in bytes
     */
    CommandQueue(const Context& context, const Device& device,
            cl_command_queue_properties properties, cl_uint queueSize)
    {
        cl_int error;
        const cl_queue_properties props[5] = { CL_QUEUE_PROPERTIES, properties,
                CL_QUEUE_SIZE, queueSize, 0 };
        queue = clCreateCommandQueueWithProperties(context, device, props, &error);
        if (queue==NULL)
            throw Error(error, "clCreateCommandQueueWithProperties");
    }
#endif
    
    /// copy-constructor
    CommandQueue(const CommandQueue& _queue) : queue(_queue.queue)
    { impl::retainInternal(queue); }
    
#ifdef __CLPP_CPP0X
    /// copy-constructor (defined only for C++0x or C++1x)
    CommandQueue(CommandQueue&& _queue) noexcept
            : queue(_queue.queue)
    { _queue.queue = NULL; }
#endif
    
    /// copy-assignment
    CommandQueue& operator=(const CommandQueue& _queue)
    {
        if (queue == _queue.queue)
            return *this;
        impl::releaseInternal(queue);
        queue = _queue.queue;
        impl::retainInternal(queue);
        return *this;
    }
#ifdef __CLPP_CPP0X
    /// move-assignment (defined only for C++0x or C++1x)
    CommandQueue& operator=(CommandQueue&& _queue)
    {
        impl::releaseInternal(queue);
        queue = _queue.queue;
        _queue.queue = NULL;
        return *this;
    }
#endif
        
    /// destructor
    ~CommandQueue()
    { impl::releaseInternal(queue); }
    
    /// clear this reference
    void clear()
    { impl::releaseInternal(queue); queue = NULL; }
    
    /// logical negation
    bool operator!() const
    { return queue==NULL; }
    
    /// to bool conversion (true if not null)
    operator bool() const
    { return queue!=NULL; }
    
    /// get (convert) cl_command_queue
    cl_command_queue operator()() const
    { return queue; }
    
    /// convert to cl_command_queue
    operator cl_command_queue() const
    { return queue; }
    
    /// comparison operator
    bool operator==(const CommandQueue& q2) const
    { return queue==q2.queue; }
    /// comparison operator
    bool operator!=(const CommandQueue& q2) const
    { return queue!=q2.queue; }
    
    /// create command queue from cl object
    static CommandQueue from(cl_command_queue clobj, bool retain = true)
    {
        CommandQueue queue;
        queue.queue = clobj;
        if (retain) impl::retainInternal(clobj);
        return queue;
    }
    
    /// get command queue info
    template<typename T>
    T getInfo(cl_command_queue_info paramName) const
    { return impl::GetInfoHelper<cl_command_queue, cl_command_queue_info, T>::getInfo(
                queue, paramName); }
    
    /// get command queue info
    template<typename T>
    void getInfo(cl_command_queue_info paramName, T& value) const
    { impl::GetInfoHelper<cl_command_queue, cl_command_queue_info, T>::getInfo(
                queue, paramName, value); }
    
    /// get command queue info
    std::string getInfoString(cl_command_queue_info paramName) const
    { return impl::GetInfoHelper<cl_command_queue, cl_command_queue_info, std::string>::
                getInfo(queue, paramName); }
    
    /// get command queue info as vector
    template<typename T>
    std::vector<T> getInfoVector(cl_command_queue_info paramName) const
    { return impl::GetInfoHelper<cl_command_queue, cl_command_queue_info, T>::
                getInfoVector(queue, paramName); }
    
    /// returns reference count for this command queue
    cl_uint refCount() const
    { return getInfo<cl_uint>(CL_QUEUE_REFERENCE_COUNT); }
    
    /// get context from command queue
    Context getContext() const
    { return getInfo<Context>(CL_QUEUE_CONTEXT); }
    
    /// get device from command queue
    Device getDevice() const
    { return getInfo<Device>(CL_QUEUE_DEVICE); }
    /// get properties for command queue
    cl_command_queue_properties getProperties() const
    { return getInfo<cl_command_queue_properties>(CL_QUEUE_PROPERTIES); }
#if __CLPP_CL_VERSION >= 200U
    /// get command queue size in bytes (defined only if OpenCL >= 2.0)
    cl_uint getSize() const
    { return getInfo<cl_uint>(CL_QUEUE_SIZE); }
#endif

#if __CLPP_CL_VERSION >= 201U
    /// get default command queue for device
    CommandQueue getDeviceDefault() const
    { return getInfo<CommandQueue>(CL_QUEUE_DEVICE_DEFAULT); }
#endif
    
#if __CLPP_CL_ABI_VERSION <= 100U || (defined(CL_USE_DEPRECATED_OPENCL_1_0_APIS) && \
            __CLPP_CL_ABI_VERSION == 101U)
    /// set command queue properties (defined only if OpenCL ABI <= 1.0)
     __CLPP_CL_1_1_DEPRECATED cl_command_queue_properties setProperty(
                cl_command_queue_properties properties, bool enable) const
    {
        cl_command_queue_properties outProps;
        const cl_int error = clSetCommandQueueProperty(queue, properties, enable, &outProps);
        if (error != CL_SUCCESS)
            throw Error(error, "clSetCommandQueueProperty");
        return outProps;
    }
#endif
    
    /// flush queue
    void flush() const
    {
        const cl_int error = clFlush(queue);
        if (error != CL_SUCCESS)
            throw Error(error, "clFlush");
    }
    
    /// finish all commands within queue
    void finish() const
    {
        const cl_int error = clFinish(queue);
        if (error != CL_SUCCESS)
            throw Error(error, "clFinish");
    }
    
    /// enqueue read buffer
    /**
     * \param buffer buffer
     * \param offset offset for buffer
     * \param size size of region to copy
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueReadBuffer(const Buffer& buffer, size_t offset, size_t size,
            void* ptr, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueReadBuffer(queue, buffer, CL_FALSE, offset, size, ptr,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReadBuffer");
        return event;
    }
    
    /// read buffer
    /**
     * \param buffer buffer
     * \param offset offset for buffer
     * \param size size of region to copy
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     */
    void readBuffer(const Buffer& buffer, size_t offset, size_t size, void* ptr,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        const cl_int error = clEnqueueReadBuffer(queue, buffer, CL_TRUE, offset, size, ptr,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReadBuffer");
    }
    
    /// enqueue write buffer
    /**
     * \param buffer buffer
     * \param offset offset for buffer
     * \param size size of region to copy
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueWriteBuffer(const Buffer& buffer, size_t offset, size_t size,
            const void* ptr, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueWriteBuffer(queue, buffer, CL_FALSE, offset, size, ptr,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWriteBuffer");
        return event;
    }
    
    /// write buffer
    /**
     * \param buffer buffer
     * \param offset offset for buffer
     * \param size size of region to copy
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     */
    void writeBuffer(const Buffer& buffer, size_t offset, size_t size, const void* ptr,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        const cl_int error = clEnqueueWriteBuffer(queue, buffer, CL_TRUE, offset, size, ptr,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWriteBuffer");
    }
    
#if __CLPP_CL_ABI_VERSION >= 101U
    /// enqueue read rectangular from buffer (defined only if OpenCL ABI >= 1.1)
    /**
     * \param buffer buffer
     * \param bufferOrigin origin place in buffer
     * \param hostOrigin origin place in host data
     * \param region region size (last zeroes automatically replaces by ones)
     * \param bufferRowPitch size of row in buffer in bytes
     * \param bufferSlicePitch size of slice in buffer in bytes
     * \param hostRowPitch size of row in host data in bytes
     * \param hostSlicePitch size of slice in host data in bytes
     * \param ptr pointer to host data
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueReadBufferRect(const Buffer& buffer, Size3 bufferOrigin,
            Size3 hostOrigin, Size3 region, size_t bufferRowPitch,
            size_t bufferSlicePitch, size_t hostRowPitch, size_t hostSlicePitch,
            void* ptr, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        const cl_int error = clEnqueueReadBufferRect(queue, buffer, CL_FALSE,
                &bufferOrigin[0], &hostOrigin[0], &region[0],
                bufferRowPitch, bufferSlicePitch, hostRowPitch, hostSlicePitch,
                ptr, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReadBufferRect");
        return event;
    }
    
    /// read rectangular from buffer (defined only if OpenCL ABI >= 1.1)
    /**
     * \param buffer buffer
     * \param bufferOrigin origin place in buffer
     * \param hostOrigin origin place in host data
     * \param region region size (last zeroes automatically replaces by ones)
     * \param bufferRowPitch size of row in buffer in bytes
     * \param bufferSlicePitch size of slice in buffer in bytes
     * \param hostRowPitch size of row in host data in bytes
     * \param hostSlicePitch size of slice in host data in bytes
     * \param ptr pointer to host data
     * \param waitList waitlist of events
     */
    void readBufferRect(const Buffer& buffer, Size3 bufferOrigin,
            Size3 hostOrigin, Size3 region, size_t bufferRowPitch,
            size_t bufferSlicePitch, size_t hostRowPitch, size_t hostSlicePitch,
            void* ptr, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        const cl_int error = clEnqueueReadBufferRect(queue, buffer, CL_TRUE,
                &bufferOrigin[0], &hostOrigin[0], &region[0],
                bufferRowPitch, bufferSlicePitch, hostRowPitch, hostSlicePitch,
                ptr, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReadBufferRect");
    }
    
    /// enqueue write rectangular from buffer (defined only if OpenCL ABI >= 1.1)
    /**
     * \param buffer buffer
     * \param bufferOrigin origin place in buffer
     * \param hostOrigin origin place in host data
     * \param region region size (last zeroes automatically replaces by ones)
     * \param bufferRowPitch size of row in buffer in bytes
     * \param bufferSlicePitch size of slice in buffer in bytes
     * \param hostRowPitch size of row in host data in bytes
     * \param hostSlicePitch size of slice in host data in bytes
     * \param ptr pointer to host data
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueWriteBufferRect(const Buffer& buffer, Size3 bufferOrigin,
            Size3 hostOrigin, Size3 region, size_t bufferRowPitch,
            size_t bufferSlicePitch, size_t hostRowPitch, size_t hostSlicePitch,
            const void* ptr, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        const cl_int error = clEnqueueWriteBufferRect(queue, buffer, CL_FALSE,
                &bufferOrigin[0], &hostOrigin[0], &region[0],
                bufferRowPitch, bufferSlicePitch, hostRowPitch, hostSlicePitch,
                ptr, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWriteBufferRect");
        return event;
    }
    
    /// write rectangular from buffer (defined only if OpenCL ABI >= 1.1)
    /**
     * \param buffer buffer
     * \param bufferOrigin origin place in buffer
     * \param hostOrigin origin place in host data
     * \param region region size (last zeroes automatically replaces by ones)
     * \param bufferRowPitch size of row in buffer in bytes
     * \param bufferSlicePitch size of slice in buffer in bytes
     * \param hostRowPitch size of row in host data in bytes
     * \param hostSlicePitch size of slice in host data in bytes
     * \param ptr pointer to host data
     * \param waitList waitlist of events
     */
    void writeBufferRect(const Buffer& buffer, Size3 bufferOrigin,
            Size3 hostOrigin, Size3 region, size_t bufferRowPitch,
            size_t bufferSlicePitch, size_t hostRowPitch, size_t hostSlicePitch,
            const void* ptr, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        const cl_int error = clEnqueueWriteBufferRect(queue, buffer, CL_TRUE,
                &bufferOrigin[0], &hostOrigin[0], &region[0],
                bufferRowPitch, bufferSlicePitch, hostRowPitch, hostSlicePitch,
                ptr, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWriteBufferRect");
    }
#endif
    
    /// enqueue copy buffer
    /**
     * \param srcBuffer source buffer
     * \param dstBuffer destination buffer
     * \param srcOffset offset for source buffer
     * \param dstOffset offset for destination buffer
     * \param size size of data to copy
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueCopyBuffer(const Buffer& srcBuffer, const Buffer& dstBuffer,
            size_t srcOffset, size_t dstOffset, size_t size,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueCopyBuffer(queue, srcBuffer, dstBuffer,
                srcOffset, dstOffset, size, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueCopyBuffer");
        return event;
    }

#if __CLPP_CL_ABI_VERSION >= 101U
    /// enqueue copy buffer rectangle (defined only if OpenCL ABI >= 1.1)
    /**
     * \param srcBuffer source buffer
     * \param dstBuffer destination buffer
     * \param srcOrigin origin place in source buffer
     * \param dstOrigin origin place in destination buffer
     * \param region region size to copy (last zeroes automatically replaces by ones)
     * \param srcRowPitch size of row in source buffer in bytes
     * \param srcSlicePitch size of slice in source buffer in bytes
     * \param dstRowPitch size of row in destination buffer in bytes
     * \param dstSlicePitch size of slice in destination buffer in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueCopyBufferRect(const Buffer& srcBuffer, const Buffer& dstBuffer,
            Size3 srcOrigin, Size3 dstOrigin, Size3 region,
            size_t srcRowPitch, size_t srcSlicePitch, size_t dstRowPitch, size_t dstSlicePitch,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueCopyBufferRect(queue, srcBuffer, dstBuffer,
                &srcOrigin[0], &dstOrigin[0], &region[0], srcRowPitch, srcSlicePitch,
                dstRowPitch, dstSlicePitch, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueCopyBufferRect");
        return event;
    }
#endif

#if __CLPP_CL_ABI_VERSION >= 102U
    /// enqueue fill buffer (defined only if OpenCL ABI >= 1.2)
    /**
     * \param buffer buffer
     * \param pattern pattern to fill
     * \param offset offset for buffer
     * \param size size to fill in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    template<typename PatternType>
    Event enqueueFillBuffer(const Buffer& buffer, const PatternType& pattern,
            size_t offset, size_t size, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueFillBuffer(queue, buffer, &pattern,
                sizeof(PatternType), offset, size, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueFillBuffer");
        return event;
    }
#endif
    
    /// enqueue map buffer
    /**
     * \param ptr pointer to mapped region
     * \param buffer buffer
     * \param mapFlags flags for mapping
     * \param offset offset for buffer
     * \param size size to map in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMapBuffer(void*& ptr, const Buffer& buffer, cl_map_flags mapFlags,
            size_t offset, size_t size, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        Event event;
        cl_int error;
        ptr = clEnqueueMapBuffer(queue, buffer, CL_FALSE, mapFlags, offset, size,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event),
                &error);
        if (ptr == NULL)
            throw Error(error, "clEnqueueMapBuffer");
        return event;
    }
    
    /// map buffer
    /**
     * \param buffer buffer
     * \param mapFlags flags for mapping
     * \param offset offset for buffer
     * \param size size to map in bytes
     * \param waitList waitlist of events
     * \return pointer to mapped region
     */
    void* mapBuffer(const Buffer& buffer, cl_map_flags mapFlags, size_t offset,
            size_t size, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        cl_int error;
        void* ptr = clEnqueueMapBuffer(queue, buffer, CL_TRUE, mapFlags, offset, size,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL, &error);
        if (ptr == NULL)
            throw Error(error, "clEnqueueMapBuffer");
        return ptr;
    }
    
    /// enqueue unmapping memobject
    /**
     * \param memory memory
     * \param ptr pointer to unmap
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueUnmapMemObject(const Memory& memory, void* ptr,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueUnmapMemObject(queue, memory, ptr, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueUnmapMemObject");
        return event;
    }
    
    /// enqueue read image
    /**
     * \param image image
     * \param origin origin place in image
     * \param region region to read (last zeroes automatically replaces by ones)
     * \param rowPitch row pitch in bytes
     * \param slicePitch slice pitch in bytes
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueReadImage(const Image& image, Size3 origin, Size3 region, size_t rowPitch,
            size_t slicePitch, void* ptr, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueReadImage(queue, image, CL_FALSE,
                &origin[0], &region[0], rowPitch, slicePitch, ptr, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReadImage");
        return event;
    }
    
    /// read image
    /**
     * \param image image
     * \param origin origin place in image
     * \param region region to read (last zeroes automatically replaces by ones)
     * \param rowPitch row pitch in bytes
     * \param slicePitch slice pitch in bytes
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     */
    void readImage(const Image& image, Size3 origin, Size3 region, size_t rowPitch,
            size_t slicePitch, void* ptr, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        const cl_int error = clEnqueueReadImage(queue, image, CL_TRUE,
                &origin[0], &region[0], rowPitch, slicePitch, ptr, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReadImage");
    }
    
    /// enqueue write image
    /**
     * \param image image
     * \param origin origin place in image
     * \param region region to write (last zeroes automatically replaces by ones)
     * \param rowPitch row pitch in bytes
     * \param slicePitch slice pitch in bytes
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueWriteImage(const Image& image, Size3 origin, Size3 region, size_t rowPitch,
            size_t slicePitch, const void* ptr, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueWriteImage(queue, image, CL_FALSE,
                &origin[0], &region[0], rowPitch, slicePitch, ptr, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWriteImage");
        return event;
    }
    
    /// write image
    /**
     * \param image image
     * \param origin origin place in image
     * \param region region to write (last zeroes automatically replaces by ones)
     * \param rowPitch row pitch in bytes
     * \param slicePitch slice pitch in bytes
     * \param ptr pointer to output data
     * \param waitList waitlist of events
     */
    void writeImage(const Image& image, Size3 origin, Size3 region, size_t rowPitch,
            size_t slicePitch, const void* ptr, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        const cl_int error = clEnqueueWriteImage(queue, image, CL_TRUE,
                &origin[0], &region[0], rowPitch, slicePitch, ptr, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWriteImage");
    }
    
    /// enqueue copy image
    /**
     * \param srcImage source image
     * \param dstImage destination image
     * \param srcOrigin origin place in source image
     * \param dstOrigin origin place in destination image
     * \param region region to copy (last zeroes automatically replaces by ones)
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueCopyImage(const Image& srcImage, const Image& dstImage,
            Size3 srcOrigin, Size3 dstOrigin, Size3 region,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueCopyImage(queue, srcImage, dstImage,
                &srcOrigin[0], &dstOrigin[0], &region[0], waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueCopyImage");
        return event;
    }

#if __CLPP_CL_ABI_VERSION >= 102U
    /// enqueue fill image (defined only if OpenCL ABI >= 1.2)
    /**
     * \param image image
     * \param color color to fill
     * \param origin origin place in image
     * \param region region to fill (last zeroes automatically replaces by ones)
     * \param waitList waitlist of events
     * \return event of command
     */
    template<typename ColorType>
    Event enqueueFillImage(const Image& image, const ColorType& color, Size3 origin,
            Size3 region, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueFillImage(queue, image, &color, &origin[0],
                &region[0], waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueFillImage");
        return event;
    }
#endif
    
    /// enqueue copy image to buffer
    /**
     * \param srcImage source image
     * \param dstBuffer destination buffer
     * \param srcOrigin origin place in source image
     * \param region region to copy (last zeroes automatically replaces by ones)
     * \param dstOffset offset for destination buffer
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueCopyImageToBuffer(const Image& srcImage, const Buffer& dstBuffer,
            Size3 srcOrigin, Size3 region, size_t dstOffset,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueCopyImageToBuffer(queue, srcImage, dstBuffer,
                &srcOrigin[0], &region[0], dstOffset, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueCopyImageToBuffer");
        return event;
    }
    
    /// enqueue copy buffer to image
    /**
     * \param srcBuffer source buffer
     * \param dstImage destination image
     * \param srcOffset offset for source buffer
     * \param dstOrigin origin place in destination image
     * \param region region to copy (last zeroes automatically replaces by ones)
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueCopyBufferToImage(const Buffer& srcBuffer, const Image& dstImage,
            size_t srcOffset, Size3 dstOrigin, Size3 region,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        const cl_int error = clEnqueueCopyBufferToImage(queue, srcBuffer, dstImage,
                srcOffset, &dstOrigin[0], &region[0], waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueCopyBufferToImage");
        return event;
    }
    
    /// enqueue map image
    /**
     * \param ptr pointer to mapped region
     * \param image image
     * \param mapFlags flags for mapping
     * \param origin origin place in image
     * \param region region to map (last zeroes automatically replaces by ones)
     * \param imageRowPitch image row pitch in bytes
     * \param imageSlicePitch image row pitch in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMapImage(void*& ptr, const Image& image, cl_map_flags mapFlags,
            Size3 origin, Size3 region, size_t& imageRowPitch, size_t& imageSlicePitch,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        cl_int error;
        ptr = clEnqueueMapImage(queue, image, CL_FALSE, mapFlags, &origin[0], &region[0],
                &imageRowPitch, &imageSlicePitch, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event), &error);
        if (ptr == NULL)
            throw Error(error, "clEnqueueMapImage");
        return event;
    }
    
    /// map image
    /**
     * \param image image
     * \param mapFlags flags for mapping
     * \param origin origin place in image
     * \param region region to map (last zeroes automatically replaces by ones)
     * \param imageRowPitch image row pitch in bytes
     * \param imageSlicePitch image row pitch in bytes
     * \param waitList waitlist of events
     * \return pointer to mapped region
     */
    void* mapImage(const Image& image, cl_map_flags mapFlags,
            Size3 origin, Size3 region, size_t& imageRowPitch, size_t& imageSlicePitch,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        cl_int error;
        void* ptr = clEnqueueMapImage(queue, image, CL_TRUE, mapFlags, &origin[0], &region[0],
                &imageRowPitch, &imageSlicePitch, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                NULL, &error);
        if (ptr == NULL)
            throw Error(error, "clEnqueueMapImage");
        return ptr;
    }
    
    /// enqueue map 2D image
    /**
     * \param ptr pointer to mapped region
     * \param image image
     * \param mapFlags flags for mapping
     * \param origin origin place in image
     * \param region region to map (last zeroes automatically replaces by ones)
     * \param imageRowPitch image row pitch in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMapImage(void*& ptr, const Image& image, cl_map_flags mapFlags,
            Size3 origin, Size3 region, size_t& imageRowPitch,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        Event event;
        cl_int error;
        ptr = clEnqueueMapImage(queue, image, CL_FALSE, mapFlags, &origin[0], &region[0],
                &imageRowPitch, NULL, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event), &error);
        if (ptr == NULL)
            throw Error(error, "clEnqueueMapImage");
        return event;
    }
    
    /// map 2D image
    /**
     * \param image image
     * \param mapFlags flags for mapping
     * \param origin origin place in image
     * \param region region to map (last zeroes automatically replaces by ones)
     * \param imageRowPitch image row pitch in bytes
     * \param waitList waitlist of events
     * \return pointer to mapped region
     */
    void* mapImage(const Image& image, cl_map_flags mapFlags, Size3 origin, Size3 region,
            size_t& imageRowPitch, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        region[2] = (region[2]!=0)?region[2]:1;
        region[1] = (region[1]!=0)?region[1]:1;
        cl_int error;
        void* ptr = clEnqueueMapImage(queue, image, CL_TRUE, mapFlags, &origin[0], &region[0],
                &imageRowPitch, NULL, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL, &error);
        if (ptr == NULL)
            throw Error(error, "clEnqueueMapImage");
        return ptr;
    }
    
    /// enqueue NDRange kernel
    /**
     * \param kernel kernel to execute
     * \param globalOffset global work offset
     * \param globalWorkSize global work size
     * \param localWorkSize local work size
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueNDRangeKernel(const Kernel& kernel, Size3 globalOffset, Size3 globalWorkSize,
            Size3 localWorkSize, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        const cl_uint dim = globalWorkSize[2]!=0 ? 3 : (globalWorkSize[1]!=0 ? 2 : 1);
        Event event;
        const cl_int error = clEnqueueNDRangeKernel(queue, kernel, dim, &globalOffset[0],
                &globalWorkSize[0], localWorkSize[0]!=0?(&localWorkSize[0]):NULL,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueNDRangeKernel");
        return event;
    }
    
    /// enqueue NDRange kernel
    /**
     * \param kernel kernel to execute
     * \param globalWorkSize global work size
     * \param localWorkSize local work size
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueNDRangeKernel(const Kernel& kernel, Size3 globalWorkSize,
            Size3 localWorkSize, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    { return enqueueNDRangeKernel(kernel, 0, globalWorkSize, localWorkSize, waitList); }
    
    /// enqueue NDRange kernel
    /**
     * \param kernel kernel to execute
     * \param globalWorkSize global work size
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueNDRangeKernel(const Kernel& kernel, Size3 globalWorkSize,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    { return enqueueNDRangeKernel(kernel, 0, globalWorkSize, 0, waitList); }
    
#if __CLPP_CL_ABI_VERSION <= 102U || \
        (defined(CL_USE_DEPRECATED_OPENCL_2_0_APIS) && !defined(CL_VERSION_2_1)) || \
        (defined(CL_USE_DEPRECATED_OPENCL_1_2_APIS) && defined(CL_VERSION_2_1))
    /// enqueue task (deprectated if OpenCL ABI >= 2.0)
    /**
     * \param kernel kernel to execute
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueTask(const Kernel& kernel, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueTask(queue, kernel, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueTask");
        return event;
    }
#endif
    
    /// enqueue native kernel
    /**
     * \param userFunc user function to call
     * \param args arguments for user function
     * \param argSize size of arguments in bytes
     * \param memObjects memory objects to pass
     * \param argsMemLoc locations for memory objects
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueNativeKernel(NativeCallback userFunc, void* args, size_t argSize,
            const std::vector<Memory>& memObjects, const std::vector<const void*>& argsMemLoc,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    { 
        Event event;
        const cl_int error = clEnqueueNativeKernel(queue, userFunc, args, argSize,
                memObjects.size(),
                reinterpret_cast<const cl_mem*>(!memObjects.empty()?&memObjects[0]:NULL),
                const_cast<const void**>((!memObjects.empty())?&argsMemLoc[0]:NULL),
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueNativeKernel");
        return event;
    }
    
#if __CLPP_CL_ABI_VERSION < 102U || defined(__CLPP_DOXYGEN)
    /// enqueue marker (if OpenCL < 1.2)
    Event enqueueMarker() const
    {
        Event event;
        const cl_int error = clEnqueueMarker(queue, reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueMarker");
        return event;
    }
#endif
    
#if __CLPP_CL_ABI_VERSION >= 102U
    /// enqueue marker (defined only if OpenCL >= 1.2)
    Event enqueueMarker(const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueMarkerWithWaitList(queue, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueMarkerWithWaitList");
        return event;
    }
#endif

#if __CLPP_CL_ABI_VERSION < 102U || defined(__CLPP_DOXYGEN)
    /// enqueue barrier and waits (if OpenCL < 1.2)
    void barrier() const
    {
        const cl_int error = clEnqueueBarrier(queue);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueBarrier");
    }
#endif

#if __CLPP_CL_ABI_VERSION >= 102U
    /// enqueue barrier (defined only if OpenCL >= 1.2)
    Event enqueueBarrier(const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueBarrierWithWaitList(queue, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueBarrierWithWaitList");
        return event;
    }
#endif
    
#if __CLPP_CL_ABI_VERSION <= 101U || defined(CL_USE_DEPRECATED_OPENCL_1_1_APIS)
    /// enqueue wait for events (and acts synchronization point) (deprecated in OpenCL 1.2)
    __CLPP_CL_1_2_DEPRECATED void enqueueWaitForEvents(
                const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        const cl_int error = clEnqueueWaitForEvents(queue, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueWaitForEvents");
    }
#endif

#if __CLPP_CL_ABI_VERSION >= 102U
    /// enqueue migrate mem objects (defined only if OpenCL ABI >= 1.2)
    /**
     * \param memObjects memObjects list to migrate
     * \param flags flags
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMigrateMemObjects(const std::vector<Memory>& memObjects,
            cl_mem_migration_flags flags, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueMigrateMemObjects(queue, memObjects.size(),
                reinterpret_cast<const cl_mem*>(&memObjects[0]), flags, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueMigrateMemObjects");
        return event;
    }
    
    /// enqueue migrate mem objects (defined only if OpenCL ABI >= 1.2)
    /**
     * \param memObject memObject list to migrate
     * \param flags flags
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMigrateMemObject(const Memory& memObject, cl_mem_migration_flags flags,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueMigrateMemObjects(queue, 1,
                reinterpret_cast<const cl_mem*>(&memObject), flags, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueMigrateMemObjects");
        return event;
    }
#endif
#if defined(__CLPP_MIGRATE_MEMOBJECT) || defined(__CLPP_DOXYGEN)
private:
    cl_int enqueueMigrateMemObjectsInternal(cl_uint numMemObjects, const cl_mem* memObjects,
            cl_mem_migration_flags_ext flags, cl_uint waitListNum, const cl_event* waitList,
            cl_event* event) const
    {
        static volatile clEnqueueMigrateMemObjectEXT_fn migrateMemObjectEXT = NULL;
        if (migrateMemObjectEXT == NULL)
        {
            migrateMemObjectEXT = reinterpret_cast<clEnqueueMigrateMemObjectEXT_fn>(
                        clGetExtensionFunctionAddress("clEnqueueMigrateMemObjectEXT"));
            if (migrateMemObjectEXT == NULL)
                migrateMemObjectEXT = clEnqueueMigrateMemObjectEXT_fn(1);
        }
        if (migrateMemObjectEXT <= clEnqueueMigrateMemObjectEXT_fn(1))
            throw Error("Unsupported clEnqueueMigrateMemObjectEXT");
        return migrateMemObjectEXT(queue, numMemObjects, memObjects, flags,
                waitListNum, waitList, event);
    }
public:

    /// enqueue migrate mem objects (defined only if __CLPP_MIGRATE_MEMOBJECT)
    /**
     * \param memObjects memObjects list to migrate
     * \param flags flags
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMigrateMemObjects(const std::vector<Memory>& memObjects,
            cl_mem_migration_flags_ext flags, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        Event event;
        const cl_int error = enqueueMigrateMemObjectsInternal(memObjects.size(),
            reinterpret_cast<const cl_mem*>(&memObjects[0]), flags, waitList.size(),
            reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
            reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueMigrateMemObjectEXT");
        return event;
    }
    
    /// enqueue migrate mem objects (defined only if __CLPP_MIGRATE_MEMOBJECT)
    /**
     * \param memObject memObject list to migrate
     * \param flags flags
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueMigrateMemObject(const Memory& memObject, cl_mem_migration_flags_ext flags,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = enqueueMigrateMemObjectsInternal(1,
                reinterpret_cast<const cl_mem*>(&memObject), flags, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueMigrateMemObjectEXT");
        return event;
    }
#endif

#ifdef __CLPP_CL_GL
    /// enqueue acquire GL objects (defined only if __CLPP_CL_GL)
    /**
     * \param memObjects memObjects list to migrate
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueAcquireGLObjects(const std::vector<Memory>& memObjects,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueAcquireGLObjects(queue, memObjects.size(),
                reinterpret_cast<const cl_mem*>(&memObjects[0]), waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueAcquireGLObjects");
        return event;
    }
    
    /// enqueue acquire GL objects (defined only if __CLPP_CL_GL)
    /**
     * \param memObject memObject list to migrate
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueAcquireGLObject(const Memory& memObject,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueAcquireGLObjects(queue, 1,
                reinterpret_cast<const cl_mem*>(&memObject), waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueAcquireGLObjects");
        return event;
    }
    
    /// enqueue release GL objects (defined only if __CLPP_CL_GL)
    /**
     * \param memObjects memObjects list to migrate
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueReleaseGLObjects(const std::vector<Memory>& memObjects,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueReleaseGLObjects(queue, memObjects.size(),
                reinterpret_cast<const cl_mem*>(&memObjects[0]), waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReleaseGLObjects");
        return event;
    }
    
    /// enqueue release GL objects (defined only if __CLPP_CL_GL)
    /**
     * \param memObject memObject list to migrate
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueReleaseGLObject(const Memory& memObject,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueReleaseGLObjects(queue, 1,
                reinterpret_cast<const cl_mem*>(&memObject), waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueReleaseGLObjects");
        return event;
    }
#endif

#if __CLPP_CL_ABI_VERSION >= 200U
    /// enqueue SVM memcpy operation (defined if only OpenCL ABI >= 2.0)
    /**
     * \param dstPtr destination pointer
     * \param srcPtr source pointer
     * \param size size to copy in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueSVMMemcpy(void* dstPtr, const void* srcPtr, size_t size,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueSVMMemcpy(queue, CL_FALSE, dstPtr, srcPtr, size,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMemcpy");
        return event;
    }
    
    /// SVM memcpy operation (defined if only OpenCL ABI >= 2.0)
    /**
     * \param dstPtr destination pointer
     * \param srcPtr source pointer
     * \param size size to copy in bytes
     * \param waitList waitlist of events
     */
    void SVMMemcpy(void* dstPtr, const void* srcPtr, size_t size,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        const cl_int error = clEnqueueSVMMemcpy(queue, CL_TRUE, dstPtr, srcPtr, size,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMemcpy");
    }
    
    /// enqueue SVM memfill operation (defined if only OpenCL ABI >= 2.0)
    /**
     * \param dstPtr destination pointer
     * \param pattern pattern
     * \param size size to copy in bytes
     * \param waitList waitlist of events
     * \return event of command
     */
    template<typename PatternType>
    Event enqueueSVMMemFill(void* dstPtr, const PatternType& pattern,
            size_t size, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueSVMMemFill(queue, dstPtr, &pattern, sizeof(PatternType),
                size, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMemFill");
        return event;
    }
    
    /// enqueue map shared virtual memory (defined if only OpenCL ABI >= 2.0)
    Event enqueueSVMMap(cl_map_flags mapFlags, void* svmPtr, size_t size,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueSVMMap(queue, CL_FALSE, mapFlags,
                svmPtr, size, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMap");
        return event;
    }
    
    /// map shared virtual memory (defined if only OpenCL ABI >= 2.0)
    void SVMMap(cl_map_flags mapFlags, void* svmPtr, size_t size,
            const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        const cl_int error = clEnqueueSVMMap(queue, CL_TRUE, mapFlags,
                svmPtr, size, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), NULL);
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMap");
    }
    
    /// enqueue unmap shared virtual memory (defined if only OpenCL ABI >= 2.0)
    Event enqueueSVMUnmap(void* svmPtr, const std::vector<Event>& waitList =
            std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueSVMUnmap(queue, svmPtr, waitList.size(),
                reinterpret_cast<const cl_event*>(!waitList.empty()?&waitList[0]:NULL),
                reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMUnmap");
        return event;
    }
    
    /// enqueue free shared virtual memory (defined if only OpenCL ABI >= 2.0)
    /**
     * \param svmPtrs pointers to shared virtual memory
     * \param callback callback
     * \param userData user data for callback
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueSVMFree(const std::vector<void*>& svmPtrs, SVMFreeCallback callback,
            void* userData, const std::vector<Event>& waitList = std::vector<Event>()) const
    {
        Event event;
        const cl_int error = clEnqueueSVMFree(queue, svmPtrs.size(),
                const_cast<void**>(&svmPtrs[0]), callback, userData,
                waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMFree");
        return event;
    }
    
    /// enqueue free shared virtual memory (defined if only OpenCL ABI >= 2.0)
    /**
     * \param svmPtrs pointers to shared virtual memory
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueSVMFree(const std::vector<void*>& svmPtrs,
                const std::vector<Event>& waitList = std::vector<Event>()) const
    { return enqueueSVMFree(svmPtrs, NULL, NULL, waitList); }
#endif
#if __CLPP_CL_ABI_VERSION >= 201U
    /// enqueue SVM migrate memories
    /**
     * \param svmPtrsNum number of svm pointers
     * \param svmPtrs pointers to shared virtual memory
     * \param sizes sizes for memories
     * \param flags migration flags
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueSVMMigrateMem(cl_uint svmPtrsNum, const void** svmPtrs, size_t* sizes,
                cl_mem_migration_flags flags,
                const std::vector<Event>& waitList = std::vector<Event>())
    {
        Event event;
        const cl_int error = clEnqueueSVMMigrateMem(queue, svmPtrsNum, svmPtrs, sizes,
                flags, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMigrateMem");
        return event;
    }
    
    /// enqueue SVM migrate memories
    /**
     * \param svmPtrs pointers to shared virtual memory
     * \param sizes sizes for memories
     * \param flags migration flags
     * \param waitList waitlist of events
     * \return event of command
     */
    Event enqueueSVMMigrateMem(const std::vector<void*>& svmPtrs,
                const std::vector<size_t>& sizes, cl_mem_migration_flags flags,
                const std::vector<Event>& waitList = std::vector<Event>())
    {
        Event event;
        const cl_int error = clEnqueueSVMMigrateMem(queue, svmPtrs.size(),
                const_cast<const void**>(&(svmPtrs[0])),
                &(sizes[0]), flags, waitList.size(), reinterpret_cast<const cl_event*>(
                !waitList.empty()?&waitList[0]:NULL), reinterpret_cast<cl_event*>(&event));
        if (error != CL_SUCCESS)
            throw Error(error, "clEnqueueSVMMigrateMem");
        return event;
    }
#endif
};

/// CommandQueue alias
typedef CommandQueue Queue;

namespace impl
{
    template<typename CLType, typename InfoType, int Option>
    struct GetInfoHelper<CLType, InfoType, CommandQueue, Option>:
                GetInfoRefHelper<CLType, InfoType, CommandQueue, Option>
    { };
}

/// get command queue for event
inline CommandQueue Event::getCommandQueue() const
{ return getInfo<CommandQueue>(CL_EVENT_COMMAND_QUEUE); }

#if __CLPP_CL_ABI_VERSION <= 101U || defined(CL_USE_DEPRECATED_OPENCL_1_1_APIS)
/// unload OpenCL compiler (deprecated for OpenCL >= 1.2)
inline __CLPP_CL_ABI_1_2_DEPRECATED void unloadCompiler()
{
    const cl_int error = clUnloadCompiler();
    if (error != CL_SUCCESS)
        throw Error(error, "clUnloadCompiler");
}
#endif

/// create command queues for all context devices
inline std::vector<CommandQueue> Context::createCommandQueues(
            cl_command_queue_properties props) const
{
    std::vector<Device> devices = getDevices();
    std::vector<CommandQueue> queues(devices.size());
    for (cl_uint i = 0; i < devices.size(); i++)
        queues[i] = CommandQueue(*this, devices[i], props);
    return queues;
}

#if __CLPP_CL_ABI_VERSION >= 200U
/// create command queues for all context devices
inline std::vector<CommandQueue> Context::createCommandQueues(
            cl_command_queue_properties props, size_t size) const
{
    std::vector<Device> devices = getDevices();
    std::vector<CommandQueue> queues(devices.size());
    for (cl_uint i = 0; i < devices.size(); i++)
        queues[i] = CommandQueue(*this, devices[i], props, size);
    return queues;
}

/// create command queues for all context devices
inline std::vector<CommandQueue> Context::createCommandQueues(
            const cl_queue_properties* props) const
{
    std::vector<Device> devices = getDevices();
    std::vector<CommandQueue> queues(devices.size());
    for (cl_uint i = 0; i < devices.size(); i++)
        queues[i] = CommandQueue(*this, devices[i], props);
    return queues;
}
#endif

#if __CLPP_CL_ABI_VERSION >= 201U
inline void Context::setDefaultDeviceCommandQueue(const Device& device,
            const CommandQueue& cmdQueue) const
{
    const cl_int error = clSetDefaultDeviceCommandQueue(context, device, cmdQueue);
    if (error != CL_SUCCESS)
        throw Error(error, "clSetDefaultDeviceCommandQueue");
}
#endif

/// Memory object mapping holder
class MemoryMapping
{
private:
    /// non-copyable
    MemoryMapping(const MemoryMapping&);
    MemoryMapping& operator=(const MemoryMapping&);
protected:
    /// command queue
    CommandQueue cmdQueue;
    /// memory to map
    Memory memory;
    /// event for a mapping command
    Event mapEvent;
    /// unmap event pointer
    Event *unmapEvent;
    /// wait list for unmap command
    std::vector<Event> unmapWaitList;
    /// pointer to mapped memory
    void* ptr;
    
    /// constructor
    /**
     * \param inCmdQueue command queue to unmap
     * \param memobj memory to map
     * \param unmapEventPtr event pointer to event to an unmapping command
     */
    MemoryMapping(const CommandQueue& inCmdQueue, const Memory& memobj, Event* unmapEventPtr) :
                cmdQueue(inCmdQueue), memory(memobj), unmapEvent(unmapEventPtr)
    { }
    
    /// constructor with waitlist vector
    /**
     * \param inCmdQueue command queue to unmap
     * \param memobj memory to map
     * \param unmapWaitList wait list for an unmapping command
     * \param unmapEventPtr event pointer to event to an unmapping command
     */
    MemoryMapping(const CommandQueue& inCmdQueue, const Memory& memobj,
            const std::vector<Event>& unmapWaitList, Event* unmapEventPtr)
            : cmdQueue(inCmdQueue), memory(memobj), unmapEvent(unmapEventPtr)
    { this->unmapWaitList = unmapWaitList; }
public:
    /// destructor
    ~MemoryMapping()
    { release(); }
    
    /// get pointer to mapped memory
    void* get() const
    { return ptr; }

    /// wait for a mapping command
    void wait() const
    { if (mapEvent) mapEvent.wait(); }
    
    /// get event for a mapping command
    const Event& getMapEvent() const
    { return mapEvent; }
    
    /// release mapping
    void release()
    {
        if (ptr == NULL) return;
        wait();
        if (unmapEvent != NULL)
            *unmapEvent = cmdQueue.enqueueUnmapMemObject(memory, ptr, unmapWaitList);
        else // wait for unmapping
            cmdQueue.enqueueUnmapMemObject(memory, ptr, unmapWaitList).wait();
        ptr = NULL;
    }
};

/// Buffer mapping holder
/** If blocking is disabled object
 * holds mapEvent that represents a mapping operation and constructor do not wait for
 * complete this event. Otherwise constructor execute a blocking mapping.
 * If unmapEventPtr is NULL then unmap command will be completed.
 * Otherwise an unmapping command event will be saved in
 * place that will be pointed by unmapEventPtr for later waiting.
 * 
 * Sample usage:
 * \code
 * {
 *   BufferMapping mapping(cmdQueue, buffer, true, CL_MAP_READ, 0, xxx);
 *   // mapping is ready
 *   ....
 *   // mapping has been automatically released
 * }
 * \endcode
 * 
 * or
 * 
 * \code
 * Event unmapEvent;
 * {
 *   BufferMapping mapping(cmdQueue, buffer, false, CL_MAP_READ, 0, xxx, &unmapEvent);
 *   ...
 *   mapping.wait(); // wait for a mapping
 *   // mapping is ready
 *   ....
 *   // mapping has been automatically released, but do not wait for an unmapping
 * }
 * ...
 * // wait for an unmapping
 * unmapEvent.wait(); 
 * \endcode
 */
class BufferMapping: public MemoryMapping
{
public:
    /// constructor
    /**
     * \param cmdQueue command queue for command sending
     * \param buffer buffer to map
     * \param blocking blocking mode
     * \param mapFlags map flags
     * \param offset offset in buffer in bytes
     * \param size size of region to map in bytes
     * \param unmapEventPtr event pointer to event to an unmapping command
     */
    BufferMapping(const CommandQueue& cmdQueue, const Buffer& buffer,
            bool blocking, cl_map_flags mapFlags, size_t offset, size_t size,
            Event* unmapEventPtr = NULL) : MemoryMapping(cmdQueue, buffer, unmapEventPtr)
    {
        if (blocking)
            ptr = cmdQueue.mapBuffer(buffer, mapFlags, offset, size);
        else
            mapEvent = cmdQueue.enqueueMapBuffer(ptr, buffer, mapFlags, offset, size);
    }
    
    /// constructor with waitlist vectors
    BufferMapping(const CommandQueue& cmdQueue, const Buffer& buffer,
            bool blocking, cl_map_flags mapFlags, size_t offset, size_t size,
            const std::vector<Event>& mapWaitList,
            const std::vector<Event>& unmapWaitList = std::vector<Event>(),
            Event* unmapEventPtr = NULL)
            : MemoryMapping(cmdQueue, buffer, unmapWaitList, unmapEventPtr)
    {
        if (blocking)
            ptr = cmdQueue.mapBuffer(buffer, mapFlags, offset, size, mapWaitList);
        else
            mapEvent = cmdQueue.enqueueMapBuffer(ptr, buffer, mapFlags,
                    offset, size, mapWaitList);
    }
};

/// image mapping holder class
/** If blocking is disabled object
 * holds mapEvent that represents a mapping operation and constructor do not wait for
 * complete this event. Otherwise constructor execute a blocking mapping.
 * If unmapEventPtr is NULL then unmap command will be completed.
 * Otherwise an unmapping command event will be saved in
 * place that will be pointed by unmapEventPtr for later waiting.
 * 
 * Sample usage:
 * \code
 * {
 *   ImageMapping mapping(cmdQueue, image, true, CL_MAP_READ, Size3(0,0), ...);
 *   // mapping is ready
 *   ....
 *   // mapping has been automatically released
 * }
 * \endcode
 * 
 * or
 * 
 * \code
 * Event unmapEvent;
 * {
 *   ImageMapping mapping(cmdQueue, image, false, CL_MAP_READ, Size3(0,0), ..., &unmapEvent);
 *   ...
 *   mapping.wait(); // wait for a mapping
 *   // mapping is ready
 *   ....
 *   // mapping has been automatically released, but do not wait for an unmapping
 * }
 * ...
 * // wait for an unmapping
 * unmapEvent.wait(); 
 * \endcode
 */
class ImageMapping: public MemoryMapping
{
private:
    size_t rowPitch;
    size_t slicePitch;
public:
    /// constructor
    /**
     * \param cmdQueue command queue for command sending
     * \param image image to map
     * \param blocking blocking mode
     * \param mapFlags map flags
     * \param origin origin place in image
     * \param region region to map (last zeroes automatically replaces by ones)
     * \param unmapEventPtr event pointer to event to an unmapping command
     */
    ImageMapping(const CommandQueue& cmdQueue, const Image& image,
            bool blocking, cl_map_flags mapFlags, Size3 origin, Size3 region,
            Event* unmapEventPtr = NULL) : MemoryMapping(cmdQueue, image, unmapEventPtr)
    {
        if (blocking)
            ptr = cmdQueue.mapImage(image, mapFlags, origin, region, rowPitch, slicePitch);
        else
            mapEvent = cmdQueue.enqueueMapImage(ptr, image, mapFlags, origin, region,
                    rowPitch, slicePitch);
    }
    
    /// constructor
    ImageMapping(const CommandQueue& cmdQueue, const Image& image,
            bool blocking, cl_map_flags mapFlags, Size3 origin, Size3 region,
            const std::vector<Event>& mapWaitList,
            const std::vector<Event>& unmapWaitList = std::vector<Event>(),
            Event* unmapEventPtr = NULL)
                : MemoryMapping(cmdQueue, image, unmapWaitList, unmapEventPtr)
    {
        if (blocking)
            ptr = cmdQueue.mapImage(image, mapFlags, origin, region,
                    rowPitch, slicePitch, mapWaitList);
        else
            mapEvent = cmdQueue.enqueueMapImage(ptr, image, mapFlags, origin, region,
                    rowPitch, slicePitch, mapWaitList);
    }
    
    /// get row pitch
    size_t getRowPitch() const
    { return rowPitch; }
    
    /// get slice pitch
    size_t getSlicePitch() const
    { return slicePitch; }
};

#if __CLPP_CL_ABI_VERSION >= 200U
/// SVM mapping holder class (defined only if OpenCL ABI >= 2.0)
/** If blocking is disabled object
 * holds mapEvent that represents a mapping operation and constructor do not wait for
 * complete this event. Otherwise constructor execute a blocking mapping.
 * If unmapEventPtr is NULL then unmap command will be completed.
 * Otherwise an unmapping command event will be saved in
 * place that will be pointed by unmapEventPtr for later waiting.
 * 
 * Sample usage:
 * \code
 * {
 *   SVMMapping mapping(cmdQueue, buffer, true, CL_MAP_READ, svmPointer);
 *   // mapping is ready
 *   ....
 *   // mapping has been automatically released
 * }
 * \endcode
 * 
 * or
 * 
 * \code
 * Event unmapEvent;
 * {
 *   SVMMapping mapping(cmdQueue, buffer, false, CL_MAP_READ, svmPointer, xxx, &unmapEvent);
 *   ...
 *   mapping.wait(); // wait for a mapping
 *   // mapping is ready
 *   ....
 *   // mapping has been automatically released, but do not wait for an unmapping
 * }
 * ...
 * // wait for an unmapping
 * unmapEvent.wait(); 
 * \endcode
 */
class SVMMapping
{
private:
    SVMMapping(const SVMMapping&);
    SVMMapping& operator=(const SVMMapping&);
    
    /// command queue
    CommandQueue cmdQueue;
    /// pointer to mapped memory
    void* svmPtr;
    /// event for a mapping command
    Event mapEvent;
    /// unmap event pointer
    Event *unmapEvent;
    /// wait list for unmap command
    std::vector<Event> unmapWaitList;
public:
    /// constructor
    /**
     * \param inCmdQueue command queue for command sending
     * \param blocking blocking mode
     * \param mapFlags map flags
     * \param inputSvmPtr svm space pointer
     * \param size size of region to map in bytes
     * \param unmapEventPtr event pointer to event to an unmapping command
     */
    SVMMapping(const CommandQueue& inCmdQueue, bool blocking, cl_map_flags mapFlags,
            void* inputSvmPtr, size_t size, Event* unmapEventPtr = NULL) :
            cmdQueue(inCmdQueue), svmPtr(inputSvmPtr), unmapEvent(unmapEventPtr)
    {
        if (blocking)
            cmdQueue.SVMMap(mapFlags, inputSvmPtr, size);
        else
            mapEvent = cmdQueue.enqueueSVMMap(mapFlags, inputSvmPtr, size);
    }
    
    /// constructor with waitlist vectors
    SVMMapping(const CommandQueue& inCmdQueue, bool blocking, cl_map_flags mapFlags,
            void* inputSvmPtr, size_t size, const std::vector<Event>& mapWaitList,
            const std::vector<Event>& unmapWaitList = std::vector<Event>(),
            Event* unmapEventPtr = NULL) : cmdQueue(inCmdQueue), svmPtr(inputSvmPtr),
            unmapEvent(unmapEventPtr)
    {
        this->unmapWaitList = unmapWaitList;
        if (blocking)
            cmdQueue.SVMMap(mapFlags, inputSvmPtr, size, mapWaitList);
        else
            mapEvent = cmdQueue.enqueueSVMMap(mapFlags, inputSvmPtr, size, mapWaitList);
    }
    
    /// destructor
    ~SVMMapping()
    { release(); }
    
    /// get pointer to mapped memory
    void* get() const
    { return svmPtr; }

    /// wait for a mapping command
    void wait() const
    { if (mapEvent) mapEvent.wait(); }
    
    /// get event for a mapping command
    const Event& getMapEvent() const
    { return mapEvent; }
    
    /// release mapping
    void release()
    {
        if (svmPtr == NULL) return;
        wait();
        if (unmapEvent != NULL)
            *unmapEvent = cmdQueue.enqueueSVMUnmap(svmPtr, unmapWaitList);
        else
            cmdQueue.enqueueSVMUnmap(svmPtr, unmapWaitList).wait();
        svmPtr = NULL;
    }
};
#endif

#if __CLPP_CL_GL
/// GLObject Lock class (defined only if __CLPP_CL_GL)
/** If releaseEventPtr is NULL then a release command will be completed.
 * Otherwise an unmapping command event will be saved in
 * place that will be pointed by unmapEventPtr for later waiting.
 * 
 * Sample usage:
 * \code
 * {
 *   GLObjectsLock gllock(cmdQueue, texture);
 *   ...
 *   gllock.wait()
 *   // lock is ready
 *   ....
 *   // lock has been automatically released
 * }
 * \endcode
 * 
 * or
 * 
 * \code
 * Event releaseEvent;
 * {
 *   GLObjectsLock gllock(cmdQueue, texture, &releaseEvent);
 *   ...
 *   gllock.wait()
 *   // lock is ready
 *   ....
 *   // lock has been automatically released, but do not wait for a releasing
 * }
 * ...
 * // wait for a releasing
 * releaseEvent.wait(); 
 * \endcode
 */
class GLObjectsLock
{
private:
    GLObjectsLock(const GLObjectsLock&);
    GLObjectsLock& operator=(const GLObjectsLock&);
    
    /// command queue
    CommandQueue cmdQueue;
    /// memory objects to lock
    std::vector<Memory> memObjects;
    /// event for an acquiring command
    Event acquireEvent;
    /// release event pointer
    Event *releaseEvent;
    /// wait list for release command
    std::vector<Event> releaseWaitList;
public:
    /// constructor
    GLObjectsLock(const CommandQueue& inCmdQueue, const std::vector<Memory>& glObjects,
            Event* relEventPtr = NULL) : cmdQueue(inCmdQueue),
            memObjects(glObjects), releaseEvent(relEventPtr)
    { acquireEvent = cmdQueue.enqueueAcquireGLObjects(memObjects); }
    
    /// constructor
    GLObjectsLock(const CommandQueue& inCmdQueue, const Memory& glObject,
            Event* relEventPtr = NULL) : cmdQueue(inCmdQueue), releaseEvent(relEventPtr)
    { memObjects.push_back(glObject);
      acquireEvent = cmdQueue.enqueueAcquireGLObject(glObject); }
    
    /// constructor
    GLObjectsLock(const CommandQueue& inCmdQueue, const std::vector<Memory>& glObjects,
            const std::vector<Event>& acquireWaitList, const std::vector<Event>& releaseWaitList,
            Event* relEventPtr = NULL) : cmdQueue(inCmdQueue),
            memObjects(glObjects), releaseEvent(relEventPtr)
    {
        this->releaseWaitList = releaseWaitList;
        acquireEvent = cmdQueue.enqueueAcquireGLObjects(memObjects, acquireWaitList);
    }
    
    /// constructor
    GLObjectsLock(const CommandQueue& inCmdQueue, const Memory& glObject,
            const std::vector<Event>& acquireWaitList, const std::vector<Event>& releaseWaitList,
            Event* relEventPtr = NULL) : cmdQueue(inCmdQueue), releaseEvent(relEventPtr)
    {
        this->releaseWaitList = releaseWaitList;
        memObjects.push_back(glObject);
        acquireEvent = cmdQueue.enqueueAcquireGLObject(glObject, acquireWaitList);
    }
    
    /// destructor
    ~GLObjectsLock()
    { release(); }
    
    /// wait for an acquiring command
    void wait() const
    { acquireEvent.wait(); }
    
    /// get event for an acquiring command
    const Event& getAcquireEvent() const
    { return acquireEvent; }
    
    /// release lock
    void release()
    {
        if (memObjects.empty()) return;
        wait(); // always acquire event before enqueueing unmap
        if (releaseEvent != NULL)
            *releaseEvent = cmdQueue.enqueueReleaseGLObjects(
                        memObjects, releaseWaitList);
        else
            cmdQueue.enqueueReleaseGLObjects(memObjects, releaseWaitList).wait();
        memObjects.clear();
    }
};
#endif

}

/// comparison operator for cl_image_format
inline bool operator==(const cl_image_format& a, const cl_image_format& b)
{ return a.image_channel_order==b.image_channel_order &&
    a.image_channel_data_type==b.image_channel_data_type; }
/// comparison operator for cl_image_format
inline bool operator!=(const cl_image_format& a, const cl_image_format& b)
{ return a.image_channel_order!=b.image_channel_order ||
    a.image_channel_data_type!=b.image_channel_data_type; }

#ifdef _WIN32
#pragma pop_macro("max")
#endif

#endif
