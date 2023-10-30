project(GD32_lvgl LANGUAGES C CXX ASM)


include_directories(${CMAKE_SOURCE_DIR}/Core/include)
include_directories(${CMAKE_SOURCE_DIR})


add_executable(${PROJECT_NAME} 
      ${CMAKE_SOURCE_DIR}/Core/Src/main.cpp
      ${CMAKE_SOURCE_DIR}/Core/Src/ST7789S.c
      ${CMAKE_SOURCE_DIR}/Core/Src/ST7789S_driver.c
      ${CMAKE_SOURCE_DIR}/Core/Src/systick.c
)

target_link_options(${PROJECT_NAME} PRIVATE -T${CMAKE_SOURCE_DIR}/GD32F470ZKT_MAIN_DEBUG.ld)


link_directories(
      ${CMAKE_SOURCE_DIR}/lvgl
      ${CMAKE_SOURCE_DIR}/lvgl/examples
      ${CMAKE_SOURCE_DIR}/gd32f4_sys
      
)

target_link_libraries(${PROJECT_NAME} lvgl lvgl_examples gd32f4_sys)


set(LV_CONF_PATH
        ${CMAKE_SOURCE_DIR}/lv_conf.h
        CACHE STRING "" FORCE)



add_custom_target(
  ${PROJECT_NAME}.hex ALL
  COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
  DEPENDS ${PROJECT_NAME}.elf)
  
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND arm-none-eabi-nm --print-size --reverse-sort --size-sort --radix=d
  ${PROJECT_NAME}.elf > mem.txt)
