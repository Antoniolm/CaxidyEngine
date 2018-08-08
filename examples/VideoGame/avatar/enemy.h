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

#ifndef ENEMY_H
#define ENEMY_H


#include "CaxidyEngine/avatar/avatar.h"
#include "CaxidyEngine/avatar/avatarmove.h"
#include "CaxidyEngine/mesh/mesh.h"
#include "CaxidyEngine/collection/meshcollection.h"
#include "CaxidyEngine/animation/scriptlmd.h"
#include "CaxidyEngine/animation/animationlist.h"
#include "CaxidyEngine/context/context.h"
#include "CaxidyEngine/matrix/matrixscript.h"
#include "CaxidyEngine/rootmap.h"
#include "CaxidyEngine/matrix/matrix4f.h"
#include "CaxidyEngine/matrix/acceleratedmovement.h"
#include "CaxidyEngine/sound/sound.h"
#include "CaxidyEngine/text.h"
#include <stdlib.h>

#include <vector>

using namespace std;
class RootMap;
class Text;
class IAEnemy;
class Equipment;
class Enemy: public AvatarMove
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Enemy();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param vis -> the context of our visualization
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
        virtual void updateState(GameState & gameState) = 0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will activated our enemy
        *    @param value -> The value said if the enemy is activated or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatedEnemy(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the enemy is activate or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set radioActivity of our enemy
        *    @param radio -> The new radio value of our enemy
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setRadioActivity(vec3f radio);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get radioActivity of the enemy
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getRadioActivity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the life of the enemy
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the exp of our hero
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        int getExp();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will manage the activated of an impact movement
        *    @param dirAvatar -> The direction of the avatar that did the hit
        *    @param enemies -> List of enemies that the avatar can't go through them
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool canImpact(avatarDirection dirAvatar,const vector<Enemy *> & enemies);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Enemy will take damage when the hero use that method(but depend of some conditions)
        *    @param posAvatar -> the position of our avatar
        *    @param dirAvatar -> the direction of our avatar
        *    @param posHero -> the position of our hero
        *    @param value -> the value of the damage
        *    @param enemies -> the vector of enemies to know if can do the impact movement
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(vec3f posAvatar,avatarDirection dirAvatar,vec3f posHero,float value,const vector<Enemy *> & enemies);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Enemy will take damage when he is on an objectScene with damage
        *    @param value -> the value of the damage
        *    @param posHero -> the position of the hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(float value,vec3f posHero);

    protected:
        vector<Matrix4f *> moveMatrix;              // Vector of movement matrix
        vector<Sound *> enemySound;                 // Vector of sound
        pair<avatarDirection,vec3f> currentMove;    // Current Move of the enemy

        AnimationList animations;                   // List of animations of the enemy
        Equipment * weapon;                         // Weapon of the enemy
        vec3f radioActivity;                        // Radio activity of the enemy
        IAEnemy * IA;                               // Ia of the enemy

        bool enemyActivate;                         // Flag for activation
        bool activatedDialog;                       // Flag for activation
        Text * currentText;                         // Text for the damage
        float jumpDelay,hitDelay,IADelay;           // Some delay between action
        int experience;                             // Experience that the hero gain when the enemy die
    private:

};

#endif // ENEMY_H
