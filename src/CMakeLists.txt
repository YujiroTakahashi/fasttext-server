set(MAIN_HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/uv/http.h
	${CMAKE_SOURCE_DIR}/include/uv/route.h
	${CMAKE_SOURCE_DIR}/include/uv/uri.h
	${CMAKE_SOURCE_DIR}/include/action.h
	${CMAKE_SOURCE_DIR}/include/croco.h
	${CMAKE_SOURCE_DIR}/include/json.hpp
	${CMAKE_SOURCE_DIR}/include/responder.h
)

set(MAIN_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/httpd.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/responder.cpp
)

add_library(ftext-server-static STATIC ${MAIN_HEADER_FILES} ${MAIN_SOURCE_FILES})
target_link_libraries(ftext-server-static 
	${fasttext-shared}
	ftext-server-http
	ftext-server-action
)
set_target_properties(ftext-server-static PROPERTIES OUTPUT_NAME ftext-server-static)

add_executable(ftext-server-bin ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(ftext-server-bin 
	pthread
	${http-parser-shared}
	${fasttext-shared}
	${uv-shared}
	croco-util
	ftext-server-http
	ftext-server-action
	ftext-server-static
)
set_target_properties(ftext-server-bin PROPERTIES OUTPUT_NAME ftext-server)
install (TARGETS ftext-server-bin RUNTIME DESTINATION bin)


add_dependencies(ftext-server-static ftext-server-action)
add_subdirectory(action)
add_subdirectory(croco)
add_subdirectory(uv)