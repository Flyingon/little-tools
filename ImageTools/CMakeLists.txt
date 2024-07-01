
# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.20)


# Name the project
project(ImageTools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(wxWidgets_LIBRARIES
        wx::net
        wx::core
        wx::base
)

# Request the required wxWidgets libs
#find_package(wxWidgets 3.3 COMPONENTS core base REQUIRED CONFIG)

# Define a variable containing a list of source files for the project
set(SRC_FILES
        src/main.cpp
)


add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES}
)

add_executable(pngsplit src/pngslit.cpp)
target_link_libraries( pngsplit ${OpenCV_LIBS} )
