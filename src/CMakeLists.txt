file(GLOB_RECURSE ACID_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/Acid/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Acid/*.h"
)

if(MSVC)
    set(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vender/glew-2.1.0/include")
    set(GML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vender/glm")
	set(SFML_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vender/SFML/include")
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ACID_SOURCE})
endif()

set(SFML_USE_STATIC_STD_LIBS TRUE)
set(BUILD_SHARED_LIBS FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_OPENGL_ES FALSE)
add_subdirectory(vender/SFML)
add_subdirectory(vender/glew-2.1.0)

add_library(Acid STATIC ${ACID_SOURCE}) 

if(MSVC)
    set_property(TARGET Acid PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set_property(
    TARGET Acid
    APPEND
    PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
)

add_compile_definitions("$<$<CONFIG:Debug>:ACID_DEBUG>")

# set(PRECOMPILED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/PublicInclude")
# target_precompile_headers(Acid PUBLIC "${PRECOMPILED_HEADER}/PreComp.h")

#${PRECOMPILED_HEADER}
target_include_directories(Acid PUBLIC ${PROJECT_BINARY_DIR}/src/Acid  ${GML_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${SFML_INCLUDE_DIR})
target_link_libraries(Acid PRIVATE GLEW sfml-system sfml-graphics sfml-window sfml-main sfml-audio)