set(CROCO_HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/croco.h
)

set(CROCO_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/di.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ini_parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
)

add_library(croco-util STATIC ${CROCO_HEADER_FILES} ${CROCO_SOURCE_FILES})
set_target_properties(croco-util PROPERTIES OUTPUT_NAME croco-util)
