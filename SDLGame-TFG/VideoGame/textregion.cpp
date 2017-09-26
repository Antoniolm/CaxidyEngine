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

#include "textregion.h"
#include "rootmapgame.h"

TextRegion::TextRegion(const Value & regionFeatures){
    speakerMessage speaker;

    position=vec3f(regionFeatures["position"][0].GetFloat(),regionFeatures["position"][1].GetFloat(),regionFeatures["position"][2].GetFloat());
    radioActivity=vec3f(regionFeatures["radioActivity"][0].GetFloat(),regionFeatures["radioActivity"][1].GetFloat(),regionFeatures["radioActivity"][2].GetFloat());
    timeBWstate=regionFeatures["timeBWstate"].GetFloat();


    const Value & dialogs=regionFeatures["dialog"];

    for(unsigned j=0;j<dialogs.Size();j++){
        if(dialogs[j]["speaker"].GetInt()==1) speaker=HERO_DIALOG;
        else speaker=MATE_DIALOG;
        stateMachine.addState(std::string(dialogs[j]["string"].GetString()),speaker);
    }

    activated=false;
    lastState=false;
    currentTime=SDL_GetTicks();
    textDelay=currentTime;
}

//**********************************************************************//

TextRegion::~TextRegion()
{
    //dtor
}

//**********************************************************************//

void TextRegion::updateState(GameState & gameState){
    RootMapGame * rootMap=dynamic_cast<RootMapGame*>(gameState.rootMap);
    float time=gameState.time;

    Hero * hero =rootMap->getHero();
    Mate * mate =rootMap->getMate();

    vec3f posHero=hero->getPosition();
    vec3f distance=vec3f(position.x,position.y,position.z)-posHero;

    if(time-currentTime>200)
        currentTime=time-50;

    //check if the region will be activated in this frame
    if(!activated && !lastState && (distance.x>-radioActivity.x && distance.x<radioActivity.x)&&
       (distance.y>-radioActivity.y && distance.y<radioActivity.y)&&
       (distance.z>-radioActivity.z && distance.z<radioActivity.z)){
            activated=true;
    }

    if(activated){

        if(textDelay<(time-timeBWstate)){ //If the time for the current text is finished
            mate->activateDialog(false);
            hero->activateDialog(false,0);
            if(lastState)
                activated=false;

            if(!lastState){
                if(stateMachine.isLastState()) //if the talk is over
                    lastState=true;

                if(stateMachine.getCurrentSpeaker()==HERO_DIALOG){ //Speaker -> hero
                    hero->setDialog(stateMachine.getCurrentState(),0);
                    hero->activateDialog(true,0);
                }
                else{ //Speaker -> Mate
                    mate->setDialog(stateMachine.getCurrentState());
                    mate->activateDialog(true);
                }
                if(!lastState)
                    stateMachine.nextState();
                textDelay=time;
            }
        }

    }

    currentTime+=time-currentTime;
}
//**********************************************************************//

void TextRegion::setTimeBWstate(float value){
    timeBWstate=value;
}

//**********************************************************************//

float TextRegion::getTimeBWstate(){
    return timeBWstate;
}
