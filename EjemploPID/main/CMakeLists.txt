add_executable(main
        main.c
        PID.c
        )

# pull in common dependencies
target_link_libraries(main pico_stdlib hardware_i2c)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
# create map/bin/hex file etc.
pico_add_extra_outputs(main)

# add url via pico_set_program_url

