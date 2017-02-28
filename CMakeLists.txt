cmake_minimum_required(VERSION 2.8)

project(Rotulin)

# Define output directory
set(PROJECT_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

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
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_CONFIGURATIONS_DIRECTORY}"
)

# Define ports directory
set(PROJECT_METACALL_PORTS_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}")

execute_process(
	COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_OUTPUT_DIRECTORY}"
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
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/frontend/manage.py" "${PROJECT_SCRIPTS_DIRECTORY}"
)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/frontend/frontend" "${PROJECT_SCRIPTS_DIRECTORY}/frontend"
)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/frontend/frontend/uploader" "${PROJECT_SCRIPTS_DIRECTORY}/frontend/uploader"
)

# Build frontend
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/migrate")
	execute_process(
		COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SCRIPTS_DIRECTORY}/manage.py migrate
	)

	file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/migrate" "")
endif()

# Configure ports path
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/frontend/metacall.py.in" "${PROJECT_SCRIPTS_DIRECTORY}/metacall.py" @ONLY)

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

execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/configurations/cs_loader.json" "${PROJECT_CONFIGURATIONS_DIRECTORY}"
)
