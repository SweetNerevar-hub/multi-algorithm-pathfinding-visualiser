list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(FindGLFW)

target_link_libraries(MAPV PRIVATE glfw)