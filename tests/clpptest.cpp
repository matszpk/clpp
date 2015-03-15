/*
 *  clpp.h - An OpenCL C++/C++11 wrapper
 *  Copyright (C) 2015 Mateusz Szpakowski
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

#if __cplusplus > 199711L
#    define __CLPP_CPP0X
#    include <initializer_list>
#endif

// prevents deprecated warnings
#if __CLPP_CL_ABI_VERSION==100
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_1_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_0_APIS 1
#endif
#if __CLPP_CL_ABI_VERSION==101
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#   define CL_USE_DEPRECATED_OPENCL_1_1_APIS 1
#endif
#if __CLPP_CL_ABI_VERSION==102
#   define CL_USE_DEPRECATED_OPENCL_2_0_APIS 1
#endif
#include <iostream>
#include <cstring>
#include <sstream>
#ifdef __CLPP_CL_GL
#    define GL_GLEXT_PROTOTYPES
// requires SDL (glut, segfaults on AMD Catalyst drivers :0)
#    include <GL/gl.h>
#    include <GL/glext.h>
#    include <GL/glu.h>
#    include <GL/glx.h>
#    include <SDL.h>
#endif
#ifdef _WINDOWS
#   include <windows.h>
#else
#   include <pthread.h>
#endif
#ifdef __APPLE__
#   include <OpenCL/cl.h>
#else
#   include <CL/cl.h>
#endif

#ifdef __CLPP_CL_GL
#ifdef __APPLE__
#   include <OpenCL/cl_gl.h>
#else
#   include <CL/cl_gl.h>
#endif
#endif

/* definition of fake OpenCL functions for testing passed argument values */
extern "C"
{
CL_API_ENTRY cl_int CL_API_CALL
fakeclSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size,
        const void * arg_value) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read,
            size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list,
            const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write,
        size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, 
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyBuffer(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer,
        size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;

#ifdef CL_VERSION_1_1
extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer,
        cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset,
        const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch,
        size_t host_row_pitch, size_t host_slice_pitch, void* ptr,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_1;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer,
        cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset,
        const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch,
        size_t host_row_pitch, size_t host_slice_pitch, const void* ptr,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_1;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer,
        const size_t* src_origin, const size_t* dst_origin, const size_t* region,
        size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch,
        size_t dst_slice_pitch, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_1;
#endif
#ifdef CL_VERSION_1_2
extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueFillBuffer(cl_command_queue command_queue, cl_mem buffer, const void* pattern, 
        size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_2;
#endif

extern CL_API_ENTRY void * CL_API_CALL
fakeclEnqueueMapBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, 
        cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event,
        cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueUnmapMemObject(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReadImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, 
        const size_t* origin, const size_t* region, size_t row_pitch, size_t slice_pitch,
        void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueWriteImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, 
        const size_t* origin, const size_t* region, size_t input_row_pitch,
        size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyImage(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image,
        const size_t* src_origin, const size_t* dst_origin, const size_t* region, 
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0;

#ifdef CL_VERSION_1_2
extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueFillImage(cl_command_queue command_queue, cl_mem image, const void* fill_color, 
        const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_2;
#endif

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem src_image,
        cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyBufferToImage(cl_command_queue command_queue, cl_mem src_buffer,
        cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY void * CL_API_CALL
fakeclEnqueueMapImage(cl_command_queue  command_queue, cl_mem image, cl_bool blocking_map,
        cl_map_flags map_flags, const size_t* origin, const size_t* region,
        size_t* image_row_pitch, size_t* image_slice_pitch, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event,
        cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim,
        const size_t* global_work_offset, const size_t* global_work_size,
        const size_t* local_work_size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;

#ifdef CL_VERSION_2_0
extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueSVMMemcpy(cl_command_queue  command_queue, cl_bool blocking_copy,
        void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_2_0;
#endif
        
#ifdef __CLPP_CL_GL
extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueAcquireGLObjects(cl_command_queue command_queue, cl_uint num_objects,
        const cl_mem* mem_objects, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReleaseGLObjects(cl_command_queue command_queue, cl_uint num_objects,
        const cl_mem* mem_objects, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0;
#endif
}

#define clSetKernelArg fakeclSetKernelArg
#define clEnqueueReadBuffer fakeclEnqueueReadBuffer
#define clEnqueueWriteBuffer fakeclEnqueueWriteBuffer
#define clEnqueueCopyBuffer fakeclEnqueueCopyBuffer
#define clEnqueueFillBuffer fakeclEnqueueFillBuffer
#define clEnqueueReadBufferRect fakeclEnqueueReadBufferRect
#define clEnqueueWriteBufferRect fakeclEnqueueWriteBufferRect
#define clEnqueueCopyBufferRect fakeclEnqueueCopyBufferRect
#define clEnqueueMapBuffer fakeclEnqueueMapBuffer
#define clEnqueueUnmapMemObject fakeclEnqueueUnmapMemObject
#define clEnqueueReadImage fakeclEnqueueReadImage
#define clEnqueueWriteImage fakeclEnqueueWriteImage
#define clEnqueueCopyImage fakeclEnqueueCopyImage
#define clEnqueueFillImage fakeclEnqueueFillImage
#define clEnqueueCopyImageToBuffer fakeclEnqueueCopyImageToBuffer
#define clEnqueueCopyBufferToImage fakeclEnqueueCopyBufferToImage
#define clEnqueueMapImage fakeclEnqueueMapImage
#define clEnqueueNDRangeKernel fakeclEnqueueNDRangeKernel
#define clEnqueueSVMMemcpy fakeclEnqueueSVMMemcpy
#define clEnqueueAcquireGLObjects fakeclEnqueueAcquireGLObjects
#define clEnqueueReleaseGLObjects fakeclEnqueueReleaseGLObjects

#include <clpp.h>

// undefine replacement
#undef clSetKernelArg
#undef clEnqueueReadBuffer
#undef clEnqueueWriteBuffer
#undef clEnqueueCopyBuffer
#undef clEnqueueFillBuffer
#undef clEnqueueReadBufferRect
#undef clEnqueueWriteBufferRect
#undef clEnqueueCopyBufferRect
#undef clEnqueueMapBuffer
#undef clEnqueueUnmapMemObject
#undef clEnqueueReadImage
#undef clEnqueueWriteImage
#undef clEnqueueCopyImage
#undef clEnqueueFillImage
#undef clEnqueueCopyImageToBuffer
#undef clEnqueueCopyBufferToImage
#undef clEnqueueMapImage
#undef clEnqueueNDRangeKernel
#undef clEnqueueSVMMemcpy
#undef clEnqueueAcquireGLObjects
#undef clEnqueueReleaseGLObjects

#ifdef _WINDOWS
// stupid Windows
#undef min
#undef max
#endif

using clpp::Size3;

static size_t kernelSetArgSize[100];
static std::vector<unsigned char> kernelSetArgValue[100];

static bool blockingMode = false;
static std::vector<cl_event> waitListInput;
static Size3 rectOffset1Input, rectOffset2Input;
static Size3 rectRegionInput;
static cl_uint workDimInput;
static Size3 globalWorkOffsetInput;
static Size3 globalWorkSizeInput;
static Size3 localWorkSizeInput;
static size_t rowPitch1Input, slicePitch1Input;
static size_t rowPitch2Input, slicePitch2Input;
static void* mappedPtr = NULL;

static void setKernelArgValuesInit()
{
    for (int i = 0; i < 100; i++)
    { kernelSetArgSize[i] = 0; kernelSetArgValue[i].clear(); }
}

/* only for testing!!!! */
extern "C"
{
CL_API_ENTRY cl_int CL_API_CALL
fakeclSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size,
               const void * arg_value) CL_API_SUFFIX__VERSION_1_0
{
    cl_int ret = clSetKernelArg(kernel, arg_index, arg_size, arg_value);
    if (ret == CL_SUCCESS)
    {
        kernelSetArgSize[arg_index] = arg_size;
        if (arg_value != NULL)
            kernelSetArgValue[arg_index].assign((const unsigned char*)arg_value,
                ((const unsigned char*)arg_value) + arg_size);
    }
    return ret;
}

static void enqueueCommandTestInit()
{
    blockingMode = false;
    workDimInput = 0;
    mappedPtr = NULL;
    rectOffset1Input = rectOffset2Input = rectRegionInput = 0;
    globalWorkOffsetInput = globalWorkSizeInput = localWorkSizeInput = 0;
    rowPitch1Input = rowPitch2Input = slicePitch1Input = slicePitch2Input = 0;
    waitListInput.clear();
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read,
            size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list,
            const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    blockingMode = blocking_read;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueReadBuffer(command_queue, buffer, blocking_read, offset, size, ptr,
        num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write,
        size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, 
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    blockingMode = blocking_write;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueWriteBuffer(command_queue, buffer, blocking_write, offset, size, ptr,
        num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyBuffer(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer,
        size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueCopyBuffer(command_queue, src_buffer, dst_buffer, src_offset,
        dst_offset, size, num_events_in_wait_list, event_wait_list, event);
}

#ifdef CL_VERSION_1_1
CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer,
        cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset,
        const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch,
        size_t host_row_pitch, size_t host_slice_pitch, void* ptr,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_1
{
    blockingMode = blocking_read;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, buffer_offset);
    rectOffset2Input = Size3(3, host_offset);
    rectRegionInput = Size3(3, region);
    rowPitch1Input = buffer_row_pitch;
    slicePitch1Input = buffer_slice_pitch;
    rowPitch2Input = host_row_pitch;
    slicePitch2Input = host_slice_pitch;
    return clEnqueueReadBufferRect(command_queue, buffer, blocking_read, buffer_offset,
        host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch,
        host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer,
        cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset,
        const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch,
        size_t host_row_pitch, size_t host_slice_pitch, const void* ptr,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_1
{
    blockingMode = blocking_write;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, buffer_offset);
    rectOffset2Input = Size3(3, host_offset);
    rectRegionInput = Size3(3, region);
    rowPitch1Input = buffer_row_pitch;
    slicePitch1Input = buffer_slice_pitch;
    rowPitch2Input = host_row_pitch;
    slicePitch2Input = host_slice_pitch;
    return clEnqueueWriteBufferRect(command_queue, buffer, blocking_write, buffer_offset,
        host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch,
        host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer,
        const size_t* src_origin, const size_t* dst_origin, const size_t* region,
        size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch,
        size_t dst_slice_pitch, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_1
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, src_origin);
    rectOffset2Input = Size3(3, dst_origin);
    rectRegionInput = Size3(3, region);
    rowPitch1Input = src_row_pitch;
    slicePitch1Input = src_slice_pitch;
    rowPitch2Input = dst_row_pitch;
    slicePitch2Input = dst_slice_pitch;
    return clEnqueueCopyBufferRect(command_queue, src_buffer, dst_buffer, src_origin,
        dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch,
        num_events_in_wait_list, event_wait_list, event);
}
#endif

#ifdef CL_VERSION_1_2
CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueFillBuffer(cl_command_queue command_queue, cl_mem buffer, const void* pattern, 
        size_t pattern_size, size_t offset, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueFillBuffer(command_queue, buffer, pattern, pattern_size, offset, size,
        num_events_in_wait_list, event_wait_list, event);
}
#endif

extern CL_API_ENTRY void * CL_API_CALL
fakeclEnqueueMapBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, 
        cl_map_flags map_flags, size_t offset, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event,
        cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
    blockingMode = blocking_map;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return mappedPtr = clEnqueueMapBuffer(command_queue, buffer, blocking_map, map_flags,
        offset, size, num_events_in_wait_list, event_wait_list, event, errcode_ret);
}

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueUnmapMemObject(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueUnmapMemObject(command_queue, memobj, mapped_ptr, num_events_in_wait_list,
        event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReadImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, 
        const size_t* origin, const size_t* region, size_t row_pitch, size_t slice_pitch,
        void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    blockingMode = blocking_read;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, origin);
    rectRegionInput = Size3(3, region);
    rowPitch1Input = row_pitch;
    slicePitch1Input = slice_pitch;
    return clEnqueueReadImage(command_queue, image, blocking_read, origin, region,
        row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueWriteImage(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, 
        const size_t* origin, const size_t* region, size_t input_row_pitch,
        size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    blockingMode = blocking_write;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, origin);
    rectRegionInput = Size3(3, region);
    rowPitch1Input = input_row_pitch;
    slicePitch1Input = input_slice_pitch;
    return clEnqueueWriteImage(command_queue, image, blocking_write, origin, region,
        input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list,
        event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyImage(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image,
        const size_t* src_origin, const size_t* dst_origin, const size_t* region, 
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, src_origin);
    rectOffset2Input = Size3(3, dst_origin);
    rectRegionInput = Size3(3, region);
    return clEnqueueCopyImage(command_queue, src_image, dst_image, src_origin, dst_origin,
        region, num_events_in_wait_list, event_wait_list, event);
}

#ifdef CL_VERSION_1_2
CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueFillImage(cl_command_queue command_queue, cl_mem image, const void* fill_color, 
        const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, origin);
    rectRegionInput = Size3(3, region);
    return clEnqueueFillImage(command_queue, image, fill_color, origin, region,
        num_events_in_wait_list, event_wait_list, event);
}
#endif

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem src_image,
        cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, src_origin);
    rectRegionInput = Size3(3, region);
    return clEnqueueCopyImageToBuffer(command_queue, src_image, dst_buffer, src_origin, region,
        dst_offset, num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueCopyBufferToImage(cl_command_queue command_queue, cl_mem src_buffer,
        cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region,
        cl_uint num_events_in_wait_list, const cl_event* event_wait_list,
        cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = Size3(3, dst_origin);
    rectRegionInput = Size3(3, region);
    return clEnqueueCopyBufferToImage(command_queue, src_buffer, dst_image, src_offset,
        dst_origin, region, num_events_in_wait_list, event_wait_list, event);
}

CL_API_ENTRY void * CL_API_CALL
fakeclEnqueueMapImage(cl_command_queue  command_queue, cl_mem image, cl_bool blocking_map,
        cl_map_flags map_flags, const size_t* origin, const size_t* region,
        size_t* image_row_pitch, size_t* image_slice_pitch, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event,
        cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
    blockingMode = blocking_map;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    rectOffset1Input = origin;
    rectRegionInput = region;
    return mappedPtr = clEnqueueMapImage(command_queue, image, blocking_map, map_flags,
        origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list,
        event_wait_list, event, errcode_ret);
}

CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim,
        const size_t* global_work_offset, const size_t* global_work_size,
        const size_t* local_work_size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    workDimInput = work_dim;
    if (work_dim <= 3)
    {
        if (global_work_offset!=NULL)
            globalWorkOffsetInput = Size3(work_dim, global_work_offset);
        globalWorkSizeInput = Size3(work_dim, global_work_size);
        if (local_work_size!=NULL)
            localWorkSizeInput = Size3(work_dim, local_work_size);
    }
    return clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset,
        global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
}

#ifdef CL_VERSION_2_0
CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueSVMMemcpy(cl_command_queue  command_queue, cl_bool blocking_copy,
        void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_2_0
{
    blockingMode = blocking_copy;
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueSVMMemcpy(command_queue, blocking_copy, dst_ptr, src_ptr, size,
        num_events_in_wait_list, event_wait_list, event);
}
#endif

#ifdef __CLPP_CL_GL
extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueAcquireGLObjects(cl_command_queue command_queue, cl_uint num_objects,
        const cl_mem* mem_objects, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueAcquireGLObjects(command_queue, num_objects, mem_objects,
        num_events_in_wait_list, event_wait_list, event);
}

extern CL_API_ENTRY cl_int CL_API_CALL
fakeclEnqueueReleaseGLObjects(cl_command_queue command_queue, cl_uint num_objects,
        const cl_mem* mem_objects, cl_uint num_events_in_wait_list,
        const cl_event* event_wait_list, cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
    if (num_events_in_wait_list != 0)
        waitListInput.assign(event_wait_list, event_wait_list + num_events_in_wait_list);
    else waitListInput.clear();
    return clEnqueueReleaseGLObjects(command_queue, num_objects, mem_objects,
        num_events_in_wait_list, event_wait_list, event);
}
#endif
}

std::ostream& operator<<(std::ostream& os, const Size3& size)
{
    os << "(" << size[0] << "," << size[1] << "," << size[2] << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Platform& platform)
{
    os << "[CLPlatform: " << platform() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Device& device)
{
    os << "[CLDev: " << device() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Context& context)
{
    os << "[CLCtx: " << context() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Memory& memory)
{
    os << "[CLMem: " << memory() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Sampler& sampler)
{
    os << "[CLSamp: " << sampler() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Program& program)
{
    os << "[CLPrg: " << program() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::Event& event)
{
    os << "[CLEv: " << event() << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clpp::CommandQueue& cmdQueue)
{
    os << "[CLCmdQ: " << cmdQueue() << "]";
    return os;
}


std::ostream& operator<<(std::ostream& os, const std::vector<unsigned char>& bin)
{
    os << "{";
    for (size_t i = 0; i < bin.size(); i++)
        os << int(bin[i]) << ((i+1<bin.size())?",":"");
    os << "}";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector)
{
    os << "{";
    for (size_t i = 0; i < vector.size(); i++)
        os << vector[i] << ((i+1<vector.size())?",":"");
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const cl_image_format& imgFmt)
{
    os << "[ImgFmt:" << imgFmt.image_channel_order << "," <<
                imgFmt.image_channel_data_type << "]";
    return os;
}

class TestException: public std::exception
{
private:
    std::string message;
public:
    TestException()
    { }
    
    TestException(const std::string& testName)
    { 
        message = "Test ";
        message += testName;
        message += " failed!";
    }
    
    template<typename T>
    TestException(const std::string& testName, const T& expected, const T& result)
    {
        std::ostringstream oss;
        oss << "Test " << testName << " failed! Expected: " << 
                expected << ", Result: " << result;
        oss.flush();
        message = oss.str();
    }
    
    virtual ~TestException() throw()
    { }
    
    const char* what() const throw()
    { return message.c_str(); }
};

static void assertBool(const std::string testName, bool good)
{
    if (!good)
        throw TestException(testName);
}

template<typename T>
static void assertEqual(const std::string testName, const T& expected, const T& result)
{
    if (expected != result)
        throw TestException(testName, expected, result);
}

static void assertCStrEqual(const std::string testName, const char* expected,
                const char* result)
{
    if (::strcmp(expected, result))
        throw TestException(testName, expected, result);
}

static void ErrorClassTester()
{
    clpp::Error error0;
    assertEqual("ErrorClassTesterEmpty error", 0, error0.err());
    assertCStrEqual("ErrorClassTesterEmpty msgTest", "No error!", error0.what());
    clpp::Error error1(7, "buru");
    assertEqual("ErrorClassTesterEmpty error", 7, error1.err());
    assertCStrEqual("ErrorClassTester msgTest", "Error code: 7, Desc: buru", error1.what());
}

static void Size3Tester()
{
    Size3 empty;
    assertEqual("Size3Empty", Size3(0,0,0), empty);
    Size3 six = 6;
    assertEqual("Size3Six", Size3(6,0,0), six);
    Size3 size3(8, 11);
    assertEqual("Size3Size3", Size3(8,11,0), size3);
    Size3 size4(18, 11, 85);
    assertEqual("Size3Size4", Size3(18,11,85), size4);
    
    std::vector<int> v;
    Size3 size4e(v);
    assertEqual("Size3Size4e", Size3(0,0,0), size4e);
    v.push_back(51);
    Size3 size5(v);
    assertEqual("Size3Size5", Size3(51,0,0), size5);
    v.push_back(831);
    Size3 size6(v);
    assertEqual("Size3Size6", Size3(51,831,0), size6);
    v.push_back(73);
    Size3 size7(v);
    assertEqual("Size3Size7", Size3(51,831,73), size7);
    v.push_back(82);
    Size3 size8(v);
    assertEqual("Size3Size8", Size3(51,831,73), size8);
    
    static const int array1[3] = { 16, 75, 11 };
    Size3 arr0s(0, array1);
    assertEqual("Size3Arr0s", Size3(0,0,0), arr0s);
    Size3 arr1s(1, array1);
    assertEqual("Size3Arr1s", Size3(16,0,0), arr1s);
    Size3 arr2s(2, array1);
    assertEqual("Size3Arr2s", Size3(16, 75, 0), arr2s);
    Size3 arr3s(3, array1);
    assertEqual("Size3Arr3s", Size3(16, 75, 11), arr3s);
    Size3 arr10s(10, array1);
    assertEqual("Size3Arr10s", Size3(16, 75, 11), arr10s);
    Size3 arrs(array1);
    assertEqual("Size3Arrs", Size3(16, 75, 11), arrs);
    
#ifdef __CLPP_CPP0X
    /* initializer list */
    Size3 initlist3({7, 31, 5});
    assertEqual("Size3InitList3", Size3(7, 31, 5), initlist3);
    Size3 initlist2({7, 31});
    assertEqual("Size3InitList2", Size3(7, 31, 0), initlist2);
    Size3 initlist1({7});
    assertEqual("Size3InitList1", Size3(7, 0, 0), initlist1);
    Size3 initlist0({});
    assertEqual("Size3InitList1", Size3(0, 0, 0), initlist0);
#endif
    
    /* assignment */
    Size3 x(6, 3, 1);
    x = v;
    assertEqual("Size3AssignV0", Size3(51,831,73), x);
#ifdef __CLPP_CPP0X
    /* initializer list */
    x = {11,33,45};
    assertEqual("Size3AssignIL", Size3(11,33,45), x);
#endif
}

static std::string getPlatformInfoString(cl_platform_id platform, cl_platform_info paramName)
{
    size_t size;
    if (clGetPlatformInfo(platform, paramName, 0, NULL, &size) != CL_SUCCESS)
        throw TestException("Failed clGetPlatformInfo");
    std::vector<char> buf(size);
    if (clGetPlatformInfo(platform, paramName, size, &buf[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetPlatformInfo");
    return std::string(&buf[0]);
}

static std::string getDeviceInfoString(cl_device_id device, cl_device_info paramName)
{
    size_t size;
    if (clGetDeviceInfo(device, paramName, 0, NULL, &size) != CL_SUCCESS)
        throw TestException("Failed clGetDeviceInfo");
    std::vector<char> buf(size);
    if (clGetDeviceInfo(device, paramName, size, &buf[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetDeviceInfo");
    return std::string(&buf[0]);
}

template<typename T>
static T getDeviceInfo(cl_device_id device, cl_device_info paramName)
{
    T value;
    if (clGetDeviceInfo(device, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetDeviceInfo");
    return value;
}

template<typename T>
static T getContextInfo(cl_context context, cl_context_info paramName)
{
    T value;
    if (clGetContextInfo(context, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetContextInfo");
    return value;
}

template<typename T>
static std::vector<T> getContextInfoVector(cl_context context, cl_context_info paramName)
{
    size_t outNum;
    if (clGetContextInfo(context, paramName, 0, NULL, &outNum) != CL_SUCCESS)
        throw TestException("Failed clGetContextInfo");
    outNum /= sizeof(T);
    std::vector<T> value(outNum);
    if (outNum == 0) return value;
    if (clGetContextInfo(context, paramName, sizeof(T)*outNum, &value[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetContextInfo");
    return value;
}

template<typename T>
static T getMemObjectInfo(cl_mem memObject, cl_mem_info paramName)
{
    T value;
    if (clGetMemObjectInfo(memObject, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetMemObjectInfo");
    return value;
}

template<typename T>
static T getImageInfo(cl_mem image, cl_image_info paramName)
{
    T value;
    if (clGetImageInfo(image, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetImageInfo");
    return value;
}

template<typename T>
static T getProgramInfo(cl_program program, cl_program_info paramName)
{
    T value;
    if (clGetProgramInfo(program, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetProgramInfo");
    return value;
}

static std::string getProgramInfoString(cl_program program, cl_program_info paramName)
{
    size_t size;
    if (clGetProgramInfo(program, paramName, 0, NULL, &size) != CL_SUCCESS)
        throw TestException("Failed clGetProgramInfo");
    std::vector<char> buf(size);
    if (clGetProgramInfo(program, paramName, size, &buf[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetProgramInfo");
    return std::string(&buf[0]);
}

template<typename T>
static std::vector<T> getProgramInfoVector(cl_program program, cl_program_info paramName)
{
    size_t outNum;
    if (clGetProgramInfo(program, paramName, 0, NULL, &outNum) != CL_SUCCESS)
        throw TestException("Failed clGetProgramInfo");
    outNum /= sizeof(T);
    std::vector<T> value(outNum);
    if (outNum == 0) return value;
    if (clGetProgramInfo(program, paramName, sizeof(T)*outNum, &value[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetProgramInfo");
    return value;
}

static std::string getProgramBuildInfoString(cl_program program, cl_device_id device,
            cl_program_build_info paramName)
{
    size_t size;
    if (clGetProgramBuildInfo(program, device, paramName, 0, NULL, &size) != CL_SUCCESS)
        throw TestException("Failed clGetProgramBuildInfo");
    std::vector<char> buf(size);
    if (clGetProgramBuildInfo(program, device, paramName, size, &buf[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetProgramBuildInfo");
    return std::string(&buf[0]);
}

template<typename T>
static T getKernelInfo(cl_kernel kernel, cl_kernel_info paramName)
{
    T value;
    if (clGetKernelInfo(kernel, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetKernelInfo");
    return value;
}

static std::string getKernelInfoString(cl_kernel kernel, cl_kernel_info paramName)
{
    size_t size;
    if (clGetKernelInfo(kernel, paramName, 0, NULL, &size) != CL_SUCCESS)
        throw TestException("Failed clGetKernelInfo");
    std::vector<char> buf(size);
    if (clGetKernelInfo(kernel, paramName, size, &buf[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetKernelInfo");
    return std::string(&buf[0]);
}

template<typename T>
static T getKernelWorkGroupInfo(cl_kernel kernel, cl_device_id device,
            cl_kernel_work_group_info paramName)
{
    T value;
    if (clGetKernelWorkGroupInfo(kernel, device, paramName, sizeof(T),
                    &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetKernelWorkGroupInfo");
    return value;
}

#if __CLPP_CL_ABI_VERSION>=102
static std::string getKernelArgInfoString(cl_kernel kernel, cl_uint argIndex,
            cl_kernel_arg_info paramName)
{
    size_t size;
    if (clGetKernelArgInfo(kernel, argIndex, paramName, 0, NULL, &size) != CL_SUCCESS)
        throw TestException("Failed clGetKernelArgInfo");
    std::vector<char> buf(size);
    if (clGetKernelArgInfo(kernel, argIndex, paramName, size, &buf[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetKernelArgInfo");
    return std::string(&buf[0]);
}

template<typename T>
static T getKernelArgInfo(cl_kernel kernel, cl_uint argIndex, cl_kernel_arg_info paramName)
{
    T value;
    if (clGetKernelArgInfo(kernel, argIndex, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetKernelArgInfo");
    return value;
}
#endif

template<typename T>
static T getEventInfo(cl_event event, cl_event_info paramName)
{
    T value;
    if (clGetEventInfo(event, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetEventInfo");
    return value;
}

template<typename T>
static T getEventProfilingInfo(cl_event event, cl_profiling_info paramName)
{
    T value;
    if (clGetEventProfilingInfo(event, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetEventProfilingInfo");
    return value;
}

template<typename T>
static T getCommandQueueInfo(cl_command_queue cmdQueue, cl_command_queue_info paramName)
{
    T value;
    if (clGetCommandQueueInfo(cmdQueue, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetCommandQueueInfo");
    return value;
}

static void GetInfoHelperTester()
{
    clpp::Platform platform = clpp::Platform::get()[0];
    std::vector<clpp::Device> devices = platform.getAllDevices();
    std::vector<clpp::Context> contexts;
    for (std::vector<clpp::Device>::const_iterator it = devices.begin();
                it != devices.end(); ++it)
        contexts.push_back(clpp::Context(*it));
    std::vector<clpp::Context> contextsToChange = contexts;
    // get refCounts for contexts
    std::vector<cl_uint> contextRefCounts;
    for (std::vector<clpp::Context>::const_iterator it = contexts.begin();
                it != contexts.end(); ++it)
         contextRefCounts.push_back(it->refCount());
    // check fatal error
    bool catched = false;
    try
    { clpp::impl::GetInfoRefHelper<cl_platform_id, cl_platform_info,
                clpp::Context, 0>::getInfoVector(platform(), 245);
    }
    catch (const clpp::Error& err)
    { catched = true; }
    
    
    assertBool("PlatformInfo failed 0!", catched);
    assertEqual("Fake platform info with contextArray", contextsToChange, contexts);
    
    std::vector<cl_uint> newContextRefCounts;
    for (std::vector<clpp::Context>::const_iterator it = contexts.begin();
                it != contexts.end(); ++it)
         newContextRefCounts.push_back(it->refCount());
    assertEqual("ContextRefCounts after fake info with contextArray", newContextRefCounts,
                contextRefCounts);
    // get info bool
    bool compilerAvailable = devices[0].getInfo<bool>(CL_DEVICE_COMPILER_AVAILABLE);
    assertBool("Boolean compilerAvailable", compilerAvailable);
    
    // string getInfos
    std::string platformName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
    std::string getInfoPName = platform.getInfo<std::string>(CL_PLATFORM_NAME);
    assertEqual("PlatformName==getInfoPName", platformName, getInfoPName);
}

static std::vector<clpp::Device> getPlatformDevices(cl_platform_id platform, cl_device_type type)
{
    cl_uint numDevices;
    if (clGetDeviceIDs(platform, type, 0, NULL, &numDevices) != CL_SUCCESS)
        throw TestException("Failed clGetDeviceIDs");
    std::vector<clpp::Device> devices(numDevices);
    if (clGetDeviceIDs(platform, type, numDevices,
                reinterpret_cast<cl_device_id*>(&devices[0]), NULL) != CL_SUCCESS)
        throw TestException("Failed clGetDeviceIDs");
    return devices;
}

static void PlatformClassTester()
{   // getting platforms
    std::vector<clpp::Platform> platforms = clpp::Platform::get();
    cl_uint platformsNum;
    if (clGetPlatformIDs(0, NULL, &platformsNum) != CL_SUCCESS)
        TestException("Failed clGetPlatformIDs");
    
    std::vector<clpp::Platform> expectedPlatforms(platformsNum);
    if (clGetPlatformIDs(platformsNum, reinterpret_cast<cl_platform_id*>(
                &expectedPlatforms[0]), NULL) != CL_SUCCESS)
        TestException("Failed clGetPlatformIDs");
    assertEqual("Platforms", expectedPlatforms, platforms);
    
    std::vector<clpp::Platform> platformVector(platformsNum);
    clpp::Platform::get(platformsNum, &platformVector[0]);
    assertEqual("PlatformsArray", expectedPlatforms, platformVector);
    
    // testing platform info
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string expName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        assertEqual("Platform "+expName+" getName()", expName, platform.getName());
        assertEqual("Platform "+expName+" getInfo()", expName,
                     platform.getInfoString(CL_PLATFORM_NAME));
        assertEqual("Platform "+expName+" getInfo<string>()", expName,
                     platform.getInfo<std::string>(CL_PLATFORM_NAME));
        
        std::vector<char> pNameVector = platform.getInfoVector<char>(CL_PLATFORM_NAME);
        assertEqual("Platform "+expName+" getInfoVector<char>(out)", expName,
                    std::string(&pNameVector[0]));
        size_t pNameSize;
        clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, NULL, &pNameSize);
        std::vector<char> pNameArray(pNameSize);
        
        size_t nameSize;
        if (clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, NULL, &nameSize) != CL_SUCCESS)
            throw TestException("Failed clGetPlatformInfo");
        
        // other infos
        assertEqual("Platform "+expName+" getProfile()",
                getPlatformInfoString(platform, CL_PLATFORM_PROFILE), platform.getProfile());
        assertEqual("Platform "+expName+" getVersion()",
                getPlatformInfoString(platform, CL_PLATFORM_VERSION), platform.getVersion());
        assertEqual("Platform "+expName+" getVendor()",
                getPlatformInfoString(platform, CL_PLATFORM_VENDOR), platform.getVendor());
        assertEqual("Platform "+expName+" getExtensions()",
                getPlatformInfoString(platform, CL_PLATFORM_EXTENSIONS),
                        platform.getExtensions());
    }
    
    // testing getting devices
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string expName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        std::vector<clpp::Device> expAllDevices = getPlatformDevices(platform,
                    CL_DEVICE_TYPE_ALL);
        assertEqual("Platform "+expName+" all devices", expAllDevices,
                    platform.getAllDevices());
        assertEqual("Platform "+expName+" CL_DEVICE_TYPE_ALL devices", expAllDevices,
                    platform.getDevices(CL_DEVICE_TYPE_ALL));
        
        std::vector<clpp::Device> allDevices = platform.getAllDevices();
        bool failed = false;
        try
        { getPlatformDevices(platform, 256); }
        catch(const TestException& ex)
        { failed = true; }
        assertBool("Platform "+expName+" Get Devices type=256 failure", failed);
        
        bool expNoGPUDevices = false;
        std::vector<clpp::Device> expGPUDevices;
        std::vector<clpp::Device> resGPUDevices;
        try
        { expGPUDevices = getPlatformDevices(platform, CL_DEVICE_TYPE_GPU); }
        catch(const TestException& ex)
        { expNoGPUDevices = true; }
        bool resNoGPUDevices = false;
        try
        { resGPUDevices = platform.getGPUDevices(); }
        catch(const clpp::Error& ex)
        { resNoGPUDevices = true; }
        assertEqual("Platform "+expName+" noGPUDevices 1", expNoGPUDevices, resNoGPUDevices);
        assertEqual("Platform "+expName+" GPUDevices 1", expGPUDevices, resGPUDevices);
        
        resGPUDevices.clear();
        resNoGPUDevices = false;
        try
        { resGPUDevices = platform.getDevices(CL_DEVICE_TYPE_GPU); }
        catch(const clpp::Error& ex)
        { resNoGPUDevices = true; }
        assertEqual("Platform "+expName+" noGPUDevices 2", expNoGPUDevices, resNoGPUDevices);
        assertEqual("Platform "+expName+" GPUDevices 2", expGPUDevices, resGPUDevices);
        
        clpp::Device defaultDevice = getPlatformDevices(platform, CL_DEVICE_TYPE_DEFAULT)[0];
        assertEqual("Platform "+expName+" default device", defaultDevice,
                    platform.getDefaultDevice());
    }
    
    clpp::Platform nullPlatform;
    assertBool("NullPlatform !", !nullPlatform);
    assertBool("NullPlatform ", !(bool)nullPlatform);
    {
        cl_platform_id clPlatform = platforms[0];
        clpp::Platform platformx = clpp::Platform::from(clPlatform);
        assertEqual("Platform::from", platforms[0], platformx);
    }
}

static void DeviceClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        
        // get info test
        for (std::vector<clpp::Device>::const_iterator it = devices.begin();
                    it != devices.end(); ++it)
        {
            const clpp::Device& device = *it;
            std::string pdName = getPlatformInfoString(platform, CL_PLATFORM_NAME)+
                    " "+getDeviceInfoString(device, CL_DEVICE_NAME);
            std::string expDName = getDeviceInfoString(device, CL_DEVICE_NAME);
            assertEqual("Device "+pdName+" getName()", expDName, device.getName());
            assertEqual("Device "+pdName+" getInfo(NAME)", expDName,
                        device.getInfoString(CL_DEVICE_NAME));
            assertEqual("Device "+pdName+" getInfo<string>(NAME)", expDName,
                        device.getInfo<std::string>(CL_DEVICE_NAME));
            size_t strArraySize;
            clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &strArraySize);
            std::vector<char> strVector = device.getInfoVector<char>(CL_DEVICE_NAME);
            assertEqual("Device "+pdName+" getInfoVector<char>(NAME)", expDName,
                        std::string(&strVector[0]));
            // other info tests
            Size3 expMaxWorkSize = getDeviceInfo<Size3>(device, CL_DEVICE_MAX_WORK_ITEM_SIZES);
            assertEqual("Device "+pdName+" maxWorkSize1", expMaxWorkSize,
                        device.getInfo<Size3>(CL_DEVICE_MAX_WORK_ITEM_SIZES));
            Size3 resMaxWorkSize;
            device.getInfo<Size3>(CL_DEVICE_MAX_WORK_ITEM_SIZES, resMaxWorkSize);
            assertEqual("Device "+pdName+" maxWorkSize2", expMaxWorkSize, resMaxWorkSize);
            
            /* other paramNames */
            assertEqual("Device "+pdName+" maxWorkGroupSize",
                    getDeviceInfo<size_t>(device, CL_DEVICE_MAX_WORK_GROUP_SIZE),
                    device.getMaxWorkGroupSize());
            assertEqual("Device "+pdName+" VendorId",
                    getDeviceInfo<cl_uint>(device, CL_DEVICE_VENDOR_ID), device.getVendorId());
            assertEqual("Device "+pdName+" MaxClockFrequency",
                    getDeviceInfo<cl_uint>(device, CL_DEVICE_MAX_CLOCK_FREQUENCY),
                    device.getMaxClockFrequency());
        }
        
#if __CLPP_CL_ABI_VERSION>=102 || defined(__CLPP_DEVICE_FISSION)
        // creating subdevices
        for (std::vector<clpp::Device>::const_iterator it = devices.begin();
                    it != devices.end(); ++it)
        {
            const clpp::Device& device = *it;
            if ((device.getType() & CL_DEVICE_TYPE_CPU) == 0)
                continue;
            std::string pdName = getPlatformInfoString(platform, CL_PLATFORM_NAME)+
                    " "+getDeviceInfoString(device, CL_DEVICE_NAME);
            
            std::vector<clpp::Device> subDevices = device.createSubDevicesEqually(1);
            for (size_t k = 0; k < subDevices.size(); k++)
            {
                assertEqual("Device "+pdName+" subDeviceEqually compUnits",
                            1U, subDevices[k].getMaxComputeUnits());
                assertEqual("Device "+pdName+" subDeviceEqually parent",
                            device, subDevices[k].getParentDevice());
            }
            // test failed
            bool failed = false;
            {
                std::vector<clpp::Device> tmpSubDevices = subDevices;
                try
                { subDevices = device.createSubDevicesEqually(10000); }
                catch(const clpp::Error& ex)
                { failed = true; }
                assertBool("Device "+pdName+" subDevicesEqually fail", failed);
                assertEqual("Device "+pdName+" old subDevicesEqually", tmpSubDevices, subDevices);
                
            }
            
            /* device reference count */
            std::vector<clpp::Device> subDevices2 = device.createSubDevicesEqually(1);
            
            clpp::Device mySubDev(subDevices[0]);
            assertEqual("Device "+pdName+" SubDevice refCount1", 2U, subDevices[0].refCount());
            mySubDev = device;
            assertEqual("Device "+pdName+" SubDevice refCount2", 1U, subDevices[0].refCount());
            mySubDev = subDevices[0];
            assertEqual("Device "+pdName+" SubDevice refCount3", 2U, subDevices[0].refCount());
            /*mySubDev = device();
            assertEqual("Device "+pdName+" SubDevice refCount4", 1U, subDevices[0].refCount());*/
            mySubDev = subDevices[0];
            clpp::Device mySubDev2(subDevices2[0]);
            std::swap(mySubDev, mySubDev2);
            assertEqual("Device "+pdName+" SubDevice refCount5", 2U, subDevices[0].refCount());
            assertEqual("Device "+pdName+" SubDevice refCount6", 2U, subDevices2[0].refCount());
#   ifdef __CLPP_CPP0X
            clpp::Device dev0 = subDevices[0];
            clpp::Device dev1 = subDevices[0];
            dev0 = std::move(dev1); // test move assignment
            assertEqual("Device "+pdName+" SubDevice refCount5", 3U, subDevices[0].refCount());
#   endif
        }
#endif
        {
            cl_device_id clDevice = devices[0];
            clpp::Device devicex = clpp::Device::from(clDevice);
            assertEqual("Device::from", devices[0], devicex);
        }
    }
}

static void ContextClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        
        clpp::Context context1Dev(devices[0]);
        clpp::Context contextAll(devices);
        const cl_context_properties ctxProps[3] = { CL_CONTEXT_PLATFORM,
                    (cl_context_properties)platform(), 0 };
        std::vector<cl_context_properties> ctxPropsV(ctxProps, ctxProps+3);
        clpp::Context contextwp(ctxProps, devices[0]);
        clpp::Context contextAllwp(ctxProps, devices);
        
        clpp::Context contextByTypewp(ctxProps, CL_DEVICE_TYPE_ALL);
        clpp::Context contextByTypewPlatform(platform, CL_DEVICE_TYPE_ALL);
        
        std::vector<clpp::Device> firstDeviceVector;
        firstDeviceVector.push_back(devices[0]);
        assertEqual("Context for " +pName+ " 1 device: device check", firstDeviceVector,
                getContextInfoVector<clpp::Device>(context1Dev, CL_CONTEXT_DEVICES));
        assertBool("Context for " +pName+ " 1 device: props check empty",
                   getContextInfoVector<cl_context_properties>(
                       context1Dev, CL_CONTEXT_PROPERTIES).empty());
        
        assertEqual("Context for " +pName+ " all devices: devices check", devices,
                getContextInfoVector<clpp::Device>(contextAll, CL_CONTEXT_DEVICES));
        assertBool("Context for " +pName+ " all devices: props check empty",
                getContextInfoVector<cl_context_properties>(
                       contextAll, CL_CONTEXT_PROPERTIES).empty());
        
        assertEqual("Context for " +pName+ " 1 device,props: device check", firstDeviceVector,
                getContextInfoVector<clpp::Device>(contextwp, CL_CONTEXT_DEVICES));
        assertEqual("Context for " +pName+ " 1 device,props: props check", ctxPropsV,
                getContextInfoVector<cl_context_properties>(contextwp, CL_CONTEXT_PROPERTIES));
        
        assertEqual("Context for " +pName+ " all devices,props: device check", devices,
                getContextInfoVector<clpp::Device>(contextAllwp, CL_CONTEXT_DEVICES));
        assertEqual("Context for " +pName+ " all devices,props: props check", ctxPropsV,
                getContextInfoVector<cl_context_properties>(contextAllwp, CL_CONTEXT_PROPERTIES));
        
        assertEqual("Context for " +pName+ " bytype devices,props: device check", devices,
                getContextInfoVector<clpp::Device>(contextByTypewp, CL_CONTEXT_DEVICES));
        assertEqual("Context for " +pName+ " all2 devices,props: props check", ctxPropsV,
            getContextInfoVector<cl_context_properties>(contextByTypewp, CL_CONTEXT_PROPERTIES));
        
        assertEqual("Context for " +pName+ " bytypePlatform devices,props: device check", devices,
                getContextInfoVector<clpp::Device>(contextByTypewPlatform, CL_CONTEXT_DEVICES));
        assertEqual("Context for " +pName+ " bytypePlatform devices,props: props check",
                ctxPropsV, getContextInfoVector<cl_context_properties>(contextByTypewPlatform,
                            CL_CONTEXT_PROPERTIES));
    }
    
    // get info tests
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        const cl_context_properties ctxProps[3] = { CL_CONTEXT_PLATFORM,
                    (cl_context_properties)platform(), 0 };
        std::vector<cl_context_properties> ctxPropsV(ctxProps, ctxProps+3);
        
        clpp::Context context(ctxProps, devices);
        assertEqual("Context for " +pName+ ". Check devices", devices, context.getDevices());
        assertEqual("Context for " +pName+ " getInfoVector<device>()", devices,
                    context.getInfoVector<clpp::Device>(CL_CONTEXT_DEVICES));
        assertEqual("Context for " +pName+ " getInfo<device>(array)", devices,
                    context.getInfoVector<clpp::Device>(CL_CONTEXT_DEVICES));
        assertEqual("Context for " +pName+ ". DevicesNum", devices.size(),
                    size_t(context.getNumDevices()));
        
        assertEqual("Context for " +pName+ ". props check", ctxPropsV, context.getProperties());
    }
    
    // references testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::Context context2(devices);
        assertEqual("Context for " +pName+ ".refcount1", 1U, context.refCount());
        assertEqual("Context for " +pName+ ".refcount2", 1U, context2.refCount());
        {
            clpp::Context contextCopy = context;
            assertEqual("Context for " +pName+ ".refcount3", 2U, context.refCount());
            assertEqual("Context for " +pName+ ".refcount4", 1U, context2.refCount());
        }
        assertEqual("Context for " +pName+ ".refcount5", 1U, context.refCount());
        clpp::Context context3;
        context3 = context2;
        assertEqual("Context for " +pName+ ".refcount6", 2U, context2.refCount());
        context3 = context;
        assertEqual("Context for " +pName+ ".refcount7", 1U, context2.refCount());
        assertEqual("Context for " +pName+ ".refcount8", 2U, context.refCount());
#   ifdef __CLPP_CPP0X
        context = std::move(context3);
        assertEqual("Context for " +pName+ ".refcount9", 1U, context.refCount());
#   endif
    }
    
    // image supported formats
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        cl_uint imgfmtsNum;
        if (clGetSupportedImageFormats(context, CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D,
                        0, NULL, &imgfmtsNum) != CL_SUCCESS)
            throw TestException("Failed clGetSupportedImageFormats");
        std::vector<clpp::ImageFormat> imgfmts(imgfmtsNum);
        if (clGetSupportedImageFormats(context, CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D,
                        imgfmtsNum, &imgfmts[0], NULL) != CL_SUCCESS)
            throw TestException("Failed clGetSupportedImageFormats");
        
        assertEqual("Context for " +pName+ ".supportedImgFmts", imgfmts,
                context.getSupportedImageFormats(CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D));
    }
    // tests for createCommandQueues
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        std::vector<clpp::CommandQueue> cmdQueues1 = context.createCommandQueues();
        std::vector<clpp::CommandQueue> cmdQueues2 = context.createCommandQueues(
                CL_QUEUE_PROFILING_ENABLE);
        assertEqual("Ctx CommandQueues1 for "+pName+" number", devices.size(),
                    cmdQueues1.size());
        assertEqual("Ctx CommandQueues2 for "+pName+" number", devices.size(),
                    cmdQueues2.size());
#if __CLPP_CL_ABI_VERSION>=200
        static const cl_queue_properties cmdqprops[5] = {
            CL_QUEUE_PROPERTIES, (cl_queue_properties)CL_QUEUE_PROFILING_ENABLE,
            CL_QUEUE_SIZE, 1000, 0 };
        std::vector<clpp::CommandQueue> cmdQueues3 = context.createCommandQueues(cmdqprops);
        std::vector<clpp::CommandQueue> cmdQueues4 = context.createCommandQueues(
            CL_QUEUE_PROFILING_ENABLE, 1000);
        
        assertEqual("Ctx CommandQueues3 for "+pName+" number", devices.size(),
                    cmdQueues3.size());
        assertEqual("Ctx CommandQueues4 for "+pName+" number", devices.size(),
                    cmdQueues4.size());
#endif
        for (size_t j = 0; j < devices.size(); j++)
        {
            const clpp::Device& device = devices[j];
            std::string xName = pName+" "+device.getName();
            assertEqual("Ctx CommandQueue1 for "+xName+" device", device,
                        cmdQueues1[j].getDevice());
            assertEqual("Ctx CommandQueue2 for "+xName+" device", device,
                        cmdQueues2[j].getDevice());
            assertEqual("Ctx CommandQueue1 for "+xName+" context", context,
                        cmdQueues1[j].getContext());
            assertEqual("Ctx CommandQueue2 for "+xName+" context", context,
                        cmdQueues2[j].getContext());
#if __CLPP_CL_ABI_VERSION>=200
            assertEqual("Ctx CommandQueue3 for "+xName+" device", device,
                        cmdQueues3[j].getDevice());
            assertEqual("Ctx CommandQueue4 for "+xName+" device", device,
                        cmdQueues4[j].getDevice());
            assertEqual("Ctx CommandQueue3 for "+xName+" context", context,
                        cmdQueues3[j].getContext());
            assertEqual("Ctx CommandQueue4 for "+xName+" context", context,
                        cmdQueues4[j].getContext());
#endif
        }
    }
    // image supported formats
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        assertEqual("Context for " +pName+ " before from()", 1U, context.refCount());
        cl_context clContext = context;
        clpp::Context contextx = clpp::Context::from(clContext);
        assertEqual("Context::from", context, contextx);
        assertEqual("Context for " +pName+ " after from(retain=true)", 2U, context.refCount());
        clpp::Context contextx2 = clpp::Context::from(clContext, false);
        assertEqual("Context for " +pName+ " after from(retain=false)", 2U, context.refCount());
        assertEqual("Context::from2", context, contextx2);
        clRetainContext(context);
    }
}

static void BufferClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        std::vector<cl_uint> myData(20000);
        clpp::Buffer buffer1(context, CL_MEM_READ_ONLY, 10000);
        clpp::Buffer buffer2(context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, 15000, &myData[0]);
        clpp::Buffer buffer3(context, true, true, 5000, &myData[0]);
        clpp::Buffer buffer4(context, false, false, 10000);
        
        assertEqual("Buffer1 for "+pName+" flags", cl_mem_flags(CL_MEM_READ_ONLY),
                getMemObjectInfo<cl_mem_flags>(buffer1, CL_MEM_FLAGS));
        assertEqual("Buffer1 for "+pName+" size", size_t(10000),
                getMemObjectInfo<size_t>(buffer1, CL_MEM_SIZE));
        assertEqual("Buffer1 for "+pName+" hostPtr", (void*)NULL,
                getMemObjectInfo<void*>(buffer1, CL_MEM_HOST_PTR));
        
        assertEqual("Buffer2 for "+pName+" flags",
                cl_mem_flags(CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR),
                getMemObjectInfo<cl_mem_flags>(buffer2, CL_MEM_FLAGS));
        assertEqual("Buffer2 for "+pName+" size", size_t(15000),
                getMemObjectInfo<size_t>(buffer2, CL_MEM_SIZE));
        assertEqual("Buffer2 for "+pName+" hostPtr", (void*)&myData[0],
                getMemObjectInfo<void*>(buffer2, CL_MEM_HOST_PTR));
        
        assertEqual("Buffer3 for "+pName+" flags",
                cl_mem_flags(CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR),
                getMemObjectInfo<cl_mem_flags>(buffer3, CL_MEM_FLAGS));
        assertEqual("Buffer3 for "+pName+" size", size_t(5000),
                getMemObjectInfo<size_t>(buffer3, CL_MEM_SIZE));
        assertEqual("Buffer3 for "+pName+" hostPtr", (void*)&myData[0],
                getMemObjectInfo<void*>(buffer3, CL_MEM_HOST_PTR));
        
        assertEqual("Buffer4 for "+pName+" flags", cl_mem_flags(CL_MEM_READ_WRITE),
                getMemObjectInfo<cl_mem_flags>(buffer4, CL_MEM_FLAGS));
        assertEqual("Buffer4 for "+pName+" size", size_t(10000),
                getMemObjectInfo<size_t>(buffer4, CL_MEM_SIZE));
        assertEqual("Buffer4 for "+pName+" hostPtr", (void*)NULL,
                getMemObjectInfo<void*>(buffer4, CL_MEM_HOST_PTR));
    }
    
    // get info testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::Buffer buffer(context, CL_MEM_READ_WRITE, 6700);
        
        {
            clpp::Context contextOut = buffer.getContext();
            assertEqual("Buffer for "+pName+" context", context, contextOut);
            assertEqual("Context from buffer for "+pName+" refCount", 3U, contextOut.refCount());
        }
        assertEqual("Context from buffer for "+pName+" refCount", 2U, context.refCount());
        assertEqual("Buffer for "+pName+" getInfo<Context>()", context,
                    buffer.getInfo<clpp::Context>(CL_MEM_CONTEXT));
        clpp::Context context0;
        buffer.getInfo(CL_MEM_CONTEXT, context0);
        assertEqual("Buffer for "+pName+" getInfo<Context>(out)", context, context0);
        std::vector<clpp::Context> expContexts;
        expContexts.push_back(context);
        assertEqual("Buffer for "+pName+" getInfoVector<Context>()", expContexts,
                    buffer.getInfoVector<clpp::Context>(CL_MEM_CONTEXT));
        std::vector<clpp::Context> contextsArray(1);
        assertEqual("Buffer for "+pName+" getSize", size_t(6700U), buffer.getSize());
    }
    
    // reference testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Buffer buffer(context, CL_MEM_READ_ONLY, 10000);
        clpp::Buffer buffer2(context, CL_MEM_WRITE_ONLY, 10000);
        
        assertEqual("Buffer for " +pName+ ".refcount1", 1U, buffer.refCount());
        assertEqual("Buffer for " +pName+ ".refcount2", 1U, buffer2.refCount());
        {
            clpp::Buffer bufferCopy = buffer;
            assertEqual("Buffer for " +pName+ ".refcount3", 2U, buffer.refCount());
            assertEqual("Buffer for " +pName+ ".refcount4", 1U, buffer2.refCount());
        }
        assertEqual("Buffer for " +pName+ ".refcount5", 1U, buffer.refCount());
        clpp::Buffer buffer3;
        buffer3 = buffer2;
        assertEqual("Buffer for " +pName+ ".refcount6", 2U, buffer2.refCount());
        buffer3 = buffer;
        assertEqual("Buffer for " +pName+ ".refcount7", 1U, buffer2.refCount());
        assertEqual("Buffer for " +pName+ ".refcount8", 2U, buffer.refCount());
#   ifdef __CLPP_CPP0X
        buffer = std::move(buffer3);
        assertEqual("Buffer for " +pName+ ".refcount9", 1U, buffer.refCount());
#   endif
    }
#if __CLPP_CL_ABI_VERSION>=102
    // testing creating subbuffers
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Buffer buffer(context, CL_MEM_READ_WRITE, 30000);
        cl_uint bufAlign = 1;
        for (std::vector<clpp::Device>::const_iterator it = devices.begin();
                    it != devices.end(); ++it)
            bufAlign = std::max(bufAlign, devices[0].getMemBaseAddrAlign()>>3);
        
        const size_t offset = (size_t(1200U)/bufAlign)*bufAlign;
        clpp::Buffer subBuffer = buffer.createSubBuffer(CL_MEM_READ_WRITE, offset, 8900);
        
        assertEqual("SubBuffer for "+pName+" size", size_t(8900U), subBuffer.getSize());
        assertEqual("SubBuffer for "+pName+" offset", offset, subBuffer.getOffset());
        assertEqual("SubBuffer for "+pName+" buffer", static_cast<const clpp::Memory&>(buffer),
                    subBuffer.getAssociatedMemObject());
    }
#endif
}

static void ImageClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        size_t imgWidth, imgHeight, imgDepth;
        
        clpp::Image2D image2D(context, CL_MEM_WRITE_ONLY,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 640, 480);
        std::vector<char> imgData(2880*480*2);
        clpp::Image2D image2D2(context, CL_MEM_WRITE_ONLY|CL_MEM_USE_HOST_PTR,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT16), 700, 480, 2880*2, &imgData[0]);
        
        clpp::Image3D image3D(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 88, 90, 75);
        std::vector<cl_float4> imgData3D(36*48*65);
        clpp::Image3D image3D2(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
                clpp::ImageFormat(CL_RGBA, CL_FLOAT), 30, 45, 62, 36*16, 36*48*16, &imgData3D[0]);
        std::vector<cl_float4> imgData3D2(36*48*65);
        clpp::Image image1(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
            clpp::ImageFormat(CL_RGBA, CL_FLOAT), 31, 47, 64, 36*16, 36*48*16, &imgData3D2[0]);
        std::vector<char> imgData2D2(2880*480*2);
        clpp::Image image2(context, CL_MEM_WRITE_ONLY|CL_MEM_USE_HOST_PTR,
            clpp::ImageFormat(CL_RGBA, CL_UNORM_INT16), 710, 450, 0, 2880*2, 0, &imgData2D2[0]);
        
        assertEqual("Image2D for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE2D),
                    image2D.getType());
        assertEqual("Image2D for "+pName+" width", size_t(640U), image2D.getWidth());
        assertEqual("Image2D for "+pName+" height", size_t(480U), image2D.getHeight());
        assertEqual("Image2D for "+pName+" depth", size_t(0U), image2D.getDepth());
        assertEqual("Image2D for "+pName+" 2DSize", Size3(640, 480), image2D.get2DSizes());
        image2D.get2DSizes(imgWidth, imgHeight);
        assertEqual("Image2D for "+pName+" 2DSize2", Size3(640, 480), Size3(imgWidth, imgHeight));
        
        assertEqual("Image2D for "+pName+" rowpitch",
                    getImageInfo<size_t>(image2D, CL_IMAGE_ROW_PITCH), image2D.getRowPitch());
        assertEqual("Image2D for "+pName+" format", getImageInfo<cl_image_format>(
                    image2D, CL_IMAGE_FORMAT), image2D.getFormat());
        assertEqual("Image2D for "+pName+" elemSize", size_t(4U), image2D.getElementSize());
        
        assertEqual("Image2D2 for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE2D),
                    image2D2.getType());
        assertEqual("Image2D2 for "+pName+" width", size_t(700U), image2D2.getWidth());
        assertEqual("Image2D2 for "+pName+" height", size_t(480U), image2D2.getHeight());
        assertEqual("Image2D2 for "+pName+" depth", size_t(0U), image2D2.getDepth());
        assertEqual("Image2D2 for "+pName+" rowpitch",
                    getImageInfo<size_t>(image2D2, CL_IMAGE_ROW_PITCH), image2D2.getRowPitch());
        assertEqual("Image2D2 for "+pName+" format", getImageInfo<cl_image_format>(
                    image2D2, CL_IMAGE_FORMAT), image2D2.getFormat());
        assertEqual("Image2D2 for "+pName+" elemSize", size_t(8U), image2D2.getElementSize());
        assertEqual("Image2D2 for "+pName+" hostPtr", (void*)&imgData[0],
                    image2D2.getHostPointer());
        
        assertEqual("Image3D for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE3D),
                    image3D.getType());
        assertEqual("Image3D for "+pName+" width", size_t(88U), image3D.getWidth());
        assertEqual("Image3D for "+pName+" height", size_t(90U), image3D.getHeight());
        assertEqual("Image3D for "+pName+" depth", size_t(75U), image3D.getDepth());
        assertEqual("Image3D for "+pName+" 3DSize", Size3(88, 90, 75), image3D.get3DSizes());
        image3D.get3DSizes(imgWidth, imgHeight, imgDepth);
        assertEqual("Image3D for "+pName+" 3DSize2", Size3(88, 90, 75),
                    Size3(imgWidth, imgHeight, imgDepth));
        
        assertEqual("Image3D for "+pName+" rowpitch",
                    getImageInfo<size_t>(image3D, CL_IMAGE_ROW_PITCH), image3D.getRowPitch());
        assertEqual("Image3D for "+pName+" slicepitch",
                    getImageInfo<size_t>(image3D, CL_IMAGE_SLICE_PITCH), image3D.getSlicePitch());
        assertEqual("Image3D for "+pName+" format", getImageInfo<cl_image_format>(
                    image3D, CL_IMAGE_FORMAT), image3D.getFormat());
        assertEqual("Image3D for "+pName+" elemSize", size_t(4U), image3D.getElementSize());
        
        assertEqual("Image3D2 for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE3D),
                    image3D2.getType());
        assertEqual("Image3D2 for "+pName+" width", size_t(30U), image3D2.getWidth());
        assertEqual("Image3D2 for "+pName+" height", size_t(45U), image3D2.getHeight());
        assertEqual("Image3D2 for "+pName+" depth", size_t(62U), image3D2.getDepth());
        assertEqual("Image3D2 for "+pName+" rowpitch", getImageInfo<size_t>(
                    image3D2, CL_IMAGE_ROW_PITCH), image3D2.getRowPitch());
        assertEqual("Image3D2 for "+pName+" slicepitch",getImageInfo<size_t>(
                    image3D2, CL_IMAGE_SLICE_PITCH), image3D2.getSlicePitch());
        assertEqual("Image3D2 for "+pName+" format", getImageInfo<cl_image_format>(
                    image3D2, CL_IMAGE_FORMAT), image3D2.getFormat());
        assertEqual("Image3D2 for "+pName+" elemSize", size_t(16U), image3D2.getElementSize());
        assertEqual("Image3D2 for "+pName+" hostPtr", (void*)&imgData3D[0],
                    image3D2.getHostPointer());
        
        assertEqual("Image1 for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE3D),
                    image1.getType());
        assertEqual("Image1 for "+pName+" width", size_t(31U), image1.getWidth());
        assertEqual("Image1 for "+pName+" height", size_t(47U), image1.getHeight());
        assertEqual("Image1 for "+pName+" depth", size_t(64U), image1.getDepth());
        assertEqual("Image1 for "+pName+" rowpitch", getImageInfo<size_t>(
                    image1, CL_IMAGE_ROW_PITCH), image1.getRowPitch());
        assertEqual("Image1 for "+pName+" slicepitch",getImageInfo<size_t>(
                    image1, CL_IMAGE_SLICE_PITCH), image1.getSlicePitch());
        assertEqual("Image1 for "+pName+" format", getImageInfo<cl_image_format>(
                    image1, CL_IMAGE_FORMAT), image1.getFormat());
        assertEqual("Image1 for "+pName+" elemSize", size_t(16U), image1.getElementSize());
        assertEqual("Image1 for "+pName+" hostPtr", (void*)&imgData3D2[0],
                    image1.getHostPointer());
        
        assertEqual("Image2 for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE2D),
                    image2.getType());
        assertEqual("Image2 for "+pName+" width", size_t(710U), image2.getWidth());
        assertEqual("Image2 for "+pName+" height", size_t(450U), image2.getHeight());
        assertEqual("Image2 for "+pName+" depth", size_t(0U), image2.getDepth());
        assertEqual("Image2 for "+pName+" rowpitch",
                    getImageInfo<size_t>(image2, CL_IMAGE_ROW_PITCH), image2.getRowPitch());
        assertEqual("Image2 for "+pName+" format", getImageInfo<cl_image_format>(
                    image2, CL_IMAGE_FORMAT), image2.getFormat());
        assertEqual("Image2 for "+pName+" elemSize", size_t(8U), image2.getElementSize());
        assertEqual("Image2 for "+pName+" hostPtr", (void*)&imgData2D2[0],
                    image2.getHostPointer());
        
#if __CLPP_CL_ABI_VERSION>=102
        clpp::Image1D image1D(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_FLOAT), 14325U);
        std::vector<cl_uint4> imgData1D2(5234U);
        clpp::Image1D image1D2(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT16), 5234U, &imgData1D2[0]);
        std::vector<cl_float4> imgData1DA(150*340);
        clpp::Image1DArray image1DA(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
                    clpp::ImageFormat(CL_RGBA, CL_FLOAT), 143U, 321U, 16*148, &imgData1DA[0]);
        
        clpp::Buffer buffer(context, CL_MEM_READ_WRITE, 44300U*4);
        clpp::Image1DBuffer image1DB(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 44300U, buffer);
        std::vector<cl_float4> imgData2DA(96*72*19);
        clpp::Image2DArray image2DA(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
                    clpp::ImageFormat(CL_RGBA, CL_FLOAT), 87U, 67U, 19U, 16*96U,
                    96U*72U*16U, &imgData2DA[0]);
        clpp::Image image11(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_FLOAT), 10200U);
        clpp::Image image12(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
                clpp::ImageFormat(CL_RGBA, CL_FLOAT),
                clpp::ImageDesc(CL_MEM_OBJECT_IMAGE2D_ARRAY, 87U, 67U, 0, 19U, 16*96U,
                        96U*72U*16U), &imgData2DA[0]);
        
        assertEqual("Image1D for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE1D),
                    image1D.getType());
        assertEqual("Image1D for "+pName+" width", size_t(14325U), image1D.getWidth());
        assertEqual("Image1D for "+pName+" height", size_t(0U), image1D.getHeight());
        assertEqual("Image1D for "+pName+" depth", size_t(0U), image1D.getDepth());
        assertEqual("Image1D for "+pName+" rowpitch",
                    getImageInfo<size_t>(image1D, CL_IMAGE_ROW_PITCH), image1D.getRowPitch());
        assertEqual("Image1D for "+pName+" format", getImageInfo<cl_image_format>(
                    image1D, CL_IMAGE_FORMAT), image1D.getFormat());
        assertEqual("Image1D for "+pName+" elemSize", size_t(16U), image1D.getElementSize());
        
        assertEqual("Image1DB Buffer for "+pName+" refCount", 2U, buffer.refCount());
        {
#if __CLPP_CL_VERSION>=200
            clpp::Memory tmpBuf = image1DB.getAssociatedMemObject();
#else
            clpp::Buffer tmpBuf = image1DB.getBuffer();
#endif
            assertEqual("Image1DB Buffer for "+pName+" refCount2", 3U, buffer.refCount());
        }
        assertEqual("Image1DB for "+pName+" type",
                    cl_mem_object_type(CL_MEM_OBJECT_IMAGE1D_BUFFER), image1DB.getType());
        assertEqual("Image1DB for "+pName+" width", size_t(44300U), image1DB.getWidth());
        assertEqual("Image1DB for "+pName+" height", size_t(0U), image1DB.getHeight());
        assertEqual("Image1DB for "+pName+" depth", size_t(0U), image1DB.getDepth());
        assertEqual("Image1DB for "+pName+" rowpitch",
                    getImageInfo<size_t>(image1DB, CL_IMAGE_ROW_PITCH), image1DB.getRowPitch());
        assertEqual("Image1DB for "+pName+" format", getImageInfo<cl_image_format>(
                    image1DB, CL_IMAGE_FORMAT), image1DB.getFormat());
        assertEqual("Image1DB for "+pName+" elemSize", size_t(4U), image1DB.getElementSize());
        assertEqual("Image1DB for "+pName+" memObject", 
#if __CLPP_CL_VERSION>=200
                    static_cast<const clpp::Memory&>(buffer), image1DB.getAssociatedMemObject()
#else
                    buffer, image1DB.getBuffer()
#endif
                   );
        assertEqual("Image1D2 for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE1D),
                    image1D2.getType());
        assertEqual("Image1D2 for "+pName+" width", size_t(5234U), image1D2.getWidth());
        assertEqual("Image1D2 for "+pName+" height", size_t(0U), image1D2.getHeight());
        assertEqual("Image1D2 for "+pName+" depth", size_t(0U), image1D2.getDepth());
        assertEqual("Image1D2 for "+pName+" rowpitch",
                    getImageInfo<size_t>(image1D2, CL_IMAGE_ROW_PITCH), image1D2.getRowPitch());
        assertEqual("Image1D2 for "+pName+" format", getImageInfo<cl_image_format>(
                    image1D2, CL_IMAGE_FORMAT), image1D2.getFormat());
        assertEqual("Image1D2 for "+pName+" elemSize", size_t(8U), image1D2.getElementSize());
        assertEqual("Image1D2 for "+pName+" hostPtr", (void*)&imgData1D2[0],
                    image1D2.getHostPointer());
        
        assertEqual("Image1DA for "+pName+" type",
                    cl_mem_object_type(CL_MEM_OBJECT_IMAGE1D_ARRAY), image1DA.getType());
        assertEqual("Image1DA for "+pName+" width", size_t(143U), image1DA.getWidth());
        assertEqual("Image1DA for "+pName+" height", size_t(0U), image1DA.getHeight());
        assertEqual("Image1DA for "+pName+" depth", size_t(0U), image1DA.getDepth());
        assertEqual("Image1DA for "+pName+" arraySize", size_t(321U), image1DA.getArraySize());
        assertEqual("Image1DA for "+pName+" rowpitch", getImageInfo<size_t>(
                    image1DA, CL_IMAGE_ROW_PITCH), image1DA.getRowPitch());
        assertEqual("Image1DA for "+pName+" slicepitch",getImageInfo<size_t>(
                    image1DA, CL_IMAGE_SLICE_PITCH), image1DA.getSlicePitch());
        assertEqual("Image1DA for "+pName+" format", getImageInfo<cl_image_format>(
                    image1DA, CL_IMAGE_FORMAT), image1DA.getFormat());
        assertEqual("Image1DA for "+pName+" elemSize", size_t(16U), image1DA.getElementSize());
        assertEqual("Image1DA for "+pName+" hostPtr", (void*)&imgData1DA[0],
                    image1DA.getHostPointer());
        
        assertEqual("Image2DA for "+pName+" type",
                    cl_mem_object_type(CL_MEM_OBJECT_IMAGE2D_ARRAY), image2DA.getType());
        assertEqual("Image2DA for "+pName+" width", size_t(87U), image2DA.getWidth());
        assertEqual("Image2DA for "+pName+" height", size_t(67U), image2DA.getHeight());
        assertEqual("Image2DA for "+pName+" depth", size_t(0U), image2DA.getDepth());
        assertEqual("Image2DA for "+pName+" arraySize", size_t(19U), image2DA.getArraySize());
        assertEqual("Image2DA for "+pName+" rowpitch", getImageInfo<size_t>(
                    image2DA, CL_IMAGE_ROW_PITCH), image2DA.getRowPitch());
        assertEqual("Image2DA for "+pName+" slicepitch",getImageInfo<size_t>(
                    image2DA, CL_IMAGE_SLICE_PITCH), image2DA.getSlicePitch());
        assertEqual("Image2DA for "+pName+" format", getImageInfo<cl_image_format>(
                    image2DA, CL_IMAGE_FORMAT), image2DA.getFormat());
        assertEqual("Image2DA for "+pName+" elemSize", size_t(16U), image2DA.getElementSize());
        assertEqual("Image2DA for "+pName+" hostPtr", (void*)&imgData2DA[0],
                    image2DA.getHostPointer());
        
        assertEqual("Image11 for "+pName+" type", cl_mem_object_type(CL_MEM_OBJECT_IMAGE1D),
                    image11.getType());
        assertEqual("Image11 for "+pName+" width", size_t(10200U), image11.getWidth());
        assertEqual("Image11 for "+pName+" height", size_t(0U), image11.getHeight());
        assertEqual("Image11 for "+pName+" depth", size_t(0U), image11.getDepth());
        assertEqual("Image11 for "+pName+" rowpitch",
                    getImageInfo<size_t>(image11, CL_IMAGE_ROW_PITCH), image11.getRowPitch());
        assertEqual("Image11 for "+pName+" format", getImageInfo<cl_image_format>(
                    image11, CL_IMAGE_FORMAT), image11.getFormat());
        assertEqual("Image11 for "+pName+" elemSize", size_t(16U), image11.getElementSize());
        
        assertEqual("Image12 for "+pName+" type",
                    cl_mem_object_type(CL_MEM_OBJECT_IMAGE2D_ARRAY), image12.getType());
        assertEqual("Image12 for "+pName+" width", size_t(87U), image12.getWidth());
        assertEqual("Image12 for "+pName+" height", size_t(67U), image12.getHeight());
        assertEqual("Image12 for "+pName+" depth", size_t(0U), image12.getDepth());
        assertEqual("Image12 for "+pName+" arraySize", size_t(19U), image12.getArraySize());
        assertEqual("Image12 for "+pName+" rowpitch", getImageInfo<size_t>(
                    image12, CL_IMAGE_ROW_PITCH), image12.getRowPitch());
        assertEqual("Image12 for "+pName+" slicepitch",getImageInfo<size_t>(
                    image12, CL_IMAGE_SLICE_PITCH), image12.getSlicePitch());
        assertEqual("Image12 for "+pName+" format", getImageInfo<cl_image_format>(
                    image12, CL_IMAGE_FORMAT), image12.getFormat());
        assertEqual("Image12 for "+pName+" elemSize", size_t(16U), image12.getElementSize());
        assertEqual("Image12 for "+pName+" hostPtr", (void*)&imgData2DA[0],
                    image12.getHostPointer());
#endif
    }
    
    // get info testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::Image2D  image2D(context, CL_MEM_WRITE_ONLY,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 840, 770);
        
        clpp::impl::retainInternal(image2D);
        clpp::impl::releaseInternal(image2D);
        
        assertEqual("Image2D for "+pName+" getImageInfo(width)", 
                getImageInfo<size_t>(image2D, CL_IMAGE_WIDTH),
                image2D.getImageInfo<size_t>(CL_IMAGE_WIDTH));
        size_t imgWidth;
        image2D.getImageInfo(CL_IMAGE_WIDTH, imgWidth);
        assertEqual("Image2D for "+pName+" getImageInfo(width,out)", 
                getImageInfo<size_t>(image2D, CL_IMAGE_WIDTH), imgWidth);
        std::vector<size_t> imgSizes = image2D.getImageInfoVector<size_t>(CL_IMAGE_HEIGHT);
        std::vector<size_t> expImgSizes;
        expImgSizes.push_back(getImageInfo<size_t>(image2D, CL_IMAGE_HEIGHT));
        assertEqual("Image2D for "+pName+" getImageInfoVector(height)",
                    expImgSizes, imgSizes);
        
        clpp::Context context0;
        image2D.getInfo(CL_MEM_CONTEXT, context0);
        assertEqual("Image2D for "+pName+" getInfo<Context>(out)", context, context0);
    }
}

#if __CLPP_CL_ABI_VERSION>=200
static void PipeClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Pipe pipe(context, CL_MEM_READ_WRITE, 100, 1000);
        assertEqual("Pipe for "+pName+" pipePacketSize", 100U, pipe.getPacketSize());
        assertEqual("Pipe for "+pName+" pipeMaxPackets", 1000U, pipe.getMaxPackets());
        cl_uint packetSize;
        pipe.getPipeInfo(CL_PIPE_PACKET_SIZE, packetSize);
        assertEqual("Pipe for "+pName+" getInfo(packetSize,out)", 100U, packetSize);
        std::vector<cl_uint> packetSizeV = pipe.getPipeInfoVector<cl_uint>(CL_PIPE_PACKET_SIZE);
        assertEqual("Pipe for "+pName+" getInfoVector(packetSize)", 100U, packetSizeV[0]);
    }
}
#endif

static void SamplerClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Sampler sampler(context, true, CL_ADDRESS_REPEAT, CL_FILTER_NEAREST);
        clpp::Sampler sampler2(context, true, CL_ADDRESS_REPEAT, CL_FILTER_LINEAR);
        clpp::Sampler sampler3(context, false, CL_ADDRESS_CLAMP, CL_FILTER_LINEAR);
        
        assertEqual("Sampler1 for "+pName+" NORM_COORDS", true, sampler.isNormalizedCoords());
        assertEqual("Sampler1 for "+pName+" ADDR_MODE",
                    cl_addressing_mode(CL_ADDRESS_REPEAT), sampler.getAddressingMode());
        assertEqual("Sampler1 for "+pName+" FILTER_MODE",
                    cl_filter_mode(CL_FILTER_NEAREST), sampler.getFilterMode());
        assertEqual("Sampler2 for "+pName+" NORM_COORDS", true, sampler2.isNormalizedCoords());
        assertEqual("Sampler2 for "+pName+" ADDR_MODE",
                    cl_addressing_mode(CL_ADDRESS_REPEAT), sampler2.getAddressingMode());
        assertEqual("Sampler2 for "+pName+" FILTER_MODE",
                    cl_filter_mode(CL_FILTER_LINEAR), sampler2.getFilterMode());
        assertEqual("Sampler3 for "+pName+" NORM_COORDS", false, sampler3.isNormalizedCoords());
        assertEqual("Sampler3 for "+pName+" ADDR_MODE",
                    cl_addressing_mode(CL_ADDRESS_CLAMP), sampler3.getAddressingMode());
        assertEqual("Sampler3 for "+pName+" FILTER_MODE",
                    cl_filter_mode(CL_FILTER_LINEAR), sampler3.getFilterMode());
        
        assertEqual("Sampler1 for "+pName+" context", context, sampler.getContext());
        assertEqual("Sampler2 for "+pName+" context", context, sampler2.getContext());
        assertEqual("Sampler3 for "+pName+" context", context, sampler3.getContext());
#if __CLPP_CL_ABI_VERSION>=200
        const cl_sampler_properties props1[7] = {
            CL_SAMPLER_NORMALIZED_COORDS, cl_uint(true),
            CL_SAMPLER_ADDRESSING_MODE, CL_ADDRESS_REPEAT,
            CL_SAMPLER_FILTER_MODE, CL_FILTER_NEAREST, 0
        };
        clpp::Sampler samplerP(context, props1);
        assertEqual("SamplerP for "+pName+" NORM_COORDS", true, samplerP.isNormalizedCoords());
        assertEqual("SamplerP for "+pName+" ADDR_MODE",
                    cl_addressing_mode(CL_ADDRESS_REPEAT), samplerP.getAddressingMode());
        assertEqual("SamplerP for "+pName+" FILTER_MODE",
                    cl_filter_mode(CL_FILTER_NEAREST), samplerP.getFilterMode());
#endif
        
        assertEqual("Sampler1 for "+pName+" getInfo(AddrMode)",
                    cl_addressing_mode(CL_ADDRESS_REPEAT),
                    sampler.getInfo<cl_addressing_mode>(CL_SAMPLER_ADDRESSING_MODE));
        cl_addressing_mode addrMode;
        sampler.getInfo<cl_addressing_mode>(CL_SAMPLER_ADDRESSING_MODE, addrMode);
        assertEqual("Sampler1 for "+pName+" getInfo(AddrMode,out)",
                    cl_addressing_mode(CL_ADDRESS_REPEAT), addrMode);
        std::vector<cl_addressing_mode> addrModeV =
                sampler.getInfoVector<cl_addressing_mode>(CL_SAMPLER_ADDRESSING_MODE);
        std::vector<cl_addressing_mode> expAddrModeV;
        expAddrModeV.push_back(CL_ADDRESS_REPEAT);
        assertEqual("Sampler1 for "+pName+" getInfoVector(AddrMode)", expAddrModeV, addrModeV);
        addrMode = 5555111;
        
        clpp::Context context0;
        sampler.getInfo(CL_SAMPLER_CONTEXT, context0);
        assertEqual("Sampler for "+pName+" getInfo<Context>(out)", context, context0);
    }
    // reference testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Sampler sampler(context, true, CL_ADDRESS_REPEAT, CL_FILTER_NEAREST);
        clpp::Sampler sampler2(context, true, CL_ADDRESS_CLAMP_TO_EDGE, CL_FILTER_NEAREST);
        
        assertEqual("Sampler for " +pName+ ".refcount1", 1U, sampler.refCount());
        assertEqual("Sampler for " +pName+ ".refcount2", 1U, sampler2.refCount());
        {
            clpp::Sampler samplerCopy = sampler;
            assertEqual("Sampler for " +pName+ ".refcount3", 2U, sampler.refCount());
            assertEqual("Sampler for " +pName+ ".refcount4", 1U, sampler2.refCount());
        }
        assertEqual("Sampler for " +pName+ ".refcount5", 1U, sampler.refCount());
        clpp::Sampler sampler3;
        sampler3 = sampler2;
        assertEqual("Sampler for " +pName+ ".refcount6", 2U, sampler2.refCount());
        sampler3 = sampler;
        assertEqual("Sampler for " +pName+ ".refcount7", 1U, sampler2.refCount());
        assertEqual("Sampler for " +pName+ ".refcount8", 2U, sampler.refCount());
#   ifdef __CLPP_CPP0X
        sampler = std::move(sampler3);
        assertEqual("Sampler for " +pName+ ".refcount9", 1U, sampler.refCount());
#   endif
    }
}

static const char* simpleProgramStr =
"kernel void simpleKernel(uint n, const global uint* a, global uint* b)\n"
"{ size_t gid = get_global_id(0);\n"
"  if (gid >= n) return;\n"
"  b[gid] = a[gid]*123445U+n; }\n";

static const char* simpleProgramStr2 =
"kernel void simpleKernel2(uint n, const global uint* a, const global uint* b, global uint* c)\n"
"{ size_t gid = get_global_id(0);\n"
"  if (gid >= n) return;\n"
"  c[gid] = a[gid]*b[gid]+n; }\n";

static const char* simpleProgramStr3 =
"kernel void simpleKernel3(float x, const global float* a,"
" const global float* b, global float* c)\n"
"{ size_t gid = get_global_id(0); c[gid] = a[gid]*b[gid]+x; }\n";

static const char* moduloProgramStr =
"kernel void modulator(uint n, const global uint* a, global uint* b)\n"
"{ size_t gid = get_global_id(0); b[gid] %= a[gid]*n; int ai; int bi; int ci; }\n";

static const char* passer24Str =
"kernel void passer(uint n1, uint n2, uint n3, uint n4, uint n5,\n"
"                uint n6, uint n7, uint n8, uint n9, uint n10,\n"
"                uint n11, uint n12, uint n13, uint n14, uint n15,\n"
"                uint n16, uint n17, uint n18, uint n19, uint n20,\n"
"                uint n21, uint n22, uint n23, uint n24)\n"
"{ }\n";

static const char* localArgStr =
"kernel void localArg(uint n, local uint* x)\n"
"{ }\n";

static cl_program programFromCallback = NULL;
static const char* textFromCallback = "";
static bool programCallbackFinished = false;
#ifdef _WINDOWS
static HANDLE programCallbackEvent = NULL;
#else
static pthread_mutex_t programCallbackMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t programCallbackCond = PTHREAD_COND_INITIALIZER;
#endif

static void programCallbackInit()
{
    programFromCallback = NULL;
    textFromCallback = "";
    programCallbackFinished = false;
}

static void programCallback(cl_program program, void* data)
{
#ifndef _WINDOWS
    if (pthread_mutex_lock(&programCallbackMutex) != 0)
    { std::cerr << "pthread_mutex_lock" << std::endl; abort(); }
#endif
    programFromCallback = program;
    textFromCallback = (const char*)data;
    programCallbackFinished = true;
#ifndef _WINDOWS
    if (pthread_cond_signal(&programCallbackCond) != 0)
    { std::cerr << "pthread_cond_signal" << std::endl; abort(); }
    if (pthread_mutex_unlock(&programCallbackMutex) != 0)
    { std::cerr << "pthread_mutex_unlock" << std::endl; abort(); }
#else
    if (!SetEvent(programCallbackEvent))
    { std::cerr << "SetEvent" << std::endl; abort(); }
#endif
}

static void programCallbackWait()
{
#ifndef _WINDOWS
    if (pthread_mutex_lock(&programCallbackMutex) != 0)
    { std::cerr << "pthread_mutex_lock" << std::endl; abort(); }
    while (!programCallbackFinished)
    {
        if (pthread_cond_wait(&programCallbackCond, &programCallbackMutex) != 0)
        { std::cerr << "pthread_cond_wait" << std::endl; abort(); }
    }
    if (pthread_mutex_unlock(&programCallbackMutex) != 0)
    { std::cerr << "pthread_mutex_unlock" << std::endl; abort(); }
#else
    if (WaitForSingleObject(programCallbackEvent, INFINITE) == WAIT_FAILED)
    { std::cerr << "WaitForSingleObject" << std::endl; abort(); }
#endif
}

static void ProgramClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Program::Source source(simpleProgramStr, ::strlen(simpleProgramStr));
        clpp::Program program1(context, simpleProgramStr);
        clpp::Program program2(context, source);
        assertEqual("Program for "+pName+" context", context, program1.getContext());
        assertEqual("Program for "+pName+" source", std::string(simpleProgramStr),
                    getProgramInfoString(program1, CL_PROGRAM_SOURCE));
        assertEqual("Program2 for "+pName+" context", context, program2.getContext());
        assertEqual("Program2 for "+pName+" source", std::string(simpleProgramStr),
                    getProgramInfoString(program2, CL_PROGRAM_SOURCE));
        
        const char* progSourcesStrs[3] = {
            simpleProgramStr, simpleProgramStr2, simpleProgramStr3 };
        clpp::Program program3(context, std::vector<const char*>(
                    progSourcesStrs, progSourcesStrs+3));
        assertEqual("Program3 for "+pName+" source", std::string(simpleProgramStr) +
                    std::string(simpleProgramStr2) + std::string(simpleProgramStr3),
                    getProgramInfoString(program3, CL_PROGRAM_SOURCE));
        
        clpp::Program program4(context, std::string(simpleProgramStr2));
        assertEqual("Program4 for "+pName+" source", std::string(simpleProgramStr2),
                    getProgramInfoString(program4, CL_PROGRAM_SOURCE));
        
        clpp::Program::Source progSourceArray[3] = {
            clpp::Program::Source(simpleProgramStr, 0),
            clpp::Program::Source(simpleProgramStr2, 0),
            clpp::Program::Source(simpleProgramStr3, 0)
        };
        
        clpp::Program::Sources progSourcesVector(progSourceArray, progSourceArray+3);
        clpp::Program program5(context, progSourcesVector);
        assertEqual("Program5 for "+pName+" source", std::string(simpleProgramStr) +
                    std::string(simpleProgramStr2) + std::string(simpleProgramStr3),
                    getProgramInfoString(program5, CL_PROGRAM_SOURCE));
        
        /* cutted sources progs */
        const size_t progSourcesCutSizes[3] = { ::strlen(simpleProgramStr)-8,
                ::strlen(simpleProgramStr2)-14, ::strlen(simpleProgramStr3)-9 };
        clpp::Program programCutted1(context, simpleProgramStr, progSourcesCutSizes[0]);
        assertEqual("ProgramCut1 for "+pName+" source",
                    std::string(simpleProgramStr, simpleProgramStr + progSourcesCutSizes[0]),
                    getProgramInfoString(programCutted1, CL_PROGRAM_SOURCE));
        
        const clpp::Program::Source progCutSource(simpleProgramStr3,
                ::strlen(simpleProgramStr3)-21);
        clpp::Program programCutted2(context, progCutSource);
        assertEqual("ProgramCut2 for "+pName+" source",
                    std::string(simpleProgramStr3, simpleProgramStr3 + progCutSource.second),
                    getProgramInfoString(programCutted2, CL_PROGRAM_SOURCE));
        
        const clpp::Program::Source progCutSourceArray[3] = {
            clpp::Program::Source(simpleProgramStr3, ::strlen(simpleProgramStr3)-17),
            clpp::Program::Source(simpleProgramStr, ::strlen(simpleProgramStr)-5),
            clpp::Program::Source(simpleProgramStr2, ::strlen(simpleProgramStr2)-23)
        };
        clpp::Program programCutted4(context, std::vector<clpp::Program::Source>(
                    progCutSourceArray, progCutSourceArray+3));
        std::string expProgSourceStr =
            std::string(simpleProgramStr3, simpleProgramStr3 + progCutSourceArray[0].second) +
            std::string(simpleProgramStr, simpleProgramStr + progCutSourceArray[1].second) +
            std::string(simpleProgramStr2, simpleProgramStr2 + progCutSourceArray[2].second);
        assertEqual("ProgramCut4 for "+pName+" source", expProgSourceStr,
                    getProgramInfoString(programCutted4, CL_PROGRAM_SOURCE));
        
        clpp::Program::Sources progCutSourceVector(progCutSourceArray, progCutSourceArray+3);
        clpp::Program programCutted5(context, progCutSourceVector);
        assertEqual("ProgramCut5 for "+pName+" source", expProgSourceStr,
                    getProgramInfoString(programCutted5, CL_PROGRAM_SOURCE));
        
        // prepare binary program
        if (clBuildProgram(program3, devices.size(), reinterpret_cast<const cl_device_id*>(
                    &devices[0]), NULL, NULL, NULL) != CL_SUCCESS)
            throw TestException("Failed clBuildProgram");
        
        const std::vector<clpp::Device> progDevices = getProgramInfoVector<clpp::Device>(
                    program3, CL_PROGRAM_DEVICES);
        
        // get binaries
        const std::vector<size_t> progBinarySizes = getProgramInfoVector<size_t>(program3,
                    CL_PROGRAM_BINARY_SIZES);
        
        std::vector<std::vector<unsigned char> > progBinaries(progDevices.size());
        std::vector<unsigned char*> progBinPointers(progDevices.size());
        for (cl_uint k = 0; k < progDevices.size(); k++)
        {
            progBinaries[k].resize(progBinarySizes[k]);
            progBinPointers[k] = &progBinaries[k][0];
        }
        if (clGetProgramInfo(program3, CL_PROGRAM_BINARIES, 
                    sizeof(unsigned char*)*progDevices.size(),
                             &progBinPointers[0], NULL) != CL_SUCCESS)
            throw TestException("Failed clGetProgramInfo");
        program3.clear();
        // check binary constructors
        cl_int binStatus1 = 111;
        clpp::Program binProg1(context, progDevices[0], progBinarySizes[0],
                    &progBinaries[0][0], &binStatus1);
        
        clpp::Program::Binaries binaries;
        for (cl_uint k = 0; k < progDevices.size(); k++)
            binaries.push_back(clpp::Program::Binary(&progBinaries[k][0], progBinarySizes[k]));
        std::vector<cl_int> binStatus4(progDevices.size(), 6367);
        clpp::Program binProg4(context, progDevices, binaries, &binStatus4);
        
        /* check progBins */
        std::vector<std::vector<unsigned char> > singleProgBin;
        singleProgBin.push_back(progBinaries[0]);
        assertEqual("BinProg1 for "+pName+" binaries", singleProgBin, binProg1.getBinaries());
        assertEqual("BinProg4 for "+pName+" binaries", progBinaries, binProg4.getBinaries());
        // check statuses
        assertEqual("BinProg1 for "+pName+" status", CL_SUCCESS, binStatus1);
        std::vector<cl_int> expStatuses(progDevices.size(), CL_SUCCESS);
        assertEqual("BinProg4 for "+pName+" status", expStatuses, binStatus4);
    }
    
    // get info testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Program program1(context, moduloProgramStr);
        program1.build("-DXXXX=1 -cl-mad-enable"); // built
        
        // context
        assertEqual("ModProg for "+pName+" context", context, program1.getContext());
        assertEqual("ModProg for "+pName+" getInfo(context)", context,
            program1.getInfo<clpp::Context>(CL_PROGRAM_CONTEXT));
        clpp::Context resContext;
        program1.getInfo(CL_PROGRAM_CONTEXT, resContext);
        assertEqual("ModProg for "+pName+" getInfo(context,out)", context, resContext);
        
        assertEqual("ModProg for "+pName+" getDevices()", devices, program1.getDevices());
        assertEqual("ModProg for "+pName+" getInfoVector(devices)", devices,
                    program1.getInfoVector<clpp::Device>(CL_PROGRAM_DEVICES));
        /* string tests */
        std::string expSource(moduloProgramStr);
        assertEqual("ModProg for "+pName+" sources", expSource, program1.getSource());
        assertEqual("ModProg for "+pName+" getInfo<string>(SOURCE)", expSource,
                    program1.getInfo<std::string>(CL_PROGRAM_SOURCE));
        assertEqual("ModProg for "+pName+" getInfo(SOURCE)", expSource,
                    program1.getInfoString(CL_PROGRAM_SOURCE));
        /* get binaries */
        std::vector<size_t> binSizes = getProgramInfoVector<size_t>(program1,
                    CL_PROGRAM_BINARY_SIZES);
        std::vector<std::vector<unsigned char> > expBinaries(devices.size());
        std::vector<unsigned char*> expBinariesPtrs(devices.size());
        for (size_t i = 0; i < devices.size(); i++)
        {
            expBinaries[i].resize(binSizes[i]);
            expBinariesPtrs[i] = &expBinaries[i][0];
        }
        if (clGetProgramInfo(program1, CL_PROGRAM_BINARIES, sizeof(char*)*devices.size(),
                    &expBinariesPtrs[0], NULL) != CL_SUCCESS)
            throw TestException("Failed clGetProgramInfo");
        assertEqual("ModProg for "+pName+" getBinaires", expBinaries,
                    program1.getBinaries());
        // insecure get binaries
        std::vector<unsigned char*> binaries2;
        try
        {
            program1.getBinaries(binaries2);
            std::vector<std::vector<unsigned char> > binResults(devices.size());
            for (size_t i = 0; i < binaries2.size(); i++)
                binResults[i].assign(binaries2[i], binaries2[i] + binSizes[i]);
            assertEqual("ModProg for "+pName+" getBinaries2", expBinaries, binResults);
        }
        catch(...)
        {
            for (size_t i = 0; i < binaries2.size(); i++)
                delete[] binaries2[i];
            throw;
        }
        for (size_t i = 0; i < binaries2.size(); i++)
            delete[] binaries2[i];
        // binaries from ptrs
        std::vector<unsigned char*> binaries3(devices.size(), (unsigned char*)NULL);
        try
        {
            for (size_t i = 0; i < binaries3.size(); i++)
                binaries3[i] = new unsigned char[binSizes[i]];
            program1.getBinariesToPtrs(binaries3);
            std::vector<std::vector<unsigned char> > binResults(devices.size());
            for (size_t i = 0; i < binaries2.size(); i++)
                binResults[i].assign(binaries3[i], binaries3[i] + binSizes[i]);
            assertEqual("ModProg for "+pName+" getBinariesToPtrs", expBinaries, binResults);
        }
        catch(...)
        {
            for (size_t i = 0; i < binaries3.size(); i++)
                delete[] binaries3[i];
            throw;
        }
        for (size_t i = 0; i < binaries3.size(); i++)
            delete[] binaries3[i];
        
        /* build infos */
        for (size_t j = 0; j < devices.size(); j++)
        {
            const clpp::Device& device = devices[j];
            std::string dName = device.getName();
            std::string buildLogStr = getProgramBuildInfoString(program1, device,
                    CL_PROGRAM_BUILD_LOG);
            std::string buildOptionsStr = getProgramBuildInfoString(program1, device,
                    CL_PROGRAM_BUILD_OPTIONS);
            assertEqual("ModProg for "+pName+" "+dName+" buildLog", buildLogStr,
                    program1.getBuildLog(device));
            assertEqual("ModProg for "+pName+" "+dName+" getBuildInfo(LOG)", buildLogStr,
                    program1.getBuildInfoString(device, CL_PROGRAM_BUILD_LOG));
            assertEqual("ModProg for "+pName+" "+dName+" buildOptions", buildOptionsStr,
                        program1.getBuildOptions(device));
            assertEqual("ModProg for "+pName+" "+dName+" getBuildInfo(OPTIONS)",
                    buildOptionsStr, program1.getBuildInfoString(
                        device, CL_PROGRAM_BUILD_OPTIONS));
        }
    }
    
    // building/compiling programs
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::Program program1(context, moduloProgramStr);
        clpp::Program program2(context, moduloProgramStr);
        clpp::Program program3(context, moduloProgramStr);
        clpp::Program programN1(context, moduloProgramStr); // notify
        clpp::Program programN2(context, moduloProgramStr); // notify
        clpp::Program programN3(context, moduloProgramStr); // notify
        
        program1.build(devices[0], "-DBUBU");
        program2.build(devices, "-DYGREK");
        program3.build(devices, "-DYGREK2");
        
        std::vector<clpp::Device> device1;
        device1.push_back(devices[0]);
        
        assertEqual("Built for "+pName+" compile devices1", device1, program1.getDevices());
        assertEqual("Built for "+pName+" compile devices2", devices, program2.getDevices());
        assertEqual("Built for "+pName+" compile devices3", devices, program3.getDevices());
        
        programCallbackInit();
        programN1.build("-DXXX", programCallback, (void*)"some text");
        programCallbackWait();
        assertEqual("BuiltWithNotify for "+pName+" program from notify",
                    programN1(), programFromCallback);
        assertCStrEqual("BuiltWithNotify for "+pName+" userData from notify",
                    "some text", textFromCallback);
        
        programCallbackInit();
        programN2.build(devices, "-DXXX", programCallback, (void*)"some text2");
        programCallbackWait();
        assertEqual("BuiltWithNotify2 for "+pName+" program from notify",
                    programN2(), programFromCallback);
        assertCStrEqual("BuiltWithNotify2 for "+pName+" userData from notify",
                    "some text2", textFromCallback);
        
        programCallbackInit();
        programN3.build(devices[0], "-DXXX", programCallback, (void*)"some text3");
        programCallbackWait();
        assertEqual("BuiltWithNotify3 for "+pName+" program from notify",
                    programN3(), programFromCallback);
        assertCStrEqual("BuiltWithNotify3 for "+pName+" userData from notify",
                    "some text3", textFromCallback);
        
#if __CLPP_CL_ABI_VERSION>=102
        clpp::Program pobj1(context, simpleProgramStr);
        clpp::Program pobj2(context, simpleProgramStr2);
        clpp::Program pobj3(context, simpleProgramStr3);
        pobj1.compile(devices, "-DX");
        pobj2.compile(devices, "-DY");
        programCallbackInit();
        pobj3.compile(devices, "-DZ", programCallback, (void*)"some text4");
        programCallbackWait();
        assertEqual("CompiledWithNotify1 for "+pName+" program from notify",
                    pobj3(), programFromCallback);
        assertCStrEqual("CompiledWithNotify1 for "+pName+" userData from notify",
                    "some text4", textFromCallback);
        
        std::vector<clpp::Program> toLink;
        toLink.push_back(pobj1);
        toLink.push_back(pobj2);
        toLink.push_back(pobj3);
        clpp::Program progl1 = clpp::Program::link(context, devices[0], toLink);
        clpp::Program progl2 = clpp::Program::link(context, devices, toLink);
        programCallbackInit();
        clpp::Program progl3 = clpp::Program::link(context, toLink, NULL, programCallback,
                    (void*)"linking...");
        programCallbackWait();
        assertEqual("LinkedWithNotify1 for "+pName+" program from notify",
                    progl3(), programFromCallback);
        assertCStrEqual("LinkedWithNotify1 for "+pName+" userData from notify",
                    "linking...", textFromCallback);
        
        assertEqual("Linked for "+pName+" link devices1", device1, progl1.getDevices());
        assertEqual("Linked for "+pName+" link devices2", devices, progl2.getDevices());
        assertEqual("Linked for "+pName+" link devices3", devices, progl3.getDevices());
#endif
    }
    // reference testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Program program(context, simpleProgramStr);
        clpp::Program program2(context, simpleProgramStr2);
        
        assertEqual("Program for " +pName+ ".refcount1", 1U, program.refCount());
        assertEqual("Program for " +pName+ ".refcount2", 1U, program2.refCount());
        {
            clpp::Program programCopy = program;
            assertEqual("Program for " +pName+ ".refcount3", 2U, program.refCount());
            assertEqual("Program for " +pName+ ".refcount4", 1U, program2.refCount());
        }
        assertEqual("Program for " +pName+ ".refcount5", 1U, program.refCount());
        clpp::Program program3;
        program3 = program2;
        assertEqual("Program for " +pName+ ".refcount6", 2U, program2.refCount());
        program3 = program;
        assertEqual("Program for " +pName+ ".refcount7", 1U, program2.refCount());
        assertEqual("Program for " +pName+ ".refcount8", 2U, program.refCount());
#   ifdef __CLPP_CPP0X
        program = std::move(program3);
        assertEqual("Program for " +pName+ ".refcount9", 1U, program.refCount());
#   endif
    }
    /* make tests createKernels() and kernelCopies() */
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        std::vector<const char*> sources;
        sources.push_back(simpleProgramStr);
        sources.push_back(simpleProgramStr2);
        sources.push_back(simpleProgramStr3);
        sources.push_back(moduloProgramStr);
        clpp::Program program(context, sources);
        program.build();
        std::vector<clpp::Kernel> kernels = program.createKernels();
        
        assertEqual("Create kernels for "+pName+" kernels num", size_t(4), kernels.size());
        static const std::string kernelNamesTbl[] = {
            "simpleKernel", "simpleKernel2", "simpleKernel3", "modulator"
        };
        for (size_t j = 0; j < kernels.size(); j++)
        {
            std::ostringstream oss;
            oss << "Create kernels for " << pName << " kernel " << j;
            bool found = false;
            for (size_t k = 0; k < kernels.size(); k++)
                if (kernels[k].getName() == kernelNamesTbl[j])
                { found = true; break; }
            assertBool(oss.str(), found);
        }
        
        /* kernel copies */
        std::vector<clpp::Kernel> modulatorCopies = program.kernelCopies("modulator", 10);
        for (size_t j = 0; j < modulatorCopies.size(); j++)
        {
            std::ostringstream oss;
            oss << "Kernel copy for " << pName << " kernel " << j;
            assertEqual(oss.str() + " name", std::string("modulator"),
                        modulatorCopies[j].getName());
        }
    }
}

template<typename T>
static void assertEqualKSetArg(const std::string& name, cl_uint argIndex, const T& expValue)
{
    assertEqual(name + " (size)", sizeof(T), kernelSetArgSize[argIndex]);
    assertEqual(name + " (size)", expValue, *reinterpret_cast<const T*>(
                &kernelSetArgValue[argIndex][0]));
}

template<typename T>
static void assertEqualKSetArgs(const std::string& name, cl_uint argsNum, const T* expValues)
{
    for (size_t i = 0; i < argsNum; i++)
    {
        std::ostringstream oss;
        oss << name << "(" << i << ")";
        assertEqualKSetArg(name, i, expValues[i]);
    }
}


static void KernelClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing and setting kernels
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        std::vector<const char*> sources;
        sources.push_back(simpleProgramStr);
        sources.push_back(simpleProgramStr2);
        sources.push_back(simpleProgramStr3);
        sources.push_back(moduloProgramStr);
        clpp::Program program(context, sources);
#if __CLPP_CL_ABI_VERSION>=102
        program.build("-cl-kernel-arg-info");
#else
        program.build();
#endif
        
        clpp::Kernel kernel1(program, "simpleKernel");
        clpp::Kernel kernel2(program, "simpleKernel2");
        clpp::Kernel kernel3(program, "simpleKernel3");
        clpp::Kernel kernel4(program, "modulator");
        
        /* info tests */
        assertEqual("Kernel1 for "+pName+" getInfo(FUNCNAME)",
                    getKernelInfoString(kernel1, CL_KERNEL_FUNCTION_NAME),
                    kernel1.getInfoString(CL_KERNEL_FUNCTION_NAME));
        assertEqual("Kernel2 for "+pName+" getInfo(FUNCNAME)",
                    getKernelInfoString(kernel2, CL_KERNEL_FUNCTION_NAME),
                    kernel2.getInfoString(CL_KERNEL_FUNCTION_NAME));
        assertEqual("Kernel3 for "+pName+" getInfo(FUNCNAME)",
                    getKernelInfoString(kernel3, CL_KERNEL_FUNCTION_NAME),
                    kernel3.getInfoString(CL_KERNEL_FUNCTION_NAME));
        assertEqual("Kernel4 for "+pName+" getInfo(FUNCNAME)",
                    getKernelInfoString(kernel4, CL_KERNEL_FUNCTION_NAME),
                    kernel4.getInfoString(CL_KERNEL_FUNCTION_NAME));
        
        assertEqual("Kernel1 for "+pName+" getInfo<string>(FUNCNAME)",
                    getKernelInfoString(kernel1, CL_KERNEL_FUNCTION_NAME),
                    kernel1.getInfo<std::string>(CL_KERNEL_FUNCTION_NAME));
        assertEqual("Kernel2 for "+pName+" getInfo<string>(FUNCNAME)",
                    getKernelInfoString(kernel2, CL_KERNEL_FUNCTION_NAME),
                    kernel2.getInfo<std::string>(CL_KERNEL_FUNCTION_NAME));
        assertEqual("Kernel3 for "+pName+" getInfo<string>(FUNCNAME)",
                    getKernelInfoString(kernel3, CL_KERNEL_FUNCTION_NAME),
                    kernel3.getInfo<std::string>(CL_KERNEL_FUNCTION_NAME));
        assertEqual("Kernel4 for "+pName+" getInfo<string>(FUNCNAME)",
                    getKernelInfoString(kernel4, CL_KERNEL_FUNCTION_NAME),
                    kernel4.getInfo<std::string>(CL_KERNEL_FUNCTION_NAME));
        
        assertEqual("Kernel1 for "+pName+" getName()",
                getKernelInfoString(kernel1, CL_KERNEL_FUNCTION_NAME), kernel1.getName());
        assertEqual("Kernel2 for "+pName+" getName()",
                getKernelInfoString(kernel2, CL_KERNEL_FUNCTION_NAME), kernel2.getName());
        assertEqual("Kernel3 for "+pName+" getName()",
                getKernelInfoString(kernel3, CL_KERNEL_FUNCTION_NAME), kernel3.getName());
        assertEqual("Kernel4 for "+pName+" getName()",
                getKernelInfoString(kernel4, CL_KERNEL_FUNCTION_NAME), kernel4.getName());
        
        assertEqual("Kernel1 for "+pName+" getNumArgs()",
                getKernelInfo<cl_uint>(kernel1, CL_KERNEL_NUM_ARGS), kernel1.getNumArgs());
        
        assertEqual("Kernel1 for "+pName+" getProgram()", program, kernel1.getProgram());
        
        /* getWorkGroupInfo */
        for (std::vector<clpp::Device>::const_iterator it = devices.begin();
                    it != devices.end(); ++it)
        {
            const clpp::Device& device = *it;
            const std::string dName = device.getName();
            const size_t wgSize = getKernelWorkGroupInfo<size_t>(kernel1, device,
                    CL_KERNEL_WORK_GROUP_SIZE);
            assertEqual("Kernel1 for "+pName+" "+dName+" getWGInfo(WGSIZE)", wgSize,
                    kernel1.getWorkGroupInfo<size_t>(device, CL_KERNEL_WORK_GROUP_SIZE));
            assertEqual("Kernel1 for "+pName+" "+dName+" getWorkGroupSize()", wgSize,
                    kernel1.getWorkGroupSize(device));
            
            const Size3 compWGSize = getKernelWorkGroupInfo<Size3>(kernel1, device,
                    CL_KERNEL_COMPILE_WORK_GROUP_SIZE);
            assertEqual("Kernel1 for "+pName+" "+dName+" getWGInfo(COMPWGSIZE)", compWGSize,
                kernel1.getWorkGroupInfo<Size3>(device, CL_KERNEL_COMPILE_WORK_GROUP_SIZE));
            assertEqual("Kernel1 for "+pName+" "+dName+" getCompileWorkGroupSize", compWGSize,
                    kernel1.getCompileWorkGroupSize(device));
            
#if __CLPP_CL_VERSION>=101
            const size_t prefWGSizeMult = getKernelWorkGroupInfo<size_t>(kernel1, device,
                    CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE);
            assertEqual("Kernel1 for "+pName+" "+dName+" getWGInfo(PREFWGSIZEMULT)",
                    prefWGSizeMult, kernel1.getWorkGroupInfo<size_t>(device,
                    CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE));
            assertEqual("Kernel1 for "+pName+" "+dName+" getPreferredWorkGroupSizeMultiple()",
                    prefWGSizeMult, kernel1.getPreferredWorkGroupSizeMultiple(device));
#endif
        }
#if __CLPP_CL_ABI_VERSION>=102
        const size_t kernel1ArgsNum = kernel1.getNumArgs();
        for (cl_uint argIdx = 0; argIdx < kernel1ArgsNum; argIdx++)
        {
            std::ostringstream oss;
            oss << pName << " " << argIdx;
            const std::string xName = oss.str();
            cl_kernel_arg_address_qualifier expArgAddrQualifier = getKernelArgInfo<
                    cl_kernel_arg_address_qualifier>(kernel1, argIdx,
                            CL_KERNEL_ARG_ADDRESS_QUALIFIER);
            assertEqual("Kernel1 for "+xName+" getInfo(ArgAddrQual)", expArgAddrQualifier,
                    kernel1.getArgInfo<cl_kernel_arg_address_qualifier>(argIdx,
                        CL_KERNEL_ARG_ADDRESS_QUALIFIER));
            assertEqual("Kernel1 for "+xName+" getArgAddressQualifier", expArgAddrQualifier,
                    kernel1.getArgAddressQualifier(argIdx));
            
            cl_kernel_arg_access_qualifier expArgAccessQualifier = getKernelArgInfo<
                    cl_kernel_arg_access_qualifier>(kernel1, argIdx,
                            CL_KERNEL_ARG_ACCESS_QUALIFIER);
            assertEqual("Kernel1 for "+xName+" getInfo(ArgAccQual)", expArgAccessQualifier,
                    kernel1.getArgInfo<cl_kernel_arg_access_qualifier>(argIdx,
                        CL_KERNEL_ARG_ACCESS_QUALIFIER));
            assertEqual("Kernel1 for "+xName+" getArgAccessQualifier", expArgAccessQualifier,
                    kernel1.getArgAccessQualifier(argIdx));
            
            const std::string argName = getKernelArgInfoString(kernel1, argIdx,
                    CL_KERNEL_ARG_NAME);
            assertEqual("Kernel1 for "+xName+" getArgName()", argName,
                    kernel1.getArgName(argIdx));
            const std::string argTypeName = getKernelArgInfoString(kernel1, argIdx,
                    CL_KERNEL_ARG_TYPE_NAME);
            assertEqual("Kernel1 for "+xName+" getArgTypeName()", argTypeName,
                    kernel1.getArgTypeName(argIdx));
        }
#endif
        /* kernel arg setting (using fake clSetKernelArg) */
        setKernelArgValuesInit();
        kernel1.setArg(0, 7);
        assertEqualKSetArg("Kernel1 "+pName+" setArg(0)", 0, 7);
        clpp::Program passer(context, passer24Str);
        passer.build();
        clpp::Kernel kernelp24(passer, "passer");
        
        static const int setArgsTable24[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs1", 1, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs2", 2, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs3", 3, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs4", 4, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs5", 5, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs6", 6, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs7", 7, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs8", 8, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs9", 9, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs10", 10, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs11", 11, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs12", 12, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs13", 13, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs14", 14, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs15", 15, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs16", 16, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs17", 17, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs18", 18, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs19", 19, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs20", 20, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs21", 21, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs22", 22, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs23", 23, setArgsTable24);
        
        setKernelArgValuesInit();
        kernelp24.setArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23, 24);
        assertEqualKSetArgs("Kernel1 "+pName+" setArgs24", 24, setArgsTable24);
        
        /* other types of set arg */
        clpp::Buffer buffer(context, CL_MEM_READ_WRITE, 1000);
        setKernelArgValuesInit();
        kernel1.setArg(2, buffer);
        assertEqualKSetArg("Kernel1 "+pName+" setArg(2, buffer)", 2, buffer);
        
        clpp::Program localArgPrg(context, localArgStr);
        localArgPrg.build();
        clpp::Kernel kernelLA(localArgPrg, "localArg");
        // local args
        setKernelArgValuesInit();
        kernelLA.setArg(1, clpp::Local(455));
        assertEqual("Kernel1 "+pName+" setArg Local", size_t(455), kernelSetArgSize[1]);
        assertEqual("Kernel1 "+pName+" setArg Local", std::vector<unsigned char>(),
                    kernelSetArgValue[1]);
        // null type
        setKernelArgValuesInit();
        kernelp24.setArg(4, 7);
        assertEqualKSetArg("Kernel1 "+pName+" setArg(4) before Null()", 4, 7);
        kernelp24.setArg(4, clpp::Null());
        assertEqualKSetArg("Kernel1 "+pName+" setArg(4) after Null()", 4, 7);
    }
#if __CLPP_CL_ABI_VERSION>=200
    // kernel setExecInfo 
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::Program program(context, moduloProgramStr);
        program.build();
        clpp::Kernel kernel(program, "modulator");
        
        kernel.setSVMFineGrainSystem();
        std::vector<void*> fakeSvmPtrs;
        fakeSvmPtrs.push_back((void*)0);
        fakeSvmPtrs.push_back((void*)16);
        fakeSvmPtrs.push_back((void*)256);
        //kernel.setSVMPointers(fakeSvmPtrs);
    }
#endif
    // reference testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::Program program(context, simpleProgramStr);
        clpp::Program program2(context, simpleProgramStr2);
        program.build();
        program2.build();
        clpp::Kernel kernel(program, "simpleKernel");
        clpp::Kernel kernel2(program2, "simpleKernel2");
        
        assertEqual("Kernel for " +pName+ ".refcount1", 1U, kernel.refCount());
        assertEqual("Kernel for " +pName+ ".refcount2", 1U, kernel2.refCount());
        {
            clpp::Kernel kernelCopy = kernel;
            assertEqual("Kernel for " +pName+ ".refcount3", 2U, kernel.refCount());
            assertEqual("Kernel for " +pName+ ".refcount4", 1U, kernel2.refCount());
        }
        assertEqual("Kernel for " +pName+ ".refcount5", 1U, kernel.refCount());
        clpp::Kernel kernel3;
        kernel3 = kernel2;
        assertEqual("Kernel for " +pName+ ".refcount6", 2U, kernel2.refCount());
        kernel3 = kernel;
        assertEqual("Kernel for " +pName+ ".refcount7", 1U, kernel2.refCount());
        assertEqual("Kernel for " +pName+ ".refcount8", 2U, kernel.refCount());
#   ifdef __CLPP_CPP0X
        kernel = std::move(kernel3);
        assertEqual("Kernel for " +pName+ ".refcount9", 1U, kernel.refCount());
#   endif
    }
}

static void EventClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    /* testing getting info and profiling info */
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::CommandQueue cmdQueue1(context, devices[0], CL_QUEUE_PROFILING_ENABLE);
        clpp::Buffer buffer1(context, CL_MEM_READ_WRITE, 204800*4);
        clpp::Buffer buffer2(context, CL_MEM_READ_WRITE, 204800*4);
        std::vector<cl_uint> data1(2048);
        for (size_t i = 0; i < data1.size(); i++)
            data1[i] = i*6366781 + 345521;
        
        enqueueCommandTestInit();
        clpp::Event event = cmdQueue1.enqueueWriteBuffer(buffer1, 0, 2048*4, &data1[0]);
        event.wait();
        
        assertEqual("Event for "+pName+" getContext()", context, event.getContext());
        assertEqual("Event for "+pName+" getInfo(CmdQueue)", cmdQueue1,
                    event.getInfo<clpp::CommandQueue>(CL_EVENT_COMMAND_QUEUE));
        assertEqual("Event for "+pName+" getCommandQueue()", cmdQueue1,
                    event.getCommandQueue());
        
        clpp::Event event2 = cmdQueue1.enqueueCopyBuffer(buffer1, buffer2, 0, 0, 2048*4);
        event2.wait();
        assertEqual("Event2 for "+pName+" getInfo(CmdType)",
                    getEventInfo<cl_command_type>(event2, CL_EVENT_COMMAND_TYPE),
                    event2.getInfo<cl_command_type>(CL_EVENT_COMMAND_TYPE));
        assertEqual("Event2 for "+pName+" getCommandType()", getEventInfo<
                cl_command_type>(event2, CL_EVENT_COMMAND_TYPE), event2.getCommandType());
        
        assertEqual("Event2 for "+pName+" getStatus()", getEventInfo<
                cl_int>(event2, CL_EVENT_COMMAND_EXECUTION_STATUS),
                    event2.getStatus());
        
        /* profiling info */
        assertEqual("Event for "+pName+" getProfilingInfo(ProfQueued)",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_QUEUED),
                    event.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_QUEUED));
        assertEqual("Event for "+pName+" getProfilingCommandQueued()",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_QUEUED),
                    event.getProfilingCommandQueued());
        assertEqual("Event for "+pName+" getProfilingInfo(ProfSubmit)",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_SUBMIT),
                    event.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_SUBMIT));
        assertEqual("Event for "+pName+" getProfilingCommandSubmit()",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_SUBMIT),
                    event.getProfilingCommandSubmit());
        assertEqual("Event for "+pName+" getProfilingInfo(ProfStart)",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_START),
                    event.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_START));
        assertEqual("Event for "+pName+" getProfilingCommandStart()",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_START),
                    event.getProfilingCommandStart());
        assertEqual("Event for "+pName+" getProfilingInfo(ProfEnd)",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_END),
                    event.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_END));
        assertEqual("Event for "+pName+" getProfilingCommandEnd()",
                    getEventProfilingInfo<cl_ulong>(event, CL_PROFILING_COMMAND_END),
                    event.getProfilingCommandEnd());
    }
    
    /* reference counting tests */
#if 0
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::CommandQueue cmdQueue1(context, devices[0], CL_QUEUE_PROFILING_ENABLE);
        clpp::Buffer buffer1(context, CL_MEM_READ_WRITE, sizeof(cl_uint)*204800);
        std::vector<cl_uint> data1(2048);
        for (size_t i = 0; i < data1.size(); i++)
            data1[i] = i*6366781 + 345521;
        
        enqueueCommandTestInit();
        clpp::Event event = cmdQueue1.enqueueWriteBuffer(buffer1, 0, 2048*4, &data1[0]);
        event.wait();
        clpp::Event event2 = cmdQueue1.enqueueWriteBuffer(buffer1, 0, 2048*4, &data1[0]);
        event2.wait();
        
        assertEqual("Event for " +pName+ ".refcount1", 1U, event.refCount());
        assertEqual("Event for " +pName+ ".refcount2", 1U, event2.refCount());
        {
            clpp::Event eventCopy = event;
            assertEqual("Event for " +pName+ ".refcount3", 2U, event.refCount());
            assertEqual("Event for " +pName+ ".refcount4", 1U, event2.refCount());
        }
        assertEqual("Event for " +pName+ ".refcount5", 1U, event.refCount());
        clpp::Event event3;
        event3 = event2;
        assertEqual("Event for " +pName+ ".refcount6", 2U, event2.refCount());
        event3 = event;
        assertEqual("Event for " +pName+ ".refcount7", 1U, event2.refCount());
        assertEqual("Event for " +pName+ ".refcount8", 2U, event.refCount());
#   ifdef __CLPP_CPP0X
        event = std::move(event3);
        assertEqual("Event for " +pName+ ".refcount9", 1U, event.refCount());
#   endif
    }
#endif
}

#if __CLPP_CL_ABI_VERSION>=101
static void UserEventClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    /* creation testing */
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::UserEvent userEvent(context);
        assertEqual("UserEvent for "+pName+" getContext()", context, userEvent.getContext());
        assertEqual("UserEvent for "+pName+" getCommandQueue()", clpp::CommandQueue(),
                    userEvent.getCommandQueue());
        assertEqual("UserEvent for "+pName+" getStatus()", getEventInfo<
                cl_int>(userEvent, CL_EVENT_COMMAND_EXECUTION_STATUS),
                    userEvent.getStatus());
        userEvent.setStatus(-1000);
        assertEqual("UserEvent for "+pName+" getStatus2()",
                    cl_int(-1000), userEvent.getStatus());
    }
}
#endif

