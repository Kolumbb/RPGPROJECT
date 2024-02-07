cmake_minimum_required(VERSION 3.27)
project(Platformer)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY  https://github.com/SFML/SFML.git
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(
        Platformer
        ${SOURCE_FILES}
)

target_precompile_headers(Platformer PRIVATE src/ResourcePath.hpp)

target_link_libraries(Platformer PRIVATE sfml-audio)
target_link_libraries(Platformer PRIVATE sfml-system)
target_link_libraries(Platformer PRIVATE sfml-network)
target_link_libraries(Platformer PRIVATE sfml-window)
target_link_libraries(Platformer PRIVATE sfml-graphics)

install(TARGETS Platformer)




