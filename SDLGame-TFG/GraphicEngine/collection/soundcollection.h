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

#ifndef SOUNDCOLLECTION_H
#define SOUNDCOLLECTION_H

#include "sound/sound.h"
#include "sound/effect.h"
#include "sound/music.h"
#include <vector>
#include <map>
#include <string>
#include "collection.h"
#include "collection.cpp"

enum SoundIndex{
    sCoin, //0
    sOpen,
    EHIT,
    SHOOT,
    sSWORD,
    sARROW,
    sSHIELD,
    HHIT,
    sWALK,
    sJUMP,
    sATRAP,
    sNTRAP,
    sREAD,
    sMOVIE,
    sMAIN
};

class SoundCollection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~SoundCollection();

        static SoundCollection * getInstance(){
            if(instance == NULL)
                instance = new SoundCollection();

            return instance;
        }

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a sound -> parameters SoundIndex
        *    \return Sound *
        */
        //////////////////////////////////////////////////////////////////////////
        Sound * getSound(SoundIndex element);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a sound -> parameters string
        *    \return Sound *
        */
        //////////////////////////////////////////////////////////////////////////
        Sound * getSound(string element);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will update the volume of all our sounds
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateVolume(float percentage);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        SoundCollection();

        static SoundCollection* instance;        // Instance of soundCollection
        Collection<Sound,SoundIndex> collection; // Collection object
};

#endif // SOUNDCOLLECTION_H
