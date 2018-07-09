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

add_executable(main src/main.cpp
    src/GraphicEngine/camera.cpp
    src/GraphicEngine/celshading.cpp
    src/GraphicEngine/decorationobject.cpp
    src/GraphicEngine/endmapregion.cpp
    src/GraphicEngine/gamestate.cpp
    src/GraphicEngine/icon.c
    src/GraphicEngine/loaderthread.cpp
    src/GraphicEngine/nodescenegraph.cpp
    src/GraphicEngine/notification.cpp
    src/GraphicEngine/object3d.cpp
    src/GraphicEngine/objectscene.cpp
    src/GraphicEngine/optionmanager.cpp
    src/GraphicEngine/particle.cpp
    src/GraphicEngine/particlesystem.cpp
    src/GraphicEngine/profile.cpp
    src/GraphicEngine/region.cpp
    src/GraphicEngine/rootmap.cpp
    src/GraphicEngine/shadowmanager.cpp
    src/GraphicEngine/shadowtexture.cpp
    src/GraphicEngine/speakingsketch.cpp
    src/GraphicEngine/text.cpp
    src/GraphicEngine/voxel.cpp
    src/GraphicEngine/voxelgroup.cpp
    src/GraphicEngine/window.cpp

    src/GraphicEngine/animation/animationlist.cpp
    src/GraphicEngine/animation/scriptanimation.cpp
    src/GraphicEngine/animation/scriptlmd.cpp

    src/GraphicEngine/avatar/avatar.cpp
    src/GraphicEngine/avatar/avatarmove.cpp

    src/GraphicEngine/collection/collection.cpp
    src/GraphicEngine/collection/materialcollection.cpp
    src/GraphicEngine/collection/meshcollection.cpp
    src/GraphicEngine/collection/soundcollection.cpp

    src/GraphicEngine/context/context.cpp
    src/GraphicEngine/context/materialstack.cpp
    src/GraphicEngine/context/matrixstack.cpp
    src/GraphicEngine/context/shader.cpp

    src/GraphicEngine/controller/controller.cpp
    src/GraphicEngine/controller/controllermanager.cpp
    src/GraphicEngine/controller/gamepadcontroller.cpp
    src/GraphicEngine/controller/keyboardcontroller.cpp

    src/GraphicEngine/light/directionallight.cpp
    src/GraphicEngine/light/light.cpp
    src/GraphicEngine/light/pointlight.cpp

    src/GraphicEngine/material/material.cpp
    src/GraphicEngine/material/stb_image.c
    src/GraphicEngine/material/texture.cpp

    src/GraphicEngine/matrix/acceleratedmovement.cpp
    src/GraphicEngine/matrix/axisrotation.cpp
    src/GraphicEngine/matrix/linearmovement.cpp
    src/GraphicEngine/matrix/matrix4f.cpp
    src/GraphicEngine/matrix/matrix4fdynamic.cpp
    src/GraphicEngine/matrix/matrixscript.cpp
    src/GraphicEngine/matrix/matrixstatic.cpp
    src/GraphicEngine/matrix/oscillaterotation.cpp

    src/GraphicEngine/menu/controlmenu.cpp
    src/GraphicEngine/menu/creditscreen.cpp
    src/GraphicEngine/menu/deadmenu.cpp
    src/GraphicEngine/menu/inventorymenu.cpp
    src/GraphicEngine/menu/loadingscreen.cpp
    src/GraphicEngine/menu/mainmenu.cpp
    src/GraphicEngine/menu/menu.cpp
    src/GraphicEngine/menu/moviescreen.cpp
    src/GraphicEngine/menu/optionmenu.cpp
    src/GraphicEngine/menu/pausemenu.cpp

    src/GraphicEngine/mesh/file_obj.cpp
    src/GraphicEngine/mesh/mesh.cpp
    src/GraphicEngine/mesh/objectgroup.cpp

    src/GraphicEngine/sound/effect.cpp
    src/GraphicEngine/sound/music.cpp
    src/GraphicEngine/sound/sound.cpp

    src/GraphicEngine/voxels/rottenvoxel.cpp
    src/GraphicEngine/voxels/slidetrap.cpp
    src/GraphicEngine/voxels/trapdoor.cpp

    src/GraphicEngine/ColladaParser/SkinLoader.cpp
    src/GraphicEngine/ColladaParser/XmlParserUtils.cpp
    src/GraphicEngine/ColladaParser/SkeletonLoader.cpp

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