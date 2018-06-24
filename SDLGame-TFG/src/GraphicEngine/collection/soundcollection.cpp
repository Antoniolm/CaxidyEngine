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

#include "soundcollection.h"

SoundCollection* SoundCollection::instance = NULL;

//**********************************************************************//

SoundCollection::SoundCollection()
{
    cout<< "Game is loading -> sounds"<< endl;
    collection.addElement(new Effect("resources/sounds/coin.wav",30,-1,0));
    collection.addElement(new Effect("resources/sounds/openSound.wav",40,-1,0));
    collection.addElement(new Effect("resources/sounds/enemyHit.wav",50,-1,0));
    collection.addElement(new Effect("resources/sounds/shoot.wav",50,-1,0));
    collection.addElement(new Effect("resources/sounds/sword.wav",5,-1,0));
    collection.addElement(new Effect("resources/sounds/arrowHit.wav",20,-1,0));
    collection.addElement(new Effect("resources/sounds/shield.wav",40,-1,0));
    collection.addElement(new Effect("resources/sounds/heroHit.wav",20,-1,0));
    collection.addElement(new Effect("resources/sounds/walking.wav",40,-1,-1));
    collection.addElement(new Effect("resources/sounds/jump.wav",20,-1,0));
    collection.addElement(new Effect("resources/sounds/fall.wav",60,-1,0));
    collection.addElement(new Effect("resources/sounds/trapActivated.wav",40,-1,0));
    collection.addElement(new Effect("resources/sounds/animationTrap.wav",20,-1,0));
    collection.addElement(new Effect("resources/sounds/bookRead.wav",20,-1,0));
    collection.addElement(new Music("resources/sounds/movieSound.wav",40));
    collection.addElement(new Music("resources/sounds/mainSound.wav",5));
    collection.addElement(new Effect("resources/sounds/rotBlock.wav",20,-1,0));
    collection.addElement(new Effect("resources/sounds/moveBlock.wav",20,-1,0));
    collection.addElement(new Effect("resources/sounds/fallBlock.wav",20,-1,0));

    //Create our map
    collection.addIndex("sCoin",sCoin);
    collection.addIndex("sOpen",sOpen);
    collection.addIndex("EHIT",EHIT);
    collection.addIndex("SHOOT",SHOOT);
    collection.addIndex("sSWORD",sSWORD);
    collection.addIndex("sARROW",sARROW);
    collection.addIndex("sSHIELD",sSHIELD);
    collection.addIndex("HHIT",HHIT);
    collection.addIndex("sWALK",sWALK);
    collection.addIndex("sJUMP",sJUMP);
    collection.addIndex("sJUMP",sFALL);
    collection.addIndex("sATRAP",sATRAP);
    collection.addIndex("sNTRAP",sNTRAP);
    collection.addIndex("sREAD",sREAD);
    collection.addIndex("sMOVIE",sMOVIE);
    collection.addIndex("sMAIN",sMAIN);
    collection.addIndex("sROT",sROT);
    collection.addIndex("sMOV",sMOV);
    collection.addIndex("sFBLOCK",sFBLOCK);
}

//**********************************************************************//

SoundCollection::~SoundCollection()
{
}

//**********************************************************************//

Sound* SoundCollection::getSound(SoundIndex element){
    return collection.getElement(element);
}

//**********************************************************************//

Sound* SoundCollection::getSound(string element){
    return collection.getElement(element);
}

//**********************************************************************//

void SoundCollection::updateVolume(float percentage){
    int tam=collection.getSize();
    for(int i=0;i<tam;i++)
        collection.getElement((SoundIndex)i)->changeVolume(percentage);
}
