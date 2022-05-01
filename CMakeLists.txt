cmake_minimum_required(VERSION 3.22)

project(ex4)

if (MSVC)
    add_executable (${PROJECT_NAME})
else()
    add_executable (${PROJECT_NAME})
endif()

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(conf)

add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)

target_link_libraries(${PROJECT_NAME} plog)

# ======== SFML
if( WIN32 ) 
    # dosnt work on linux from package manager (need to manualy compile dynamic lib)...
    set (SFML_STATIC_LIBRARIES TRUE)
    set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")
    # required for audio
    configure_file ("C:/SFML/SFML-2.5.1/bin/openal32.dll" ${CMAKE_BINARY_DIR} COPYONLY)
endif()

find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

if( WIN32 ) 
    # sfml-main - is windows only 
    set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-audio sfml-main)
else()
    set_target_properties (sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-audio)
endif()
# ==========

if (MSVC)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/std:c++latest")
else()
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++2a -fconcepts")
endif()
