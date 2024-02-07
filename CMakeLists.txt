cmake_minimum_required(VERSION 3.22)
project(SofaIGTLink)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)


# SOFA packages containing our dependencies
find_package(Sofa.Framework REQUIRED) # Needed to use SofaCore, SofaHelper and SofaDefaultType
find_package(Sofa.Component.Topology REQUIRED) # Needed to use SofaCore, SofaHelper and SofaDefaultType
find_package(Sofa.Component.StateContainer REQUIRED) # Needed to use SofaCore, SofaHelper and SofaDefaultType

find_package(Threads REQUIRED)

find_package(OpenIGTLink QUIET) # Needed to use SofaCore, SofaHelper and SofaDefaultType
if(NOT OpenIGTLink_FOUND )
        message("SofaSlicer: DEPENDENCY OpenIGTLink NOT FOUND, fetching OpenIGTLink...")

        include(FetchContent)
        FetchContent_Declare(OpenIGTLink
                GIT_REPOSITORY https://github.com/openigtlink/OpenIGTLink
                GIT_TAG master
        )

        FetchContent_MakeAvailable(OpenIGTLink)
#        if(NOT OpenIGTLink_POPULATED)
#                FetchContent_Populate(OpenIGTLink)
#
#                set(OpenIGTLink_BUILD_GENERATE_PIC OFF CACHE INTERNAL "")
#                set(OpenIGTLink_BUILD_SHARED_LIBS ON CACHE INTERNAL "")
#                set(OpenIGTLink_BUILD_TESTING OFF CACHE INTERNAL "")
#                message("SofaSlicer: adding subdirectory ${OpenIGTLink_SOURCE_DIR}")
#
#                add_subdirectory(${OpenIGTLink_SOURCE_DIR})
#        endif()
endif()

# Our nice new SOFA Components
file(GLOB_RECURSE HEADER_FILES
        "src/*.h"
        "src/*.inl"
        )

file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        )

# SOFA plugin are basically libraries
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Sofa.Framework Sofa.Component.Topology Sofa.Component.StateContainer OpenIGTLink Threads::Threads)
include_directories(src)


install(TARGETS
        ${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME})


