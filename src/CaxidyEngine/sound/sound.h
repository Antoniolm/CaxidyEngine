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

#ifndef SOUND_H
#define SOUND_H

#include "SDL2/SDL_mixer.h"
#include <string>
#include <iostream>
#include <unistd.h>

#define MAX_CHANNEl 16

namespace CaxidyEngine {

class Sound
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Sound();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    The method will load the sound file
        *    \param aFile -> string with the name of a file.
        *    \param aType -> int with the type of element(music or effect)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual bool loadSound(const std::string & aFile,int aVolume=128 ,int aChannel=-1, int aloop=-1)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will play the loaded sound and return the channel
        *    where is played
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        virtual int play(float distance=0)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will stop the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void stop(int currentChannel=-1)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will pause the loaded sound.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void pause(int currentChannel=-1)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will resume the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void resume(int currentChannel=-1)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show if the sound is playing or not
        *    \return bool true-> The sound is playing
        *                 false-> The sound is not playing
        */
        //////////////////////////////////////////////////////////////////////////
        virtual bool isPlaying(int currentChannel=-1)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show if the sound is paused or not
        *    \return bool true-> The sound is paused
        *                 false-> The sound is not paused
        */
        //////////////////////////////////////////////////////////////////////////
        virtual bool isPause(int currentChannel=-1)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the name of sound file
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        std::string & getFile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the volume of our sound according to the distance
        *    between the hero and the object that will produce the sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateVolume(int currentChannel,float distance);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will change the volume of our sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void changeVolume(float percentage);

    protected:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the volume of our sound and that
        *    depends of the distance with the hero
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int calculateVolume(float distance);

        int channel;              // Channel where the effect will be play
        int loop;                 // Number of loop in a reproduction
        int volume;               // Initial volume of the sound
        int currentVolume;        // Current volume of the sound
        std::string file;              // File of the sound (wav extension)

    private:


};

} // CaxidyEngine

#endif // SOUND_H
