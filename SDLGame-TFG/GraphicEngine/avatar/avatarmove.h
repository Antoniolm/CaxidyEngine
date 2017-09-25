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

#ifndef AVATARMOVE_H
#define AVATARMOVE_H

#include "avatar.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/acceleratedmovement.h"
#include "../GraphicEngine/matrix/linearmovement.h"
#include "../GraphicEngine/objectscene.h"

class RootMap;
class Enemy;
class Projectile;
class AvatarMove: public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~AvatarMove();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will move our avatar
        *    @param aMove -> the new movement of our avatar
        *    @param aDir -> the new direction of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool moveBody(vec3f aMove,avatarDirection aDir);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will create the gravity for our avatar
        *    \param time -> the current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * gravity(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will jump our avatar
        *    \param velocity -> the velocity of our jump
        *    @param acceleration -> the acceleration of our movement
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activeJump(vec3f velocity,vec3f acceleration);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will jump our avatar
        *    \param time -> the current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool jump(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will get the position of our avatar
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will get the direction of our avatar
        *    \return avatarDirection
        */
        //////////////////////////////////////////////////////////////////////////
        avatarDirection getDirection();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will show the object in our interface
        *    @param vis -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis) = 0;

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
        *    It will detect if the hero will be hurt for an attack
        *    @param posAvatar -> Position of the avatar that did the hit
        *    @param dirAvatar -> The direction of the avatar that did the hit
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool detectHit(vec3f posAvatar,avatarDirection dirAvatar);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will detect if the hero will be able to protect him for an attack
        *    @param posAvatar -> Position of the avatar that did the hit
        *    @param dirAvatar -> The direction of the avatar that did the hit
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool detectShield(vec3f posAvatar,avatarDirection dirAvatar);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will active an impactMove in our avatar
        *    @param dirAvatar -> The direction of the avatar that did the hit
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activeImpact(avatarDirection dirAvatar);

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
        *    It will manage an impactMove that was activated in our avatar
        *    @param time -> The time of our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void impactMove(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will let to change the direction of our avatar
        *    @param aDir -> the new direction of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void changeDirection(avatarDirection aDir);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a projectile
        *    @param damage -> the damage of the created projectile
        *    \return Projectile *
        */
        //////////////////////////////////////////////////////////////////////////
        Projectile * createProjectile(float damage);

    protected:
        RootMap * currentMap;                   // Current Map
        ObjectScene * currentObject;            // Current object
        Matrix4f * moveAvatar;                  // Matrix 4x4 of the avatar
        avatarDirection direction;              // Direction of the avatar
        AcceleratedMovement * acceleratedMove;  // Accelerated movement
        vec3f impactMovement;                   // Impact movement
        float limitBottom;                      // LimitBottom of the avatar

        //Some flag for know the state of the hero
        bool isMoving,isFalling,isJumping,isMoveCollision,isHitting,isImpacted,isShielded;
        float currentTime;// Current time of the application
        float dmgDelay;   // Time between damage
        float impactTime; // Time for an impact
    private:
};

#endif // AVATARMOVE_H
