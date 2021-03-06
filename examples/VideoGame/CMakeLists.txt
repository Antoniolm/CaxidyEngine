
add_executable(main 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/coin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/door.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemylist.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/equipment.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gamestatechild.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/herostate.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/inventory.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/inventorymenugame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/item.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/jumpbuttongame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/movablevoxelgame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/potion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/projectile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/projectilesystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/respawnvoxelgame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rootmapgame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/savedmanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/soulcarrier.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/soul.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/spiketrap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/textregion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/enemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/hero.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/mate.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/meleeenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/npc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/rangedenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ia/iaenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ia/iameleeenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ia/ianpc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ia/iarangedenemy.cpp"
)

target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/CaxidyEngine"
    "${CMAKE_SOURCE_DIR}/examples/VideoGame"
    "${CMAKE_SOURCE_DIR}/resources/lib"
)

target_link_libraries(main 
    ${SDL2_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${SDL2TTF_LIBRARY}
    ${OPENGL_LIBRARIES}  
    ${GLEW_LIBRARIES}
    Threads::Threads
    CaxidyEngine
)
