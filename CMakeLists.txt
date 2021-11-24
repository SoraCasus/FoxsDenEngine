cmake_minimum_required( VERSION 3.20 )
project( FoxsDenEngine )

set( CMAKE_CXX_STANDARD 23 )

set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Wall -Wextra -DFD_DEBUG" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

set( FD_DEPS ${CMAKE_SOURCE_DIR}/_deps )

# Include OpenGL
find_package( OpenGL REQUIRED )

# Include SFML
add_subdirectory( ${FD_DEPS}/SFML )
set( FD_SFML_LIBS sfml-system sfml-window sfml-network sfml-graphics sfml-audio )

# Include JSON
set( JSON_BuildTexts OFF CACHE INTERNAL "" )
add_subdirectory( ${FD_DEPS}/json )
set( FD_JSON_LIBS nlohmann_json::nlohmann_json )

# Include spdlog
add_subdirectory( ${FD_DEPS}/spdlog )
set( FD_SPDLOG_LIBS spdlog::spdlog )

# Include ImGui


file( WRITE ${CMAKE_BINARY_DIR}/cmake-scripts/GenIncludes.cmake
        "file(
            COPY ${CMAKE_SOURCE_DIR}/foxsden
            DESTINATION ${CMAKE_SOURCE_DIR}/include
            FILES_MATCHING PATTERN *.h) \n" )


# ENGINE
add_library( FoxsDenEngine SHARED foxsden/Test.h foxsden/Test.cpp )
target_link_libraries( FoxsDenEngine ${FD_SFML_LIBS} ${OPENGL_LIBRARIES} ${FD_JSON_LIBS} ${FD_SPDLOG_LIBS} )
target_compile_definitions( FoxsDenEngine PUBLIC FD_BUILD_DLL )
target_include_directories( FoxsDenEngine PRIVATE ${FD_DEPS}/SFML/include )
target_include_directories( FoxsDenEngine PRIVATE ${OPENGL_INCLUDE_DIRS} )
target_include_directories( FoxsDenEngine PRIVATE ${FD_DEPS}/spdlog/include )
target_include_directories( FoxsDenEngine PRIVATE ${FD_DEPS}/json/include )

# SANDBOX
add_executable( FoxsDenEngine-Sandbox sandbox/main.cpp )
target_link_libraries( FoxsDenEngine-Sandbox FoxsDenEngine ${FD_SFML_LIBS} ${OPENGL_LIBRARIES} ${FD_JSON_LIBS} )
target_include_directories( FoxsDenEngine-Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/include )
target_include_directories( FoxsDenEngine-Sandbox PRIVATE ${OPENGL_INCLUDE_DIRS} )
target_include_directories( FoxsDenEngine-Sandbox PRIVATE ${FD_DEPS}/json/include )

add_custom_command(
        TARGET FoxsDenEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -P
        ${CMAKE_BINARY_DIR}/cmake-scripts/GenIncludes.cmake
)

