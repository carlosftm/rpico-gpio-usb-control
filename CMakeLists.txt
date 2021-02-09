add_executable(gpio-usb-control
        rpico-gpio-usb-control.c
        )

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(gpio-usb-control pico_stdlib hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(gpio-usb-control 1)
pico_enable_stdio_uart(gpio-usb-control 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(gpio-usb-control)

# add url via pico_set_program_url
example_auto_set_url(gpio-usb-control)
