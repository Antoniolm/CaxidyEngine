// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David López Machado
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

#include "coin.h"

Coin::Coin(const Value & coinFeatures){
    position=vec4f(coinFeatures["position"][0].GetFloat(),coinFeatures["position"][1].GetFloat(),coinFeatures["position"][2].GetFloat(),1.0f);
    value=coinFeatures["value"].GetInt();

    notTake=true;
    type=iCOIN;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect = SoundCollection::getInstance();

    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(100,0.0,1.0,0.0);

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(animationMatrix);
    root->add(materialCollect->getMaterial(coinFeatures["material"].GetString()));
    root->add(meshCollect->getMesh(coinFeatures["geometry"].GetString()));
    currentTime=SDL_GetTicks();

    soundTake=soundCollect->getSound(sCoin);
}

//**********************************************************************//

Coin::~Coin(){
    delete root;
    delete rotation;
}

//**********************************************************************//

void Coin::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Coin::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=dynamic_cast<RootMapGame *>(gameState.rootMap)->getHero();
    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.y-posHero.y,2.0)+pow(position.z-posHero.z,2.0));

    if(distance<=0.4){
        notTake=false;

        hero->addCoin(value);
        soundTake->play();
    }

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());
    currentTime+=time-currentTime;
}
