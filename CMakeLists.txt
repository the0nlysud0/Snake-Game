cmake_minimum_required(VERSION 3.12)

project(SnakeOGL)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories("Include/")


# Add source files
add_executable(SnakeOGL "Source/main.cpp"
        "Source/graphics/glad.c"
        "Source/graphics/mb_shader.cpp"
        "Source/graphics/mb_renderer.cpp"
        "Source/utils/mb_FileDialog.mm"
        "source/utils/mb_utils.cpp"
        )

# macOS config
if(APPLE)
    # Proper variable reference
    set_source_files_properties(Source/mb_FileDialog.mm PROPERTIES COMPILE_FLAGS "-x objective-c++")
    link_directories("${CMAKE_SOURCE_DIR}/Libs/macOS")
    target_compile_definitions(SnakeOGL PRIVATE MACOS)
    # Link against glfw3 library and the apple default frameworks
    target_link_libraries(SnakeOGL
        "${CMAKE_SOURCE_DIR}/Libs/macOS/libglfw3.a"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo")
elseif(WIN32)
    target_compile_definitions(SnakeOGL PRIVATE WINDOWS)
elseif(UNIX)
    target_compile_definitions(SnakeOGL PRIVATE LINUX)
endif()


# Adds both release and debug configs
target_compile_definitions(SnakeOGL PRIVATE DEBUG)

