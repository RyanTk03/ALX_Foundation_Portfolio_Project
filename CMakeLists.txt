cmake_minimum_required(VERSION 3.29)
project("Crazy_Pong")

set(CMAKE_CXX_STANDARD 17)

# Add the executable
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "inc/*.h")
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include header directories
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/tgui/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/include)

# Define macros for static libraries
target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)
target_compile_definitions(${PROJECT_NAME} PRIVATE TGUI_STATIC)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libogg.a
        ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libFLAC.a
        ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libvorbisenc.a
        ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libvorbisfile.a
        ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libvorbis.a
        ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libopenal32.a)
# Link other libraries depending on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/tgui/lib/libtgui-s-d.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-graphics-s-d.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-window-s-d.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-system-s-d.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-network-s-d.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-main-d.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-audio-s-d.a)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/tgui/lib/libtgui-s.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-graphics-s.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-window-s.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-system-s.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-network-s.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-audio-s.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libsfml-main.a)
endif()

# Link necessary libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    opengl32
    ${PROJECT_SOURCE_DIR}/deps/sfml/lib/libfreetype.a
    winmm
    gdi32
)