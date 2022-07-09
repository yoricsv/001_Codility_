cmake_minimum_required(VERSION 3.19.2 FATAL_ERROR)

    set( PROJECT_NAME
            Codility_Test_3
    )

project(
    ${PROJECT_NAME}
        VERSION 1.0.0.0
)


# BEGIN > ----- SET PROJECT PROPERTIES -------------------------------
    set( PROJECT_PROPERTIES
            CMAKE_BUILD_TYPE                Debug
            CXX_EXTENSIONS                  YES
            CXX_FLAGS                       -O3
            CXX_FLAGS                       -Wall
            CXX_STANDARD                    14
            CXX_STANDARD_REQUIRED           ON
    )
    option(
        USE_SPECIAL_SOURCE_DIRECTORY
            "Use the source files hierarchy structure in a project"
                ON
    )
    option(
        USE_SPECIAL_INCLUDE_DIRECTORY
            "Use the header file hierarchy structure in a project"
                ON
    )
    option(
        USE_CONFIGURATION_FILE
            "Use a config file in a project"
                ON
    )

    option(
        USE_EXTERNAL_SOURCE_LIBRARY
            "Using an External Source Library in a Project"
                OFF
    )
    # set external source library name
    set( EXTERNAL_SOURCE_LIBRARY_NAME
            ""                      # Instead of double quotes (""),
    )                               # enter the name of the library

    option(
        USING_BASIC_TESTS
            "Using basic tests for Project"
                ON
    )
    option(
        USING_ADDITIONAL_TESTS
            "Using advanced tests for Project"
                OFF
    )
# END >   ----- SET PROJECT PROPERTIES -------------------------------



# BEGIN > ----- SET ADDITIONAL TEST CONFIGURATION --------------------
if (USING_ADDITIONAL_TESTS)

    # ----------------------: IMPORTANT :---------------------- #
    #  You must set the correct data before using any test!!!!  #
    #     *  CMake can't pass empty argument via prompt  *      #
    # --------------------------------------------------------- #

    option(
        CORRECT_ARGUMENT_VALIDATION
            "Check operation in case of passing correct data"
                OFF
    )
    if (CORRECT_ARGUMENT_VALIDATION)
        set( VALUE_OK           9)
        set( RESULT_OK          3)
    endif ()


    option(
        INCORRECT_ARGUMENT_VALIDATION
            "Check operation in case of passing incorrect data"
                OFF
    )
    if (INCORRECT_ARGUMENT_VALIDATION)
        set( VALUE_BAD          5)
        set( RESULT_BAD         2.236)
    endif ()


    option(
        ZERO_ARGUMENT_VALIDATION
            "Check operation in case of passing null value"
                OFF
    )
    if ()
        set( VALUE_ZERO         0)
        set( RESULT_ZERO        (-nan|nan|0))
    endif ()


    option(
        POSITIVE_ARGUMENT_VALIDATION
            "Check operation in case of passing positive data"
                OFF
    )
    if ()
        set( VALUE_POSITIVE     1)
        set( RESULT_POSITIVE    1)
    endif ()


    option(
        NEGATIVE_ARGUMENT_VALIDATION
            "Check operation in case of passing negative data"
                OFF
    )
    if ()
        set( VALUE_NEGATIVE     -1)
        set( RESULT_NEGATIVE    (-nan|nan|0))
    endif ()


    option(
        REAL_ARGUMENT_VALIDATION
            "Check operation in case of passing a real data type"
                OFF
    )
    if ()
        set( VALUE_REAL         0.0001)
        set( RESULT_REAL        0.01)
    endif ()


    option(
        STRING_ARGUMENT_VALIDATION
            "Check operation in case of passing strings"
                OFF
    )
    if ()
        set( VALUE_STRING       value)
        set( RESULT_STRING      (-nan|nan|0))
    endif ()


    option(
        OVERFLOW_CHECK
            "Check the operation in case of overflow"
                OFF
    )
    if ()
        # LONG LONG INT   (Max: 9223372036854775807)
        set( VALUE_OVERFLOW     9223372036854775809)
        set( RESULT_OVERFLOW    9223372036854775809)
    endif ()


    # NOTE: CMake can't pass empty argument via prompt
    option(
        EMPTY_ARGUMENT_VALIDATION
            "Check the operation in case of passing empty arguments"
                OFF
    )
    if ()
        set( VALUE_EMPTY        "")
        set( RESULT_EMPTY       (-nan|nan|0))
    endif ()
endif ()
# END >   ----- SET ADDITIONAL TEST CONFIGURATION --------------------



# BEGIN > ----- PREPARATION OF DEFINITIONS ---------------------------
if(USE_SPECIAL_SOURCE_DIRECTORY)
    set( SPECIAL_SOURCE_DIR
            /${PROJECT_NAME}/src
    )
