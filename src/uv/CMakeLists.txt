set(HTTP_HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/uv/http.h
	${CMAKE_SOURCE_DIR}/include/uv/route.h
	${CMAKE_SOURCE_DIR}/include/uv/uri.h
)

set(HTTP_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/http-client.cc
	${CMAKE_CURRENT_SOURCE_DIR}/http-server.cc
	${CMAKE_CURRENT_SOURCE_DIR}/http.cc
	${CMAKE_CURRENT_SOURCE_DIR}/route.cc
)


add_library(ftext-server-http STATIC ${HTTP_HEADER_FILES} ${HTTP_SOURCE_FILES})
target_link_libraries(ftext-server-http	${http-parser-shared} ${uv-shared})
set_target_properties(ftext-server-http PROPERTIES OUTPUT_NAME ftext-server-http)
