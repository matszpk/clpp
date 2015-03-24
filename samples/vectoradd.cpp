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
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <clpp.h>

static const char* kernelCode =
"kernel void vectorAdd(uint n, const global float* avec, const global float* bvec,\n"
"        global float* cvec)\n"
"{\n"
"    const size_t i = get_global_id(0);\n"
"    if (i >= n) return;\n"
"    cvec[i] = avec[i] + bvec[i];\n"
"}\n";

static const size_t vectorSize =700;

static float randomFloat()
{
    return float(std::rand())/float(RAND_MAX);
}

int main(int argc, const char** argv)
try
{
    const clpp::Platform platform = clpp::Platform::get()[0];
    const clpp::Device device = platform.getGPUDevices()[0];
    const clpp::Context context(device);
    
    std::vector<float> avec(vectorSize);
    std::vector<float> bvec(vectorSize);
    std::generate(avec.begin(), avec.end(), randomFloat);
    std::generate(bvec.begin(), bvec.end(), randomFloat);
    
    clpp::Buffer abuf(context, CL_MEM_READ_ONLY, sizeof(float)*vectorSize);
    clpp::Buffer bbuf(context, CL_MEM_READ_ONLY, sizeof(float)*vectorSize);
    clpp::Buffer cbuf(context, CL_MEM_READ_ONLY, sizeof(float)*vectorSize);
    
    clpp::Program program(context, kernelCode);
    program.build(device);
    clpp::Kernel kernel(program, "vectorAdd");
    kernel.setArgs(cl_uint(vectorSize), abuf, bbuf, cbuf);
    
    clpp::CommandQueue cmdQueue(context, device);
    cmdQueue.writeBuffer(abuf, 0, sizeof(float)*vectorSize, &avec[0]);
    cmdQueue.writeBuffer(bbuf, 0, sizeof(float)*vectorSize, &bvec[0]);
    
    const size_t workGroupSize = kernel.getWorkGroupSize(device);
    const size_t alignedSize = ((vectorSize+workGroupSize-1)/workGroupSize)*workGroupSize;
    cmdQueue.enqueueNDRangeKernel(kernel, alignedSize, workGroupSize).wait();
    
    std::vector<float> cvec(vectorSize);
    cmdQueue.readBuffer(cbuf, 0, sizeof(float)*vectorSize, &cvec[0]);
    for (size_t i = 0; i < vectorSize; i++)
        std::cout << i << ": " << cvec[i] << "\n";
    std::cout.flush();
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

