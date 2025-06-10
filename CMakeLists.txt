cmake_minimum_required(VERSION 3.10)
project(ngopi LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively find all .cpp files in src directory
file(GLOB_RECURSE NGOPI_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Define the executable output name based on platform
if(WIN32)
    set(EXECUTABLE_NAME ngopi.exe)
else()
    set(EXECUTABLE_NAME ngopi)
endif()

add_executable(${EXECUTABLE_NAME} ${NGOPI_SOURCES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/core/crypto
    ${CMAKE_SOURCE_DIR}/src/optionals
    ${CMAKE_SOURCE_DIR}/src/shared
    ${CMAKE_SOURCE_DIR}/src/tool
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/vm
)

# Platform-specific settings (optional, can be extended)
if(WIN32)
    # Windows-specific settings
elseif(APPLE)
    # macOS-specific settings
elseif(UNIX)
    # Linux-specific settings
endif()
