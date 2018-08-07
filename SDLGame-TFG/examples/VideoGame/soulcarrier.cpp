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

#include "soulcarrier.h"
#include "rootmapgame.h"

SoulCarrier::SoulCarrier(const Value & soulFeatures)
{
    position=vec4f(soulFeatures["position"][0].GetFloat(),soulFeatures["position"][1].GetFloat(),soulFeatures["position"][2].GetFloat(),1.0);
    activated=false;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(100,0.0,1.0,0.0);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(animationMatrix);
    root->add(materialCollect->getMaterial(mGLYPH));
    root->add(meshCollect->getMesh(GLYPH));
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

SoulCarrier::~SoulCarrier()
{
    delete root;
}

//**********************************************************************//

void SoulCarrier::visualization(Context & cv){
    if(!cv.shadow_mode)
        root->visualization(cv);
}

//**********************************************************************//

void SoulCarrier::updateState(GameState & gameState ){
    float time=gameState.time;
    Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();
    Soul * soul=hero->getSoul();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    //if hero is near of a soulCarrier and he push E -> SoulCarrier catch the soul in his arms
    if(soul!=0 && !activated && gameState.controller->checkButton(cACTION) && distance<=1.5 && (position.y>posHero.y-1 && position.y<posHero.y+1)){
        activated=true;
        soul->setPosition(vec3f(position.x,position.y+1.0,position.z));
        soul->setInCarrier(true);
        hero->setSoul(0);
    }

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());

    currentTime+=time-currentTime;
}

//**********************************************************************//

bool SoulCarrier::isActivated(){
    return activated;
}
