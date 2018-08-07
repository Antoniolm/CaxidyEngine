
add_executable(BasicVideoGame 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/coin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gamestatechild.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/herostate.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/item.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/jumpbutton.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/movablevoxel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/potion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/projectile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/projectilesystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/respawnvoxel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rootmapgame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/savedmanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/spiketrap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/hero.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/npc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ia/ianpc.cpp"
)

target_include_directories(BasicVideoGame PRIVATE ${SDL2_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/GraphicEngine"
    "${CMAKE_SOURCE_DIR}/examples/BasicVideoGame"
    "${CMAKE_SOURCE_DIR}/resources/lib"
)

target_link_libraries(BasicVideoGame 
    ${SDL2_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${SDL2TTF_LIBRARY}
    ${OPENGL_LIBRARIES}  
    ${GLEW_LIBRARIES}
    Threads::Threads
    GraphicEngine
)
