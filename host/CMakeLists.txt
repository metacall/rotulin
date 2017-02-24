#
# External dependencies
#

# CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# MetaCall Library
find_package(MetaCall REQUIRED)

if(NOT METACALL_FOUND)
	message(STATUS "MetaCall libraries not found")
	return()
endif()

include_directories(${METACALL_INCLUDE_DIRS})

#
# Executable name and options
#

# Target name
set(target rotulin)

#
# Create executable
#

add_executable(${target}
	main.cpp
)

#
# Include directories
#

target_include_directories(${target}
	PRIVATE
	${METACALL_INCLUDE_DIRS} # MetaCall includes
)

#
# Libraries
#

target_link_libraries(${target}
	PRIVATE
	${METACALL_LIBRARIES} # MetaCall libraries

	#pthread
	#jpeg
	#png
)

#
# Output directory
#

add_custom_command(TARGET ${target}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target}> ${PROJECT_OUTPUT_DIRECTORY}
)
