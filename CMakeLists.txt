cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH "/home/eber/raspPicoSDK/pico-sdk")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PICO_SDK_FETCH_FROM_GIT 1)

include(pico_sdk_import.cmake)

pico_sdk_init()


project(RP2040-Zero-gamecube-controller CXX C)
include_directories(include pico-joybus-comms/include)
add_executable(
  RP2040-Zero-gamecube-controller
  src/main.cpp
  src/communication_protocols/joybus.cpp
  src/dac_algorithms/melee_F1.cpp
  src/gpio_to_button_sets/F1.cpp
  src/other/runtime_remapping_mode.cpp
)
target_compile_definitions(RP2040-Zero-gamecube-controller PRIVATE ULT_2IP_WITH_REAC=0)
pico_generate_pio_header(RP2040-Zero-gamecube-controller ${CMAKE_CURRENT_LIST_DIR}/pio/my_pio.pio)
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/my_pio.pio.h
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/my_pio.pio
        COMMAND Pioasm ${CMAKE_CURRENT_LIST_DIR}/my_pio.pio ${CMAKE_CURRENT_LIST_DIR}/generated/my_pio.pio.h
        )
target_link_libraries(RP2040-Zero-gamecube-controller pico_stdlib hardware_adc hardware_pio pico_time pico_bootrom hardware_resets hardware_timer hardware_irq hardware_sync hardware_flash)
pico_add_extra_outputs(RP2040-Zero-gamecube-controller)
