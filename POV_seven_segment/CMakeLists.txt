cmake_minimum_required(VERSION 3.28)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_C_COMPILER avr-gcc CACHE STRING "C Compiler" FORCE)
set(CMAKE_CXX_COMPILER avr-g++ CACHE STRING "C++ Compiler" FORCE)
set(CMAKE_OBJCOPY	avr-objcopy	CACHE STRING "avr-objcopy" FORCE)
set(CMAKE_C_FLAGS	"-mmcu=atmega32 -O1	-DF_CPU=8000000ULL")
###################################################################
project(AVR_FIRST C)
file(GLOB_RECURSE SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"	*.c *.h) 
# message("${SRCS}")
string(REGEX REPLACE "build/[^;]+;?" "" SRCS "${SRCS}")
message("${PROJECT_NAME}")

add_executable(${PROJECT_NAME}.elf ${SRCS})
#formating
add_custom_target(flash ALL
				DEPENDS ${PROJECT_NAME}.elf
				COMMAND avr-objcopy -j .text -j .data -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
				)
				
				
add_custom_target(burn
				DEPENDS flash
				COMMAND avrdude.exe -c usbasp -p m32 -B 0.5 -U flash:w:"${PROJECT_NAME}.hex":a
				)

# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED True)

# set(SRC_FILES
    # main.c
    # src/calc.c )
	
# # set(SRC_FILES "main.c;src/calc.c" )
# set (p $ENV{PATH})




# # message(STATUS "pathe = $ENV{PATH}")
# # message(STATUS " path is ${CMAKE_SOURCE_DIR}")
# # message(STATUS " vlaue is ${XX}")
# # message(" standard is ${CMAKE_C_STANDARD_REQUIRED}")

# # if(EXISTS ${CMAKE_SOURCE_DIR}/main.c)
	# # message("here")
# # else()
	# # message("not here")
# # endif()

# if(DEBUG)
	# set(DEBUGINFO "Raghad Islam")
# endif()

# # foreach(I IN ITEMS R A G H A D)
	# # message(STATUS ${I})
# # endforeach()
# # set(VAR 10)
# # while(VAR)
# # message("${VAR}")
# # math(EXPR VAR "${VAR} - 1")
# # endwhile()

# # function(func arg1)
# # message("${arg1}")
# # message("${${arg1}}")
# # message("${ARGN}")
# # message("${ARGC}")

# # endfunction()

# # set(lista 1 2 3 4 5 6 7 8)
# # func(lista "raghad" "rahaf")

# # set(VAR2 TRUE CACHE BOOL "VAR1 Is BOOL")
# # message("var 1 is ${VAR2}")

# add_subdirectory(${CMAKE_SOURCE_DIR}/lib)

# add_executable(hellobinary ${SRC_FILES})

# target_compile_definitions(hellobinary PUBLIC "STD_C=20")
# target_compile_options(hellobinary PUBLIC -march=native)

# install(FILES "${PROJECT_BINARY_DIR}/hellobinary.exe"
		# DESTINATION "${PROJECT_BINARY_DIR}/executable")
		
		
# install(FILES 
		# "${CMAKE_SOURCE_DIR}/include/calc.h"
		# "${CMAKE_SOURCE_DIR}/lib/wifi.h"
		# DESTINATION "${PROJECT_BINARY_DIR}/include")
		
# # FILE

# # FILE(READ "main.c" MAIN_FILE)
# # message("${MAIN_FILE}")

# # FILE(STRINGS "main.c" MAIN_FILE)
# # message("${MAIN_FILE}")

# # why would I want
# # FILE(STRINGS "main.c" MAIN_FILE REGEX "^int.") # set in the variable any line that sterts with int to the end of that line
# # FILE(STRINGS "main.c" MAIN_FILE REGEX "int.") # set in the variable any line that contains int in the beginning with int to the end of that line
# # message("${MAIN_FILE}")

# # file(GLOB_RECURSE SRCS "*.c") # from where i stand. find all files.c and put them in SRCS variable
# # message("${SRCS}")
# ####################################################################################################################

# # string

# # FILE(READ "main.c" MAIN_FILE)
# # STRING(REGEX REPLACE "mo" "uu" OUT ${MAIN_FILE})
# # message("${OUT}")
# ####################################################################################################################


# # function and macro
# # set(Global_var	12)
# # macro(runMacro var)
# # message("${var}")
# # message("${${var}}")
# # set(Global_var	10)
# # endmacro()

# # set(x 9)

# # message("${Global_var}")
# # runMacro(x)
# # message("${Global_var}") # will print 10 not 12
# # ---------------------------------------------------

# # set(Global_var	12)
# # function(runfunction var)
# # message("${var}")
# # message("${${var}}")
# # set(Global_var	10)
# # endfunction()

# # set(x 9)

# # message("${Global_var}")
# # runfunction(x)
# # message("${Global_var}") # will print 12 not 10
# # -----------------------------------------------------

# # set(Global_var	12)
# # function(runfunction var)
# # message("${var}")
# # message("${${var}}")
# # set(Global_var	10 PARENT_SCOPE)
# # endfunction()

# # set(x 9)

# # message("${Global_var}")
# # runfunction(x)
# # message("${Global_var}") # will print 10

# ##############################################################
# # execute_process()
# # execute_process(COMMAND "ls")

# set(CMAKE_PREFIX_PATH "C:/Program Files/vcpkg/vcpkg/installed/x64-windows/share")
# # find_package(fmt CONFIG REQUIRED)

# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(hellobinary PRIVATE fmt::fmt)


# set(PRODUCT_YEAR	"2025")
# configure_file(defaultconfig.h.in  defaultconfig.h)

# target_include_directories(hellobinary PUBLIC include/ lib/ ${PROJECT_BINARY_DIR})
# target_link_libraries(hellobinary PUBLIC wifi_lib)
# # target_link_libraries(hellobinary PRIVATE fmt)


