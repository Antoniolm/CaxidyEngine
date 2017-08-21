// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David López Machado
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



#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "item.h"

enum EquipmentType{
    RANGED,
    MELEE,
    eSHIELD
};

class Equipment : public Item
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Equipment(const Value & equipFeatures);

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
        Equipment(vec3f aPos,EquipmentType atype,float aDamage,string aMesh,string aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Equipment();

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


        void setImageProfile(const string & imageFile);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of our weapon
        *    @param value -> the new value of our damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(int value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of the equipment
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the image profile of the equip
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getImageProfile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the mesh of the equip
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getMesh();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the material of the equip
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getMaterial();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of the equip
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the armour of the equip
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getArmour();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the life of the equip
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the equipment type of the equip
        *    \return EquipmentType
        */
        //////////////////////////////////////////////////////////////////////////
        EquipmentType getEquipType();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set our equipment like another equipment
        *    @param equip -> the new value of our object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setEquip(const Equipment & equip);

    protected:
        string name;
        string imageProfile;
        string mesh;
        string material;
        EquipmentType equipType;

        int damage;
        int armour;
        int life;
    private:
};

#endif // EQUIPMENT_H
