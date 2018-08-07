cmake_minimum_required(VERSION 3.3.2) 

project(GraphicEngine VERSION 1.0)

include(CMakePackageConfigHelpers)  

add_library(GraphicEngine 
    "${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/celshading.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/decorationobject.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/endmapregion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gamestate.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/icon.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/loaderthread.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/nodescenegraph.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/notification.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/object3d.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/objectscene.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/optionmanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/particle.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/particlesystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/profile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/region.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rootmap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shadowmanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shadowtexture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/speakingsketch.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/text.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/voxel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/voxelgroup.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animation/animationlist.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animation/scriptanimation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animation/scriptlmd.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/avatar.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/avatarmove.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/collection/collection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/collection/materialcollection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/collection/meshcollection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/collection/soundcollection.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/context/context.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/context/materialstack.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/context/matrixstack.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/context/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/controller/controller.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/controller/controllermanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/controller/gamepadcontroller.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/controller/keyboardcontroller.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/light/directionallight.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/light/light.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/light/pointlight.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/material/material.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/material/stb_image.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/material/texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/acceleratedmovement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/axisrotation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/linearmovement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/matrix4f.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/matrix4fdynamic.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/matrixscript.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/matrixstatic.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/oscillaterotation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/controlmenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/creditscreen.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/deadmenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/inventorymenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/loadingscreen.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/mainmenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/moviescreen.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/optionmenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/pausemenu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mesh/file_obj.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mesh/mesh.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mesh/objectgroup.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sound/effect.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sound/music.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sound/sound.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/voxels/rottenvoxel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/voxels/slidetrap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/voxels/trapdoor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/SkinLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/XmlParserUtils.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/SkeletonLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/GeometryLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/AnimationLoader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/ColladaLoader.cpp"
)

target_include_directories(GraphicEngine PUBLIC 
    ${SDL2_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/GraphicEngine>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/VideoGame>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/resources/lib>
)

target_link_libraries(GraphicEngine 
    ${SDL2_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES} 
    ${SDL2TTF_LIBRARY}
    ${OPENGL_LIBRARIES}  
    ${GLEW_LIBRARIES}
    Threads::Threads
)

# Set configuration variables
set(version_config "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

# Write configuration version file
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Create a config file of the library
configure_package_config_file(
    "resources/cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME}"
)

# Install target
install(TARGETS GraphicEngine
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    OBJECTS DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    INCLUDES DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)

# Add header files
FILE(GLOB children RELATIVE animation/ animation/*)

FOREACH(child ${children})
    IF(IS_DIRECTORY animation/ ${child})
        message(INSTERESTING ${child})
    ENDIF()
ENDFOREACH()

FILE(GLOB header_files 
    "${CMAKE_CURRENT_SOURCE_DIR}/animation/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/avatar/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ColladaParser/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/collection/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/context/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/controller/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/light/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/material/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/matrix/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/menu/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sound/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/voxels/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

install(
    FILES "${header_files}"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/include/"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME}"
)

install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${PROJECT_NAME}::"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME}"
)
