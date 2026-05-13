cmake_minimum_required(VERSION 3.30)

project(scierzko-znajdywacz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build libs as statcic" FORCE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets Gui QUIET)

include(CheckCXXCompilerFlag)
function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

find_package(Git REQUIRED)
if(Git_FOUND)
  message("Git found: ${GIT_EXECUTABLE}")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)
if(Qt6_FOUND)
  message("Qt6 found: ${QT6_EXECUTABLE}")
endif()

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries(scierzko-znajdywacz PRIVATE 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Gui
)

if(WIN32)
    set_target_properties(scierzko-znajdywacz PROPERTIES WIN32_EXECUTABLE FALSE)
endif()

enable_cxx_compiler_flag_if_supported("-Wall")