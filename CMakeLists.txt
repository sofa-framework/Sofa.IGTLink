cmake_minimum_required(VERSION 3.22)
project(SofaIGTLink VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)


# SOFA packages containing our dependencies
find_package(Sofa.Framework REQUIRED) # Needed to use SofaCore, SofaHelper and SofaDefaultType
find_package(Sofa.Component.Topology REQUIRED) # Needed to use SofaCore, SofaHelper and SofaDefaultType
find_package(Sofa.Component.StateContainer REQUIRED) # Needed to use SofaCore, SofaHelper and SofaDefaultType
find_package(Threads REQUIRED)

find_package(OpenIGTLink QUIET) # Needed to use SofaCore, SofaHelper and SofaDefaultType
if(NOT OpenIGTLink_FOUND )
        message("SofaIGTLink: DEPENDENCY OpenIGTLink NOT FOUND, fetching OpenIGTLink...")
        include(FetchContent)
        FetchContent_Declare(OpenIGTLink
                GIT_REPOSITORY https://github.com/openigtlink/OpenIGTLink
                GIT_TAG master
        )

        set(BUILD_SHARED_LIBS ON CACHE BOOL "FORCE VALUE" FORCE)
        FetchContent_MakeAvailable(OpenIGTLink)
endif()

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


sofa_create_package_with_targets(
        PACKAGE_NAME ${PROJECT_NAME}
        PACKAGE_VERSION ${PROJECT_VERSION}
        TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
        INCLUDE_SOURCE_DIR "src"
        INCLUDE_INSTALL_DIR ${PROJECT_NAME}
        RELOCATABLE "plugins"
)


