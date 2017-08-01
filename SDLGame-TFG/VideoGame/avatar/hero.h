// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
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

#ifndef HERO_H
#define HERO_H

#include "avatar.h"
#include "avatarmove.h"
#include "../GraphicEngine/mesh/mesh.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/materialcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../GraphicEngine/animation/scriptlmd.h"
#include "../GraphicEngine/context/context.h"
#include "../GraphicEngine/matrix/matrixscript.h"
#include "../GraphicEngine/rootmap.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/acceleratedmovement.h"
#include "../GraphicEngine/sound/sound.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/animation/animationlist.h"
#include "../GraphicEngine/controller/controller.h"
#include "../lib/rapidjson/document.h"
#include "soul.h"
#include <stdlib.h>


#include <vector>

using namespace std;
class RootMap;
class Text;
class Weapon;
class Soul;
class Projectile;
class Hero: public AvatarMove
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *    @param aPos -> the initial position of our hero
        */
        //////////////////////////////////////////////////////////////////////////
        Hero(vec3f aPos);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Hero();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param vis -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will enable the sound of our hero.That will use when the game
        *    will be pause.
        *    @param value -> Bool that indicate if the sound is enable or disable
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void enableSound(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set a new message for our text
        *    \param message -> it is the new message that our text will show
        *    @param index -> The index of our text in the vector of texts
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDialog(string message,int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the text of our hero
        *    @param value -> Bool that indicate if the text is enable or disable
        *    @param index -> The index of our text in the vector of texts
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateDialog(bool value,int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set the coins of our hero
        *    @param value -> The new value of our coins.
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        void setCoin(int value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set if the hero take a soul in his arm
        *    @param aSoul -> the current soul that our hero has taken
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setSoul(Soul * aSoul);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will reset animations because the hero isn't in movement
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void noMove();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return if the hero is hitting or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isHit();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the life of our hero
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the coins of our hero
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getCoin();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get if the hero take a soul in his arm
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        Soul * getSoul();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new coin to our current coins
        *    @param value -> Adding to our courrent coint the value
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addCoin(int value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Hero will take damage when a enemy use that method(but depend of some conditions)
        *    @param posAvatar -> the position of the enemy avatar
        *    @param dirAvatar -> the direction of the enemy avatar
        *    @param value -> the value of the damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(vec3f posAvatar,avatarDirection dirAvatar,float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Hero will take damage when he is on an objectScene with damage
        *    @param value -> the value of the damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(float value);
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        vector<Projectile *> projectiles;   // Vector of projectiles
        vector<Matrix4f *> moveMatrix;      // Vector of movements
        vector<Sound *> heroSound;          // Vector of sounds
        vector<int> channelSound;           // Vector of channels for the sound
        AnimationList animations;           // List of animations of the hero
        vector<Text *> texts;               // Vector of texts
        vector<bool> activatedTexts;        // Vector of state of texts
        Soul * soul;                        // Soul catch in the arms of the hero
        Weapon * currentWeapon;             // Current weapon of the hero
        Weapon * meleeWeapon;               // Close weapon of the hero
        Weapon * rangedWeapon;              // Ranged weapon of the hero

        //Some delays for action of the hero
        float jumpDelay,hitDelay,coinDelay,shieldDelay,swapDelay,shootDelay,swordDelay;
        int currentCoin;    //Current coin of the hero
};

#endif // HERO_H


