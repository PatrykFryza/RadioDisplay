#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit "VARIABLES"-section to suit project requirements.
#        For debug build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug VERBOSE=1
#        For release build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
#          make -C Release VERBOSE=1
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)

###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
set (MCPU_CORTEX_M0				      "-mcpu=cortex-m0")
set (MCPU_CORTEX_M0PLUS				  "-mcpu=cortex-m0plus")
set (MCPU_CORTEX_M3				      "-mcpu=cortex-m3")
set (MCPU_CORTEX_M4				      "-mcpu=cortex-m4")
set (MCPU_CORTEX_M7				      "-mcpu=cortex-m7")
set (MCPU_CORTEX_M33				  "-mcpu=cortex-m33")
set (MCPU_CORTEX_M55				  "-mcpu=cortex-m55")
set (MCPU_CORTEX_M85				  "-mcpu=cortex-m85")
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_STD_C            "")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################

###################### VARIABLES ######################################
set (PROJECT_NAME             "RadioDisplay")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "../STM32F429ZITX_FLASH.ld")
set (MCPU                     "-mcpu=Cortex-M4")
set (MFPU                 "-mfpu=fpv4-sp-d16")
set (MFLOAT_ABI               "")
set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")


set (PROJECT_SOURCES
	# LIST SOURCE FILES HERE
	Startup/startup_stm32f429zitx.s
	src/main.c
	src/init.c
	src/syscalls.c
	src/sysmem.c
	src/system_stm32f4xx.c
	libs/system_periph/stm32f4xx_rcc.c
	libs/system_periph/stm32f4xx_spi.c
	libs/system_periph/stm32f4xx_gpio.c
	libs/system_periph/stm32f4xx_dma.c
	libs/system_periph/stm32f4xx_tim.c
	libs/system_periph/misc.c
	libs/display/tm_stm32f4_gpio.c
	libs/display/tm_stm32f4_delay.c
	libs/display/tm_stm32f4_spi.c
	libs/display/tm_stm32f4_dma.c
	libs/display/tm_stm32f4_spi_dma.c
	libs/display/tm_stm32f4_fonts.c
	libs/display/tm_stm32f4_ili9341.c
	libs/display/tm_stm32f4_stmpe811.c
	libs/display/tm_stm32f4_timer_properties.c
	libs/ll_lib/src/stm32f4xx_ll_exti.c
	libs/ll_lib/src/stm32f4xx_ll_gpio.c
	libs/ll_lib/src/stm32f4xx_ll_rcc.c
	libs/ll_lib/src/stm32f4xx_ll_utils.c
	libs/ll_lib/src/stm32f4xx_ll_i2c.c
	libs/ll_lib/src/stm32f4xx_ll_spi.c
	libs/rf/nRF24.c
	

	)

set (PROJECT_DEFINES
	# LIST COMPILER DEFINITIONS HERE

    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
	inc
	libs/display
	libs/cmsis
	libs/system_periph
	libs/ll_lib/inc
	libs/rf
    )

############ MODIFY ACCORDING TO REQUIREMENTS) ########################

#######################################################################

################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(ASM)

if (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_EXECUTABLE})
  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
elseif (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
  add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=test.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
