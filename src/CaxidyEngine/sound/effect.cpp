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

#include "effect.h"

namespace CaxidyEngine {
    
Effect::Effect()
{
    file="";
}

//**********************************************************************//

Effect::~Effect()
{
    if(effect!=NULL)
        Mix_FreeChunk(effect);
}

//**********************************************************************//

Effect::Effect(const Effect & aSound){
    file=aSound.file;
    channel=aSound.channel;
    loop=aSound.loop;
    volume=aSound.volume;
    currentVolume=volume;


    effect= Mix_LoadWAV(&file[0u]);
    if( effect == NULL) std::cout<< "Unable to load the effect ->"<< file<< std::endl;

}

//**********************************************************************//

Effect::Effect(const std::string & aFile,int aVolume,int aChannel,int aloop){
    std::cout<< "Sound ->"<< aFile<<std::endl;
    file=aFile;
    channel=aChannel;
    loop=aloop;
    volume=aVolume;
    currentVolume=volume;


    effect= Mix_LoadWAV(&file[0u]);
    if( effect == NULL) std::cout<< "Unable to load the effect ->"<< file<<std::endl;

}

//**********************************************************************//

int Effect::play(float distance){
    int currentChannel=channel;

    if(channel!=-1){ //if have a channel
        Mix_PlayChannel(channel,effect,loop);
        Mix_Volume(channel,volume);
    }
    else{ //if sound has channel -1 ->take the first free channel
        currentChannel=Mix_PlayChannel(-1,effect,loop);
        Mix_Volume(currentChannel,calculateVolume(distance));
    }

    return currentChannel;
}

//**********************************************************************//

void Effect::stop(int currentChannel){
    if(channel!=-1 && Mix_Playing(channel)==1){
        Mix_HaltChannel(channel);
    }
    else if(channel==-1 && currentChannel!=-1)
        Mix_HaltChannel(currentChannel);
}

//**********************************************************************//

void Effect::pause(int currentChannel){
    if(channel!=-1 && Mix_Paused(channel)==0)
        Mix_Pause(channel);
    else if(channel==-1 && currentChannel!=-1)
        Mix_Pause(currentChannel);

}

//**********************************************************************//

void Effect::resume(int currentChannel){
    if(channel!=-1 && Mix_Paused(channel)==1){
        Mix_Resume(channel);
    }
    else if(channel==-1 && currentChannel!=-1)
        Mix_Resume(currentChannel);
}

//**********************************************************************//

bool Effect::isPlaying(int currentChannel){
    bool result=false;

    if(channel!=-1 && Mix_Playing(channel)==1){
        result=true;
    }
    else if(channel==-1 && currentChannel!=-1){
        if(Mix_Playing(currentChannel)==1)
            result=true;
    }

    return result;
}

//**********************************************************************//

bool Effect::isPause(int currentChannel){
    bool result=false;

    if(channel!=-1 && Mix_Paused(channel)==1){
        result=true;
    }
    else if(channel==-1 && currentChannel!=-1){
        if(Mix_Paused(currentChannel)==1)
            result=true;
    }

    return result;
}

//**********************************************************************//

bool Effect::loadSound(const std::string & aFile,int aVolume,int aChannel,int aloop){
    file=aFile;
    channel=aChannel;
    loop=aloop;
    volume=aVolume;
    currentVolume=volume;

    bool result = true;

    effect= Mix_LoadWAV(&file[0u]);
    if( effect == NULL){
        std::cout<< "Unable to load the effect ->"<< file<<std::endl;
        result=false;
    }

    return result;
}

//**********************************************************************//

std::string & Effect::getFile(){
    return file;
}

//**********************************************************************//

void Effect::updateVolume(int currentChannel,float distance){
    if(currentChannel!=-1){
        Mix_Volume(currentChannel,calculateVolume(distance));
    }
}

} // CaxidyEngine