else()
    set( SPECIAL_SOURCE_DIR     "")
endif()

if(USE_SPECIAL_INCLUDE_DIRECTORY)
    set( SPECIAL_INCLUDE_DIR
            /${PROJECT_NAME}/inc
    )
else()
    set( SPECIAL_INCLUDE_DIR    "")
endif()

if(USE_CONFIGURATION_FILE)
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
if (USE_CONFIGURATION_FILE)
    configure_file(
        ${PROJECT_CONFIG_DIR}/${PROJECT_NAME}Config.h.in
        ${PROJECT_HEADERS_DIR}/${PROJECT_NAME}Config.h
    )
endif ()
# END >   ----- SET SOURCE, HEADER AND CONFIG FILES LOCATIONS --------



# BEGIN > ----- INCLUDE EXTERNAL LIBRARY -----------------------------
if(USE_EXTERNAL_SOURCE_LIBRARY)
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
            ${PROJECT_SOURCE_DIR}/CommandPromptArgValidator.cpp
            ${PROJECT_SOURCE_DIR}/ReportStructure.cpp
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
if(USE_EXTERNAL_SOURCE_LIBRARY)
    target_link_libraries(
            ${PROJECT_NAME}
        PUBLIC
            ${EXTERNAL_SOURCE_LIBRARY_NAME}
    )
endif()
# END >   ----- INCLUDE EXTERNAL LIBRARY -----------------------------



# BEGIN > ----- HEADER FILES DIRECTORIES -----------------------------
if(USE_EXTERNAL_SOURCE_LIBRARY)
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



# BEGIN > ----- TROUBLESHOOTING (TESTS) ------------------------------
if (USING_BASIC_TESTS)

    enable_testing()

    # set basic tests data
    set( VALUE_VERSION      -v)
    set( ANY_PROMPT_ARG     Test)

    # Can the application run
    add_test(
        NAME
            Runnable
        COMMAND
            ${PROJECT_NAME} ${ANY_PROMPT_ARG}
    )

    # Can the application display a message
    add_test(
        NAME
            PromptMode
        COMMAND
            ${PROJECT_NAME}
    )
    set_tests_properties(
            PromptMode
        PROPERTIES
            PASS_REGULAR_EXPRESSION
                "|The*mode|"
    )

    # Does the application display a message about its version
    add_test(
        NAME
            PrintVersion
        COMMAND
            ${PROJECT_NAME}
            ${VALUE_VERSION}
    )
    set_tests_properties(
            PrintVersion
        PROPERTIES
            PASS_REGULAR_EXPRESSION
                "v.*.*"
    )
endif()



if (USING_ADDITIONAL_TESTS)
    # Define a function DO_TEST
    function(
        do_test
            target
                arg
                result
    )
        add_test(
            NAME
                PassedValue_${arg}
            COMMAND
                ${target}
                ${arg}
        )
        set_tests_properties(
                PassedValue_${arg}
            PROPERTIES
                PASS_REGULAR_EXPRESSION
                    ${result}
        )
    endfunction()


    # ADDITION TESTS
    if (CORRECT_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_OK}
                "${VALUE_OK} is ${RESULT_OK}"
        )
    endif ()

    if (INCORRECT_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_BAD}
                "${VALUE_BAD} is ${RESULT_BAD}"
        )
    endif ()

    if (ZERO_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME} ${VALUE_ZERO}
                "${VALUE_ZERO} is ${RESULT_ZERO}"
        )
    endif ()

    if (POSITIVE_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_POSITIVE}
                "${VALUE_POSITIVE} is ${RESULT_POSITIVE}"
        )
    endif ()

    if (NEGATIVE_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_NEGATIVE}
                "${VALUE_NEGATIVE} is ${RESULT_NEGATIVE}"
        )
    endif ()

    if (REAL_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_REAL}
                "${VALUE_REAL} is ${RESULT_REAL}"
        )
    endif ()

    if (STRING_ARGUMENT_VALIDATION)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_STRING}
                "${VALUE_STRING} is ${RESULT_STRING}"
        )
    endif ()

    if (OVERFLOW_CHECK)
        do_test(
            ${PROJECT_NAME}
                ${VALUE_OVERFLOW}
                "${VALUE_OVERFLOW} is ${RESULT_OVERFLOW}"
        )
    endif ()

    # CMake can't pass empty argument via prompt
    if (EMPTY_ARGUMENT_VALIDATION)
        do_test(
                ${PROJECT_NAME}
                ${VALUE_EMPTY}
                "${VALUE_EMPTY} is ${RESULT_EMPTY}"
        )
    endif ()

endif ()
# END >   ----- TROUBLESHOOTING (TESTS) ------------------------------