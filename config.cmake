function(src_executable EXECUTABLE_SRC_NAME EXECUTABLE_SOURCES)
    message(STATUS "Game executable: '${EXECUTABLE_SRC_NAME}' is built with ${EXECUTABLE_SOURCES}")

    add_executable(
            ${EXECUTABLE_SRC_NAME}
            ${EXECUTABLE_SOURCES}
    )

    target_link_libraries(
            ${EXECUTABLE_SRC_NAME}

            engine
    )

endfunction()