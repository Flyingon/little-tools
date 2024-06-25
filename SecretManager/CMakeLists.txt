cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(SecretManager)

# 设置变量以区分平台
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(PLATFORM_WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(PLATFORM_MAC TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(PLATFORM_IOS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(PLATFORM_ANDROID TRUE)
endif ()

# 查找并包含必要的库
if (PLATFORM_WINDOWS)
    find_package(SQLite3 REQUIRED)
    find_package(CURL REQUIRED)
    include(${wxWidgets_USE_FILE})
elseif (PLATFORM_MAC OR PLATFORM_IOS)
    find_package(SQLite3 REQUIRED)
    find_package(CURL REQUIRED)
elseif (PLATFORM_ANDROID)
    find_library(log-lib log)
    find_package(SQLite3 REQUIRED)
    find_package(CURL REQUIRED)
endif ()

set(SOURCES
        src/main.cpp
        src/App.cpp
        src/MainFrame.cpp
        src/SecretManager.cpp
        src/SecretDialog.cpp
)

set(wxWidgets_LIBRARIES
        wx::net
        wx::core
        wx::base
)


add_executable(secret-manager ${SOURCES})
#target_link_libraries(secret-manager wx::net wx::core wx::base SQLite::SQLite3)

# 链接库
if (PLATFORM_WINDOWS)
    target_link_libraries(secret-manager ${wxWidgets_LIBRARIES} SQLite::SQLite3 CURL::libcurl)
elseif (PLATFORM_MAC)
    target_link_libraries(secret-manager ${wxWidgets_LIBRARIES} SQLite::SQLite3 CURL::libcurl)
    set_target_properties(secret-manager PROPERTIES
            MACOSX_BUNDLE YES
    )
    # 添加资源文件
    set(RESOURCE_FILES
#            assets/LaunchScreen.storyboard
#            assets/Images.xcassets
    )
    foreach (RESOURCE ${RESOURCE_FILES})
        add_custom_command(TARGET secret-manager POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${RESOURCE} $<TARGET_FILE_DIR:secret-manager>/)
    endforeach ()
    # 设置 Info.plist
    set_target_properties(secret-manager PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/assets/Info.plist
    )
elseif (PLATFORM_IOS)
    target_link_libraries(secret-manager ${wxWidgets_LIBRARIES} SQLite::SQLite3 CURL::libcurl)
    set_target_properties(secret-manager PROPERTIES
            MACOSX_BUNDLE YES
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"  # 1 = iPhone, 2 = iPad
    )
    # 添加资源文件
    set(RESOURCE_FILES
#            assets/LaunchScreen.storyboard
#            assets/Images.xcassets
    )
    foreach (RESOURCE ${RESOURCE_FILES})
        add_custom_command(TARGET secret-manager POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${RESOURCE} $<TARGET_FILE_DIR:secret-manager>/)
    endforeach ()
    # 设置 Info.plist
    set_target_properties(secret-manager PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/assets/Info.plist
    )
elseif (PLATFORM_ANDROID)
    target_link_libraries(secret-manager ${log-lib} SQLite::SQLite3 CURL::libcurl)
endif ()