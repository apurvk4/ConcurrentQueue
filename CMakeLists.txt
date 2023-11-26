cmake_minimum_required(VERSION 3.11)

project(ConcurrentQueue)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_library(ConcurrentQueue INTERFACE)
target_include_directories(ConcurrentQueue INTERFACE
    $<INSTALL_INTERFACE:include/ConcurrentQueue>
)

file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/*.h")
install(FILES ${HEADER_FILES} DESTINATION include/ConcurrentQueue)

install(TARGETS ConcurrentQueue
    EXPORT ConcurrentQueueConfig
    RUNTIME DESTINATION bin/ConcurrentQueue
    ARCHIVE DESTINATION lib/ConcurrentQueue
    LIBRARY DESTINATION lib/ConcurrentQueue
)
install(EXPORT ConcurrentQueueConfig DESTINATION lib/cmake/ConcurrentQueue)
