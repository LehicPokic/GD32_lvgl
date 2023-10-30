cmake_minimum_required(VERSION 3.5)
project(gd32f4_sys LANGUAGES C CXX ASM)

add_library(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME} SYSTEM PUBLIC . CMSIS CMSIS/GD/GD32F4xx/Include
                         GD32F4xx_standard_peripheral/Include)
file(GLOB SPL_SRCS GD32F4xx_standard_peripheral/Source/*)
# target_compile_options(${PROJECT_NAME} PRIVATE -Wno-register)

target_sources(${PROJECT_NAME} PRIVATE ${SPL_SRCS} startup_f470_gnu.s
                                       system_f470.c)
                                       
