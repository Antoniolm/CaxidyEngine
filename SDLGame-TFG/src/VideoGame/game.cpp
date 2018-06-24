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
////////////////////////////////////////

#include "game.h"
#include "rootmapgame.h"

Game* Game::instance = NULL;

//**********************************************************************//

Game::Game(){
    //Load the options of our user
    options=OptionManager::getInstance();
    options->load();

    window=Window::getInstance();
    window->setParameters("NapMare",1200,800);
    window->createWindow();
    window->fullScreen(!options->getWindow());

    //Set the setting of our user
    SoundCollection::getInstance()->updateVolume((float)options->getVolume()/100.0);

    //Create our shader
    context.currentShader=new Shader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    glUseProgram(context.currentShader->getProgram()); //We use the program now

    //ShadowManager
    shadowManager=new ShadowManager(new Shader("shaders/depthShader.vs","shaders/depthShader.fs"));

    //CelShading
    celShading=new CelShading(new Shader("shaders/celShading.vs","shaders/celShading.fs"));

    //Create ours menus
    MeshCollection::getInstance();
    MaterialCollection::getInstance();
    
    //Create MainMenu
    gameState.mainMenu=new MainMenu(vec3f(0.0,6.70,11.0),"./textures/mainBackMenu.png");
    gameState.mainMenu->add("./textures/mainMenuStart.png",START);
    gameState.mainMenu->add("./textures/mainMenuCont.png",CONTINUE);
    gameState.mainMenu->add("./textures/mainMenuControl.png",CONTROLS);
    gameState.mainMenu->add("./textures/mainMenuOption.png",OPTION);
    gameState.mainMenu->add("./textures/mainMenuQuit.png",EXIT);
    gameState.mainMenu->activate();
    cout<<"boom"<<endl;
    checkUserProgress();
    cout<<"boom2"<<endl;
    
    //Create PauseMenu
    gameState.pauseMenu = new PauseMenu(vec3f(0.0,-1.23,-2.0),"./textures/menuBack.png");
    gameState.pauseMenu->add("./textures/menuPauseResume.png",pRESUME);
    gameState.pauseMenu->add("./textures/menuPauseQuit.png",pQUIT);

    
    //Create deadMenu
    gameState.deadMenu = new DeadMenu(vec3f(0.0,-1.23,-2.0),"./textures/menuBack.png");
    gameState.deadMenu->add("./textures/dieMenu.png");

    //Create creditScreen
    gameState.creditScreen= new CreditScreen(vec3f(0.0f,6.77f,11.0f),"./textures/menuBack.png");
    gameState.creditScreen->add("./textures/creditScreen.png");

    //Create LoadingScreen
    gameState.loadScreen=new LoadingScreen(vec3f(0.0f,6.77f,11.0f),250,"./textures/loading1.png");
    gameState.loadScreen->add("./textures/loading2.png");
    gameState.loadScreen->add("./textures/loading3.png");

    //Create optionMenu
    gameState.optionMenu=new OptionMenu(vec3f(0.0,6.70,11.0),"./textures/mainMenuOption.png","./textures/optionResol.png","./textures/mainBackMenu.png");
    gameState.optionMenu->add("./textures/optionResol.png");
    gameState.optionMenu->add("./textures/optionWindow.png");
    gameState.optionMenu->add("./textures/optionVolume.png");
    gameState.optionMenu->add("./textures/optionSave.png");
    gameState.optionMenu->add("./textures/optionQuit.png");

    
    //Create controlMenu
    gameState.controlMenu=new ControlMenu(vec3f(0.0f,6.70f,11.0f),"./textures/mainBackMenu.png");

    //Create inventoryMenu
    gameState.inventoryMenu=new InventoryMenuGame(vec3f(0.0f,-1.23,-2.0),vec3f(0.207f,0.288f,0.0f),"./textures/inventory.png");

    //Create speakingSketch
    gameState.speakingSketch=new SpeakingSketch(vec3f(0.0f,-1.23,-2.0),"mSPEAK");

    heroState=new HeroState();

    isClosing=false;

    notiGamePad=new Notification(vec3f(0.0,0.0,0.0),vec3f(0.0,0.0,0.0),0,mVOID);

    //////////////////////////////////////////////////////
    /////         Initialize controller              /////
    //////////////////////////////////////////////////////
    gameState.controller=new ControllerManager();
}

//**********************************************************************//

Game::~Game(){
    delete window;
    delete notiGamePad;
    delete heroState;

    delete shadowManager;
    delete celShading;
    delete options;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    delete meshCollect;

    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    delete materialCollect;

    SoundCollection * soundCollect= SoundCollection::getInstance();
    delete soundCollect;
    //delete profile
}

