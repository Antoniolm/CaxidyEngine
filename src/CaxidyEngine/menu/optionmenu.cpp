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

#include "optionmenu.h"
#include "CaxidyEngine/text.h"

namespace CaxidyEngine {

OptionMenu::OptionMenu(vec3f posMenu, std::string mat, std::string currentMat, std::string matBack)
{
    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,currentMat);
    materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,matBack);

    //Initialize text
    TTF_Font *font=TTF_OpenFont( "resources/font/Xolonium-Regular.ttf", 15);

    resolText=new Text(mVOID,font);
    windText=new Text(mVOID,font);
    volText=new Text(mVOID,font);

    //Initialize options
    resolution.push_back(std::pair<int,int> (800,600));
    resolution.push_back(std::pair<int,int> (1200,800));
    resolution.push_back(std::pair<int,int> (1400,800));

    //Setting the current setting
    initOptions();

    //Transformation
    positionMenu=new Matrix4f();
    positionMenu->translation(posMenu.x,posMenu.y,posMenu.z);

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Text
    Matrix4f * positionText=new Matrix4f();
    positionText->translation(0.0,0.0,0.2);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.5,2.0,0.5);

    NodeSceneGraph * nodeText=new NodeSceneGraph(false,true);
    nodeText->add(positionText);
    nodeText->add(scaleMenu);
    nodeText->add(currentMaterial);
    nodeText->add(meshCollect->getMesh(TEXT));

    ///////////////////////
    //Back
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(1.0,4.2,1.0);

    NodeSceneGraph * nodeBack=new NodeSceneGraph(false,true);
    nodeBack->add(scaleMenuBack);
    nodeBack->add(materialBack);
    nodeBack->add(meshCollect->getMesh(TEXT));

    //////////////////////
    // MainMenuBack
    Matrix4f * positionMainBack=new Matrix4f();
    positionMainBack->translation(0.725,0.5,0.8);

    Matrix4f * scaleMain=new Matrix4f();
    scaleMain->scale(0.35,1.8,0.5);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,mat);

    NodeSceneGraph * nodeMainBack=new NodeSceneGraph(false,true);
    nodeMainBack->add(positionMainBack);
    nodeMainBack->add(scaleMain);
    nodeMainBack->add(material);
    nodeMainBack->add(meshCollect->getMesh(TEXT));


    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(betweenMenu);
    root->add(nodeBack);
    root->add(nodeText);
    root->add(nodeMainBack);
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=soundCollect->getSound(sOpen);
    moveSound=soundCollect->getSound(sCoin);

}

//**********************************************************************//

OptionMenu::~OptionMenu()
{
    delete root;

    for(std::vector<Texture *>::iterator it = options.begin() ; it != options.end(); ++it){
        if((*it)->getFile()!=currentMaterial->getTexture()->getFile())
            delete (*it);
    }

    delete materialBack;
    delete currentMaterial;
    delete material;
}

//**********************************************************************//

void OptionMenu::visualization(Context & cv){
    if(activateMenu){
        root->visualization(cv);
        resolText->visualization(cv);
        windText->visualization(cv);
        volText->visualization(cv);
    }
}

//**********************************************************************//