static void assertEqualWaitListInput(const std::string& name,
            std::vector<clpp::Event>& expWaitList)
{
    std::vector<clpp::Event> result;
    for (size_t i = 0; i < waitListInput.size(); i++)
        result.push_back(clpp::Event::from(waitListInput[i]));
    assertEqual(name, expWaitList, result);
}

static void CommandQueueClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::CommandQueue cmdQueue1(context, devices[0]);
        clpp::CommandQueue cmdQueue2(context, devices[0], CL_QUEUE_PROFILING_ENABLE);
#if __CLPP_CL_ABI_VERSION>=200
        static const cl_queue_properties cmdqprops[5] = {
            CL_QUEUE_PROPERTIES, (cl_queue_properties)CL_QUEUE_PROFILING_ENABLE,
            CL_QUEUE_SIZE, 1000, 0 };
        clpp::CommandQueue cmdQueue3(context, devices[0], cmdqprops);
#endif
        
        // testing getInfo
        assertEqual("CommandQueue for "+pName+" getInfo(device)", devices[0],
                    cmdQueue1.getInfo<clpp::Device>(CL_QUEUE_DEVICE));
        assertEqual("CommandQueue for "+pName+" getDevice()", devices[0],
                    cmdQueue1.getDevice());
        assertEqual("CommandQueue2 for "+pName+" getInfo(device)", devices[0],
                    cmdQueue2.getInfo<clpp::Device>(CL_QUEUE_DEVICE));
        assertEqual("CommandQueue2 for "+pName+" getDevice()", devices[0],
                    cmdQueue2.getDevice());
        assertEqual("CommandQueue for "+pName+" getInfo(context)", context,
                    cmdQueue1.getInfo<clpp::Context>(CL_QUEUE_CONTEXT));
        assertEqual("CommandQueue for "+pName+" getContext()", context,
                    cmdQueue1.getContext());
        assertEqual("CommandQueue2 for "+pName+" getInfo(context)", context,
                    cmdQueue2.getInfo<clpp::Context>(CL_QUEUE_CONTEXT));
        assertEqual("CommandQueue2 for "+pName+" getContext()", context,
                    cmdQueue2.getContext());