//**********************************************************************//

void Game::setClose(bool value){
    isClosing=value;
}

//**********************************************************************//

void Game::loop(){
    SDL_Event event;
    float time;
    string fileMap;
    bool firstTime=true;
    vec3f posHero;

    int windowH=800,windowW=1200;
    Profile * profile=Profile::getInstance();

    //Create our camera
    gameState.camera=new Camera(vec3f(0,8.0f,13.0f),vec3f(0.0,0.0,0.0),vec3f(0.0,1.0,0.0));

    pair<int,int> resolution=options->getResolution();
    gameState.camera->setPerspectiveProjection(30.0f,(float)( (float) resolution.first / (float) resolution.second), 0.1f, 200.0f);
    gameState.camera->setOrthographicProjection(-1,1,-1,1,-3,3);

    ////
    if(options->getWindow())
        window->resizeWindow(resolution.second,resolution.first);
    else if(resolution.first==1400)
        window->resizeWindow(800,1200);
    ////

    //Show our window.
    window->showScreen();
    while (!isClosing)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isClosing = true;
            }
            if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_RESIZED ){
                if(event.window.data2<600)windowH=600; //MinHeight
                else windowH=event.window.data2;

                if(event.window.data1<800) windowW=800; //MinWidth
                else windowW=event.window.data1;

                window->resizeWindow(windowH,windowW);
            }

            if((event.type==SDL_CONTROLLERBUTTONDOWN || event.type==SDL_CONTROLLERBUTTONUP || event.type==SDL_CONTROLLERDEVICEADDED
              || event.type==SDL_CONTROLLERDEVICEREMOVED || event.type==SDL_CONTROLLERAXISMOTION)){
                gameState.controller->checkEvent(event);;
            }

           if(event.type==SDL_CONTROLLERDEVICEADDED) //If the game is connected
                notiGamePad=new Notification(vec3f(0.4,7.4,10.6),vec3f(0.05,0.175,0.05),2000,mGMPADV);
            else if(event.type==SDL_CONTROLLERDEVICEREMOVED) //If the game is disconnected
                notiGamePad=new Notification(vec3f(0.4,7.4,10.6),vec3f(0.05,0.175,0.05),2000,mGMPADX);
        }

        gameState.controller->catchKeyBoardState(SDL_GetKeyboardState(NULL));
        window->cleanScreen();

        //CASE -> MAINMENU
        if(gameState.mainMenu->isActivate()){
            gameState.updateMenu(context.currentShader->getProgram());

            if(!gameState.mainMenu->isActivate())
                createRootMap(gameState.mainMenu->getOptionSelected());

            if(!gameState.optionMenu->isActivate() && !gameState.controlMenu->isActivate())
                gameState.mainMenu->visualization(context);

            gameState.optionMenu->visualization(context);
            gameState.controlMenu->visualization(context);
            firstTime=true;
        }

        //CASE -> LOADING
        else if(gameState.rootMap->isLoading()){
            //loading screen here
            gameState.updateLoading(context.currentShader->getProgram());

            gameState.loadScreen->visualization(context);
            firstTime=true;

            //Consume events
            gameState.controller->consumeButtons();
        }

        //CASE -> CREDIT SCREEN
        else if(gameState.creditScreen->isActivate()){
            //loading screen here
            gameState.updateCredit(context.currentShader->getProgram());

            gameState.creditScreen->visualization(context);
            firstTime=true;
        }

        //CASE -> PLAYING
        else{
            if(firstTime){
                gameState.initPlay(context.currentShader->getProgram());
                firstTime=false;
            }
            
            ///////////////////
            // UPDATE STATE
            ///////////////////
            gameState.time=SDL_GetTicks();
            Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();

            if(hero->getLife()<=0.0){ //check if the hero is dead
                gameState.deadMenu->activate();
            }

            gameState.refPoint=hero->getPosition();
            heroState->updateState(gameState);
            gameState.updatePlay();

            //Update the camera, lifeText, coinText, profile
            posHero=gameState.refPoint;

            gameState.camera->update(gameState,context.currentShader->getProgram(),
                          (gameState.pauseMenu->isActivate() || gameState.deadMenu->isActivate() || gameState.mainMenu->isActivate()
                           || gameState.inventoryMenu->isActivate()));

            notiGamePad->updateState(gameState);

            profile->addUpdateTime(SDL_GetTicks()-gameState.time);

            ///////////////////
            // VISUALIZATION
            ///////////////////
            time=SDL_GetTicks();

            //1- Render of our deph map for shadow mapping
            glViewport(0, 0, 2048,2048);
            shadowManager->setCamera(vec3f(posHero.x-1.0, posHero.y+8.0f,posHero.z-2.0),vec3f(posHero.x,0.0,posHero.z),vec3f(0.0,1.0,0.0));
            shadowManager->setOrthoProjection(-20.0,20.0,-20.0,20.0,-1,20);
            shadowManager->generateShadow(gameState);

            //2- Cel Shading renderer

            context.celShading_mode=true;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            celShading->generateCelTexture(gameState);

            context.celShading_mode=false;

            //3- Normal render of our scene
            glViewport(0, 0, window->getWidth(), window->getHeight());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(context.currentShader->getProgram()); //We use the program now
            gameState.camera->activateCamera(context.currentShader->getProgram());
            gameState.rootMap->activatedLight(context.currentShader->getProgram());

            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "diffuseMap"), 0);
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "normalMap"), 1);
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "shadowMap"), 2);
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "depthMap"), 3);
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "celMap"), 4);

            glUniform3f(glGetUniformLocation(context.currentShader->getProgram(), "lightPosVertex"),posHero.x-1.0, posHero.y+5.0f,posHero.z-2.0);
            glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, shadowManager->getLightSpace().getMatrix());
            glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "spaceMatrix"), 1, GL_FALSE,  celShading->getCameraSpace().getMatrix());

            shadowManager->activateShadowTexture();
            celShading->activateTexture();
            gameState.camera->activatePerspecProjection(context.currentShader->getProgram());
            gameState.rootMap->visualization(context);

            gameState.camera->activateOrthoProjection(context.currentShader->getProgram());
            heroState->visualization(context);
            gameState.pauseMenu->visualization(context);
            gameState.inventoryMenu->visualization(context);
            gameState.deadMenu->visualization(context);
            gameState.speakingSketch->visualization(context);
            gameState.movie->visualization(context);
            notiGamePad->visualization(context);

            profile->addVisualTime(SDL_GetTicks()-time);
            profile->incrementFrames();

            if(gameState.rootMap->isFinished()){
                //Get the next Map and save the match
                fileMap=gameState.rootMap->getNextMap();
                if(fileMap!=""){
                    SavedManager::getInstance()->save(fileMap,gameState,hero->getCoin(),
                                                      hero->getExp(),hero->getMaxExp(),hero->getLevel());

                    checkUserProgress();

                    //Delete the currentMap
                    delete gameState.rootMap;

                    //Save the progress and create the new map
                    gameState.rootMap=new RootMapGame(fileMap,true);
                }
                else
                    gameState.creditScreen->activate();


                gameState.controller->consumeButtons();
                firstTime=true;
            }

        }
        window->updateScreen();
    }

    profile->showResult();
}

