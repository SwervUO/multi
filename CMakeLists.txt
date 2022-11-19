cmake_minimum_required(VERSION 3.18)
project(multi VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# *************************************************************************
# The basic executable we are making
# *************************************************************************

add_executable(multi
	source/main.cpp
	source/argument.cpp
	source/argument.hpp
	source/support/art.hpp
	source/support/art.cpp
	source/support/bitmap.hpp
	source/support/hash.hpp
	source/support/hash.cpp
	source/support/multi.hpp
	source/support/multi.cpp
	source/support/strutil.hpp
	source/support/uop.hpp
	source/support/uop.cpp
	$<$<STREQUAL:${CMAKE_SYSTEM_NAME},Windows>:${PROJECT_SOURCE_DIR}/asset/appicon.rc>
)

# *************************************************************************
# Platform specific settings
# *************************************************************************

if (WIN32)
set (CMAKE_RC_STANDARD_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/asset/)
	
target_compile_definitions(multi PRIVATE
		WIN32
		_WINDOWS
		_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
		_CRT_NO_VA_START_VALIDATION
		_CRT_SECURE_NO_DEPRECATE
		_CRT_NONSTDC_NO_DEPRECATE
		_CONSOLE
		$<$<CONFIG:Release>:NDEBUG>
		$<$<CONFIG:Debug>:_DEBUG>
	)
	
	target_compile_options( multi PRIVATE
		/J
		$<$<CONFIG:Release>:/O2>
	)
else()

	target_compile_definitions( multi PRIVATE
		$<$<CONFIG:Debug>:_DEBUG>
	)
	
	if (APPLE)
		target_compile_options( multi PRIVATE
			$<$<CONFIG:Release>:-Os>
		)
	else()
		target_compile_options(multi PRIVATE
			$<$<CONFIG:Release>:-O2>
		)
	endif(APPLE)
endif(WIN32)



# *************************************************************************
# the directories we need on the include path
# *************************************************************************

target_include_directories(uox3
	PUBLIC
		${PROJECT_SOURCE_DIR}/compression
		${PROJECT_SOURCE_DIR}/source
		${PROJECT_SOURCE_DIR}/source/support
		
)

# *************************************************************************
# The libraries we need
# *************************************************************************
target_link_libraries(uox3 PRIVATE
	compression 
	$<$<PLATFORM_ID:Windows>:Kernel32>
)

# *************************************************************************
# The items we need built first
# *************************************************************************
add_subdirectory(${PROJECT_SOURCE_DIR}/compression subproject/compression)