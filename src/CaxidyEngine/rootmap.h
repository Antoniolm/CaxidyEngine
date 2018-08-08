// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#ifndef ROOTMAP_H
#define ROOTMAP_H

#include "object3d.h"
#include "nodescenegraph.h"
#include <list>
#include <vector>
#include <map>
#include "light/directionallight.h"
#include "light/pointlight.h"
#include "matrix/matrix4f.h"
#include "matrix/matrix4fdynamic.h"
#include "matrix/linearmovement.h"
#include "matrix/axisrotation.h"
#include "matrix/matrixstatic.h"
#include "matrix/oscillaterotation.h"
#include "particlesystem.h"
#include "particle.h"
#include "mesh/mesh.h"
#include "objectscene.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "decorationobject.h"
#include "voxels/voxel.h"
#include "voxelgroup.h"
#include "sound/sound.h"
#include "sound/music.h"
#include "controller/controller.h"
#include "controller/keyboardcontroller.h"
#include "region.h"
#include "endmapregion.h"
#include "notification.h"
#include "loaderthread.h"
#include "menu/moviescreen.h"

namespace CaxidyEngine {

class ObjectGroup;
class ParticleSystem;
class EndMapRegion;
class Notification;
class LoaderThread;
class MovieScreen;

class RootMap : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        RootMap();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RootMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize our rootMap
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        virtual void initialize(std::string fileMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will enable the sound of our rootmap.That will use when the game
        *    will be pause.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void enableSound(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will check if the position (indexObj) is collision with
        *    a objectScene
        *    \return ObjectScene *
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * collision(const vec3f & indexObj);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will check if between the position first and position second there is collision with
        *    a objectScene
        *    \return ObjectScene *
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * collision(const vec3f & posFirst, const vec3f & posSecond);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add the collision of an object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addCollision(vec2f voxelPosition,int objID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will remove the collision of an object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void removeCollision(vec2f voxelPosition,int objID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the light of our map
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatedLight(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the objectGroups of our map
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatedObjectGroup();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will notify is a rootmap is been loading now.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isLoading();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will notify is our map has been finished
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        virtual bool isFinished();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the file of next map
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        std::string getNextMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the movie of next map
        *    \return MovieScreen
        */
        //////////////////////////////////////////////////////////////////////////
        MovieScreen * getMovie();

    protected:

        std::vector<int> indexMap[500][500];             // Array of vector for spacial indexation
        std::vector<ObjectScene *> objs;                 // Vector of objects scene
        std::vector<ObjectGroup *> objectGroup;          // Vector of groups of objects
        std::vector<ObjectScene *> decorationObjs;       // Vector of decorations objects
        std::vector<Object3D *> elements;                // Vector with all the elements of the game
        std::vector<Region *> regions;               // Vector of regions
        std::vector<Light *> lights;                     // Vector of lights
        EndMapRegion * endMapRegion;                // End region of the map
        Notification * title;                       // Title of the map
        ObjectScene * background;                   // Background of the map
        Sound * backSound;                          // back sound of the map
        MovieScreen * movie;                        // Screen of movie of the map
        std::string nextMapFile;                         // Next map
        LoaderThread * loader;                      // Loader of map
        bool loading;                               // Flag the map is loading

    private:
        void deleteObject3d(Object3D * obj);
};

} // CaxidyEngine 

#endif // ROOTMAP_H
