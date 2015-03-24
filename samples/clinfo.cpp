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

#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_1_0_APIS

#include <iostream>
#include <vector>
#include <string>
#include <clpp.h>

using clpp::Size3;

static std::string getDeviceTypeDesc(cl_device_type devType)
{
    std::string desc;
    if ((devType & CL_DEVICE_TYPE_CPU) != 0)
        desc = "CPU";
    if ((devType & CL_DEVICE_TYPE_GPU) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "GPU";
    }
    if ((devType & CL_DEVICE_TYPE_ACCELERATOR) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "ACC";
    }
#if __CLPP_CL_VERSION >= 102U
    if ((devType & CL_DEVICE_TYPE_CUSTOM) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc = "Custom";
    }
#endif
    return desc;
}

static std::string getFPConfigDesc(cl_device_fp_config fpConfig)
{
    std::string desc;
    if ((fpConfig & CL_FP_DENORM) != 0)
        desc = "Denorm";
    if ((fpConfig & CL_FP_INF_NAN) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "InfNan";
    }
    if ((fpConfig & CL_FP_ROUND_TO_NEAREST) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "RTN";
    }
    if ((fpConfig & CL_FP_ROUND_TO_ZERO) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "RTZ";
    }
    if ((fpConfig & CL_FP_ROUND_TO_INF) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "RTI";
    }
    if ((fpConfig & CL_FP_FMA) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "FMA";
    }
#if __CLPP_CL_VERSION >= 101U
    if ((fpConfig & CL_FP_SOFT_FLOAT) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "SoftFloat";
    }
#endif
#if __CLPP_CL_VERSION >= 102U
    if ((fpConfig & CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "CRDivSqrt";
    }
#endif
    return desc;
}

static std::string getCacheTypeDesc(cl_device_mem_cache_type cacheType)
{
    switch(cacheType)
    {
        case CL_NONE:
            return "None";
        case CL_READ_ONLY_CACHE:
            return "Read-Only";
        case CL_READ_WRITE_CACHE:
            return "Read-Write";
        default:
            return "Unknown";
    }
}

static std::string getLocalMemTypeDesc(cl_device_local_mem_type localMemType)
{
    switch(localMemType)
    {
        case CL_NONE:
            return "None";
        case CL_LOCAL:
            return "Local";
        case CL_GLOBAL:
            return "Global";
        default:
            return "Unknown";
    }
}

static std::string getExecCapabilitiesDesc(cl_device_exec_capabilities execCaps)
{
    std::string desc;
    if ((execCaps & CL_EXEC_KERNEL) != 0)
        desc = "Kernel";
    if ((execCaps & CL_EXEC_NATIVE_KERNEL) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "NativeKernel";
    }
    return desc;
}

static std::string getCommandQueuePropsDesc(cl_command_queue_properties props)
{
    std::string desc;
    if ((props & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) != 0)
        desc = "OutOfOrder";
    if ((props & CL_QUEUE_PROFILING_ENABLE) != 0)
    {
        if (!desc.empty()) desc += ' ';
        desc += "Profiling";
    }
    return desc;
}

int main(int argc, const char** argv)
try
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    
    for (cl_uint i = 0; i < platforms.size(); i++)
    {
        std::cout << "------------------------------------------------------------\n";
        const clpp::Platform p = platforms[i];
        
        std::cout << "Platform name: " << p.getName() << "\n"
            "  Version: " << p.getVersion() << "\n"
            "  Profile: " << p.getProfile() << "\n"
            "  Vendor: " << p.getVendor() << "\n"
            "  Extensions: " << p.getExtensions() << "\n";
        const std::vector<clpp::Device> devices = p.getAllDevices();
        
        for (cl_uint j = 0; j < devices.size(); j++)
        {
            std::cout << "  ------------------------------------------------------------\n";
            const clpp::Device d = devices[j];
            const cl_uint dimsNum = d.getMaxWorkItemDims();
            std::cout << "  Device name: " << d.getName() << "\n"
                    "    Type: " << getDeviceTypeDesc(d.getType()) << "\n"
                    "    VendorId: " << d.getVendorId() << "\n"
                    "    MaxComputeUnits: " << d.getMaxComputeUnits() << "\n"
                    "    MaxWorkItemDims: " << dimsNum << "\n";
                
            const Size3 maxWorkItemSizes = d.getMaxWorkItemSizes();
            std::cout << "    MaxWorkItemSizes:";
            for (size_t k = 0; k < dimsNum; k++)
                std::cout << " " << maxWorkItemSizes[k];
            
            const bool isImageSupport = d.isImageSupport();
            
            std::cout << "\n    MaxWorkGroupSize: " << d.getMaxWorkGroupSize() << "\n"
                "    PrefVectorWidthChar: " << d.getPreferredVectorWidthChar() << " elems\n"
                "    PrefVectorWidthShort: " << d.getPreferredVectorWidthShort() <<
                        " elems\n"
                "    PrefVectorWidthInt: " << d.getPreferredVectorWidthInt() << " elems\n"
                "    PrefVectorWidthLong: " << d.getPreferredVectorWidthLong() << " elems\n"
                "    PrefVectorWidthFloat: " << d.getPreferredVectorWidthFloat() <<
                        " elems\n"
                "    PrefVectorWidthDouble: " << d.getPreferredVectorWidthDouble() <<
                        " elsms\n"
#if __CLPP_CL_VERSION >= 101U
                "    PrefVectorWidthHalf: " << d.getPreferredVectorWidthHalf() << "\n"
#endif
#if __CLPP_CL_VERSION >= 102U
                "    NativeVectorWidthChar: " << d.getNativeVectorWidthChar() << " elems\n"
                "    NativeVectorWidthShort: " << d.getNativeVectorWidthShort() << " elems\n"
                "    NativeVectorWidthInt: " << d.getNativeVectorWidthInt() << " elems\n"
                "    NativeVectorWidthLong: " << d.getNativeVectorWidthLong() << " elems\n"
                "    NativeVectorWidthFloat: " << d.getNativeVectorWidthFloat() << " elems\n"
                "    NativeVectorWidthDouble: " << d.getNativeVectorWidthDouble() <<
                        " elems\n"
                "    NativeVectorWidthHalf: " << d.getNativeVectorWidthHalf() << "elems\n"
#endif
                "    MaxClockFrequency: " << d.getMaxClockFrequency() << " MHz\n"
                "    AddressBits: " << d.getAddressBits() << " bits\n"
                "    MaxMemAllocSize: " << d.getMaxMemAllocSize() << " bytes\n"
                "    IsImageSupport: " << (isImageSupport?"Yes":"No") << "\n";
            if (isImageSupport)
            {
                std::cout <<
                "    MaxReadImageArgs: " << d.getMaxReadImageArgs() << "\n"
                "    MaxWriteImageArgs: " << d.getMaxWriteImageArgs() << "\n"
#if __CLPP_CL_VERSION>=200
                "    MaxReadWriteImageArgs: " << d.getMaxReadWriteImageArgs() << "\n"
#endif
                ;
                {
                    size_t w,h,z;
                    d.getImage2DMaxSizes(w, h);
                    std::cout << "    MaxImage2DMaxSizes: " << w << "x" << h << " pixels\n";
                    d.getImage3DMaxSizes(w, h, z);
                    std::cout << "    MaxImage3DMaxSizes: " << w << "x" << h <<
                            "x" << z << " pixels\n";
                }
#if __CLPP_CL_VERSION >= 102U
                std::cout <<
                    "    ImageMaxBufferSize: " << d.getImageMaxBufferSize() << " pixels\n"
                    "    ImageMaxArraySize: " << d.getImageMaxArraySize() << " images\n"
                    "    ImagePitchAlignment: " << d.getImagePitchAlign() << " pixels\n"
                    "    ImageBaseAddressAlignment: " << d.getImageBaseAddrAlign() <<
                            " pixels\n";
#endif
            }
            std::cout <<
#if __CLPP_CL_VERSION >= 200U
                "    MaxPipeArgs: " << d.getMaxPipeArgs() << "\n"
                "    PipeMaxActiveReservations: " << d.getPipeMaxActiveReservations() << "\n"
                "    PipeMaxPacketSize: " << d.getPipeMaxPacketSize() << " bytes\n"
#endif
                "    MemBaseAddrAlign: " << d.getMemBaseAddrAlign() << " bits\n"
                "    MinDataTypeAlignSize: " << d.getMinDataTypeAlignSize() << " bytes\n"
                "    MaxSamplers: " << d.getMaxSamplers() << "\n"
                "    MaxParameterSize: " << d.getMaxParameterSize() << " bytes\n"
                "    SingleFPConfig: " << getFPConfigDesc(d.getSingleFPConfig()) << "\n"
#if __CLPP_CL_VERSION >= 102U || defined(__CLPP_CL_EXT)
                "    DoubleFPConfig: " << getFPConfigDesc(d.getDoubleFPConfig()) << "\n"
#endif
#ifdef __CLPP_CL_EXT
                "    HalfFPConfig: " << getFPConfigDesc(d.getHalfFPConfig()) << "\n"
#endif
                "    GlobalCacheType: " << getCacheTypeDesc(d.getGlobalMemCacheType()) << "\n"
                "    GlobalMemCacheLineSize: " << d.getGlobalMemCacheLineSize() << " bytes\n"
                "    GlobalMemCacheSize: " << d.getGlobalMemCacheSize() << " bytes\n"
                "    GlobalMemSize: " << d.getGlobalMemSize() << " bytes\n"
                "    MaxConstantBufferSize: " << d.getMaxConstantBufferSize() << " bytes\n"
                "    MaxConstantArgs: " << d.getMaxConstantArgs() << "\n"
#if __CLPP_CL_VERSION >= 200U
                "    MaxGlobalVariableSize: " << d.getMaxGlobalVariableSize() << "\n"
                "    GlobalVariablePreferredTotalSize: " <<
                        d.getGlobalVariablePreferredTotalSize() << "\n"
#endif
                "    LocalMemType: " << getLocalMemTypeDesc(d.getLocalMemType()) << "\n"
                "    LocalMemSize: " << d.getLocalMemSize() << "\n"
                "    ErrorCorrectionSupport: " <<
                        (d.isErrorCorrectionSupport()?"Yes":"No") << "\n"
#if __CLPP_CL_VERSION >= 101U
                "    HostUnifiedMemory: " << (d.isHostUnifiedMemory()?"Yes":"No") << "\n"
#endif
                "    ProfilingTimerResolution: " << d.getProfilingTimerResolution() << "\n"
                "    EndianLittle: " << (d.isEndianLittle()?"Yes":"No") << "\n"
                "    Available: " << (d.isAvailable()?"Yes":"No") << "\n"
                "    CompilerAvailable: " << (d.isCompilerAvailable()?"Yes":"No") << "\n"
#if __CLPP_CL_VERSION >= 102U
                "    LinkerAvailable: " << (d.isLinkerAvailable()?"Yes":"No") << "\n"
#endif
                "    ExecCapabilities: " <<
                        getExecCapabilitiesDesc(d.getExecCapabilities()) << "\n"
                "    QueueProperties: " << getCommandQueuePropsDesc(
                            d.getQueueProperties()) << "\n"
#if __CLPP_CL_VERSION >= 200U
                "    QueueOnHostProperties: " << getCommandQueuePropsDesc(
                            d.getQueueOnHostProperties()) << "\n"
                "    QueueOnDeviceProperties: " << getCommandQueuePropsDesc(
                            d.getQueueOnDeviceProperties()) << "\n"
                "    QueueOnDevicePreferredSize: " << d.getQueueOnDevicePreferredSize() << "\n"
                "    QueueOnDeviceMaxSize: " << d.getQueueOnDeviceMaxSize() << "\n"
                "    MaxOnDevicesQueues: " << d.getMaxOnDevicesQueues() << "\n"
                "    MaxOnDevicesEvents: " << d.getMaxOnDevicesEvents() << "\n"
#endif
#if __CLPP_CL_VERSION >= 102U
                "    BuilInKernels: " << d.getBuilInKernels() << "\n"
#endif
                "    Vendor: " << d.getVendor() << "\n"
                "    Profile: " << d.getProfile() << "\n"
                "    DriverVersion: " << d.getDriverVersion() << "\n"
                "    Version: " << d.getVersion() << "\n"
#if __CLPP_CL_VERSION >= 101U
                "    OpenCLCVersion: " << d.getOpenCLCVersion() << "\n"
#endif
                "    Extensions: " << d.getExtensions() << "\n"
#if __CLPP_CL_VERSION >= 102U
                "    PrintfBufferSize: " << d.getPrintfBufferSize() << "\n"
                "    PreferredInterOpUserSync: " <<
                        (d.isPreferredInterOpUserSync()?"Yes":"No") << "\n"
#endif
#if __CLPP_CL_VERSION >= 200U
                "    SVMCapabilities: " << d.getSVMCapabilities() << "\n"
                "    PreferredPlatformAtomicAlignment: " <<
                        d.getPreferredPlatformAtomicAlign() << "\n"
                "    PreferredGlobalAtomicAlignment: " <<
                        d.getPreferredGlobalAtomicAlign() << "\n"
                "    PreferredLocalAtomicAlignment: " <<
                        d.getPreferredLocalAtomicAlign() << "\n";
#endif
                ;
        }
        std::cout.flush();
    }
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
