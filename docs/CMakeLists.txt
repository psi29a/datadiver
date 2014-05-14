IF( BUILD_DOCUMENTATION )
  # Builds the documentation.
  find_package( Sphinx REQUIRED )

  SET( SPHINX_DESTINATION ${DATADIVER_BINARY_DIR} )
  #SET( SPHINX_DEPENDENCIES something )

  configure_file(
    ${CMAKE_SOURCE_DIR}/source/conf.py.in
    ${CMAKE_BINARY_DIR}/conf.py
    @ONLY)

  configure_file(
    ${CMAKE_SOURCE_DIR}/run_sphinx_build.sh.in
    ${CMAKE_BINARY_DIR}/run_sphinx_build.sh
    @ONLY)

  IF(UNIX)
    EXECUTE_PROCESS(COMMAND chmod +x ${DATADIVER_BINARY_DIR}/run_sphinx_build.sh)
  ENDIF(UNIX)

  SET( sphinx_target_base_name build )
  #Sphinx_add_targets( ${sphinx_target_base_name} ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${SPHINX_DESTINATION} ${SPHINX_DEPENDENCIES} )

  IF( ${SPHINX_HTML_OUTPUT} )
    INSTALL( DIRECTORY ${SPHINX_DESTINATION}/html
      DESTINATION share/Datadiver/doc
      COMPONENT Doc
      PATTERN "${SPHINX_DESTINATION}/html/*"
      )
    INSTALL( FILES
      DESTINATION share/Datadiver/doc/html
      COMPONENT Doc
      )
  ENDIF()

  IF( ${SPHINX_LATEX_OUTPUT} )
    SET( DOC_WITH_LOCAL_DOXYGEN OFF )

    # Build the PDF with pdflatex
    find_package( LATEX )
    IF( NOT PDFLATEX_COMPILER )
      message("pdflatex compiler was not found. Please pass to advanced mode and provide its full path")
    ELSE()
      # Needs to be executed twice to get table of contents.
      ADD_CUSTOM_COMMAND( TARGET ${sphinx_target_base_name}_latex
        POST_BUILD
        COMMAND ${PDFLATEX_COMPILER}
          ${SPHINX_DESTINATION}/latex/Datadiver.tex
          -output-directory ${SPHINX_DESTINATION}/latex
        COMMAND ${MAKEINDEX_COMPILER}
          Datadiver.idx
        COMMAND ${PDFLATEX_COMPILER}
          ${SPHINX_DESTINATION}/latex/Datadiver.tex
          -output-directory ${SPHINX_DESTINATION}/latex
        COMMAND ${CMAKE_COMMAND} -E copy
          ${SPHINX_DESTINATION}/latex/Datadiver.pdf
          ${SPHINX_DESTINATION}/html/Documentation/Download/Datadiver-${DATADIVER_VERSION}.pdf
        WORKING_DIRECTORY ${SPHINX_DESTINATION}/latex
        COMMENT "Building PDF"
        )
      INSTALL( FILES ${SPHINX_DESTINATION}/html/Documentation/Download/Datadiver-${DATADIVER_VERSION}.pdf
        DESTINATION share/Datadiver/doc/pdf
        COMPONENT Doc
        )
    ENDIF()
  ENDIF()

  IF( ${SPHINX_EPUB_OUTPUT} )
    ADD_CUSTOM_COMMAND( TARGET ${sphinx_target_base_name}_epub
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
        ${SPHINX_DESTINATION}/epub/Datadiver.epub
        ${SPHINX_DESTINATION}/html/Documentation/Download/Datadiver-${DATADIVER_VERSION}.epub
        COMMENT "Copying EPUB"
        )
    INSTALL( FILES ${SPHINX_DESTINATION}/html/Documentation/Download/Datadiver-${DATADIVER_VERSION}.epub
      DESTINATION share/Datadiver/doc/epub
      COMPONENT Doc
      )
  ENDIF()

ENDIF()