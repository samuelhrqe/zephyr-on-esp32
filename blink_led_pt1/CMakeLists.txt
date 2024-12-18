cmake_minimum_required(VERSION 3.20.0)

set(BOARD esp32_devkitc_wroom)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(blink_led_pt1)

target_sources(app PRIVATE src/main.c)