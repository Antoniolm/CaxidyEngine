project(prueba)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/resources/cmake")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

INCLUDE(FindPkgConfig)
INCLUDE(resources/cmake/FindSDL2_mixer.cmake)
INCLUDE(resources/cmake/FindSDL2TTF.cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory("src/GraphicEngine")

add_executable(main src/main.cpp
    src/VideoGame/coin.cpp
    src/VideoGame/door.cpp
    src/VideoGame/enemylist.cpp
    src/VideoGame/equipment.cpp
    src/VideoGame/game.cpp
    src/VideoGame/gamestatechild.cpp
    src/VideoGame/herostate.cpp
    src/VideoGame/inventory.cpp
    src/VideoGame/inventorymenugame.cpp
    src/VideoGame/item.cpp
    src/VideoGame/jumpbutton.cpp
    src/VideoGame/movablevoxel.cpp
    src/VideoGame/potion.cpp
    src/VideoGame/projectile.cpp
    src/VideoGame/projectilesystem.cpp
    src/VideoGame/respawnvoxel.cpp
    src/VideoGame/rootmapgame.cpp
    src/VideoGame/savedmanager.cpp
    src/VideoGame/soulcarrier.cpp
    src/VideoGame/soul.cpp
    src/VideoGame/spiketrap.cpp
    src/VideoGame/textregion.cpp

    src/VideoGame/avatar/enemy.cpp
    src/VideoGame/avatar/hero.cpp
    src/VideoGame/avatar/mate.cpp
    src/VideoGame/avatar/meleeenemy.cpp
    src/VideoGame/avatar/npc.cpp
    src/VideoGame/avatar/rangedenemy.cpp

    src/VideoGame/ia/iaenemy.cpp
    src/VideoGame/ia/iameleeenemy.cpp
    src/VideoGame/ia/ianpc.cpp
    src/VideoGame/ia/iarangedenemy.cpp

    $<TARGET_OBJECTS:GraphicEngine>
)

target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/GraphicEngine"
    "${CMAKE_SOURCE_DIR}/src/VideoGame"
    "${CMAKE_SOURCE_DIR}/resources/lib"
)

target_link_libraries(main 
    ${SDL2_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${SDL2TTF_LIBRARY}
    ${OPENGL_LIBRARIES}  
    ${GLEW_LIBRARIES}
    Threads::Threads
)