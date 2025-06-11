cmake_minimum_required(VERSION 3.20)

set(EXTRA_CONF_FILE "boards/esp32_devkitc_wroom.conf")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(random_generator)

target_sources(app PRIVATE
    src/main.c
)