cmake_minimum_required(VERSION 3.19.0)

project(Minecraft 
        VERSION 0.0.0
        LANGUAGES CXX C
        DESCRIPTION "Minecraft clone")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GAME_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/GameSrc/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/GameSrc/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/GameSrc/*.glsl"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ACID_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Acid")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${GAME_SOURCE})

add_subdirectory(src)

add_executable(Minecraft ${GAME_SOURCE})

if(MSVC)
    set_property(TARGET Minecraft PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_compile_options(Minecraft PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
)

set_property(
    TARGET Minecraft
    APPEND
    PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
)

#Using a bit of post-processing we can select the varaiables we need to
#get the correct version of the share library after compiling it.
#As we have already built the Game target it will know where to copy it to.
add_custom_command(TARGET Minecraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/GameSrc/Resources"
        $<TARGET_FILE_DIR:Minecraft>)

add_custom_command(TARGET Minecraft POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/GameSrc/Resources"
        ${PROJECT_BINARY_DIR})

target_include_directories(Minecraft PUBLIC ${ACID_INCLUDE_DIR})
target_link_libraries(Minecraft PRIVATE Acid)