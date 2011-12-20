/*  Copyright 2011, The Ready Bunch

    This file is part of Ready.

    Ready is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ready is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ready. If not, see <http://www.gnu.org/licenses/>.         */

#ifndef __OPENCL_RD__
#define __OPENCL_RD__

// local:
#include "BaseRD.hpp"

// OpenCL:
#if defined(__APPLE__) || defined(__MACOSX)
 #include <OpenCL/opencl.h>
#else
 // load OpenCL dynamically
 #include "OpenCL_Dyn_Load.h"
#endif

// base class for those RD implementations that use OpenCL
class OpenCL_RD : public BaseRD
{
    public:

        OpenCL_RD();
        ~OpenCL_RD();

        bool HasEditableProgram() const { return true; }

        void SetPlatform(int i);
        void SetDevice(int i);
        int GetPlatform() const;
        int GetDevice() const;
        static std::string GetOpenCLDiagnostics();
        static int GetNumberOfPlatforms();
        static int GetNumberOfDevices(int iPlatform);
        static std::string GetPlatformDescription(int iPlatform);
        static std::string GetDeviceDescription(int iPlatform,int iDevice);

        void TestProgram(std::string program_string) const;

    protected:

        void ReloadContextIfNeeded();
        void ReloadKernelIfNeeded();

        void CreateOpenCLBuffers();
        void WriteToOpenCLBuffers();
        void ReadFromOpenCLBuffers();

        void Update2Steps();

        static cl_int LinkOpenCL();
        static void throwOnError(cl_int ret,const char* message);
        static const char* descriptionOfError(cl_int err);

    private:

        // OpenCL things for re-use
        cl_device_id device_id;
        cl_context context;
        cl_command_queue command_queue;
        cl_kernel kernel;
        cl_mem buffer1,buffer2;
        size_t global_range[3],local_range[3];

        std::string kernel_function_name;

        int iPlatform,iDevice;
        bool need_reload_context;
};

#endif