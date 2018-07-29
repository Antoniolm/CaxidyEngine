
add_library(GraphicEngine OBJECT 
    camera.cpp
    celshading.cpp
    decorationobject.cpp
    endmapregion.cpp
    gamestate.cpp
    icon.c
    loaderthread.cpp
    nodescenegraph.cpp
    notification.cpp
    object3d.cpp
    objectscene.cpp
    optionmanager.cpp
    particle.cpp
    particlesystem.cpp
    profile.cpp
    region.cpp
    rootmap.cpp
    shadowmanager.cpp
    shadowtexture.cpp
    speakingsketch.cpp
    text.cpp
    voxel.cpp
    voxelgroup.cpp
    window.cpp

    animation/animationlist.cpp
    animation/scriptanimation.cpp
    animation/scriptlmd.cpp

    avatar/avatar.cpp
    avatar/avatarmove.cpp

    collection/collection.cpp
    collection/materialcollection.cpp
    collection/meshcollection.cpp
    collection/soundcollection.cpp

    context/context.cpp
    context/materialstack.cpp
    context/matrixstack.cpp
    context/shader.cpp

    controller/controller.cpp
    controller/controllermanager.cpp
    controller/gamepadcontroller.cpp
    controller/keyboardcontroller.cpp

    light/directionallight.cpp
    light/light.cpp
    light/pointlight.cpp

    material/material.cpp
    material/stb_image.c
    material/texture.cpp

    matrix/acceleratedmovement.cpp
    matrix/axisrotation.cpp
    matrix/linearmovement.cpp
    matrix/matrix4f.cpp
    matrix/matrix4fdynamic.cpp
    matrix/matrixscript.cpp
    matrix/matrixstatic.cpp
    matrix/oscillaterotation.cpp

    menu/controlmenu.cpp
    menu/creditscreen.cpp
    menu/deadmenu.cpp
    menu/inventorymenu.cpp
    menu/loadingscreen.cpp
    menu/mainmenu.cpp
    menu/menu.cpp
    menu/moviescreen.cpp
    menu/optionmenu.cpp
    menu/pausemenu.cpp

    mesh/file_obj.cpp
    mesh/mesh.cpp
    mesh/objectgroup.cpp

    sound/effect.cpp
    sound/music.cpp
    sound/sound.cpp

    voxels/rottenvoxel.cpp
    voxels/slidetrap.cpp
    voxels/trapdoor.cpp

    ColladaParser/SkinLoader.cpp
    ColladaParser/XmlParserUtils.cpp
    ColladaParser/SkeletonLoader.cpp
    ColladaParser/GeometryLoader.cpp
    ColladaParser/AnimationLoader.cpp
    ColladaParser/ColladaLoader.cpp
)

target_include_directories(GraphicEngine PRIVATE 
    ${SDL2_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/GraphicEngine"
    "${CMAKE_SOURCE_DIR}/src/VideoGame"
    "${CMAKE_SOURCE_DIR}/resources/lib"
)
