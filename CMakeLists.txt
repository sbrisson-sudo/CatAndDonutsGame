# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(CatsGame VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Explicitly set CMAKE_PREFIX_PATH to system paths
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu" "/usr/lib" "/usr/local/lib")

include(CMakePrintHelpers)

# Find system fmt package
find_package(fmt REQUIRED PATHS /usr/lib/x86_64-linux-gnu NO_CMAKE_ENVIRONMENT_PATH)

# Find Allegro packages
find_package(PkgConfig REQUIRED)

# Collect all source files from src directory
file(GLOB SOURCES "src/*.cpp" "src/*.h")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 allegro_ttf-5)

cmake_print_variables(ALLEGRO5_LIBRARIES)
cmake_print_variables(ALLEGRO5_INCLUDE_DIRS)

target_link_libraries(${PROJECT_NAME} 
    ${ALLEGRO5_LIBRARIES}
    fmt::fmt
)
target_include_directories(${PROJECT_NAME} PUBLIC ${ALLEGRO5_INCLUDE_DIRS})

# Optional: Add compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
        -Werror
    )
endif()

# Optional: Configure debug and release builds
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Copy the 'sprites' folder to the build directory 
file(COPY ${CMAKE_SOURCE_DIR}/sprites DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/levels DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})
