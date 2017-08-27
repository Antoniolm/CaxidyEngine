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

#include "speakingsketch.h"

SpeakingSketch::SpeakingSketch(const Value & speakSkFeatures){
    position=vec4f(speakSkFeatures["position"][0].GetFloat(),
               speakSkFeatures["position"][1].GetFloat(),
               speakSkFeatures["position"][2].GetFloat(),1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    transActivate=new Matrix4f();
    transActivate->identity();

    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(1.0,4.2,1.0);

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(scaleMenuBack);
    root->add(materialCollect->getMaterial(mBUTTON));
    root->add(meshCollect->getMesh(BUTTONB));

    currentTime=SDL_GetTicks();
    activated=false;
}

//**********************************************************************//

SpeakingSketch::~SpeakingSketch(){
    delete root;
}

//**********************************************************************//

void SpeakingSketch::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void SpeakingSketch::updateState(GameState & gameState){

}
