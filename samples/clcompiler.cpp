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
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <clpp.h>

static void listPlatformsAndDevices()
{
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    for (size_t i = 0; i < platforms.size(); i++)
    {
        const clpp::Platform platform = platforms[i];
        const std::vector<clpp::Device> devices = platform.getAllDevices();
        std::cout << i << ": " << platform.getName() << "\n";
        for (size_t j = 0; j < devices.size(); j++)
            std::cout << "  " << j << ": " << devices[j].getName() << "\n";
    }
    std::cout.flush();
}

int main(int argc, const char** argv)
try
{
    std::string options;
    cl_uint platformNum;
    cl_uint deviceNum;
    
    std::vector<std::string> filesToCompile;
    
    for (int i = 1; i < argc; i++)
    {
        const std::string arg = (argv[i]);
        
        std::string optArg;
        if (!arg.empty() && arg[0] == '-' && (arg[1] == 'P' || arg[1] == 'D' ||
            arg[1] == 'O'))
        {   // get option argument
            if (arg.size() > 2)
                optArg = arg.substr(2);
            else
            {
                if (i+1 >= argc)
                {
                    std::cerr << "No required argument for " << arg << std::endl;
                    return 1;
                }
                optArg = argv[i+1];
                i++;
            }
        }
        if (arg == "--platform" || arg == "--device" || arg == "--options")
        {   // get long option argument
            if (i+1 >= argc)
            {
                std::cerr << "No required argument for " << arg << std::endl;
                return 1;
            }
            optArg = argv[i+1];
            i++;
        }
        
        if (arg == "-L" || arg == "--list")
        {
            listPlatformsAndDevices();
            return 0;
        }
        else if (arg == "-?" || arg == "--help")
        {   // help
            std::cout << "Usage: clcompiler [OPTIONS] FILE...\n"
            "\n"
            "Options:\n"
            " -L, --list               list devices\n"
            " -P, --platform PNUM      set platform number\n"
            " -D, --device DNUM        set device number\n"
            " -O, --options COMPOPTS   set compiler options\n"
            " -?, --help               print this help\n";
            std::cout.flush();
            return 0;
        }
        else if (arg.substr(0, 2) == "-P" || arg == "--platform")
        {   // get platform number (in order list)
            std::istringstream iss(optArg);
            iss.exceptions(std::ios::failbit);
            try
            { iss >> platformNum; }
            catch(const std::exception& ex)
            {
                std::cerr << "Can't parse platform number" << std::endl;
                return 1;
            }
        }
        else if (arg.substr(0, 2) == "-D" || arg == "--device")
        {   // get device number (in order list)
            std::istringstream iss(optArg);
            iss.exceptions(std::ios::failbit);
            try
            { iss >> deviceNum; }
            catch(const std::exception& ex)
            {
                std::cerr << "Can't parse platform number" << std::endl;
                return 1;
            }
        }
        else if (arg.substr(0, 2) == "-O" || arg == "--options")
            options = optArg;   // build options
        else if (!arg.empty() && arg[0] == '-')
        {   // unknown option
            std::cerr << "Unknown option: " << arg << std::endl;
            return 1;
        }
        else // file
            filesToCompile.push_back(arg);
    }
    
    const std::vector<clpp::Platform> platforms = clpp::Platform::get();
    if (platformNum >= platforms.size())
    {   // if platform number out of range
        std::cerr << "Platform number out of range" << std::endl;
        return 1;
    }
    const clpp::Platform platform = platforms[platformNum];
    const std::vector<clpp::Device> devices = platform.getAllDevices();
    if (deviceNum >= devices.size())
    {   // if device number out of range
        std::cerr << "Device number out of range" << std::endl;
        return 1;
    }
    const clpp::Device device = devices[deviceNum];
    const clpp::Context context(device);
    
    int ret = 0;
    for (size_t i = 0; i < filesToCompile.size(); i++)
    {
        try
        {
            const std::string& fileName = filesToCompile[i];
            
            std::cout << "Compiling " << fileName << "..." << std::endl;
            // determine output filename with .clo extension
            std::string outFileName = fileName;
            if (outFileName.size() >= 4 && outFileName.substr(outFileName.size()-3) == ".cl")
                outFileName += "o";
            else
                outFileName += ".clo";
            
            std::string source;
            {   // read source file
                std::ifstream ifs(fileName.c_str(), std::ios::binary);
                if (!ifs)
                {
                    std::cerr << "Can't open input file " << fileName << std::endl;
                    return 1;
                }
                ifs.exceptions(std::ios::badbit); // enable exception handling
                while (true)
                {
                    int c = ifs.get();
                    if (ifs.eof()) break; // ends if end-of-file
                    source.push_back(c); // push to source
                }
            }
            
            clpp::Program program(context, source);
            try // try to compile
            { program.build(device, options.c_str()); }
            catch(const clpp::Error& error)
            {
                if (!program.getDevices().empty()) // if devices set
                    std::cerr << "Source " << fileName << ":\n" <<
                            program.getBuildLog(device) << std::endl;
                throw;
            }
            const std::string buildLog = program.getBuildLog(device);
            if (!buildLog.empty())      // if build logs is not empty print them
                std::cerr << "Source " << fileName << ":\n" << buildLog << std::endl;
            
            {   // write output file
                std::ofstream ofs(outFileName.c_str(), std::ios::binary);
                if (!ofs)
                {
                    std::cerr << "Can't open output file " << outFileName << std::endl;
                    return 1;
                }
                ofs.exceptions(std::ios::badbit);
                
                std::vector<std::vector<unsigned char> > binaries = program.getBinaries();
                // binaries
                ofs.write(reinterpret_cast<const char*>(&(binaries[0][0])), binaries[0].size());
                ofs.flush();
            }
        }
        catch(const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
            ret = 1;
        }
        catch(...)
        {
            std::cerr << "Unknown exception!" << std::endl;
            ret = 1;
        }
    }
    
    return ret;
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
