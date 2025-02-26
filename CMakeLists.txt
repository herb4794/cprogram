cmake_minimum_required(VERSION 3.10)  # Set the minimum version of CMake
project(MyCMakeProject)                 # Define the project name

set(CMAKE_CXX_STANDARD 11)              # Specify the C++ standard (e.g., C++11)

# Set build type to Debug to include debug symbols (-g flag)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Add debug flags explicitly
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")


file(GLOB SRC
"src/headers/*.h"
"src/methods/*.c"
"src/methods/**/*"
"src/*.c"
"src/*.h"
)
# Add an executable target
add_executable(producers ${SRC})  # Specify the target name and source files
