cmake_minimum_required(VERSION 2.8)

project(Rotulin)

# Define output directory
set(PROJECT_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/output")

execute_process(
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_OUTPUT_DIRECTORY}"
)

# Define scripts directory
set(PROJECT_SCRIPTS_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/scripts")

execute_process(
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SCRIPTS_DIRECTORY}"
)

# Define configurations directory
set(PROJECT_CONFIGURATIONS_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/configurations")

execute_process(
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SCRIPTS_DIRECTORY}"
)

#
# Host
#

# Add host application
add_subdirectory(host)

#
# Frontend
#

# Configure frontend
# ...


# External dependencies
find_package(PythonLibs 3 REQUIRED)

if(NOT PYTHONLIBS_FOUND)
	message(STATUS "Python libraries not found")
	return()
endif()

set(Python_ADDITIONAL_VERSIONS 3.4)

find_package(PythonInterp REQUIRED)

if(NOT PYTHONINTERP_FOUND)
	message(STATUS "Python interpreter not found")
	return()
endif()

# Copy frontend
execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/frontend/frontend.py" "${PROJECT_SCRIPTS_DIRECTORY}"
)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/frontend/frontend" "${PROJECT_SCRIPTS_DIRECTORY}/frontend"
)

# Build frontend
execute_process(
	COMMAND ${PYTHON3_EXECUTABLE} frontend.py migrate
)

#
# Cache
#

# Configure cache
# ...

# Build cache
# ...

# Copy cache
execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/cache/cache.rb" "${PROJECT_SCRIPTS_DIRECTORY}"
)

#
# Image
#

# Configure image
# ...

# Build image
# ...

# Copy image
# ...

#
# Configurations
#

# Global configuration
execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/configurations/global.json" "${PROJECT_CONFIGURATIONS_DIRECTORY}"
)
