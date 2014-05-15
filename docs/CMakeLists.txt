IF( WANT_DOCS )
  # Builds the documentation.
  FIND_PACKAGE( Sphinx REQUIRED )

  SET( SPHINX_SOURCE_DIR ${CMAKE_SOURCE_DIR}/docs/sphinx )
  SET( SPHINX_DESTINATION ${DATADIVER_BINARY_DIR}/docs )

  CONFIGURE_FILE(
    ${SPHINX_SOURCE_DIR}/source/conf.py.in
    ${SPHINX_DESTINATION}/conf.py
    @ONLY)

  CONFIGURE_FILE(
    ${SPHINX_SOURCE_DIR}/run_sphinx_build.sh.in
    ${SPHINX_DESTINATION}/run_sphinx_build.sh
    @ONLY)

  IF(UNIX)
    EXECUTE_PROCESS(COMMAND chmod +x ${SPHINX_DESTINATION}/run_sphinx_build.sh OUTPUT_QUIET)
    EXECUTE_PROCESS(COMMAND ${SPHINX_DESTINATION}/run_sphinx_build.sh OUTPUT_QUIET)
  ENDIF(UNIX)

ENDIF()