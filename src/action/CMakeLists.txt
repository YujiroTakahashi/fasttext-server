set(ACTION_HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/action.h
	${CMAKE_SOURCE_DIR}/include/croco.h
	${CMAKE_SOURCE_DIR}/include/json.hpp
)

set(ACTION_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/vectors.cpp
)

add_dependencies(ftext-server-static croco-util)

add_library(ftext-server-action STATIC ${ACTION_HEADER_FILES} ${ACTION_SOURCE_FILES})
target_link_libraries(ftext-server-action croco-util)
set_target_properties(ftext-server-action PROPERTIES OUTPUT_NAME ftext-server-action)