void OptionMenu::updateState(GameState & gameState){
    vec3f position;
    std::string newOptionStr;
    std::stringstream sStream;


    float time=gameState.time;
    ControllerManager * controller=gameState.controller;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ //If the menu is activated

        ////////////////////////////////
        //PUSH -> cUP
        if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption-=1;
            if(currentOption==-1)
                currentOption=(options.size()-1);

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->play();
        }

        ////////////////////////////////
        //PUSH -> cDOWN
        else if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption++;
            if((unsigned)currentOption==options.size())
                currentOption=0;

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->play();
        }


        ////////////////////////////////
        //PUSH -> cLEFT
        if(controller->checkButton(cLEFT) && menuDelay<(time-300)){ //If the user push the action move on the menu

            //Update the current option
            switch(currentOption){
                case 0: //Resolution
                    indexResolution--;
                    if(indexResolution==-1){
                        indexResolution=resolution.size()-1;
                    }

                    sStream << resolution[indexResolution].first<< "x"<< resolution[indexResolution].second;
                    newOptionStr = sStream.str();
                break;
                case 1: //Window type
                    newOptionStr = "FullScreen";
                    window=!window;
                    if(window)
                        newOptionStr = "Window";
                break;
                case 2: //VolumeOption
                    volume-=10;
                    if(volume==0)
                        volume=100;

                    sStream << volume;
                    newOptionStr = sStream.str();
                break;
            }

            //Update the value of our currentOption
            updateOption(currentOption,newOptionStr);

            if(currentOption<3){
                menuDelay=time;
                moveSound->play(9);
            }
        }

        ////////////////////////////////
        //PUSH -> cRIGHT
        if(controller->checkButton(cRIGHT) && menuDelay<(time-300)){ //If the user push the action move on the menu

            //Update the current option
            switch(currentOption){
                case 0: //ResolutionOption
                    indexResolution++;
                    if((unsigned)indexResolution==resolution.size()){
                        indexResolution=0;
                    }
                    sStream << resolution[indexResolution].first<< "x"<< resolution[indexResolution].second;
                    newOptionStr = sStream.str();
                break;
                case 1: //WindowOption
                    newOptionStr = "FullScreen";
                    window=!window;
                    if(window)
                        newOptionStr = "Window";
                break;
                case 2: //VolumeOption
                    volume+=10;
                    if(volume==110)
                        volume=10;

                    sStream << volume;
                    newOptionStr = sStream.str();
                break;
            }

            //Update the value of our currentOption
            updateOption(currentOption,newOptionStr);

            if(currentOption<3){
                menuDelay=time;
                moveSound->play(9);
            }
        }

        ////////////////////////////////
        //PUSH -> cACTION
        if(controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
            switch(currentOption){
                case 3: //Save the new options and quit
                    OptionManager::getInstance()->save(resolution[indexResolution],window,volume);
                    //Update our setting
                    if(!Window::getInstance()->getIsFullScreen())
                        gameState.camera->setPerspectiveProjection(30.0f,(float)( (float) resolution[indexResolution].first / (float)resolution[indexResolution].second)
                                                               , 0.1f, 200.0f);
                    ////
                    Window::getInstance()->fullScreen(!window);
                    SDL_Delay(200);
                    if(window){
                        Window::getInstance()->resizeWindow(resolution[indexResolution].second,resolution[indexResolution].first);
                    }
                    else if(resolution[indexResolution].second==1400)
                        Window::getInstance()->resizeWindow(800,1200);
                    ////

                    SoundCollection::getInstance()->updateVolume((float)volume/100.0);
                    activateMenu=false;
                break;
                case 4: //Quit without save the options
                    activateMenu=false;
                break;
            }

            menuDelay=time;
            controller->setState(false,cACTION);
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void OptionMenu::setPosition(vec3f aPosition){
    positionMenu->translation(aPosition.x,aPosition.y+6.75,aPosition.z+11.0);
}


//**********************************************************************//

void OptionMenu::activate(){
    activateMenu=true;
    currentOption=0;
    currentMaterial->setTexture(options[currentOption]);
}

//**********************************************************************//

void OptionMenu::add(std::string fileName){
    addOption(new Texture(fileName.c_str()));
}

//**********************************************************************//

void OptionMenu::updateOption(int option, std::string value){
    switch(option){
        case 0: //Exit
            resolText->setMessage(value);
            resolText->init();
            resolText->setScaleDialog(vec3f(0.1,0.2,0.5));
            resolText->setScaleText(vec3f(0.1,0.2,0.5));
            resolText->setPosition(vec3f(0.10,6.95,11.1));
        break;
        case 1: //Exit
            windText->setMessage(value);
            windText->init();
            windText->setScaleDialog(vec3f(0.1,0.2,0.5));
            windText->setScaleText(vec3f(0.1,0.2,0.5));
            windText->setPosition(vec3f(0.10,6.85,11.2));
        break;
        case 2: //Exit
            volText->setMessage(value);
            volText->init();
            volText->setScaleDialog(vec3f(0.05,0.2,0.5));
            volText->setScaleText(vec3f(0.05,0.2,0.5));
            volText->setPosition(vec3f(0.10,6.75,11.3));
        break;
    }
}

//**********************************************************************//

void OptionMenu::initOptions(){
    OptionManager * options=OptionManager::getInstance();
    std::pair<int,int> currentResolution=options->getResolution();
    window=options->getWindow();
    volume=options->getVolume();

    //ResolutionOption
    for(unsigned i=0;i<resolution.size();i++)
        if(currentResolution==resolution[i])
            indexResolution=i;

    std::stringstream strResolution;
    strResolution<< resolution[indexResolution].first<< "x"<< resolution[indexResolution].second;

    //WindowOption
    std::string strWindow = "FullScreen";
    if(window)
        strWindow = "Window";

    //VolumeOption
    std::stringstream strVolume;
    strVolume << volume;

    updateOption(0,strResolution.str());
    updateOption(1,strWindow);
    updateOption(2,strVolume.str());
}

} // CaxidyEngine
