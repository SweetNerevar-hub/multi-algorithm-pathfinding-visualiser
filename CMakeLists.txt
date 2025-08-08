cmake_minimum_required(VERSION 3.28)

project(MAPV VERSION 3 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_PATH			"${CMAKE_SOURCE_DIR}/src")
set(LIB_INCLUDE_PATH	"${CMAKE_SOURCE_DIR}/externals/include")
set(LIB_PATH			"${CMAKE_SOURCE_DIR}/externals/lib")

include("${CMAKE_SOURCE_DIR}/src/CMakeLists.txt")
include("${CMAKE_SOURCE_DIR}/externals/CMakeLists.txt")

target_include_directories(MAPV PUBLIC "${SRC_PATH}" "${LIB_INCLUDE_PATH}")

if(WIN32)
	if(MSVC)
		string(REGEX MATCH "winmm.lib" MATCHED_SUBSTRING "${CMAKE_CXX_STANDARD_LIBRARIES}")
		if(NOT ${MATCHED_SUBSTRING} STREQUAL "")
			message("WinMM library already exists in cache!")
		else()
			set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} winmm.lib" CACHE STRING "Libraries linked by default with all C++ applications." FORCE)
		endif()

	else()
		string(REGEX MATCH "-lwinmm" MATCHED_SUBSTRING "${CMAKE_CXX_STANDARD_LIBRARIES}")
		if(NOT ${MATCHED_SUBSTRING} STREQUAL "")
			message("WinMM library already exists in cache!")
		else()
			set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lwinmm" CACHE STRING "Libraries linked by default with all C++ applications." FORCE)
		endif()
	endif()
endif()

# Copy the resources folder into the generated executable's folder
add_custom_command(
	TARGET MAPV
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND}
	-E copy_directory_if_different
	"${CMAKE_CURRENT_SOURCE_DIR}/resources"	
	"$<TARGET_FILE_DIR:MAPV>/resources"
)

# Copy the imgui config file into the generated executable's folder
add_custom_command(
	TARGET MAPV
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND}
	-E copy_if_different
	"${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini"	
	"$<TARGET_FILE_DIR:MAPV>/imgui.ini"
)