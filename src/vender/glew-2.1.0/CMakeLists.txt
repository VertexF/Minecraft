add_library(GLEW STATIC include/GL/glew.h src/glew.c
                        include/GL/eglew.h
                        include/GL/glxew.h
                        include/GL/wglew.h)

set_target_properties(GLEW PROPERTIES LINKER_LANGUAGE C)

find_package(OpenGL REQUIRED)
if(MSVC)
    set_property(TARGET GLEW PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set_property(
    TARGET GLEW
    APPEND
    PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
)

include_directories(GLEW PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GLEW PRIVATE OpenGL::GL OpenGL::GLU)