#if __CLPP_CL_ABI_VERSION>=200
        assertEqual("CommandQueue3 for "+pName+" getContext()", context,
                    cmdQueue3.getContext());
#endif
        
        assertEqual("CommandQueue1 for "+pName+" getProperties",
                getCommandQueueInfo<cl_command_queue_properties>(cmdQueue1,
                        CL_QUEUE_PROPERTIES), cmdQueue1.getProperties());
        assertEqual("CommandQueue2 for "+pName+" getProperties",
                getCommandQueueInfo<cl_command_queue_properties>(cmdQueue2,
                        CL_QUEUE_PROPERTIES), cmdQueue2.getProperties());
#if __CLPP_CL_ABI_VERSION>=200
        assertEqual("CommandQueue3 for "+pName+" getProperties",
                getCommandQueueInfo<cl_command_queue_properties>(cmdQueue3,
                        CL_QUEUE_PROPERTIES), cmdQueue3.getProperties());
#endif
    }
    
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::CommandQueue cmdQueue1(context, devices[0]);
        clpp::Buffer buffer1(context, CL_MEM_READ_WRITE, sizeof(cl_uint)*204800);
        clpp::Buffer buffer2(context, CL_MEM_READ_WRITE, sizeof(cl_uint)*307200);
        std::vector<cl_uint> data1(2048);
        std::vector<cl_uint> fromBuffer(2048);
        std::vector<cl_uint> data2(304800);
        for (size_t i = 0; i < data1.size(); i++)
            data1[i] = i*6366781 + 345521;
        
        /*
         * using a fake OpenCL functions to test waitList input passing and other arguments
         */
        /* blocking read/write */
        enqueueCommandTestInit();
        cmdQueue1.writeBuffer(buffer1, 0, 2048*sizeof(cl_uint), &data1[0]);
        assertEqual("WriteBuffer for "+pName+" empty waitList", std::vector<cl_event>(),
                    waitListInput);
        assertBool("WriteBuffer for "+pName+" blockingMode", blockingMode);
        
        enqueueCommandTestInit();
        cmdQueue1.readBuffer(buffer1, 0, 2048*sizeof(cl_uint), &fromBuffer[0]);
        assertEqual("ReadBuffer for "+pName+" empty waitList", std::vector<cl_event>(),
                    waitListInput);
        assertBool("ReadBuffer for "+pName+" blockingMode", blockingMode);
        
        assertEqual("ReadWrite for "+pName+" data1", data1, fromBuffer);
        
        /* nonblocking read/write */
        enqueueCommandTestInit();
        cmdQueue1.enqueueWriteBuffer(buffer1, 0, 2048*sizeof(cl_uint), &data1[0]).wait();
        assertEqual("EnqueueWriteBuffer for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertBool("EnqueueWriteBuffer for "+pName+" nonblockingMode", !blockingMode);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueReadBuffer(buffer1, 0, 2048*sizeof(cl_uint), &fromBuffer[0]).wait();
        assertEqual("EnqueueReadBuffer for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertBool("EnqueueReadBuffer for "+pName+" nonblockingMode", !blockingMode);
        
        assertEqual("EnqueueReadWrite for "+pName+" data1", data1, fromBuffer);
        
        std::vector<clpp::Event> expWaitList;
        expWaitList.push_back(cmdQueue1.enqueueReadBuffer(
                    buffer1, 0, 2048*sizeof(cl_uint), &fromBuffer[0]));
        expWaitList.push_back(cmdQueue1.enqueueReadBuffer(
                    buffer1, 0, 1000*sizeof(cl_uint), &fromBuffer[0]));
        expWaitList.push_back(cmdQueue1.enqueueReadBuffer(
                    buffer1, 200*sizeof(cl_uint), 1000*sizeof(cl_uint), &fromBuffer[0]));
        clpp::Event::waitForEvents(expWaitList);
        /* with event list */
        enqueueCommandTestInit();
        cmdQueue1.readBuffer(buffer1, 0, 2048*sizeof(cl_uint), &fromBuffer[0], expWaitList);
        assertEqualWaitListInput("ReadBufferWL for "+pName+" waitList", expWaitList);
        enqueueCommandTestInit();
        cmdQueue1.writeBuffer(buffer1, 0, 2048*sizeof(cl_uint), &data1[0], expWaitList);
        assertEqualWaitListInput("WriteBufferWL for "+pName+" waitList", expWaitList);
        
        cmdQueue1.enqueueReadBuffer(buffer1, 0, 2048*sizeof(cl_uint),
                    &fromBuffer[0],expWaitList).wait();
        assertEqualWaitListInput("EnqueueReadBufferWL for "+pName+" waitList", expWaitList);
        enqueueCommandTestInit();
        cmdQueue1.enqueueWriteBuffer(buffer1, 0, 2048*sizeof(cl_uint),
                    &data1[0], expWaitList).wait();
        assertEqualWaitListInput("EnqueueWriteBufferWL for "+pName+" waitList", expWaitList);
        
        // copy buffer
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyBuffer(buffer1, buffer2, 250*4, 700*4, 1700*4).wait();
        assertEqual("EnqueueCopyBuffer for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        cmdQueue1.readBuffer(buffer2, 700*4, 1700*4, &fromBuffer[0]);
        assertEqual("EnqueueCopyBuffer for "+pName+" empty waitList",
                    std::vector<cl_uint>(data1.begin()+250, data1.begin()+250+1700),
                    std::vector<cl_uint>(fromBuffer.begin(), fromBuffer.begin()+1700));
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyBuffer(buffer1, buffer2, 250*4, 700*4, 1700*4,
                    expWaitList).wait();
        assertEqualWaitListInput("EnqueueCopyBufferWL for "+pName+" waitList", expWaitList);

#if __CLPP_CL_ABI_VERSION>=101
        // read/write/copy rect buffer
        enqueueCommandTestInit();
        cmdQueue1.readBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0]);
        assertEqual("ReadBufferRect for "+pName+" bufferOrigin",
                    Size3(3, 5), rectOffset1Input);
        assertEqual("ReadBufferRect for "+pName+" hostOrigin",
                    Size3(6, 7), rectOffset2Input);
        assertEqual("ReadBufferRect for "+pName+" region",
                    Size3(123, 214, 1), rectRegionInput);
        assertEqual("ReadBufferRect for "+pName+" bufferRowPitch",
                    size_t(140), rowPitch1Input);
        assertEqual("ReadBufferRect for "+pName+" bufferSlicePitch",
                    size_t(220*140), slicePitch1Input);
        assertEqual("ReadBufferRect for "+pName+" hostRowPitch",
                    size_t(130), rowPitch2Input);
        assertEqual("ReadBufferRect for "+pName+" hostSlicePitch",
                    size_t(215*130), slicePitch2Input);
        assertBool("ReadBufferRect for "+pName+" blockingMode", blockingMode);
        assertEqual("ReadBufferRect for "+pName+" empty waitList", std::vector<cl_event>(),
                    waitListInput);
        enqueueCommandTestInit();
        cmdQueue1.readBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0], expWaitList);
        assertEqualWaitListInput("ReadBufferRectWL for "+pName+" waitList", expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueReadBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0]).wait();
        assertEqual("EnqueueReadBufferRect for "+pName+" bufferOrigin",
                    Size3(3, 5), rectOffset1Input);
        assertEqual("EnqueueReadBufferRect for "+pName+" hostOrigin",
                    Size3(6, 7), rectOffset2Input);
        assertEqual("EnqueueReadBufferRect for "+pName+" region",
                    Size3(123, 214, 1), rectRegionInput);
        assertEqual("EnqueueReadBufferRect for "+pName+" bufferRowPitch",
                    size_t(140), rowPitch1Input);
        assertEqual("EnqueueReadBufferRect for "+pName+" bufferSlicePitch",
                    size_t(220*140), slicePitch1Input);
        assertEqual("EnqueueReadBufferRect for "+pName+" hostRowPitch",
                    size_t(130), rowPitch2Input);
        assertEqual("EnqueueReadBufferRect for "+pName+" hostSlicePitch",
                    size_t(215*130), slicePitch2Input);
        assertBool("EnqueueReadBufferRect for "+pName+" nonblockingMode", !blockingMode);
        assertEqual("EnqueueReadBufferRect for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        enqueueCommandTestInit();
        cmdQueue1.enqueueReadBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0], expWaitList).wait();
        assertEqualWaitListInput("EnqueueReadBufferRectWL for "+pName+" waitList",
                    expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.writeBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0]);
        assertEqual("WriteBufferRect for "+pName+" bufferOrigin",
                    Size3(3, 5), rectOffset1Input);
        assertEqual("WriteBufferRect for "+pName+" hostOrigin",
                    Size3(6, 7), rectOffset2Input);
        assertEqual("WriteBufferRect for "+pName+" region",
                    Size3(123, 214, 1), rectRegionInput);
        assertEqual("WriteBufferRect for "+pName+" bufferRowPitch",
                    size_t(140), rowPitch1Input);
        assertEqual("WriteBufferRect for "+pName+" bufferSlicePitch",
                    size_t(220*140), slicePitch1Input);
        assertEqual("WriteBufferRect for "+pName+" hostRowPitch",
                    size_t(130), rowPitch2Input);
        assertEqual("WriteBufferRect for "+pName+" hostSlicePitch",
                    size_t(215*130), slicePitch2Input);
        assertBool("WriteBufferRect for "+pName+" blockingMode", blockingMode);
        assertEqual("WriteBufferRect for "+pName+" empty waitList", std::vector<cl_event>(),
                    waitListInput);
        enqueueCommandTestInit();
        cmdQueue1.writeBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0], expWaitList);
        assertEqualWaitListInput("WriteBufferRectWL for "+pName+" waitList", expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueWriteBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0]).wait();
        assertEqual("EnqueueWriteBufferRect for "+pName+" bufferOrigin",
                    Size3(3, 5), rectOffset1Input);
        assertEqual("EnqueueWriteBufferRect for "+pName+" hostOrigin",
                    Size3(6, 7), rectOffset2Input);
        assertEqual("EnqueueWriteBufferRect for "+pName+" region",
                    Size3(123, 214, 1), rectRegionInput);
        assertEqual("EnqueueWriteBufferRect for "+pName+" bufferRowPitch",
                    size_t(140), rowPitch1Input);
        assertEqual("EnqueueWriteBufferRect for "+pName+" bufferSlicePitch",
                    size_t(220*140), slicePitch1Input);
        assertEqual("EnqueueWriteBufferRect for "+pName+" hostRowPitch",
                    size_t(130), rowPitch2Input);
        assertEqual("EnqueueWriteBufferRect for "+pName+" hostSlicePitch",
                    size_t(215*130), slicePitch2Input);
        assertBool("EnqueueWriteBufferRect for "+pName+" nonblockingMode", !blockingMode);
        assertEqual("EnqueueWriteBufferRect for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        enqueueCommandTestInit();
        cmdQueue1.enqueueWriteBufferRect(buffer1, Size3(3, 5), Size3(6, 7), Size3(123, 214),
                140, 220*140, 130, 215*130, &data2[0], expWaitList).wait();
        assertEqualWaitListInput("EnqueueWriteBufferRectWL for "+pName+" waitList",
                    expWaitList);
        
        // copy buffer rect
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyBufferRect(buffer1, buffer2, Size3(3, 5), Size3(6, 7),
                Size3(123, 214), 140, 220*140, 130, 215*130).wait();
        assertEqual("EnqueueCopyBufferRect for "+pName+" bufferOrigin",
                    Size3(3, 5), rectOffset1Input);
        assertEqual("EnqueueCopyBufferRect for "+pName+" hostOrigin",
                    Size3(6, 7), rectOffset2Input);
        assertEqual("EnqueueCopyBufferRect for "+pName+" region",
                    Size3(123, 214, 1), rectRegionInput);
        assertEqual("EnqueueCopyBufferRect for "+pName+" bufferRowPitch",
                    size_t(140), rowPitch1Input);
        assertEqual("EnqueueCopyBufferRect for "+pName+" bufferSlicePitch",
                    size_t(220*140), slicePitch1Input);
        assertEqual("EnqueueCopyBufferRect for "+pName+" hostRowPitch",
                    size_t(130), rowPitch2Input);
        assertEqual("EnqueueCopyBufferRect for "+pName+" hostSlicePitch",
                    size_t(215*130), slicePitch2Input);
        assertEqual("EnqueueCopyBufferRect for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyBufferRect(buffer1, buffer2, Size3(3, 5), Size3(6, 7),
                Size3(123, 214), 140, 220*140, 130, 215*130, expWaitList).wait();
        assertEqualWaitListInput("EnqueueCopyBufferRectWL for "+pName+" waitList",
                    expWaitList);
#endif
#if __CLPP_CL_ABI_VERSION>=102
        // fill buffer
        enqueueCommandTestInit();
        cl_uint4 fillValue = {{55,77,33,11}};
        cmdQueue1.enqueueFillBuffer(buffer1, fillValue, 68*4, 1432*4).wait();
        assertEqual("EnqueueFillBuffer for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        for (size_t i = 68; i < 1432+68; i+=4)
        {
            data1[i] = 55;
            data1[i+1] = 77;
            data1[i+2] = 33;
            data1[i+3] = 11;
        }
        cmdQueue1.readBuffer(buffer1, 68*4, 1432*4, &fromBuffer[0]);
        assertEqual("EnqueueFillBuffer for "+pName+" fromBuffer",
                    std::vector<cl_uint>(data1.begin()+68, data1.begin()+68+1432),
                    std::vector<cl_uint>(fromBuffer.begin(), fromBuffer.begin()+1432));
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueFillBuffer(buffer1, fillValue, 68*4, 1432*4, expWaitList).wait();
        assertEqualWaitListInput("EnqueueFillBufferWL for "+pName+" waitList", expWaitList);
#endif
        /* read/write image test */
        clpp::Image2D image2D1(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 600, 400);
        clpp::Image2D image2D2(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 800, 600);
        std::vector<cl_uint> imgData1(800*800);
        for (size_t i = 0; i < imgData1.size(); i++)
            imgData1[i] = i*6366781 + 345521;
        
        enqueueCommandTestInit();
        cmdQueue1.writeImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0, &imgData1[0]);
        assertBool("WriteImage for "+pName+" blockingMode", blockingMode);
        assertEqual("WriteImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("WriteImage for "+pName+" origin", Size3(20,30), rectOffset1Input);
        assertEqual("WriteImage for "+pName+" region", Size3(400,300,1), rectRegionInput);
        assertEqual("WriteImage for "+pName+" rowPitch", size_t(2048), rowPitch1Input);
        assertEqual("WriteImage for "+pName+" slicePitch", size_t(0), slicePitch1Input);
        
        enqueueCommandTestInit();
        cmdQueue1.writeImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0, &imgData1[0],
                    expWaitList);
        assertEqualWaitListInput("WriteImageWL for "+pName+" waitList", expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueWriteImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0,
                    &imgData1[0]).wait();
        assertBool("EnqueueWriteImage for "+pName+" blockingMode", !blockingMode);
        assertEqual("EnqueueWriteImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("EnqueueWriteImage for "+pName+" origin", Size3(20,30), rectOffset1Input);
        assertEqual("EnqueueWriteImage for "+pName+" region", Size3(400,300,1), rectRegionInput);
        assertEqual("EnqueueWriteImage for "+pName+" rowPitch", size_t(2048), rowPitch1Input);
        assertEqual("EnqueueWriteImage for "+pName+" slicePitch", size_t(0), slicePitch1Input);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueWriteImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0,
                    &imgData1[0], expWaitList).wait();
        assertEqualWaitListInput("EnqueueWriteImageWL for "+pName+" waitList", expWaitList);
        // readimage
        enqueueCommandTestInit();
        cmdQueue1.readImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0, &imgData1[0]);
        assertBool("ReadImage for "+pName+" blockingMode", blockingMode);
        assertEqual("ReadImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("ReadImage for "+pName+" origin", Size3(20,30), rectOffset1Input);
        assertEqual("ReadImage for "+pName+" region", Size3(400,300,1), rectRegionInput);
        assertEqual("ReadImage for "+pName+" rowPitch", size_t(2048), rowPitch1Input);
        assertEqual("ReadImage for "+pName+" slicePitch", size_t(0), slicePitch1Input);
        
        enqueueCommandTestInit();
        cmdQueue1.readImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0, &imgData1[0],
                    expWaitList);
        assertEqualWaitListInput("ReadImageWL for "+pName+" waitList", expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueReadImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0,
                    &imgData1[0]).wait();
        assertBool("EnqueueReadImage for "+pName+" blockingMode", !blockingMode);
        assertEqual("EnqueueReadImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("EnqueueReadImage for "+pName+" origin", Size3(20,30), rectOffset1Input);
        assertEqual("EnqueueReadImage for "+pName+" region", Size3(400,300,1), rectRegionInput);
        assertEqual("EnqueueReadImage for "+pName+" rowPitch", size_t(2048), rowPitch1Input);
        assertEqual("EnqueueReadImage for "+pName+" slicePitch", size_t(0), slicePitch1Input);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueReadImage(image2D1, Size3(20,30), Size3(400, 300), 2048, 0,
                    &imgData1[0], expWaitList).wait();
        assertEqualWaitListInput("EnqueueReadImageWL for "+pName+" waitList", expWaitList);
        
        // copy image
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyImage(image2D1, image2D2, Size3(42, 12), Size3(10, 15),
                    Size3(321, 125)).wait();
        assertEqual("EnqueueCopyImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("EnqueueCopyImage for "+pName+" srcOrigin",
                    Size3(42,12), rectOffset1Input);
        assertEqual("EnqueueCopyImage for "+pName+" dstOrigin",
                    Size3(10,15), rectOffset2Input);
        assertEqual("EnqueueCopyImage for "+pName+" region",
                    Size3(321,125,1), rectRegionInput);
        cmdQueue1.enqueueCopyImage(image2D1, image2D2, Size3(42, 12), Size3(10, 15),
                    Size3(321, 125), expWaitList).wait();
        assertEqualWaitListInput("EnqueueCopyImageWL for "+pName+" waitList", expWaitList);
        
#if __CLPP_CL_ABI_VERSION>=102
        // fill image
        enqueueCommandTestInit();
        cl_float4 fillColor = {{ 0.6f, 0.65f, 0.12f, 0.0f }};
        cmdQueue1.enqueueFillImage(image2D1, fillColor, Size3(20,30), Size3(400, 300)).wait();
        assertEqual("EnqueueFillImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("EnqueueFillImage for "+pName+" origin", Size3(20,30), rectOffset1Input);
        assertEqual("EnqueueFillImage for "+pName+" region", Size3(400,300,1), rectRegionInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueFillImage(image2D1, fillColor, Size3(20,30),
                    Size3(400, 300), expWaitList).wait();
        assertEqualWaitListInput("EnqueueFillImageWL for "+pName+" waitList", expWaitList);
#endif
        /* copy image from/to buffer */
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyImageToBuffer(image2D1, buffer1, Size3(30, 54),
                    Size3(100, 70), 100).wait();
        assertEqual("EnqueueCopyImageToBuffer for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("EnqueueCopyImageToBuffer for "+pName+" origin",
                    Size3(30,54), rectOffset1Input);
        assertEqual("EnqueueCopyImageToBuffer for "+pName+" region",
                    Size3(100,70,1), rectRegionInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyImageToBuffer(image2D1, buffer1, Size3(30, 54),
                    Size3(100, 70), 100, expWaitList).wait();
        assertEqualWaitListInput("EnqueueCopyImageToBufferWL for "+pName+" waitList",
                    expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyBufferToImage(buffer1, image2D1, 14, Size3(11, 22),
                    Size3(122, 90)).wait();
        assertEqual("EnqueueCopyBufferToImage for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        assertEqual("EnqueueCopyBufferToImage for "+pName+" region",
                    Size3(122,90,1), rectRegionInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueCopyBufferToImage(buffer1, image2D1, 14, Size3(11, 22),
                    Size3(122, 90), expWaitList).wait();
        assertEqualWaitListInput("EnqueueCopyBufferToImageWL for "+pName+" waitList",
                    expWaitList);
        
        /* map buffer */
        void* ptr1 = NULL;
        void* ptr2 = NULL;
        try
        {
            enqueueCommandTestInit();
            ptr1 = cmdQueue1.mapBuffer(buffer1, CL_MAP_READ, 100, 2000);
            assertEqual("MapBuffer for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            assertBool("MapBuffer for "+pName+" blocking mode", blockingMode);
            assertEqual("MapBuffer for "+pName+" ptr", mappedPtr, ptr1);
            
            cmdQueue1.enqueueUnmapMemObject(buffer1, ptr1).wait();
            ptr1 = NULL;
            
            enqueueCommandTestInit();
            ptr1 = cmdQueue1.mapBuffer(buffer1, CL_MAP_READ, 170, 2000, expWaitList);
            assertEqualWaitListInput("MapBuffer for "+pName+" waitList", expWaitList);
            assertBool("MapBuffer for "+pName+" blocking mode", blockingMode);
            assertEqual("MapBuffer for "+pName+" ptr", mappedPtr, ptr1);
            
            enqueueCommandTestInit();
            cmdQueue1.enqueueMapBuffer(ptr2, buffer1, CL_MAP_READ, 100, 2111).wait();
            assertEqual("EnqueueMapBuffer for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            assertBool("EnqueueMapBuffer for "+pName+" blocking mode", !blockingMode);
            assertEqual("EnqueueMapBuffer for "+pName+" ptr", mappedPtr, ptr2);
            
            cmdQueue1.enqueueUnmapMemObject(buffer2, ptr2).wait();
            ptr2 = NULL;
            
            enqueueCommandTestInit();
            cmdQueue1.enqueueMapBuffer(ptr2, buffer1, CL_MAP_READ, 130, 2023,
                        expWaitList).wait();
            assertEqualWaitListInput("MapBuffer for "+pName+" waitList", expWaitList);
            assertBool("EnqueueMapBuffer for "+pName+" non-blocking mode", !blockingMode);
            assertEqual("EnqueueMapBuffer for "+pName+" ptr", mappedPtr, ptr2);
        }
        catch(...)
        {
            if (ptr1 != NULL) cmdQueue1.enqueueUnmapMemObject(buffer1, ptr1).wait();
            if (ptr2 != NULL) cmdQueue1.enqueueUnmapMemObject(buffer1, ptr2).wait();
            throw;
        }
        if (ptr1 != NULL) cmdQueue1.enqueueUnmapMemObject(buffer1, ptr1).wait();
        if (ptr2 != NULL) cmdQueue1.enqueueUnmapMemObject(buffer1, ptr2).wait();
        
        /* map image */
        size_t imageRowPitch, imageSlicePitch;
        try
        {
            enqueueCommandTestInit();
            ptr1 = cmdQueue1.mapImage(image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch, imageSlicePitch);
            assertEqual("MapImage for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            assertBool("MapImage for "+pName+" blocking mode", blockingMode);
            assertEqual("MapImage for "+pName+" ptr", mappedPtr, ptr1);
            assertEqual("MapImage for "+pName+" origin", Size3(10, 25), rectOffset1Input);
            assertEqual("MapImage for "+pName+" region", Size3(440, 300, 1), rectRegionInput);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr1).wait();
            ptr1 = NULL;
            
            enqueueCommandTestInit();
            ptr1 = cmdQueue1.mapImage(image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch, imageSlicePitch, expWaitList);
            assertBool("MapImage for "+pName+" blocking mode", blockingMode);
            assertEqual("MapImage for "+pName+" ptr", mappedPtr, ptr1);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr1).wait();
            ptr1 = NULL;
            /* map Image 2d (no slicePitch) */
            enqueueCommandTestInit();
            ptr1 = cmdQueue1.mapImage(image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch);
            assertEqual("MapImage2D for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            assertBool("MapImage2D for "+pName+" blocking mode", blockingMode);
            assertEqual("MapImage2D for "+pName+" ptr", mappedPtr, ptr1);
            assertEqual("MapImage2D for "+pName+" origin", Size3(10, 25), rectOffset1Input);
            assertEqual("MapImage2D for "+pName+" region",
                        Size3(440, 300, 1), rectRegionInput);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr1).wait();
            ptr1 = NULL;
            
            enqueueCommandTestInit();
            ptr1 = cmdQueue1.mapImage(image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch, expWaitList);
            assertBool("MapImage2D for "+pName+" blocking mode", blockingMode);
            assertEqual("MapImage2D for "+pName+" ptr", mappedPtr, ptr1);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr1).wait();
            ptr1 = NULL;
            
            /* enqueue map image */
            enqueueCommandTestInit();
            cmdQueue1.enqueueMapImage(ptr2, image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch, imageSlicePitch).wait();
            assertEqual("EnqueueMapImage for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            assertBool("EnqueueMapImage for "+pName+" non-blocking mode", !blockingMode);
            assertEqual("EnqueueMapImage for "+pName+" ptr", mappedPtr, ptr2);
            assertEqual("EnqueueMapImage for "+pName+" origin",
                        Size3(10, 25), rectOffset1Input);
            assertEqual("EnqueueMapImage for "+pName+" region",
                        Size3(440, 300, 1), rectRegionInput);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr2).wait();
            ptr2 = NULL;
            
            enqueueCommandTestInit();
            cmdQueue1.enqueueMapImage(ptr2, image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch, imageSlicePitch, expWaitList).wait();
            assertBool("EnqueueMapImage for "+pName+" non-blocking mode", !blockingMode);
            assertEqual("EnqueueMapImage for "+pName+" ptr", mappedPtr, ptr2);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr2).wait();
            ptr2 = NULL;
            /* map Image 2d (no slicePitch) */
            enqueueCommandTestInit();
            cmdQueue1.enqueueMapImage(ptr2, image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch).wait();
            assertEqual("EnqueueMapImage2D for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            assertBool("EnqueueMapImage2D for "+pName+" non-blocking mode", !blockingMode);
            assertEqual("EnqueueMapImage2D for "+pName+" ptr", mappedPtr, ptr2);
            assertEqual("EnqueueMapImage2D for "+pName+" origin",
                        Size3(10, 25), rectOffset1Input);
            assertEqual("EnqueueMapImage2D for "+pName+" region",
                        Size3(440, 300, 1), rectRegionInput);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr2).wait();
            ptr2 = NULL;
            
            enqueueCommandTestInit();
            cmdQueue1.enqueueMapImage(ptr2, image2D1, CL_MAP_READ, Size3(10, 25),
                    Size3(440, 300), imageRowPitch, expWaitList).wait();
            assertBool("EnqueueMapImage2D for "+pName+" non-blocking mode", !blockingMode);
            assertEqual("EnqueueMapImage2D for "+pName+" ptr", mappedPtr, ptr2);
            cmdQueue1.enqueueUnmapMemObject(image2D1, ptr2).wait();
            ptr2 = NULL;
        }
        catch(...)
        {
            if (ptr1 != NULL) cmdQueue1.enqueueUnmapMemObject(image2D1, ptr1).wait();
            if (ptr2 != NULL) cmdQueue1.enqueueUnmapMemObject(image2D1, ptr2).wait();
            throw;
        }
        if (ptr1 != NULL) cmdQueue1.enqueueUnmapMemObject(image2D1, ptr1).wait();
        if (ptr2 != NULL) cmdQueue1.enqueueUnmapMemObject(image2D1, ptr2).wait();
        
        /* enqueue NDRange Kernel */
        clpp::Program program(context, simpleProgramStr);
        program.build();
        clpp::Kernel kernel(program, "simpleKernel");
        kernel.setArgs(2000, buffer1, buffer2);
        //
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, 2, 2048, 64).wait();
        assertEqual("Enqueue1DRangeKernel for "+pName+" workDim", cl_uint(1U),
                    workDimInput);
        assertEqual("Enqueue1DRangeKernel for "+pName+" globalWorkOffset",
                    Size3(2), globalWorkOffsetInput);
        assertEqual("Enqueue1DRangeKernel for "+pName+" globalWorkSize",
                    Size3(2048), globalWorkSizeInput);
        assertEqual("Enqueue1DRangeKernel for "+pName+" localWorkSize",
                    Size3(64), localWorkSizeInput);
        assertEqual("Enqueue1DRangeKernel for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, 2, 2048, 64, expWaitList).wait();
        assertEqualWaitListInput("Enqueue1DRangeKernelWL for "+pName+" waitList",
                    expWaitList);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, Size3(2,6,0), Size3(2048, 8),
                    Size3(8, 8)).wait();
        assertEqual("Enqueue2DRangeKernel for "+pName+" workDim", cl_uint(2U),
                    workDimInput);
        assertEqual("Enqueue2DRangeKernel for "+pName+" globalWorkOffset",
                    Size3(2, 6), globalWorkOffsetInput);
        assertEqual("Enqueue2DRangeKernel for "+pName+" globalWorkSize",
                    Size3(2048, 8), globalWorkSizeInput);
        assertEqual("Enqueue2DRangeKernel for "+pName+" localWorkSize",
                    Size3(8, 8), localWorkSizeInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, Size3(2,6,9), Size3(1024, 8, 16),
                    Size3(8, 4, 2)).wait();
        assertEqual("Enqueue3DRangeKernel for "+pName+" workDim", cl_uint(3U),
                    workDimInput);
        assertEqual("Enqueue3DRangeKernel for "+pName+" globalWorkOffset",
                    Size3(2, 6, 9), globalWorkOffsetInput);
        assertEqual("Enqueue3DRangeKernel for "+pName+" globalWorkSize",
                    Size3(1024, 8, 16), globalWorkSizeInput);
        assertEqual("Enqueue3DRangeKernel for "+pName+" localWorkSize",
                    Size3(8, 4, 2), localWorkSizeInput);
        
        /* two argument enqueueNDRangeKernel */
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, 2048, 64).wait();
        assertEqual("Enqueue1DRangeKernel2 for "+pName+" workDim", cl_uint(1U),
                    workDimInput);
        assertEqual("Enqueue1DRangeKernel2 for "+pName+" globalWorkOffset",
                    Size3(0), globalWorkOffsetInput);
        assertEqual("Enqueue1DRangeKernel2 for "+pName+" globalWorkSize",
                    Size3(2048), globalWorkSizeInput);
        assertEqual("Enqueue1DRangeKernel2 for "+pName+" localWorkSize",
                    Size3(64), localWorkSizeInput);
        assertEqual("Enqueue1DRangeKernel2 for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, Size3(2048, 8), Size3(8, 8)).wait();
        assertEqual("Enqueue2DRangeKernel2 for "+pName+" workDim", cl_uint(2U),
                    workDimInput);
        assertEqual("Enqueue2DRangeKernel2 for "+pName+" globalWorkOffset",
                    Size3(0, 0), globalWorkOffsetInput);
        assertEqual("Enqueue2DRangeKernel2 for "+pName+" globalWorkSize",
                    Size3(2048, 8), globalWorkSizeInput);
        assertEqual("Enqueue2DRangeKernel2 for "+pName+" localWorkSize",
                    Size3(8, 8), localWorkSizeInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, Size3(1024, 8, 16), Size3(8, 4, 2)).wait();
        assertEqual("Enqueue3DRangeKernel2 for "+pName+" workDim", cl_uint(3U),
                    workDimInput);
        assertEqual("Enqueue3DRangeKernel2 for "+pName+" globalWorkOffset",
                    Size3(0, 0, 0), globalWorkOffsetInput);
        assertEqual("Enqueue3DRangeKernel2 for "+pName+" globalWorkSize",
                    Size3(1024, 8, 16), globalWorkSizeInput);
        assertEqual("Enqueue3DRangeKernel2 for "+pName+" localWorkSize",
                    Size3(8, 4, 2), localWorkSizeInput);
        
        /* single argument enqueueNDRangeKernel */
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, 2048).wait();
        assertEqual("Enqueue1DRangeKernel3 for "+pName+" workDim", cl_uint(1U),
                    workDimInput);
        assertEqual("Enqueue1DRangeKernel3 for "+pName+" globalWorkOffset",
                    Size3(0), globalWorkOffsetInput);
        assertEqual("Enqueue1DRangeKernel3 for "+pName+" globalWorkSize",
                    Size3(2048), globalWorkSizeInput);
        assertEqual("Enqueue1DRangeKernel3 for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, Size3(2048, 8)).wait();
        assertEqual("Enqueue2DRangeKernel3 for "+pName+" workDim", cl_uint(2U),
                    workDimInput);
        assertEqual("Enqueue2DRangeKernel3 for "+pName+" globalWorkOffset",
                    Size3(0, 0), globalWorkOffsetInput);
        assertEqual("Enqueue2DRangeKernel3 for "+pName+" globalWorkSize",
                    Size3(2048, 8), globalWorkSizeInput);
        
        enqueueCommandTestInit();
        cmdQueue1.enqueueNDRangeKernel(kernel, Size3(1024, 8, 16)).wait();
        assertEqual("Enqueue3DRangeKernel3 for "+pName+" workDim", cl_uint(3U),
                    workDimInput);
        assertEqual("Enqueue3DRangeKernel3 for "+pName+" globalWorkOffset",
                    Size3(0, 0, 0), globalWorkOffsetInput);
        assertEqual("Enqueue3DRangeKernel3 for "+pName+" globalWorkSize",
                    Size3(1024, 8, 16), globalWorkSizeInput);
    }
    
    // reference testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        
        clpp::CommandQueue cmdQueue(context, devices[0]);
        clpp::CommandQueue cmdQueue2(context, devices[0]);
        
        assertEqual("CommandQueue for " +pName+ ".refcount1", 1U, cmdQueue.refCount());
        assertEqual("CommandQueue for " +pName+ ".refcount2", 1U, cmdQueue2.refCount());
        {
            clpp::CommandQueue cmdQueueCopy = cmdQueue;
            assertEqual("CommandQueue for " +pName+ ".refcount3", 2U, cmdQueue.refCount());
            assertEqual("CommandQueue for " +pName+ ".refcount4", 1U, cmdQueue2.refCount());
        }
        assertEqual("CommandQueue for " +pName+ ".refcount5", 1U, cmdQueue.refCount());
        clpp::CommandQueue cmdQueue3;
        cmdQueue3 = cmdQueue2;
        assertEqual("CommandQueue for " +pName+ ".refcount6", 2U, cmdQueue2.refCount());
        cmdQueue3 = cmdQueue;
        assertEqual("CommandQueue for " +pName+ ".refcount7", 1U, cmdQueue2.refCount());
        assertEqual("CommandQueue for " +pName+ ".refcount8", 2U, cmdQueue.refCount());
#   ifdef __CLPP_CPP0X
        cmdQueue = std::move(cmdQueue3);
        assertEqual("CommandQueue for " +pName+ ".refcount9", 1U, cmdQueue.refCount());
#   endif
    }
}

#if __CLPP_CL_ABI_VERSION>=200
static void SVMMemoryTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::CommandQueue cmdQueue(context, devices[0]);
        
        void* ptr1 = NULL ,* ptr2 = NULL;
        try
        {
            ptr1 = context.SVMAlloc(CL_MEM_READ_WRITE, 100000);
            ptr2 = context.SVMAlloc(CL_MEM_READ_WRITE, 200000);
            assertBool("SVMAlloc for "+pName+" pointer1", ptr1!=NULL);
            assertBool("SVMAlloc for "+pName+" pointer2", ptr2!=NULL);
            context.SVMFree(ptr1);
            ptr1 = NULL;
            context.SVMFree(ptr2);
            ptr2 = NULL;
        }
        catch(...)
        {
            if (ptr1!=NULL) context.SVMFree(ptr1);
            if (ptr2!=NULL) context.SVMFree(ptr2);
            throw;
        }
        
        try
        {
            ptr1 = context.SVMAlloc(CL_MEM_READ_WRITE, 100000);
            ptr2 = context.SVMAlloc(CL_MEM_READ_WRITE, 200000);
            /* testing enqueue methods */
            enqueueCommandTestInit();
            cmdQueue.SVMMemcpy(ptr1, ptr2, 400);
            assertBool("SVMMemcpy for "+pName+" blocking mode", blockingMode);
            assertEqual("SVMemcpy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
            
            /*enqueueCommandTestInit();
            cmdQueue.enqueueSVMMemcpy(ptr1, ptr2, 400).wait();
            assertBool("EnqueueSVMMemcpy for "+pName+" non-blocking mode", !blockingMode);
            assertEqual("EnqueueSVMemcpy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);*/
        }
        catch(...)
        {
            if (ptr1!=NULL) context.SVMFree(ptr1);
            if (ptr2!=NULL) context.SVMFree(ptr2);
            throw;
        }
        if (ptr1!=NULL) context.SVMFree(ptr1);
        if (ptr2!=NULL) context.SVMFree(ptr2);
        
        std::vector<int, clpp::SVMAllocator<int> > myVec(
                clpp::SVMAllocator<int>(context, CL_MEM_READ_WRITE));
        myVec.resize(1000);
    }
}
#endif

