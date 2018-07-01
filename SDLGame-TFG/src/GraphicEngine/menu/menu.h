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

#ifndef MENU_H
#define MENU_H

#include "GraphicEngine/object3d.h"

class NodeSceneGraph;
class Mesh;
class GameState;
class Context;
class Texture;
class Material;
class Sound;
class Menu : public Object3D
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Menu();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new texture for another option that our menu will have
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addOption(Texture * aTexture);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the position of our menu
        *    @param aPosition -> the new position of our menu
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f aPosition);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv) = 0 ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState) = 0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get if the menu is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivate();


    protected:
        NodeSceneGraph * root;      // Root of the object
        Matrix4f * positionMenu;    // Position of the menu
        bool activateMenu;          // Flag for activated menu
        vector<Texture *> options;  // Vector of options
        int currentOption;          // Current option
        Material * currentMaterial; // Current material
        Material * materialBack;    // Material back
        float menuDelay;            // Delay between options

    private:

};

#endif // MENU_H
