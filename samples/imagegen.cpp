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

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <zlib.h>
#include <png.h>
#include <clpp.h>

class Error: public std::exception
{
private:
    std::string message;
public:
    explicit Error(const char* _msg) : message(_msg) { }
    virtual ~Error() __CLPP_NOEXCEPT { }
    const char* what() const __CLPP_NOEXCEPT
    { return message.c_str(); }
};

using clpp::Size3;

static const char* kernelCode =
"kernel void imageGen(float pangle, float pshift, write_only image2d_t image)\n"
"{\n"
"    const uint width = get_image_width(image);\n"
"    const uint height = get_image_height(image);\n"
"    const int2 pos = (int2)(get_global_id(0), get_global_id(1));\n"
"    if (pos.x >= width || pos.y >= height) return;\n"
"    const float2 cpos = (float2)(pos.x, pos.y)/\n"
"            (float2)((float)width,(float)height)-(float2)0.5f;\n"
"    const float2 normxy = normalize(cpos);\n"
"    const float angle = fmod((atan2pi(normxy.y, normxy.x)+1.0f)*0.5f + pangle, 1.f);\n"
"    const float len = fmod(length(cpos)*pshift, 1.f);\n"
"    const float4 color = (float4)(angle, len, 0.f, (angle+len)*0.1f+0.8f);\n"
"    write_imagef(image, pos, color);\n"
"}\n";

static const cl_uint imageWidth = 1024;
static const cl_uint imageHeight = 1024;

void png_warn_error_fn(png_structp pngstr, const char *str)
{
    fputs(str,stderr);
}

int main(int argc, const char** argv)
try
{
    std::cout << "Usage: imagegen [ANGLE [SCALE]]\n";
    float angle = 0;
    float scale = 10.0f;
    if (argc >= 2)
    {
        std::istringstream iss(argv[1]);
        iss.exceptions(std::ios::failbit);
        try
        { iss >> angle; }
        catch(std::exception& ex)
        { std::cerr << "Cant parse angle!" << std::endl; 
          return 1; }
    }
    if (argc >= 3)
    {
        std::istringstream iss(argv[2]);
        iss.exceptions(std::ios::failbit);
        try
        { iss >> scale; }
        catch(std::exception& ex)
        { std::cerr << "Cant parse scale!" << std::endl; 
          return 1; }
    }
    
    // choose first platform
    const clpp::Platform platform = clpp::Platform::get()[0];
    // choose first device from platform
    const clpp::Device device = platform.getAllDevices()[0];
    const clpp::Context context(device);
    
    clpp::Image image(context, CL_MEM_WRITE_ONLY, clpp::ImageFormat(CL_RGBA, CL_UNORM_INT8),
                      imageWidth, imageHeight);
    clpp::Program program(context, kernelCode);
    try
    { program.build(device); }
    catch(const clpp::Error& error)
    { std::cerr << program.getBuildLog(device) << std::endl;
      throw; }
    clpp::Kernel kernel(program, "imageGen");
    kernel.setArgs(angle, scale, image);
    
    clpp::CommandQueue cmdQueue(context, device);
    
    const size_t workGroupSize = kernel.getWorkGroupSize(device);
    size_t localDim = 0;
    for (size_t i = 1; i*i <= workGroupSize; i++)
        if (workGroupSize%i == 0 && i > localDim)
            localDim = i;
    
    const Size3 localSize(localDim, workGroupSize/localDim);
    std::cout << "LocalDim: " << localSize[0] << "x" << localSize[1] << std::endl;
    const Size3 alignedSize(((imageWidth+localSize[0]-1)/localSize[0])*localSize[0],
            ((imageHeight+localSize[1]-1)/localSize[1])*localSize[1]);
    
    cmdQueue.enqueueNDRangeKernel(kernel, alignedSize, localSize).wait();
    std::cout << "Generated now!" << std::endl;
    std::vector<cl_uchar4> outPixels(imageWidth*imageHeight);
    // read output image
    cmdQueue.readImage(image, 0, Size3(imageWidth, imageHeight), 0, 0, &outPixels[0]);
    // write PNG to file
    FILE* outFile = NULL;
    png_structp pngstr=NULL;
    png_infop info=NULL;
    try
    {
        outFile = fopen("outputimg.png", "wb");
        if (outFile==NULL)
            throw Error("Cant open output file");
        if((pngstr=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,
            png_warn_error_fn, png_warn_error_fn))==NULL)
            throw Error("Can't initialize PNG structures!");
        if((info=png_create_info_struct(pngstr))==NULL)
            throw Error("Can't initialize PNG structures!");
        png_init_io(pngstr, outFile);
        png_set_compression_level(pngstr, Z_BEST_COMPRESSION);
        png_set_IHDR(pngstr, info, imageWidth, imageHeight, 8, PNG_COLOR_TYPE_RGB_ALPHA,
                     PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        png_write_info(pngstr,info);
        for (cl_uint y = 0; y < imageHeight; y++)
            png_write_row(pngstr, (png_bytep)&outPixels[y*imageWidth]);
        png_write_end(pngstr,info);
        png_destroy_write_struct(&pngstr,&info);
        fclose(outFile);
    }
    catch(...)
    {
        if (pngstr) png_destroy_write_struct(&pngstr, &info);
        if (outFile) fclose(outFile);
        throw;
    }
    return 0;
}
catch(const std::exception& ex)
{
    std::cerr << ex.what() << std::endl;
    return 1;
}
catch(...)
{
    std::cerr << "Unknown exception!" << std::endl;
    return 1;
}
