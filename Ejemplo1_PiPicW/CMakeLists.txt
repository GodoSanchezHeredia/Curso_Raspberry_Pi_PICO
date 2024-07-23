cmake_minimum_required(VERSION 3.12)

# Establecer la ruta al SDK de Pico
set(PICO_SDK_PATH "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk")

# Establecer la ruta al archivo de herramientas de cadena de herramientas
set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/pico-sdk/cmake/preload/toolchains/pico_arm_gcc.cmake")

# Establecer el programa de construcción (Ninja en este caso)
set(CMAKE_MAKE_PROGRAM "C:/Program Files/Raspberry Pi/Pico SDK v1.5.1/ninja/ninja.exe")

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

include(pico_sdk_import.cmake)
project(ejemplo1_pipicw C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

pico_enable_stdio_usb(ejemplo1_pipicw 1)
pico_enable_stdio_uart(ejemplo1_pipicw 1)
pico_add_extra_outputs(ejemplo1_pipicw)
target_include_directories(ejemplo1_pipicw PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(ejemplo1_pipicw pico_cyw43_arch_lwip_threadsafe_background pico_stdlib)