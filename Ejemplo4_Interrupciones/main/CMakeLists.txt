add_executable(main
        main.c
        LCD.c
        )

# pull in common dependencies
target_link_libraries(main pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(main)

# add url via pico_set_program_url

