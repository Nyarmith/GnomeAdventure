cmake_minimum_required(VERSION 3.1)
project(GnomeAdventure)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_BUILD_TYPE Debug)

#warnings at max
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif ( MSVC )


#get libraries that we're using and put in var
find_package(SFML 2.5 REQUIRED COMPONENTS graphics audio system window)
set(ALL_SFML_LIBS "sfml-graphics sfml-audio sfml-window sfml-system")

#include_directories(util)
include_directories("include")
#add_subdirectory(tests)

#add_subdirectory(game) #add this when you will actually define the game
