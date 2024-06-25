cmake_minimum_required(VERSION 3.12)

# Establecer la ruta al SDK de Pico
set(PICO_SDK_PATH "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk")
# Establecer la ruta al archivo de herramientas de cadena de herramientas
set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk/cmake/preload/toolchains/pico_arm_gcc.cmake")
# Establecer el programa de construcción (Ninja en este caso)
set(CMAKE_MAKE_PROGRAM "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/ninja/ninja.exe")

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)


project(tp2 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(tp2_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()




