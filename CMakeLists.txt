cmake_minimum_required(VERSION 3.29)
project(crazy_pong)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(crazy_pong src/main.cpp)

# Include header directories
target_include_directories(crazy_pong PRIVATE ./inc)
target_include_directories(crazy_pong PRIVATE ./deps/tgui/include)
target_include_directories(crazy_pong PRIVATE ./deps/sfml/include)

# Define macros for static libraries
target_compile_definitions(crazy_pong PRIVATE SFML_STATIC)
target_compile_definitions(crazy_pong PRIVATE TGUI_STATIC)

# Link libraries depending on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(crazy_pong PRIVATE ./deps/tgui/lib/libtgui-s-d.a)
    target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libsfml-graphics-s-d.a)
    target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libsfml-window-s-d.a)
    target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libsfml-system-s-d.a)
else()
    target_link_libraries(crazy_pong PRIVATE ./deps/tgui/lib/libtgui-s.a)
    target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libsfml-graphics-s.a)
    target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libsfml-window-s.a)
    target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libsfml-system-s.a)
endif()

# Link other necessary libraries
target_link_libraries(crazy_pong PRIVATE ./deps/sfml/lib/libfreetype.a)
target_link_libraries(crazy_pong PRIVATE opengl32)
target_link_libraries(crazy_pong PRIVATE winmm)
target_link_libraries(crazy_pong PRIVATE gdi32)