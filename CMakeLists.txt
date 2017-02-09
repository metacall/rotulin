cmake_minimum_required(VERSION 2.8)

project(Rotulin)

# Define output directory
set(PROJECT_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/output")

# Define scripts directory
set(PROJECT_SCRIPTS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/output/scripts")

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

# Build frontend
# ...

# Copy frontend
# ...

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

