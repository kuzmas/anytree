project(anytree C)

cmake_minimum_required(VERSION 2.6)


set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(FULL_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR})
message(STATUS "")
message(STATUS "Version: ${FULL_VERSION}")
message(STATUS "")

add_definitions(-Wall)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES [Dd]ebug)
	message(STATUS "Debug build")
	add_definitions(-DDEBUG)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
else()
	message(STATUS "Release build")
	add_definitions(-DNDEBUG)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()


include_directories("${PROJECT_SOURCE_DIR}"
	"${PROJECT_BINARY_DIR}")



configure_file(
	"${PROJECT_SOURCE_DIR}/version.h.in"
	"${PROJECT_BINARY_DIR}/version.h"
	@ONLY
)

configure_file(
	"${PROJECT_SOURCE_DIR}/main.h.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}.h"
	@ONLY
)


set(${PROJECT_NAME}_SOURCES
	avl.c
	rb.c
	bs.c
	splay.c
	any.c
)

set(${PROJECT_NAME}_PUBLIC_HEADERS
	${PROJECT_BINARY_DIR}/version.h
	avl.h
	rb.h
	bs.h
	splay.h
	any.h
)

set(${PROJECT_NAME}_PRIVATE_HEADERS
)



set(${PROJECT_NAME}_HEADERS
	${${PROJECT_NAME}_MAIN_HEADER}
	${${PROJECT_NAME}_PUBLIC_HEADERS}
	${${PROJECT_NAME}_PRIVATE_HEADERS}
)

set(${PROJECT_NAME}_ALL_FILES
	${${PROJECT_NAME}_SOURCES}
	${${PROJECT_NAME}_HEADERS}
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${FULL_VERSION})


configure_file(
	"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.pc.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc"
	@ONLY
)


# install

install(TARGETS ${PROJECT_NAME} DESTINATION lib COMPONENT runtime)
install(FILES ${${PROJECT_NAME}_PUBLIC_HEADERS} DESTINATION include/${PROJECT_NAME} COMPONENT development)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.h" DESTINATION include COMPONENT development)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION lib/pkgconfig COMPONENT development)


# uninstall
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY
)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)


# pack
include(InstallRequiredSystemLibraries)
# set(CPACK_PACKAGE_DESCRIPTION_FILE ... )
# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "")
# set(CPACK_PACKAGE_ICON ... )
set(CPACK_PACKAGE_VENDOR "Kuzma Shapran")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
include(CPack)