static void MemoryMappingClassTester()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    // creation testing
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        clpp::Context context(devices);
        clpp::CommandQueue cmdQueue(context, devices[0]);
        
        clpp::Buffer buffer1(context, CL_MEM_READ_WRITE, 1000000U);
        clpp::Image2D image2D1(context, CL_MEM_READ_WRITE,
                    clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8), 2000, 1500);
        std::vector<clpp::Event> expWaitList;
        std::vector<cl_uint> data1(2000);
        
        for (size_t i = 0; i < 5; i++)
            expWaitList.push_back(cmdQueue.enqueueReadBuffer(buffer1, 0, 1000, &data1[0]));
        clpp::Event::waitForEvents(expWaitList);
        
        clpp::Event unmapEvent, unmapEvent2;
        {    // mapping1
            enqueueCommandTestInit();
            clpp::BufferMapping mapping1(cmdQueue, buffer1, true, CL_MAP_READ, 100, 23480);
            assertEqual("BufferMapping for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            enqueueCommandTestInit();
        }
        assertEqual("BufferMappingDestroy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        {    // mapping2
            enqueueCommandTestInit();
            clpp::BufferMapping mapping2(cmdQueue, buffer1, false, CL_MAP_READ, 100, 23480,
                        &unmapEvent);
            assertEqual("BufferMapping2 for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            mapping2.wait();
            enqueueCommandTestInit();
        }
        assertEqual("BufferMapping2Destroy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        {    // mapping3
            enqueueCommandTestInit();
            clpp::BufferMapping mapping3(cmdQueue, buffer1, true, CL_MAP_READ,
                        100, 23480, expWaitList);
            assertEqualWaitListInput("BufferMapping3WL for "+pName+" waitlist",
                        expWaitList);
            enqueueCommandTestInit();
        }
        assertEqual("BufferMapping3Destroy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        {    // mapping4
            enqueueCommandTestInit();
            clpp::BufferMapping mapping4(cmdQueue, buffer1, true, CL_MAP_READ,
                        100, 23480, expWaitList, expWaitList);
            assertEqualWaitListInput("BufferMapping4WL for "+pName+" waitlist",
                        expWaitList);
            enqueueCommandTestInit();
        }
        assertEqualWaitListInput("BufferMapping4WLDestroy for "+pName+" waitlist",
                        expWaitList);
        {    // imageMapping1
            enqueueCommandTestInit();
            clpp::ImageMapping imgMapping(cmdQueue, image2D1, true, CL_MAP_READ,
                        Size3(13, 45), Size3(1310, 854));
            assertEqual("ImageMapping for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
            enqueueCommandTestInit();
        }
        assertEqual("ImageMapping1Destroy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        {    // imageMapping2
            enqueueCommandTestInit();
            clpp::ImageMapping imgMapping2(cmdQueue, image2D1, true, CL_MAP_READ,
                        Size3(13, 45), Size3(1310, 854), expWaitList, expWaitList);
            assertEqualWaitListInput("ImageMapping2WL for "+pName+" waitlist",
                        expWaitList);
            enqueueCommandTestInit();
        }
        assertEqualWaitListInput("ImageMapping2WLDestroy for "+pName+" waitlist",
                        expWaitList);
        {    // imageMapping3
            enqueueCommandTestInit();
            clpp::ImageMapping imgMapping3(cmdQueue, image2D1, false, CL_MAP_READ,
                        Size3(13, 45), Size3(1310, 854), expWaitList, expWaitList,
                        &unmapEvent);
            assertEqualWaitListInput("ImageMapping3WL for "+pName+" waitlist",
                        expWaitList);
            imgMapping3.wait();
            enqueueCommandTestInit();
        }
        assertEqualWaitListInput("ImageMapping3WLDestroy for "+pName+" waitlist",
                        expWaitList);
        {    // imageMapping5 (mapWaitList, noUnmapWaitList
            enqueueCommandTestInit();
            clpp::ImageMapping imgMapping5(cmdQueue, image2D1, true, CL_MAP_READ,
                        Size3(13, 45), Size3(1310, 854), expWaitList);
            assertEqualWaitListInput("ImageMapping5WL for "+pName+" waitlist",
                        expWaitList);
            enqueueCommandTestInit();
        }
        assertEqual("ImageMapping5WLDestroy for "+pName+" empty waitList",
                    std::vector<cl_event>(), waitListInput);
        
        if (unmapEvent) unmapEvent.wait();
        if (unmapEvent2) unmapEvent2.wait();
    }
}

#ifdef __CLPP_CL_GL
static volatile clGetGLContextInfoKHR_fn getGLContextInfoKHR = NULL;

static void initclGetGLContextInfo(const cl_context_properties* props)
{
    if (getGLContextInfoKHR == NULL)
    {
#   if __CLPP_CL_ABI_VERSION>=102
        /* slow but sure */
        cl_platform_id platform = NULL;
        if (props != NULL)
            for (const cl_context_properties* p = props; *p != 0; p+=2)
                if (*p == CL_CONTEXT_PLATFORM) // get platform
                    platform = cl_platform_id(p[1]);
        getGLContextInfoKHR =
            reinterpret_cast<clGetGLContextInfoKHR_fn>(
                clGetExtensionFunctionAddressForPlatform(platform, "clGetGLContextInfoKHR"));
#   else
        getGLContextInfoKHR = reinterpret_cast<clGetGLContextInfoKHR_fn>(
                clGetExtensionFunctionAddress("clGetGLContextInfoKHR"));
#   endif
        if (getGLContextInfoKHR == NULL)
            getGLContextInfoKHR = clGetGLContextInfoKHR_fn(1);
    }
    
    if (getGLContextInfoKHR <= clGetGLContextInfoKHR_fn(1))
        throw TestException("Unsupported clGetGLContextInfoKHR");
}

static std::vector<clpp::Device> getGLContextInfoDevices(const cl_context_properties* props,
        cl_gl_context_info paramName)
{
    initclGetGLContextInfo(props);
    size_t numDevices;
    if (getGLContextInfoKHR(props, paramName, 0, NULL, &numDevices) != CL_SUCCESS)
        throw TestException("Failed clGetGLContextInfoKHR");
    numDevices /= sizeof(cl_device_id);
    std::vector<clpp::Device> devices(numDevices);
    if (getGLContextInfoKHR(props, paramName, numDevices*sizeof(cl_device_id),
                &devices[0], NULL) != CL_SUCCESS)
        throw TestException("Failed clGetGLContextInfoKHR");
    // retain is not required because they are base devices */
    return devices;
}

static clpp::Device getGLContextInfoDevice(const cl_context_properties* props,
        cl_gl_context_info paramName)
{
    initclGetGLContextInfo(props);
    clpp::Device device;
    if (getGLContextInfoKHR(props, paramName, sizeof(cl_device_id),
                &device, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetGLContextInfoKHR");
    // retain is not required because they are base devices */
    return device;
}

static void getGLObjectInfo(cl_mem memory, cl_gl_object_type* type, cl_GLuint* name)
{
    if (clGetGLObjectInfo(memory, type, name) != CL_SUCCESS)
        throw TestException("Failed clGetGLObjectInfo");
}

template<typename T>
static T getGLTextureInfo(cl_mem texture, cl_gl_texture_info paramName)
{
    T value;
    if (clGetGLTextureInfo(texture, paramName, sizeof(T), &value, NULL) != CL_SUCCESS)
        throw TestException("Failed clGetGLTextureInfo");
    return value;
}

static void CLGLInteropTester()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw TestException("Can't initialize SDL GL");
 
    SDL_Surface* surfDisplay = NULL;
    try
    {
    if((surfDisplay = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE |
                SDL_DOUBLEBUF | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
        throw TestException("Can't create surface display");
    
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    for (std::vector<clpp::Platform>::const_iterator it = platforms.begin();
                    it != platforms.end(); ++it)
    {
        const clpp::Platform& platform = *it;
        std::string pName = getPlatformInfoString(platform, CL_PLATFORM_NAME);
        
        const cl_context_properties clglProps[5] = { CL_CONTEXT_PLATFORM,
            (cl_context_properties)platforms[0](), CL_GL_CONTEXT_KHR,
            (cl_context_properties)glXGetCurrentContext(), 0
        };
        
        const std::vector<clpp::Device> expDevices = getGLContextInfoDevices(clglProps,
                    CL_DEVICES_FOR_GL_CONTEXT_KHR);
        assertEqual("CLGLDevices for "+pName, expDevices,  platform.getDevicesForGL(
                    CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext()));
        
        clpp::Device expDevice = getGLContextInfoDevice(clglProps,
                    CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR);
        clpp::Device device = platform.getCurrentDeviceForGL(CL_GL_CONTEXT_KHR,
                    (cl_context_properties)glXGetCurrentContext());
        assertEqual("CLGLDevice for "+pName, expDevice, device);
        
        clpp::Context context(CL_GL_CONTEXT_KHR,
                (cl_context_properties)glXGetCurrentContext(), platform, device);
        clpp::Context contextAll(CL_GL_CONTEXT_KHR,
                (cl_context_properties)glXGetCurrentContext(), platform, expDevices);
        
        /* testing BufferGL */
        std::vector<float> myData(1000);
        
        for (cl_uint i = 0; i < 1000; i++)
            myData[i] = (float)rand()/(float)RAND_MAX;
        
        bool isBufferObj = false;
        GLuint bufferObj;
        try
        {
            glGenBuffers(1, &bufferObj);
            bufferObj = true;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObj);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1000*sizeof(float), &myData[0],
                    GL_STREAM_READ);
            
            clpp::BufferGL bufferGL(context, CL_MEM_READ_ONLY, bufferObj);
            cl_gl_object_type expGLobjType, resGLobjType;
            GLuint expGLobjName, resGLobjName;
            getGLObjectInfo(bufferGL, &expGLobjType, &expGLobjName);
            bufferGL.getGLObjectInfo(&resGLobjType, &resGLobjName);
            
            assertEqual("BufferGL for "+pName+" getGLObjectInfo objType",
                        expGLobjType, resGLobjType);
            assertEqual("BufferGL for "+pName+" getGLObjectInfo objName",
                        expGLobjName, resGLobjName);
        }
        catch(...)
        {
            if (isBufferObj) glDeleteBuffers(1, &bufferObj);
            throw;
        }
        
        if (isBufferObj) glDeleteBuffers(1, &bufferObj);
        
        /* textures */
        std::vector<cl_uchar> imageData(300*200*4);
        std::vector<cl_uchar> imageData3D(70*60*30*4);
        for (cl_uint i = 0; i < 300*200*4; i++)
            imageData[i] = rand()&255;
        for (cl_uint i = 0; i < 70*60*30*4; i++)
            imageData3D[i] = rand()&255;
        
        bool isTextureObj = false;
        bool isTextureObj3D = false;
        GLuint textureObj;
        GLuint textureObj3D;
        
        try
        {
            glGenTextures(1, &textureObj);
            isTextureObj = true;
            glGenTextures(1, &textureObj3D);
            isTextureObj3D = true;
            glBindTexture(GL_TEXTURE_RECTANGLE_ARB, textureObj);
            glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, 300, 200, 0, GL_RGBA, GL_BYTE,
                    &imageData[0]);
            glBindTexture(GL_TEXTURE_RECTANGLE_ARB, textureObj);
            
            glBindTexture(GL_TEXTURE_3D, textureObj3D);
            glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 70, 60, 30, 0, GL_RGBA, GL_BYTE,
                    &imageData3D[0]);
            
            clpp::TextureGL textureGL(context, CL_MEM_READ_WRITE,
                    GL_TEXTURE_RECTANGLE_ARB, 0, textureObj);
            clpp::TextureGL textureGL3D(context, CL_MEM_READ_WRITE,
                    GL_TEXTURE_3D, 0, textureObj3D, true);
            
            // getGLObjectInfo
            cl_gl_object_type expGLobjType, resGLobjType;
            GLuint expGLobjName, resGLobjName;
            getGLObjectInfo(textureGL, &expGLobjType, &expGLobjName);
            textureGL.getGLObjectInfo(&resGLobjType, &resGLobjName);
            
            assertEqual("TextureGL for "+pName+" getGLObjectInfo objType",
                        expGLobjType, resGLobjType);
            assertEqual("TextureGL for "+pName+" getGLObjectInfo objName",
                        expGLobjName, resGLobjName);
            
            getGLObjectInfo(textureGL3D, &expGLobjType, &expGLobjName);
            textureGL3D.getGLObjectInfo(&resGLobjType, &resGLobjName);
            
            assertEqual("TextureGL3D for "+pName+" getGLObjectInfo objType",
                        expGLobjType, resGLobjType);
            assertEqual("TextureGL3D for "+pName+" getGLObjectInfo objName",
                        expGLobjName, resGLobjName);
            
            /* getGLTextureInfo */
            assertEqual("GLTexture for "+pName+" getInfo(TextureTarget)",
                        getGLTextureInfo<GLenum>(textureGL, CL_GL_TEXTURE_TARGET),
                        textureGL.getGLTextureInfo<GLenum>(CL_GL_TEXTURE_TARGET));
            assertEqual("GLTexture for "+pName+" getTextureTarget",
                        getGLTextureInfo<GLenum>(textureGL, CL_GL_TEXTURE_TARGET),
                        textureGL.getGLTextureTarget());
            assertEqual("GLTexture for "+pName+" getInfo(MipMapLevel)",
                        getGLTextureInfo<GLint>(textureGL, CL_GL_MIPMAP_LEVEL),
                        textureGL.getGLTextureInfo<GLint>(CL_GL_MIPMAP_LEVEL));
            assertEqual("GLTexture for "+pName+" getMipMapLevel",
                        getGLTextureInfo<GLint>(textureGL, CL_GL_MIPMAP_LEVEL),
                        textureGL.getGLMipMapLevel());
            
            assertEqual("GLTexture3D for "+pName+" getInfo(TextureTarget)",
                        getGLTextureInfo<GLenum>(textureGL3D, CL_GL_TEXTURE_TARGET),
                        textureGL3D.getGLTextureInfo<GLenum>(CL_GL_TEXTURE_TARGET));
            assertEqual("GLTexture3D for "+pName+" getTextureTarget",
                        getGLTextureInfo<GLenum>(textureGL3D, CL_GL_TEXTURE_TARGET),
                        textureGL3D.getGLTextureTarget());
            assertEqual("GLTexture3D for "+pName+" getInfo(MipMapLevel)",
                        getGLTextureInfo<GLint>(textureGL3D, CL_GL_MIPMAP_LEVEL),
                        textureGL3D.getGLTextureInfo<GLint>(CL_GL_MIPMAP_LEVEL));
            assertEqual("GLTexture3D for "+pName+" getMipMapLevel",
                        getGLTextureInfo<GLint>(textureGL3D, CL_GL_MIPMAP_LEVEL),
                        textureGL3D.getGLMipMapLevel());
        }
        catch(...)
        {
            if (isTextureObj) glDeleteTextures(1, &textureObj);
            if (isTextureObj3D) glDeleteTextures(1, &textureObj3D);
            throw;
        }
        if (isTextureObj) glDeleteTextures(1, &textureObj);
        if (isTextureObj3D) glDeleteTextures(1, &textureObj3D);
        
        /* renderbuffers */
        bool isRenderBufObj = false;
        GLuint renderBufObj;
        
        try
        {
            glGenRenderbuffers(1, &renderBufObj);
            isRenderBufObj = true;
            glBindRenderbuffer(GL_RENDERBUFFER, renderBufObj);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 300, 200);
            
            clpp::RenderbufferGL renderbufGL(context, CL_MEM_READ_ONLY, renderBufObj);
            
            // getGLObjectInfo
            cl_gl_object_type expGLobjType, resGLobjType;
            GLuint expGLobjName, resGLobjName;
            getGLObjectInfo(renderbufGL, &expGLobjType, &expGLobjName);
            renderbufGL.getGLObjectInfo(&resGLobjType, &resGLobjName);
            
            assertEqual("RenderbufferGL for "+pName+" getGLObjectInfo objType",
                        expGLobjType, resGLobjType);
            assertEqual("RenderbufferGL for "+pName+" getGLObjectInfo objName",
                        expGLobjName, resGLobjName);
        }
        catch(...)
        {
            if (isRenderBufObj) glDeleteRenderbuffers(1, &renderBufObj);
            throw;
        }
        if (isRenderBufObj) glDeleteRenderbuffers(1, &renderBufObj);
        
        // enqueue acquire/release objects testing
        clpp::CommandQueue cmdQueue(context, expDevices[0]);
        
        GLuint GLobjs[5];
        bool isGLobjs = false;
        try
        {
            glGenTextures(5, GLobjs);
            isGLobjs = true;
            std::vector<clpp::Memory> clglObjs;
            for (int i = 0; i < 5; i++)
            {
                glBindTexture(GL_TEXTURE_RECTANGLE_ARB, GLobjs[i]);
                glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, 300, 200, 0,
                        GL_RGBA, GL_BYTE, &imageData[0]);
                clglObjs.push_back(clpp::TextureGL(context, CL_MEM_READ_WRITE,
                    GL_TEXTURE_RECTANGLE_ARB, 0, textureObj));
            }
            
            // enqueue
            bool acquired = false;
            try
            {
                std::vector<clpp::Event> expWaitList;
                enqueueCommandTestInit();
                clpp::Event event1 = cmdQueue.enqueueAcquireGLObjects(clglObjs);
                event1.wait();
                expWaitList.push_back(event1);
                acquired = true;
                assertEqual("EnqueueAcquireGLObjects 5objs for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
                
                enqueueCommandTestInit();
                clpp::Event event2 = cmdQueue.enqueueReleaseGLObjects(clglObjs);
                event2.wait();
                expWaitList.push_back(event2);
                acquired = false;
                assertEqual("EnqueueReleaseGLObjects 5objs for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
                
                enqueueCommandTestInit();
                cmdQueue.enqueueAcquireGLObjects(clglObjs, expWaitList).wait();
                acquired = true;
                assertEqualWaitListInput("EnqueueAcquireGLObjects 5objs for "
                        +pName+" waitlist", expWaitList);
                
                enqueueCommandTestInit();
                cmdQueue.enqueueReleaseGLObjects(clglObjs, expWaitList).wait();
                acquired = true;
                assertEqualWaitListInput("EnqueueReleaseGLObjects 5objs for "
                        +pName+" waitlist", expWaitList);
            }
            catch(...)
            {
                if (acquired) cmdQueue.enqueueReleaseGLObjects(clglObjs);
                throw;
            }
            if (acquired) cmdQueue.enqueueReleaseGLObjects(clglObjs);
            
            acquired = false;
            
            try
            {
                std::vector<clpp::Event> expWaitList;
                enqueueCommandTestInit();
                clpp::Event event1 = cmdQueue.enqueueAcquireGLObject(clglObjs[0]);
                event1.wait();
                expWaitList.push_back(event1);
                acquired = true;
                assertEqual("EnqueueAcquireGLObject 1obj for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
                
                enqueueCommandTestInit();
                clpp::Event event2 = cmdQueue.enqueueReleaseGLObject(clglObjs[0]);
                event2.wait();
                expWaitList.push_back(event2);
                acquired = false;
                assertEqual("EnqueueReleaseGLObject 1obj for "+pName+" empty waitList",
                        std::vector<cl_event>(), waitListInput);
                
                enqueueCommandTestInit();
                cmdQueue.enqueueAcquireGLObject(clglObjs[0], expWaitList).wait();
                acquired = true;
                assertEqualWaitListInput("EnqueueAcquireGLObject 1obj for "
                        +pName+" waitlist", expWaitList);
                
                enqueueCommandTestInit();
                cmdQueue.enqueueReleaseGLObject(clglObjs[0], expWaitList).wait();
                acquired = true;
                assertEqualWaitListInput("EnqueueReleaseGLObject 1obj for "
                        +pName+" waitlist", expWaitList);
            }
            catch(...)
            {
                if (acquired) cmdQueue.enqueueReleaseGLObject(clglObjs[0]);
                throw;
            }
            if (acquired) cmdQueue.enqueueReleaseGLObject(clglObjs[0]);
            
            { clpp::GLObjectsLock lock(cmdQueue, clglObjs); }
            { clpp::GLObjectsLock lock2(cmdQueue, clglObjs[0]); }
        }
        catch(...)
        {
            if (isGLobjs) glDeleteTextures(5, GLobjs);
            throw;
        }
        if (isGLobjs) glDeleteTextures(5, GLobjs);
        
#ifdef CL_COMMAND_GL_FENCE_SYNC_OBJECT_KHR
        GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
        clpp::Event glsyncEvent = clpp::Event(context, sync);
        glDeleteSync(sync);
#endif
    } // for
    }
    catch(...)
    {
        if (surfDisplay!=NULL)
            SDL_FreeSurface(surfDisplay);
        SDL_Quit();
        throw;
    }
    if (surfDisplay!=NULL)
        SDL_FreeSurface(surfDisplay);
    SDL_Quit();
}
#endif

int main(int argc, const char** argv)
try
{
#ifdef _WINDOWS
    programCallbackEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (programCallbackEvent == NULL)
        throw TestException("Can't initialize event!");
#endif
    std::cout << "ErrorClassTester..." << std::endl;
    ErrorClassTester();
    std::cout << "Size3Tester..." << std::endl;
    Size3Tester();
    std::cout << "GetInfoHelperTester..." << std::endl;
    GetInfoHelperTester();
    std::cout << "PlatformClassTester..." << std::endl;
    PlatformClassTester();
    std::cout << "DeviceClassTester..." << std::endl;
    DeviceClassTester();
    std::cout << "ContextClassTester..." << std::endl;
    ContextClassTester();
    std::cout << "BufferClassTester..." << std::endl;
    BufferClassTester();
    std::cout << "ImageClassTester..." << std::endl;
    ImageClassTester();
#if __CLPP_CL_ABI_VERSION>=200
    std::cout << "PipeClassTester..." << std::endl;
    PipeClassTester();
#endif
    std::cout << "SamplerClassTester..." << std::endl;
    SamplerClassTester();
    std::cout << "ProgramClassTester..." << std::endl;
    ProgramClassTester();
    std::cout << "KernelClassTester..." << std::endl;
    KernelClassTester();
    std::cout << "EventClassTester..." << std::endl;
    EventClassTester();
#if __CLPP_CL_ABI_VERSION>=101
    std::cout << "UserEventClassTester..." << std::endl;
    UserEventClassTester();
#endif
    std::cout << "CommandQueueClassTester..." << std::endl;
    CommandQueueClassTester();
#if __CLPP_CL_ABI_VERSION>=200
    std::cout << "SVMMemoryTester..." << std::endl;
    SVMMemoryTester();
#endif
    std::cout << "MemoryMappingClassTester..." << std::endl;
    MemoryMappingClassTester();
#ifdef __CLPP_CL_GL
    std::cout << "CLGLInteropTester..." << std::endl;
    CLGLInteropTester();
#endif
#ifdef _WINDOWS
    if (programCallbackEvent != NULL)
        CloseHandle(programCallbackEvent);
#endif
    return 0;
}
catch(const std::exception& ex)
{
#ifdef _WINDOWS
    if (programCallbackEvent != NULL)
        CloseHandle(programCallbackEvent);
#endif
    std::cerr << ex.what() << std::endl;
    return 1;
}
