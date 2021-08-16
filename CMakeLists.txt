cmake_minimum_required(VERSION 3.20)
project(blocky)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(SOURCES
    src/main.cpp
    src/Block.cpp
    src/Blockchain.cpp
    src/Transaction.cpp
    src/Wallet.hpp
    src/utils/Crypto.cpp
    src/utils/SignatureKeypair.cpp)

add_executable(blocky ${SOURCES})

# Top level include directories
target_include_directories(blocky PRIVATE src)

# Dependencies
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(LIBSODIUM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libsodium)
    target_include_directories(blocky PRIVATE ${LIBSODIUM_DIR}/include)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(blocky PRIVATE ${LIBSODIUM_DIR}/x64/Debug/v142/dynamic/libsodium.lib)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_libraries(blocky PRIVATE ${LIBSODIUM_DIR}/x64/Release/v142/dynamic/libsodium.lib)
    endif()
endif()

# Copy necessary Dlls to the executable location
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(
            TARGET blocky
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${LIBSODIUM_DIR}/x64/Debug/v142/dynamic/libsodium.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libsodium.dll"
        )
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(
            TARGET quasar
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${LIBSODIUM_DIR}/x64/Release/v142/dynamic/libsodium.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libsodium.dll"
        )
    endif()
endif()
