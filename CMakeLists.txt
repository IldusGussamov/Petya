cmake_minimum_required(VERSION 3.10)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматический поиск библиотек в MSYS2
list(APPEND CMAKE_PREFIX_PATH "C:/msys64/mingw64")

# Ищем библиотеки
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Добавляем исполняемый файл
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


add_custom_command(TARGET arkanoid POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:arkanoid>/assets
    COMMENT "Copying assets to output directory"
)

# Подключаем заголовки
target_include_directories(arkanoid PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Линкуем библиотеки
target_link_libraries(arkanoid PRIVATE
    OpenGL::GL
    ${GLUT_LIBRARIES}
)

# Для Windows: копируем SOIL.dll автоматически
# if(WIN32)
#     set_target_properties(arkanoid PROPERTIES WIN32_EXECUTABLE TRUE)
# endif()
