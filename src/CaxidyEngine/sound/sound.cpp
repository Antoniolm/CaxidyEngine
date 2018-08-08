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

#include "sound.h"

namespace CaxidyEngine {

Sound::~Sound(){

}

//**********************************************************************//

int Sound::play(float distance){
    return 0;
}

//**********************************************************************//

void Sound::stop(int currentChannel){}

//**********************************************************************//

void Sound::pause(int currentChannel){}

//**********************************************************************//

void Sound::resume(int currentChannel){}

//**********************************************************************//

bool Sound::isPlaying(int currentChannel){
    return false;
}

//**********************************************************************//

bool Sound::isPause(int currentChannel){
    return false;
}

//**********************************************************************//

bool Sound::loadSound(const std::string & aFile,int aVolume,int aChannel,int aloop){
    return false;
}

//**********************************************************************//

std::string & Sound::getFile(){
    return file;
}

//**********************************************************************//

void Sound::updateVolume(int currentChannel,float distance){
}

//**********************************************************************//

void Sound::changeVolume(float percentage){
    currentVolume=volume*percentage;
}

//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

int Sound::calculateVolume(float distance){
    int resultVolume;
    float distFactor=0.0;

    if(distance>=10.0) //if is far of 10 is not sound
        resultVolume=0;
    else if(distance <=3.0) //if is near of 3 is 100% sound
        resultVolume=currentVolume;
    else{ //if is between 3 and 10 is a x% sound
        distFactor=1.0-((distance-3.0)/7.0);
        resultVolume=currentVolume*distFactor;
    }

    return resultVolume;
}

} // CaxidyEngine
