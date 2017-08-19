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

#ifndef WEAPON_H
#define WEAPON_H

#include "equipment.h"
#include "item.h"
#include "../GraphicEngine/material/material.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../GraphicEngine/matrix/axisrotation.h"
#include "../GraphicEngine/sound/sound.h"

enum WeaponType{
    RANGED,
    MELEE
};

class Weapon : public Equipment
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Weapon(const Value & weaponFeatures);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        *    @param aPos -> the initial position of our weapon
        *    @param atype -> the type of weapon that will be our new weapon
        *    @param aDamage -> the damage of our weapon
        *    @param mesh -> the mesh that will have our weapon
        *    @param material -> the material that will have our weapon
        */
        //////////////////////////////////////////////////////////////////////////
        Weapon(vec3f aPos,WeaponType atype,float aDamage,string mesh,string material);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Weapon();

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
        *    It will set the damage of our weapon
        *    @param value -> the new value of our damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of our weapon
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the type of our weapon
        *    \return WeaponType
        */
        //////////////////////////////////////////////////////////////////////////
        WeaponType getWeaponType();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set our weapon like another weapon
        *    @param weapon -> the new value of our object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setWeapon(const Weapon & weapon);

    protected:

    private:
        float damage;           // Damage of the weapon
        WeaponType typeWeapon;        // Type of the weapon
};

#endif // WEAPON_H
