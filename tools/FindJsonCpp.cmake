# - Try to find the JsonCpp library
#
# Once done this will define:
#
#  JSONCPP_FOUND        - System has JsonCpp.
#  JSONCPP_INCLUDE_DIRS - The JsonCpp include directories.
#  JSONCPP_LIBRARIES    - The libraries needed to use JsonCpp.
#  JSONCPP_DEFINITIONS  - Compiler switches required for using JsonCpp.
#
# You can specify an environment variable JSONCPP_DIR or a cmake variable to give a hint where
# to find the JsonCpp library.
#
# JSONCPP_DIR=${HOME}/local cmake ../
#
# or
#
# cmake -DJSONCPP_DIR:PATH=${HOME}/local ../
#
#
# Usage:
#
# find_package(JsonCpp REQUIRED)
#
# add_executable(TestJsonCpp
#	TestJsonCpp.cpp
# )
#
# target_link_libraries(TestJsonCpp
#	JsonCpp::Json
# )

# Copyright 2016 Covidien LP
# All Rights Reserved. The information contained herein is confidential
# property of Covidien LP. The use, copying, transfer or disclosure of such
# information is prohibited except by express written agreement with Covidien LP.

set(OPT_JSONCPP_DIR "/opt/jsoncpp/1.6.2/Linux/x86_64/")
if (NOT TARGET JsonCpp::Json)

    unset(JSONCPP_FOUND)
    unset(JSONCPP_INCLUDE_DIRS)
    unset(JSONCPP_LIBRARIES)
    unset(JSONCPP_DEFINITIONS)

    message("OPT_JSONCPP_DIR: ${OPT_JSONCPP_DIR}")

    set(JSONCPP_INCLUDE_PATHS
            "${OPT_JSONCPP_DIR}/include"
            "$ENV{JSONCPP_DIR}/include"
            "${JSONCPP_DIR}/include"
            )

    set(JSONCPP_LIBRARY_PATHS
            "${OPT_JSONCPP_DIR}/lib"
            "$ENV{JSONCPP_DIR}/lib"
            "${JSONCPP_DIR}/lib"
            )

    # message(STATUS "JSONCPP_LIBRARY_PATHS: ${JSONCPP_LIBRARY_PATHS}")

    find_package(PkgConfig)
    pkg_check_modules(PC_JsonCpp QUIET jsoncpp)
    set(JSONCPP_DEFINITIONS ${PC_JsonCpp_CFLAGS_OTHER})

    find_path(JSONCPP_INCLUDE_DIR json/json.h
            HINTS ${PC_JsonCpp_INCLUDEDIR} ${PC_JsonCpp_INCLUDE_DIRS} ${JSONCPP_INCLUDE_PATHS})

    find_library(JSONCPP_LIBRARY NAMES jsoncpp_lib
            HINTS ${PC_JsonCpp_LIBDIR} ${PC_JsonCpp_LIBRARY_DIRS} ${JSONCPP_LIBRARY_PATHS})

    set(JSONCPP_LIBRARIES ${JSONCPP_LIBRARY})
    set(JSONCPP_INCLUDE_DIRS ${JSONCPP_INCLUDE_DIR})

    # message(STATUS "JSONCPP_LIBRARIES: ${JSONCPP_LIBRARIES}")
    # message(STATUS "JSONCPP_INCLUDE_DIRS: ${JSONCPP_INCLUDE_DIRS}")

    include(FindPackageHandleStandardArgs)

    # handle the QUIETLY and REQUIRED arguments and set JsonCpp_FOUND to TRUE
    # if all listed variables are TRUE
    find_package_handle_standard_args(JsonCpp
            REQUIRED_VARS
            JSONCPP_LIBRARIES JSONCPP_INCLUDE_DIRS)

    mark_as_advanced(JSONCPP_FOUND JSONCPP_INCLUDE_DIRS JSONCPP_LIBRARIES JSONCPP_DEFINITIONS)

    if(JSONCPP_FOUND)
        add_library(JsonCpp::Json UNKNOWN IMPORTED)
        set_target_properties(JsonCpp::Json
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${JSONCPP_INCLUDE_DIRS}"
                IMPORTED_LOCATION "${JSONCPP_LIBRARIES}"
                INTERFACE_COMPILE_DEFINITIONS "${JSONCPP_DEFINITIONS}"
                )
    endif(JSONCPP_FOUND)

endif(NOT TARGET JsonCpp::Json)
