
# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

set(wxWidgets_LIBRARIES
        wx::net
        wx::core
        wx::base
)

if (APPLE AND NOT CMAKE_OSX_DEPLOYMENT_TARGET)
    # If no deployment target has been set default to the minimum supported
    # OS version (this has to be set before the first project() call)
    if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0 CACHE STRING "iOS Deployment Target")
    else ()
        set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10 CACHE STRING "macOS Deployment Target")
    endif ()
endif ()

# Name the project
project(SecretManager)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Request the required wxWidgets libs
#find_package(wxWidgets 3.3 COMPONENTS core base REQUIRED CONFIG)

# Define a variable containing a list of source files for the project
set(SRC_FILES
        src/main.cpp
        src/App.cpp
        src/MainFrame.cpp
        src/SecretManager.cpp
        src/SecretDialog.cpp
)

find_package(SQLite3 REQUIRED)
#find_package(CURL REQUIRED)

if (WIN32)
    # Include a RC file for windows
    list(APPEND SRC_FILES ../third_party/wxWidgets/samples/sample.rc)
elseif (APPLE)
    # Add an icon for the apple .app file
    list(APPEND SRC_FILES ../third_party/wxWidgets/samples/../src/osx/carbon/wxmac.icns)
endif ()

# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SRC_FILES})
# Link executable to the wxWidgets target
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES}
        SQLite::SQLite3
#        CURL::libcurl
)

if (MSVC)
    # Use manifest from wx.rc
    set_target_properties(${PROJECT_NAME} PROPERTIES
            COMPILE_FLAGS "/DwxUSE_RC_MANIFEST"
            LINK_FLAGS "/MANIFEST:NO"
    )
elseif (APPLE)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "little-tools.secret-manager")
#    set(CMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "YOUR_TEAM_ID")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            RESOURCE "../third_party/wxWidgets/samples/../src/osx/carbon/wxmac.icns"
            MACOSX_BUNDLE_ICON_FILE wxmac.icns
            MACOSX_BUNDLE_COPYRIGHT "Copyright wxWidgets"
            MACOSX_BUNDLE_GUI_IDENTIFIER "org.wxwidgets.minimal"
    )
endif ()
