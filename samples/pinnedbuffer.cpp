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
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <clpp.h>

static cl_uchar randomUChar()
{
    return std::rand()&255;
}

int main(int argc, const char** argv)
try
{
    std::cout << "This program measures performance of the reading and writing from/to\n"
        "pinned and normal buffers.\n"
        "Usage: pinnedbuffer BUFFERSIZE [ITERSNUM]\n" << std::endl;
    
    cl_uint itersNum = 10;
    size_t bufferSize = 1000000;
    if (argc >= 2)
    {   // get from command line buffer size
        std::istringstream iss(argv[1]);
        iss.exceptions(std::ios::failbit);
        try
        { iss >> bufferSize; }
        catch(const std::exception& ex)
        {
            std::cerr << "Can't parse buffer size" << std::endl;
            return 1;
        }
    }
    
    if (argc >= 3)
    {   // get from command line buffer size
        std::istringstream iss(argv[2]);
        iss.exceptions(std::ios::failbit);
        try
        { iss >> itersNum; }
        catch(const std::exception& ex)
        {
            std::cerr << "Can't parse buffer size" << std::endl;
            return 1;
        }
    }
    
    std::cout << "Testing for buffer size: " << bufferSize <<
            ", iterations: " << itersNum << std::endl;
    
    // choose first platform
    const clpp::Platform platform = clpp::Platform::get()[0];
    // choose first device from platform
    const clpp::Device device = platform.getAllDevices()[0];
    const clpp::Context context(device);
    const clpp::CommandQueue cmdQueue(context, device, CL_QUEUE_PROFILING_ENABLE);
    
    
    std::vector<cl_uchar> readData(bufferSize);
    std::vector<cl_uchar> writeData(bufferSize);
    std::generate(writeData.begin(), writeData.end(), randomUChar);
    // normal buffer performance measurement
    {
        const clpp::Buffer buffer(context, CL_MEM_READ_WRITE, bufferSize);
        double totalWriteTime = 0.0;
        for (cl_uint i = 0; i < itersNum; i++)
        {
            const clpp::Event writeEvent =
                    cmdQueue.enqueueWriteBuffer(buffer, 0, bufferSize, &writeData[0]);
            writeEvent.wait();
            totalWriteTime += double(writeEvent.getProfilingCommandEnd() -
                    writeEvent.getProfilingCommandStart())*1.0e-9;
        }
        totalWriteTime /= itersNum;
        std::cout << "Normal buffer write time: " << totalWriteTime << " seconds\n" <<
                "Normal buffer write bandwidth: " << (bufferSize/totalWriteTime)*1e-6 <<
                " MB/sec" << std::endl;
        
        double totalReadTime = 0.0;
        for (cl_uint i = 0; i < itersNum; i++)
        {
            const clpp::Event readEvent =
                    cmdQueue.enqueueReadBuffer(buffer, 0, bufferSize, &readData[0]);
            readEvent.wait();
            totalReadTime += double(readEvent.getProfilingCommandEnd() -
                    readEvent.getProfilingCommandStart())*1.0e-9;
        }
        totalReadTime /= itersNum;
        std::cout << "Normal buffer read time: " << totalReadTime << " seconds\n" <<
                "Normal buffer read bandwidth: " << (bufferSize/totalReadTime)*1e-6 <<
                " MB/sec" << std::endl;
    }
    
    // pinned buffer performance measurement
    {
        clpp::Buffer pinBuffer(context, CL_MEM_READ_WRITE|CL_MEM_ALLOC_HOST_PTR,
                         bufferSize);
        // map pinBuffer to make pinned buffering
        clpp::BufferMapping pinBufferMapping(cmdQueue, pinBuffer, true,
                    CL_MAP_READ|CL_MAP_WRITE, 0, bufferSize);
        unsigned char* ptr = reinterpret_cast<unsigned char*>(pinBufferMapping.get());
        std::copy(writeData.begin(), writeData.end(), ptr);
        
        const clpp::Buffer buffer(context, CL_MEM_READ_WRITE, bufferSize);
        double totalWriteTime = 0.0;
        for (cl_uint i = 0; i < itersNum; i++)
        {
            const clpp::Event writeEvent =
                    cmdQueue.enqueueWriteBuffer(buffer, 0, bufferSize, ptr);
            writeEvent.wait();
            totalWriteTime += double(writeEvent.getProfilingCommandEnd() -
                    writeEvent.getProfilingCommandStart())*1.0e-9;
        }
        totalWriteTime /= itersNum;
        std::cout << "Pinned buffer write time: " << totalWriteTime << " seconds\n" <<
                "Pinned buffer write bandwidth: " << (bufferSize/totalWriteTime)*1e-6 <<
                " MB/sec" << std::endl;
        
        double totalReadTime = 0.0;
        for (cl_uint i = 0; i < itersNum; i++)
        {
            const clpp::Event readEvent =
                    cmdQueue.enqueueReadBuffer(buffer, 0, bufferSize, ptr);
            readEvent.wait();
            totalReadTime += double(readEvent.getProfilingCommandEnd() -
                    readEvent.getProfilingCommandStart())*1.0e-9;
        }
        totalReadTime /= itersNum;
        std::cout << "Pinned buffer read time: " << totalReadTime << " seconds\n" <<
                "Pinned buffer read bandwidth: " << (bufferSize/totalReadTime)*1e-6 <<
                " MB/sec" << std::endl;
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
