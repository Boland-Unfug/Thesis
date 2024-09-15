cmake_minimum_required(VERSION 3.28)
set(CMAKE_TOOLCHAIN_FILE C:/Users/boogl/.vscode-insiders/Projects/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
project(MySFMLProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wsign-conversion -Wconversion")


# Find SFML. If using a specific component like graphics, window, system, you can specify it
set(SFML_DIR C:/Users/boogl/.vscode-insiders/Projects/vcpkg/installed/x64-mingw-dynamic/share/sfml/)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
set(Box2D_DIR C:/Users/boogl/.vscode-insiders/Projects/vcpkg/installed/x64-mingw-dynamic/share/box2d/)
find_package(Box2D CONFIG REQUIRED)

# If the SFML was found, link the libraries to your executable
add_executable(MySFMLProject main.cpp PhysicsEngine.cpp RenderingEngine.cpp)
target_link_libraries(MySFMLProject PRIVATE sfml-system sfml-window sfml-graphics)
target_link_libraries(MySFMLProject PRIVATE box2d::box2d)
