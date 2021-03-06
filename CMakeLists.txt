cmake_minimum_required(VERSION 3.14.0)

project(ChernoOpenGL 
        VERSION 0.0.0
        LANGUAGES CXX
        DESCRIPTION "Youtube ChernoOpenGL")

set(GLEW_USE_STATIC_LIBS TRUE)
add_compile_definitions(GLEW_STATIC)

#Sets ups the module path to work with the a custom on so the defualt CMake modules work.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}../../../glew-2.1.0/")

set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../SDL2-2.0.10/include")
set(SDL2_LIBRARY "${CMAKE_SOURCE_DIR}../../../SDL2-2.0.10/lib/x64/SDL2.lib")
set(SDL2MAIN_LIBRARY "${CMAKE_SOURCE_DIR}../../../SDL2-2.0.10/lib/x64/SDL2main.lib")
set(IL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}../../../DevIL Windows SDK/include")
set(IL_LIBRARIES "${CMAKE_SOURCE_DIR}../../../DevIL Windows SDK/lib/x64/Release/DevIL.lib")
set(ILU_LIBRARIES "${CMAKE_SOURCE_DIR}../../../DevIL Windows SDK/lib/x64/Release/ILU.lib")
set(ILUT_LIBRARIES "${CMAKE_SOURCE_DIR}../../../DevIL Windows SDK/lib/x64/Release/ILUT.lib")

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(DevIL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${IL_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/res")

add_executable(Practice main.cpp Game.h Game.cpp)

add_subdirectory(Graphics)

if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINRARY_DIR)
    #Adds the resources to build directory
    #TODO try and find a better solution than this.
    #add_custom_command(
    #    TARGET Practice
    #    PRE_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E copy_directory
    #        "${CMAKE_SOURCE_DIR}/Graphics/res"
    #        "$<TARGET_FILE_DIR:Practice>/res")

    #Adds the shared libraries to exe
    add_custom_command(
        TARGET Practice
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/External"
             $<TARGET_FILE_DIR:Practice>)
endif()

target_link_libraries(Practice PRIVATE OpenGL::GL OpenGL::GLU SDL2::Core SDL2::Main GLEW::GLEW ${IL_LIBRARIES} ${ILU_LIBRARIES} ${ILUT_LIBRARIES} Graphics_lib)