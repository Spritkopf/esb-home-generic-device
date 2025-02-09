cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchain/toolchain_arm_cm4f.cmake)
project(esb-home-generic-device-fw C ASM)


set(NRF_SDK_HOME "${PROJECT_SOURCE_DIR}/lib/nrf5_sdk")

add_subdirectory(src)
add_subdirectory(lib)
