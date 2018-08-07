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

#ifndef SPIKETRAP_H
#define SPIKETRAP_H

#include "GraphicEngine/object3d.h"
#include "enemylist.h"
#include "avatar/enemy.h"
#include "GraphicEngine/nodescenegraph.h"
#include "GraphicEngine/matrix/matrix4f.h"
#include "GraphicEngine/matrix/matrix4fdynamic.h"
#include "GraphicEngine/collection/meshcollection.h"
#include "GraphicEngine/collection/materialcollection.h"
#include "GraphicEngine/collection/soundcollection.h"
#include "rapidjson/document.h"

using namespace rapidjson;

class SpikeTrap : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param spikeFeatures -> the value json that contain all the information of our spikeTrap object
        */
        //////////////////////////////////////////////////////////////////////////
        SpikeTrap(const Value & spikeFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~SpikeTrap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

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
        *    It will set the damage of our spike trap
        *    @param value -> the new value of our damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of our spike trap
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the trap is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of the spike trap
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Check the enemies that can activate the spikeTrap
        *    \return vector<Int> -> Enemies on top it
        */
        //////////////////////////////////////////////////////////////////////////
        std::vector<int> checkEnemies(std::vector<Enemy *> & enemies);

        NodeSceneGraph * root;      // Root of the object
        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the spiketrap
        ScriptLMD * animationUp;    // Up animation of the spike trap
        ScriptLMD * animationDown;  // Down animation of the spike trap
        float delayTime;            // Delay time
        float hitDelay;             // time between hit the hero
        float desactivatedDelay;    // Delay time for its deactivation
        float activatedTime;        // Time for its activation
        float damage;               // Damage of the spike trap
        bool activated;             // Flag to activation
        bool delayActivated;        // Flag to delay time
        Sound * activatedTrap;      // Sound for its activation
        Sound * animationSound;     // Sound for its up animation
};

#endif // SPIKETRAP_H
