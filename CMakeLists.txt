cmake_minimum_required(VERSION 3.10)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(arkanoid
    src/main.cpp
    src/Entity.cpp
    src/Platform.cpp
    src/Ball.cpp
    src/Brick.cpp
    src/utils.cpp
    src/Map.cpp
    src/Game.cpp
    src/PowerfulBrick.cpp
    src/SimpleBrick.cpp
    src/SeriousBrick.cpp
    src/CombatBrick.cpp
    src/MagicBrick.cpp
    src/Bonus.cpp
    src/Rocket.cpp
    )

target_include_directories(arkanoid PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(arkanoid
    PRIVATE
        OpenGL::GL
        ${GLUT_LIBRARIES}
)

if (WIN32)
    set_target_properties(arkanoid PROPERTIES WIN32_EXECUTABLE TRUE)
endif()