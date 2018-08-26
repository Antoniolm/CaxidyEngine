// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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
#include "rapidjson/document.h"
#include "CaxidyEngine/object3d.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "CaxidyEngine/material/material.h"
#include "CaxidyEngine/matrix/matrix4f.h"
#include "CaxidyEngine/matrix/matrix4fdynamic.h"
#include "CaxidyEngine/collection/meshcollection.h"
#include "CaxidyEngine/collection/soundcollection.h"
#include "CaxidyEngine/matrix/axisrotation.h"
#include "CaxidyEngine/sound/sound.h"

using namespace rapidjson;

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
        Equipment();

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
        Equipment(vec3f aPos,EquipmentType atype, bool aEquipped ,int aDmg,int aLife, int aArmour,string aImg,string aMesh,string aMaterial,string aName);

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

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the image profile of the equipment
        *    @param imageFile -> the new value of the image profile
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setImageProfile(const string & imageFile);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of the equipment
        *    @param dmg -> the new value of the damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(int dmg);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of the equipment
        *    @param aMesh -> the new value of the mesh
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setMesh(const string & aMesh);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of the equipment
        *    @param aMaterial -> the new value of the material
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setMaterial(const string & aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of the equipment
        *    @param aName -> the new value of the name
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setName(const string & aName);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of our equipment
        *    @param anArmour -> the new value of our damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setArmour(int anArmour);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of the equipment
        *    @param aLife -> the new value of our damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setLife(int aLife);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the type of the equipment
        *    @param aTypeEquip -> the new value of the type of the equipment
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setEquipType(EquipmentType aTypeEquip);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the equipment is equipped or not
        *    @param isEquip -> the new value -> true is equipped - false is not equipped
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setEquipped(bool isEquip);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the position of the equipment in the avatar
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosInAvatar();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of the equipment
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the image profile of the equipment
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getImageProfile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the mesh of the equipment
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getMesh();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the material of the equipment
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getMaterial();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the name of the equipment
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getName();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the armour of the equipment
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getArmour();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the life of the equipment
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the equipment type of the equipment
        *    \return EquipmentType
        */
        //////////////////////////////////////////////////////////////////////////
        EquipmentType getEquipType();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the equipment is equipped or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isEquipped();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set our equipment like another equipment
        *    @param equip -> the new value of our object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setEquip(const Equipment & equip);

    protected:

    private:
        string name;                // Name of the equipment
        string imageProfile;        // Image profile of the equipment
        string mesh;                // Mesh of the equipment
        string material;            // Material of the equipment
        EquipmentType equipType;    // type of the equipment

        int damage;                 // Damage of the equipment
        int armour;                 // Armour of the equipment
        int life;                   // Life of the equipment

        bool equipped;              // Flag to know if is equipped or not

        vec3f posInAvatar;          // Position on the avatar of the equipment
        Matrix4f * transObject;     // Matrix4f with the position of the equipment
};

#endif // EQUIPMENT_H
