# CMakeList.txt : CMake project for reachEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)

set(PROJECT_NAME reachEngine)



project(${PROJECT_NAME})
set(<PROJECT-NAME>_VERSION_MAJOR 0)
set(<PROJECT-NAME>_VERSION_MINOR 1)

# AUTO_LOCATE_VULKAN - accepted value ON or OFF
# ON  - Use CMake to auto locate the Vulkan SDK.
# OFF - Vulkan SDK path can be specified manually. This is helpful to test the build on various Vulkan version.
option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if(AUTO_LOCATE_VULKAN)
	message(STATUS "Attempting auto locate Vulkan using CMake......")
	# Find Vulkan Path using CMake's Vulkan Module
	# This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
	# Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
	find_package(Vulkan)
	
	# Try extracting VulkanSDK path from ${Vulkan_INCLUDE_DIRS}
	if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
		set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
		STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
	endif()
		 
	if(NOT Vulkan_FOUND)
		# CMake may fail to locate the libraries but could be able to 
		# provide some path in Vulkan SDK include directory variable
		# 'Vulkan_INCLUDE_DIRS', try to extract path from this.
		message(STATUS "Failed to locate Vulkan SDK, retrying again...")
		if(EXISTS "${VULKAN_PATH}")
			message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
		else()
			message("Error: Unable to locate Vulkan SDK. Please turn off auto locate option by specifying 'AUTO_LOCATE_VULKAN' as 'OFF'")
			message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt.")
			return()
		endif()
	endif()
else()
	message(STATUS "Attempting to locate Vulkan SDK using manual path......")
	set(VULKAN_SDK "O:/C++/Libraries/VulkanSDK")
	# set(VULKAN_VERSION "1.3.261.1")
	set(VULKAN_PATH "${VULKAN_SDK}")
	message(STATUS "Using manual specified path: ${VULKAN_PATH}")

	# Check if manual set path exists
	if(NOT EXISTS "${VULKAN_PATH}")
		message("Error: Unable to locate this Vulkan SDK path VULKAN_PATH: ${VULKAN_PATH}, please specify correct path.
		For more information on correct installation process, please refer to subsection 'Getting started with Lunar-G SDK'
		and 'Setting up first project with CMake' in Chapter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469809.")
	   return()
	endif()
endif()

# BUILD_SPV_ON_COMPILE_TIME - accepted value ON or OFF, default value OFF.
# ON  - Reads the GLSL shader file and auto convert in SPIR-V form (.spv). 
# 			This requires additional libraries support from 
#			VulkanSDK like SPIRV glslang OGLCompiler OSDependent HLSL
# OFF - Only reads .spv files, which need to be compiled offline 
#			using glslangValidator.exe.
# For example: glslangValidator.exe <GLSL file name> -V -o <output filename in SPIR-V(.spv) form>
option(BUILD_SPV_ON_COMPILE_TIME "BUILD_SPV_ON_COMPILE_TIME" OFF)

# Add any required preprocessor definitions here
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

# GLM SETUP - Mathematic libraries for 3D transformation
set(EXTDIR "${CMAKE_SOURCE_DIR}/external")

# Include GLM in your project
set(GLM_INCLUDE_DIR "${EXTDIR}/glm-master/glm")
include_directories(${GLM_INCLUDE_DIR})


# vulkan-1 library for build Vulkan application.
set(VULKAN_LIB_LIST "vulkan-1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Include Vulkan header files from Vulkan SDK
	include_directories(AFTER ${VULKAN_PATH}/Include)

	# Link directory for vulkan-1
	link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)

	if(BUILD_SPV_ON_COMPILE_TIME)
		
		# Preprocessor  flag allows the solution to use glslang library functions
		add_definitions(-DAUTO_COMPILE_GLSL_TO_SPV)

		#GLSL - use Vulkan SDK's glslang library for compling GLSL to SPV 
		# This does not require offline coversion of GLSL shader to SPIR-V(.spv) form 
		set(GLSLANGDIR "${VULKAN_PATH}/glslang")
		get_filename_component(GLSLANG_PREFIX "${GLSLANGDIR}" ABSOLUTE)
		if(NOT EXISTS ${GLSLANG_PREFIX})
			message(FATAL_ERROR "Necessary glslang components do not exist: " ${GLSLANG_PREFIX})
		endif()
		include_directories( ${GLSLANG_PREFIX} )
		
		# If compiling GLSL to SPV using we need the following libraries
		set(GLSLANG_LIBS SPIRV glslang OGLCompiler OSDependent HLSL)

		# Generate the list of files to link, per flavor.
		foreach(x ${GLSLANG_LIBS})
			list(APPEND VULKAN_LIB_LIST debug ${x}d optimized ${x})
		endforeach()
		
		# Note: While configuring CMake for glslang we created the binaries in a "build" folder inside ${VULKAN_PATH}/glslang.
		# Therefore, you must edit the below lines for your custorm path like <Your binary path>/OGLCompilersDLL , <Your binary path>/OSDependent/Windows
		link_directories(${VULKAN_PATH}/glslang/build/OGLCompilersDLL )
		link_directories(${VULKAN_PATH}/glslang/build/glslang/OSDependent/Windows)
		link_directories(${VULKAN_PATH}/glslang/build/glslang)
		link_directories(${VULKAN_PATH}/glslang/build/SPIRV)
		link_directories(${VULKAN_PATH}/glslang/build/hlsl)
	endif()
endif()


# Define directories and the contained folder and files inside.
if(WIN32)
    source_group("include" REGULAR_EXPRESSION "include/*")
    source_group("source" REGULAR_EXPRESSION "source/*")
endif(WIN32)

# add the tiny_obj and stb_image librarires
include_directories(${EXTDIR})

# add SDL2 library
set(SDL_DIR "${EXTDIR}/sdl")
set(SDL_STATIC_LIBRARIES TRUE)
include_directories(${SDL_DIR}/include)
link_directories(${SDL_DIR}/VisualC/x64/Debug)

# add the include directories of the ptoject
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3DEngine/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3DEngine/vulkan/include)

# Gather list of header and source files for compilation
file(GLOB_RECURSE 3D_ENGINE_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/3DEngine/src/*.cpp)
file(GLOB_RECURSE 3D_ENGINE_HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/3DEngine/include/*.*)
file(GLOB_RECURSE VULKAN_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/3DEngine/vulkan/src/*.cpp)
file(GLOB_RECURSE VULKAN_HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/3DEngine/vulkan/include/*.*)
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)

# Add source to this project's executable.
add_executable(${PROJECT_NAME}  
				${CPP_FILES} 
				${HPP_FILES}
				${3D_ENGINE_CPP_FILES}
				${3D_ENGINE_HPP_FILES}
				${VULKAN_CPP_FILES}
				${VULKAN_HPP_FILES}
				"src/Main_ReachEngine.cpp"
				)

# set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/binaries/${PROJECT_NAME}.exe")

# Define project properties
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/binaries)




# Link the debug and release libraries to the project
target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2main)
target_link_libraries( ${PROJECT_NAME} ${VULKAN_LIB_LIST} )

# Define C++ version to be used for building the project
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)


