# Setup our datadiver library that we link to
SET(DATADIVER_SRCS
    datadiver.cpp
)

SET(DATADIVER_HDRS
    datadiver.h
)

# do we want a static library?
IF(WANT_STATIC)
    ADD_LIBRARY(datadiver_static STATIC 
        ${DATADIVER_SRCS}
        ${DATADIVER_HDRS}
        )

    SET_TARGET_PROPERTIES(datadiver_static PROPERTIES 
        OUTPUT_NAME ${LIBRARY_STATIC_NAME} CLEAN_DIRECT_OUTPUT 1
        COMPILE_DEFINITIONS DATADIVER_BUILD
        )
        
    TARGET_LINK_LIBRARIES(datadiver_dynamic
    ${Boost_LIBRARIES}
        )
ENDIF(WANT_STATIC)

# always build our dynamic library
ADD_LIBRARY(datadiver_dynamic SHARED
    ${DATADIVER_SRCS}
    ${DATADIVER_HDRS}
    )

SET_TARGET_PROPERTIES(datadiver_dynamic PROPERTIES 
    SOVERSION ${SOVERSION}
    VERSION ${VERSION}
    OUTPUT_NAME ${LIBRARY_DYN_NAME} CLEAN_DIRECT_OUTPUT 1
    )

TARGET_LINK_LIBRARIES(datadiver_dynamic
    ${Boost_LIBRARIES}
    )

IF(WIN32)
    SET_TARGET_PROPERTIES(datadiver_dynamic PROPERTIES 
        DEFINE_SYMBOL DLL_EXPORT
        COMPILE_DEFINITIONS DATADIVER_BUILD
    )
ELSEIF(HAVE_VISIBILITY_HIDDEN AND HAVE_VISIBILITY_DEFAULT) # GCC, Clang
    SET_TARGET_PROPERTIES(datadiver_dynamic PROPERTIES
        COMPILE_DEFINITIONS "DATADIVER_BUILD;SYM_VISIBILITY"
        COMPILE_FLAGS "-fvisibility=hidden"
    )
#ELSEIF(HAVE_LDSCOPE_HIDDEN AND HAVE_VISIBILITY_DEFAULT) # SunPro (__SUNPRO_C >= 0x590)
#   SET_TARGET_PROPERTIES(datadiver_dynamic PROPERTIES
#       COMPILE_DEFINITIONS "DATADIVER_BUILD;SYM_VISIBILITY"
#       COMPILE_FLAGS "-xldscope=hidden"
#   )
ELSEIF(HAVE_LDSCOPE_HIDDEN AND HAVE_LDSCOPE_GLOBAL) # SunPro (__SUNPRO_C >= 0x550)
    SET_TARGET_PROPERTIES(datadiver_dynamic PROPERTIES
        COMPILE_DEFINITIONS "DATADIVER_BUILD;SYM_LDSCOPE"
        COMPILE_FLAGS "-xldscope=hidden"
    )
ELSE()
    SET_TARGET_PROPERTIES(datadiver_dynamic PROPERTIES
        COMPILE_DEFINITIONS DATADIVER_BUILD
    )
ENDIF()

# MS Visual Studio
IF(MSVC)
    SET(GETOPT getopt_long.c)
    SET(LIBDATADIVER "${CMAKE_BINARY_DIR}\\${CMAKE_BUILD_TYPE}\\${LIBRARY_DYN_NAME}.lib")
ENDIF(MSVC)

# MinGW or MinGW-w64
IF(CMAKE_COMPILER_IS_MINGW)
    SET(LIBDATADIVER "${CMAKE_BINARY_DIR}\\lib${LIBRARY_DYN_NAME}.dll.a")
ENDIF(CMAKE_COMPILER_IS_MINGW)

# Apple's Xcode
IF(CMAKE_GENERATOR STREQUAL "Xcode")
    SET(LIBDATADIVER "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib${LIBRARY_DYN_NAME}.dylib")
ELSEIF(APPLE) # Apple's CLI default
    SET(LIBDATADIVER "${CMAKE_BINARY_DIR}/lib${LIBRARY_DYN_NAME}.dylib")
ENDIF(CMAKE_GENERATOR STREQUAL "Xcode")

# add install target:
IF(UNIX AND NOT APPLE)
    # install our libraries
    IF(WANT_STATIC)
        INSTALL(TARGETS datadiver_static DESTINATION "lib${LIB_SUFFIX}/${CMAKE_LIBRARY_ARCHITECTURE}")
    ENDIF(WANT_STATIC)
    INSTALL(TARGETS datadiver_dynamic DESTINATION "lib${LIB_SUFFIX}/${CMAKE_LIBRARY_ARCHITECTURE}")

    # install supporting man pages and headers
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/include/datadiver.h DESTINATION include)
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/docs/man/ DESTINATION share/man)
ENDIF(UNIX AND NOT APPLE)
