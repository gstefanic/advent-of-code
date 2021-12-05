MACRO(SUBDIRLIST result curdir)
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")
	FOREACH(child ${children})
		IF(IS_DIRECTORY ${curdir}/${child})
			LIST(APPEND dirlist ${child})
		ENDIF()
	ENDFOREACH()
	SET(${result} ${dirlist})
ENDMACRO()

FUNCTION(ADD_PROJECT_DAY)
	SET(OPTIONS)
	SET(ARGS DIR)
	SET(LIST_ARGS)
	CMAKE_PARSE_ARGUMENTS(
		PARSE_ARGV 0
		ARG
		"${OPTIONS}"
		"${ARGS}"
		"${LIST_ARGS}"
	)
	MESSAGE(STATUS "ADD_PROJECT_DAY: ${ARG_DIR}")
	SET(project_name ${ARG_DIR})
	#PROJECT(${project_name} C)
	FILE(GLOB sources "${ARG_DIR}/*.c" "${ARG_DIR}/*.h" "${ARG_DIR}/*.cpp" "${ARG_DIR}/*.hpp")
	MESSAGE(STATUS "SOURCES: ${sources}")
	ADD_EXECUTABLE(${project_name} ${sources})
	TARGET_LINK_LIBRARIES(${project_name} PRIVATE lib)
	FILE(GLOB input "${ARG_DIR}/input.txt")
	add_custom_command(
        TARGET ${project_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_SOURCE_DIR}/${ARG_DIR}/input.txt"
                ${CMAKE_CURRENT_BINARY_DIR}/input.txt)
ENDFUNCTION()

SUBDIRLIST(SUBDIRS "${CMAKE_CURRENT_SOURCE_DIR}")

FOREACH(subdir ${SUBDIRS})
	ADD_PROJECT_DAY(DIR ${subdir})
ENDFOREACH()