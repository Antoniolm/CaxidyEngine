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

#include "music.h"

Music::Music()
{
    file="";
}

//**********************************************************************//

Music::~Music()
{
    if(music !=NULL)
        Mix_FreeMusic(music);
}

//**********************************************************************//

Music::Music(Music & aSound){
    file=aSound.file;
    channel=aSound.channel;
    loop=aSound.loop;
    volume=aSound.volume;
    currentVolume=volume;

    music= Mix_LoadMUS(&file[0u]);
    if( music == NULL ) cout<< "Unable to load the background music ->"<< file<<endl;
}

//**********************************************************************//

Music::Music(const string & aFile,int aVolume,int aChannel,int aloop){
    cout<< "Music ->"<< aFile<<endl;
    file=aFile;
    channel=aChannel;
    loop=aloop;
    volume=aVolume;
    currentVolume=volume;

    music= Mix_LoadMUS(&file[0u]);
    if( music == NULL ) cout<< "Unable to load the background music ->"<< file<<endl;
}

//**********************************************************************//

int Music::play(float distance){
    int currentChannel=channel;

    if(Mix_PlayingMusic()==0){
        Mix_PlayMusic(music, loop);
        Mix_VolumeMusic(volume);
    }

    return currentChannel;
}

//**********************************************************************//

void Music::stop(int currentChannel){
    if(Mix_PlayingMusic()==1)
        Mix_HaltMusic();
}

//**********************************************************************//

void Music::pause(int currentChannel){
    if(Mix_PausedMusic()==0)
        Mix_PauseMusic();
}

//**********************************************************************//

void Music::resume(int currentChannel){
    if(Mix_PausedMusic()==1)
        Mix_ResumeMusic();
}

//**********************************************************************//

bool Music::isPlaying(int currentChannel){
    bool result=false;

    if(Mix_PlayingMusic()==1)
        result=true;

    return result;
}

//**********************************************************************//

bool Music::isPause(int currentChannel){
    bool result=false;

    if(Mix_PausedMusic()==1)
        result=true;

    return result;
}

//**********************************************************************//

bool Music::loadSound(const string & aFile,int aVolume,int aChannel,int aloop){
    file=aFile;
    channel=aChannel;
    loop=aloop;
    volume=aVolume;
    currentVolume=volume;

    bool result = true;

    music= Mix_LoadMUS(&file[0u]);
    if( music == NULL ){
        cout<< "Unable to load the background music ->"<< file<<endl;
        result=false;
    }

    return result;
}

