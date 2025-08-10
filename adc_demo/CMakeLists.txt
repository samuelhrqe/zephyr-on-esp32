cmake_minimum_required(VERSION 3.20.0)

set(BOARD esp32_devkitc_wroom)

set(BOARD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boards)
set(DTC_OVERLAY_FILE ${BOARD_DIR}/esp32_devkitc_wroom.overlay)
set(EXTRA_CONF_FILE ${BOARD_DIR}/esp32_devkitc_wroom.conf)
# set(EXTRA_DTC_OVERLAY_FILE ${BOARD_DIR}/esp32_devkitc_wroom.overlay)
# set(CONF_FILE "${BOARD_DIR}/esp32_devkitc_wroom.conf" "${CMAKE_CURRENT_SOURCE_DIR}/prj.conf")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(adc_demo)

target_sources(app PRIVATE src/main.c)

message(STATUS "Board: ${BOARD}")
message(STATUS "Devicetree Overlay: ${DTC_OVERLAY_FILE}")
message(STATUS "Extra Config File: ${EXTRA_CONF_FILE}")