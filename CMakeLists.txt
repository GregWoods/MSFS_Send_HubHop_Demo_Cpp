cmake_minimum_required(VERSION 3.14)
project(MSFS_G1000_WAPI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    MSFS_G1000_WAPI.cpp
    # Add other source files as needed
)

add_executable(${PROJECT_NAME} ${SOURCES})

# User-configurable paths (edit these as needed)
set(SIMCONNECT_SDK_INCLUDE "C:/MSFS 2024 SDK/SimConnect SDK/include" CACHE PATH "SimConnect SDK include directory")
set(SIMCONNECT_SDK_LIB "C:/MSFS 2024 SDK/SimConnect SDK/lib/static" CACHE PATH "SimConnect SDK library directory")
set(FSUIPC_WAPI_INCLUDE "./FSUIPC_WAPI/include" CACHE PATH "FSUIPC_WAPI include directory")
set(FSUIPC_WAPI_LIB "./FSUIPC_WAPI/lib" CACHE PATH "FSUIPC_WAPI library directory")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SIMCONNECT_SDK_INCLUDE}
    ${FSUIPC_WAPI_INCLUDE}
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${SIMCONNECT_SDK_LIB}
    ${FSUIPC_WAPI_LIB}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SimConnect
    $<$<CONFIG:Debug>:FSUIPC_WAPI_debug>
    $<$<CONFIG:Release>:FSUIPC_WAPI>
      ws2_32
      shlwapi
  )