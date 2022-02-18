cmake_minimum_required(VERSION 3.19.2 FATAL_ERROR)

    set( PROJECT_NAME
            001_Codility_Test_1
    )

project(
    ${PROJECT_NAME}
        VERSION 1.0.0.0
)


# BEGIN > ----- SET PROJECT PROPERTIES -------------------------------
    set( PROJECT_PROPERTIES
            CMAKE_BUILD_TYPE                Debug
            CMAKE_CXX_FLAGS                 -O3
            CMAKE_CXX_FLAGS                 -Wall
            CMAKE_CXX_STANDARD              17
            CMAKE_CXX_STANDARD_REQUIRED     True
    )
    set( IS_A_SPECIAL_SOURCE_DIRECTORY_USED
            True
    )
    set( IS_A_SPECIAL_INCLUDE_DIRECTORY_USED
            True
    )
    set( IS_A_CONFIGURATION_FILE_BEING_USED
            False
    )
    set( IS_AN_EXTERNAL_SOURCE_LIBRARY_USED
            False
    )
    set( EXTERNAL_SOURCE_LIBRARY_NAME
            ""                      # Instead of double quotes (""),
    )                               # enter the name of the library
# END >   ----- SET PROJECT PROPERTIES -------------------------------



# BEGIN > ----- PREPARATION OF DEFINITIONS ---------------------------
if(IS_A_SPECIAL_SOURCE_DIRECTORY_USED)
    set( SPECIAL_SOURCE_DIR
            /${PROJECT_NAME}/src
    )
else()
    set( SPECIAL_SOURCE_DIR     "")
endif()

if(IS_A_SPECIAL_INCLUDE_DIRECTORY_USED)
    set( SPECIAL_INCLUDE_DIR
            /${PROJECT_NAME}/inc
    )
else()
    set( SPECIAL_INCLUDE_DIR    "")
endif()

if(IS_A_CONFIGURATION_FILE_BEING_USED)
    set( SPECIAL_CONFIG_DIR
            /${PROJECT_NAME}/cfg
    )
else()
    set( SPECIAL_CONFIG_DIR    "")
endif()
# END >   ----- PREPARATION OF DEFINITIONS ---------------------------



# BEGIN > ----- SET SOURCE, HEADER AND CONFIG FILES LOCATIONS --------
    set( PROJECT_SOURCE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}${SPECIAL_SOURCE_DIR}
    )
    set( PROJECT_HEADERS_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}${SPECIAL_INCLUDE_DIR}
    )
    set( PROJECT_CONFIG_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}${SPECIAL_CONFIG_DIR}
    )
if (IS_A_CONFIGURATION_FILE_BEING_USED)
    configure_file(
        ${PROJECT_CONFIG_DIR}/${PROJECT_NAME}Config.h.in
        ${PROJECT_HEADERS_DIR}/${PROJECT_NAME}Config.h
    )
endif ()
# END >   ----- SET SOURCE, HEADER AND CONFIG FILES LOCATIONS --------



# BEGIN > ----- INCLUDE EXTERNAL LIBRARY -----------------------------
if(IS_AN_EXTERNAL_SOURCE_LIBRARY_USED)
        set( EXTERNAL_SOURCE_LIBRARY_LOCATION
                ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_SOURCE_LIBRARY_NAME}
        )
    add_subdirectory(
        ${EXTERNAL_SOURCE_LIBRARY_LOCATION}
    )
endif()
# END >   ----- INCLUDE EXTERNAL LIBRARY -----------------------------



# BEGIN > ----- ADD SOURCE FILES TO THE TARGET -----------------------
    set( SOURCES
            ${PROJECT_SOURCE_DIR}/main.cpp
    )
if(ANDROID)
    add_library(                        # Create target as a library
            ${PROJECT_NAME}
        SHARED
            ${SOURCES}
    )
else()
    add_executable(                     # Create target as executable
        ${PROJECT_NAME}
            ${SOURCES}
    )
endif()
# END >   ----- ADD SOURCE FILES TO THE TARGET -----------------------



# BEGIN > ----- INCLUDE EXTERNAL LIBRARY -----------------------------
if(IS_AN_EXTERNAL_SOURCE_LIBRARY_USED)
    target_link_libraries(
            ${PROJECT_NAME}
        PUBLIC
            ${EXTERNAL_SOURCE_LIBRARY_NAME}
    )
endif()
# END >   ----- INCLUDE EXTERNAL LIBRARY -----------------------------



# BEGIN > ----- HEADER FILES DIRECTORIES -----------------------------
if(IS_AN_EXTERNAL_SOURCE_LIBRARY_USED)
    target_include_directories(
            ${PROJECT_NAME}
        PUBLIC
            ${PROJECT_BINARY_DIR}
            ${PROJECT_HEADERS_DIR}
        PRIVATE
            ${EXTERNAL_SOURCE_LIBRARY_LOCATION}
    )
else()
    target_include_directories(
            ${PROJECT_NAME}
        PUBLIC
            ${PROJECT_BINARY_DIR}
            ${PROJECT_HEADERS_DIR}
    )
endif()
# END >   ----- HEADER FILES DIRECTORIES -----------------------------



# BEGIN > ----- TO SET PROJECT PROPERTIES ----------------------------
set_target_properties(
        ${PROJECT_NAME}
    PROPERTIES
        ${PROJECT_PROPERTIES}
)
# END >   ----- TO SET PROJECT PROPERTIES ----------------------------