cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(little-tools)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()

add_subdirectory(./SecretManager)
add_subdirectory(./third_party/wxWidgets)