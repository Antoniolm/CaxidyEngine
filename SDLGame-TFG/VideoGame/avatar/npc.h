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

#ifndef NPC_H
#define NPC_H

#include "../GraphicEngine/ia/ianpc.h"
#include "../../GraphicEngine/avatar/avatar.h"
#include "../GraphicEngine/mesh/mesh.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/matrix/structdata.h"
#include "../GraphicEngine/animation/scriptlmd.h"
#include "../lib/rapidjson/document.h"
#include "../rootmapgame.h"
#include "SDL2/SDL_ttf.h"

using namespace rapidjson;

class Text;
class Npc : public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Npc();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *    @param npcFeatures -> the value json that contain all the information of the npc
        */
        //////////////////////////////////////////////////////////////////////////
        Npc(const Value & npcFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Npc();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new dialog in our avatar
        *    \param state -> the new element of our vector
        *    \param speaker -> the speaker of our new state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addDialog(const string state,speakerMessage speaker);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will show the current dialog of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void currentDialog();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will pass for the next dialog of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void nextDialog();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of dialog of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumDialog();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
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
        *    It will activate our npc
        *    @param value -> Bool that indicate if the conversation with our
        *                    npc is enable or disable
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateNpc(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the avatar is activate or not.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getActivate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the position of our avatar
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will check if that npc is in the first state.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isInitialState();


    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our npc
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        IANpc stateMachine;             // State of machine
        Text * currentText;             // Current text of the npc
        ScriptLMD animation;            // Animation of the npc
        vector<Matrix4f *> moveMatrix;  // Vector of movement
        bool npcActivate,heroActivate;  // Flag of the conversation
        float dialogTime;               // Time between states
};

#endif // NPC_H
