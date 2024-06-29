# Toolchain for cross-compiling to iOS

# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Specify the target platform
set(CMAKE_SYSTEM_NAME iOS)

# Detect if we are building for the simulator
if(CMAKE_OSX_SYSROOT MATCHES "iphonesimulator")
    set(IOS_PLATFORM "iphonesimulator")
else()
    set(IOS_PLATFORM "iphoneos")
endif()

# Specify the minimum iOS version
set(CMAKE_OSX_DEPLOYMENT_TARGET "9.0")

# Specify the architectures to build for
if(IOS_PLATFORM STREQUAL "iphonesimulator")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

# Set the sysroot to the appropriate iOS SDK
set(CMAKE_OSX_SYSROOT ${IOS_PLATFORM})

# Specify the C and C++ compilers
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
