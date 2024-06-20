cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(secret-manager)

set(SOURCES
        src/main.cpp
        src/App.cpp
        src/MainFrame.cpp
        src/SecretManager.cpp
        src/SecretDialog.cpp
)

find_package(SQLite3 REQUIRED)

add_executable(secret-manager ${SOURCES})
target_link_libraries(secret-manager wx::net wx::core wx::base SQLite::SQLite3)