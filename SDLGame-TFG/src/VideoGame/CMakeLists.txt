add_executable(main 
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    coin.cpp
    door.cpp
    enemylist.cpp
    equipment.cpp
    game.cpp
    gamestatechild.cpp
    herostate.cpp
    inventory.cpp
    inventorymenugame.cpp
    item.cpp
    jumpbutton.cpp
    movablevoxel.cpp
    potion.cpp
    projectile.cpp
    projectilesystem.cpp
    respawnvoxel.cpp
    rootmapgame.cpp
    savedmanager.cpp
    soulcarrier.cpp
    soul.cpp
    spiketrap.cpp
    textregion.cpp

    avatar/enemy.cpp
    avatar/hero.cpp
    avatar/mate.cpp
    avatar/meleeenemy.cpp
    avatar/npc.cpp
    avatar/rangedenemy.cpp

    ia/iaenemy.cpp
    ia/iameleeenemy.cpp
    ia/ianpc.cpp
    ia/iarangedenemy.cpp

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