//**********************************************************************//

void Game::createRootMap(MainMenuOption option){
    SavedManager * saveManager;
    string fileLoad;
    InventoryMenuGame * inv=dynamic_cast<InventoryMenuGame*>(gameState.inventoryMenu);

    switch(option){
        case START: //Start Game

            if(gameState.rootMap!=0)
                delete gameState.rootMap;

            //Added the initial equipment of the hero
            inv->addEquip(new Equipment(vec3f(0.0,-0.2,0.0),RANGED,true,20,25,5,"mARCHENEMY","CBOW","mARCHENEMY","Bow"));
            inv->addEquip(new Equipment(vec3f(0.025,-0.05,0.34),MELEE,true,25,25,5,"mSWORD","SWORD","mSWORD","Sword"));
            inv->addEquip(new Equipment(vec3f(-0.1375,0.0,0.0),eSHIELD,true,0,0,10,"mSHIELDPR","SHIELD","mSHIELD","Shield"));

            cout<< "Saving"<< endl;
            SavedManager::getInstance()->save("",gameState,0);
            cout<< "Saved"<< endl;
            gameState.rootMap=new RootMapGame("./maps/map00.json",true);
            checkUserProgress();

        break;
        case CONTINUE: //Continue
            //Catch the saved progress and load the map
            saveManager=SavedManager::getInstance();
            saveManager->load(true);

            inv->setInventory(saveManager->getInv(),saveManager->getPosInv());

            fileLoad=saveManager->getMap();

            if(gameState.rootMap!=0)
                delete gameState.rootMap;

            gameState.rootMap=new RootMapGame(fileLoad,true);

        break;
        case CONTROLS: //Controls
        break;
        case OPTION: //Option
        break;
        case EXIT: //Exit
        break;

    }
}

//**********************************************************************//

void Game::checkUserProgress(){
    SavedManager * saveManager=SavedManager::getInstance();
    saveManager->load();

    bool hasSave=false;
    if(saveManager->getMap()!="")
        hasSave=true;

    gameState.mainMenu->setHasSave(hasSave);

}

