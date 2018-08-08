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

#include "pausemenu.h"

namespace CaxidyEngine {

PauseMenu::PauseMenu(vec3f initPos, std::string fileName)
{
    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();
    initialPosition=initPos;

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"");
    materialBack=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileName.c_str());

    positionMenu=new Matrix4f();
    positionMenu->identity();

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.1);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.3,1.5,0.4);
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(5.0,4.0,4.0);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(currentMaterial);
    root->add(meshCollect->getMesh(TEXT));
    root->add(betweenMenu);
    root->add(scaleMenuBack);
    root->add(materialBack);
    root->add(meshCollect->getMesh(TEXT));
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=soundCollect->getSound(sOpen);
    moveSound=soundCollect->getSound(sCoin);
}

//**********************************************************************//

PauseMenu::~PauseMenu()
{
    delete root;

    for(std::vector<Texture *>::iterator it = options.begin() ; it != options.end(); ++it){
        if((*it)->getFile()!=currentMaterial->getTexture()->getFile())
            delete (*it);
    }

    delete currentMaterial;
    delete materialBack;
}

//**********************************************************************//

void PauseMenu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void PauseMenu::updateState(GameState & gameState){
    vec3f position;

    if(!gameState.movie->isActivated() && !gameState.deadMenu->isActivate() && !gameState.inventoryMenu->isActivate()
       && !gameState.camera->isViewMode()){
        float time=gameState.time;
        ControllerManager * controller=gameState.controller;

        if(time-currentTime>200)
            currentTime=time-50;

        if(controller->checkButton(cPAUSE) && menuDelay<(time-600)){
            activateMenu=!activateMenu;
            menuDelay=time;
            if(activateMenu){
                (Profile::getInstance())->showResult();
                position=gameState.camera->getPosition();
                positionMenu->translation(position.x+initialPosition.x,position.y+initialPosition.y,position.z+initialPosition.z);

                //Consume the current events -> User has to push again the buttons
                controller->setState(false,cUP);
                controller->setState(false,cDOWN);
                controller->setState(false,cACTION);
            }
            else {
                currentOption=0;
                currentMaterial->setTexture(options[currentOption]);
            }
            openSound->play();
        }


        if(activateMenu){ //If the menu is activated
            if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentOption-=1;
                if(currentOption==-1)
                    currentOption=(options.size()-1);

                currentMaterial->setTexture(options[currentOption]);
                menuDelay=time;
                moveSound->play();
            }
            else if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentOption++;
                if((unsigned)currentOption==options.size())
                    currentOption=0;

                currentMaterial->setTexture(options[currentOption]);
                menuDelay=time;
                moveSound->play();
            }
            //If the user push an option
            if(controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
                switch(actionOption[currentOption]){
                    case pRESUME: //Resume
                        currentOption=0;
                         currentMaterial->setTexture(options[currentOption]);
                        activateMenu=false;
                        openSound->play();
                    break;
                    case pQUIT: //Exit
                        currentOption=0;
                        currentMaterial->setTexture(options[currentOption]);
                        (Profile::getInstance())->showResult();
                        gameState.mainMenu->activate();
                        activateMenu=false;

                        //Clear inventory
                        gameState.inventoryMenu->clearInventory();

                    break;

                }

                menuDelay=time;
                controller->setState(false,cACTION);
            }
        }

        currentTime+=time-currentTime;
    }
}

//**********************************************************************//

void PauseMenu::add(std::string fileName,PauseMenuOption aOption){
    addOption(new Texture(fileName.c_str()));
    actionOption.push_back(aOption);

    if(actionOption.size()==1)
        currentMaterial->setTexture(options[0]);
}

} // CaxidyEngine
