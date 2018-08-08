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

#ifndef ANIMATIONLIST_H
#define ANIMATIONLIST_H

#include <vector>
#include "scriptlmd.h"

namespace CaxidyEngine {

class AnimationList
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        AnimationList();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~AnimationList();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new animation
        *    @param animation -> the new element added to our animation list
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(ScriptLMD * animation);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate an animation
        *    @param the position of the scriptLMD that our want to activate
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate(int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will update the current animation
        *    @param time -> the time between the lastTime and the currentTime
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void update(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will reset an animation
        *    @param the position of the scriptLMD that our want to reset
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void resetAnimation(int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the current state
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the activated animation
        *    \return ScriptLMD *
        */
        //////////////////////////////////////////////////////////////////////////
        ScriptLMD * getAnimation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of animation of our list
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumAnimation();

    protected:

    private:
        std::vector<ScriptLMD *> animations;
        int currentAnimation;
};

} // CaxidyEngine

#endif // ANIMATIONLIST_H
