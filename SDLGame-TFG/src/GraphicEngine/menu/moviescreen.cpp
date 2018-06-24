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

#include "moviescreen.h"
#include "../gamestate.h"

MovieScreen::MovieScreen(const Value & movieFeatures)
{
    currentOption=0;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    positionMenu=new Matrix4f();

    if(movieFeatures.Size()==0){
        activateMenu=false;
        root=0;
        currentMaterial=0;
    }
    else{
        activateMenu=true;
        currentMaterial=new Material();

        for(unsigned i=0;i<movieFeatures.Size();i++){
            textures.push_back(movieFeatures[i]["texture"].GetString());
        }

        positionMenu->identity();

        Matrix4f * scaleMenu=new Matrix4f();
        scaleMenu->scale(1.0,4.1,0.5);

        Matrix4f * rotationMenu=new Matrix4f();
        rotationMenu->rotation(20,1.0,0.0,0.0);

        root=new NodeSceneGraph(false,true);
        root->add(positionMenu);
        root->add(rotationMenu);
        root->add(scaleMenu);
        root->add(currentMaterial);
        root->add(meshCollect->getMesh(TEXT));
    }
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    //Get sound
    actionSound=soundCollect->getSound(sREAD);
    ambientSound=soundCollect->getSound(sMOVIE);
}

//**********************************************************************//

MovieScreen::~MovieScreen()
{
    if(root!=0)
        delete root;
    for(unsigned i=0;i<options.size();i++)
      delete options[i];
}

//**********************************************************************//

void MovieScreen::visualization(Context & cv){
    if(activateMenu){
        root->visualization(cv);
    }
}

//**********************************************************************//

void MovieScreen::updateState(GameState & gameState){
    float time=gameState.time;
    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ // If is activated
        if(!ambientSound->isPlaying()) // if the ambient sound is not playing
            ambientSound->play();

        if(gameState.controller->checkButton(cACTION) && menuDelay<(time-500)){ //If the user push the event action
            currentOption++;

            if((unsigned)currentOption==options.size()){
                activateMenu=false;
                currentOption=0;
                ambientSound->stop();
            }
            else {
                actionSound->play();
                ambientSound->play();
            }

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;

            gameState.controller->consumeButtons();
        }
    }
    currentTime+=time-currentTime;
}

//**********************************************************************//

void MovieScreen::setActivate(bool value){
    activateMenu=value;
}

//**********************************************************************//

bool MovieScreen::isActivated(){
    return activateMenu;
}

//**********************************************************************//

void MovieScreen::activateAllTexture(){
    if(textures.size()!=0){
        for(unsigned i=0;i<textures.size();i++)
            options.push_back(new Texture(textures[i]));

        //Set the first texture
        currentMaterial->setAmbient(vec3f(1.0,1.0,1.0));
        currentMaterial->setDiffuse(vec3f(1.0f, 0.5f, 0.5f));
        currentMaterial->setSpecular(vec3f(0.5f, 0.5f, 0.5f));
        currentMaterial->setShininess(32.0f);
        currentMaterial->setTexture(options[0]);
    }
}
