cmake_minimum_required(VERSION 3.10)
project(sdltest)

if (NOT EMSCRIPTEN)
	find_package(SDL REQUIRED)
	include_directories(${SDL_INCLUDE_DIR})
else ()
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

add_executable(sdltest src/sdltest.c)
target_link_libraries(sdltest ${SDL_LIBRARY})
