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

#include "npc.h"
#include "VideoGame/rootmapgame.h"

Npc::Npc(){}

//**********************************************************************//

Npc::Npc(const Value & npcFeatures)
{
    position=vec4f(npcFeatures["position"][0].GetFloat(),npcFeatures["position"][1].GetFloat(),npcFeatures["position"][2].GetFloat(),1.0);
    speakerMessage speaker;

    const Value & dialogs=npcFeatures["dialog"];

    //Create the conversation
    for(unsigned j=0;j<dialogs.Size();j++){
        if(dialogs[j]["speaker"].GetInt()==0) speaker=NPC_DIALOG;
        else speaker=HERO_DIALOG;
        addDialog(std::string(dialogs[j]["string"].GetString()),speaker);
    }

    npcActivate=false;
    heroActivate=false;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    //Matrix for animation
    Matrix4f * matrix=new Matrix4f();
    matrix->identity();
    moveMatrix.push_back(matrix);

    Matrix4f * transNPC=new Matrix4f();
    transNPC->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transNPC);
    root->add(moveMatrix[0]);
    root->add(materialCollect->getMaterial(npcFeatures["material"].GetString()));
    root->add(meshCollect->getMesh(npcFeatures["mesh"].GetString()));

    TTF_Font *font=TTF_OpenFont( npcFeatures["textFont"].GetString(), npcFeatures["textSize"].GetInt());
    currentText=new Text(mBDIALOG,font);
    currentText->setPosition(vec3f(position.x+npcFeatures["textPosition"][0].GetFloat(),
                                   position.y+npcFeatures["textPosition"][1].GetFloat(),
                                   position.z+npcFeatures["textPosition"][2].GetFloat()));
    currentTime=SDL_GetTicks();
    dialogTime=currentTime;
    initAnimation();

}

//**********************************************************************//

Npc::~Npc()
{
    delete currentText;
    delete root;
}

//**********************************************************************//

void Npc::addDialog(const string state,speakerMessage speaker){
    stateMachine.addState(state,speaker);
}

//**********************************************************************//

void Npc::currentDialog(){
    currentText->setMessage(stateMachine.getCurrentState());
    currentText->init();
}

//**********************************************************************//

void Npc::nextDialog(){
    if(stateMachine.isLastState()){
        npcActivate=false;
        stateMachine.firstState();
    }
    else {
        stateMachine.nextState();
    }
}

//**********************************************************************//

int Npc::getNumDialog(){
    return stateMachine.getNumState();
}

//**********************************************************************//

void Npc::visualization(Context & cv){
     if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
            root->visualization(cv);

    if(npcActivate && stateMachine.getCurrentSpeaker()==NPC_DIALOG)
        currentText->visualization(cv);
}

//**********************************************************************//

void Npc::updateState(GameState & gameState){
    Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();
    vec3f posHero=hero->getPosition();
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    //Check if the hero is near to a npc
    vec3f distance=vec3f(position.x,position.y,position.z)-posHero;
    if(!npcActivate && (distance.x>-1 && distance.x<1)&&(distance.y>-2 && distance.y<2)&&(distance.z>-1 && distance.z<1)){
        hero->setDialog(" ",1);
        hero->activateDialog(true,1);
        heroActivate=true;
    }

    if(heroActivate && ((distance.x<-2 || distance.x>2)||(distance.y<-2 || distance.y>2)||(distance.z<-2 || distance.z>2))){
        heroActivate=false;
        hero->activateDialog(false,1);

        // deactivation speak mode
        gameState.camera->setSpeakMode(false);
    }

    if(npcActivate){ //If hero is talking and he is a good distance
        hero->activateDialog(false,1);
        if((distance.x<-2 || distance.x>2)||(distance.y<-2 || distance.y>2)||(distance.z<-2 || distance.z>2)){
            activateNpc(false);
            hero->activateDialog(false,0);

            // deactivation speak mode
            gameState.camera->setSpeakMode(false);
        }
    }

    //User push the button -> J
    if(gameState.controller->checkButton(cACTION) && dialogTime<(time-400.0)){

        if(npcActivate){ //If hero is talking -> nextDialog

            bool finishSpeak=stateMachine.isLastState();
            nextDialog();

            //Check the speaker
            if(stateMachine.getCurrentSpeaker()==NPC_DIALOG){ //speaker -> Npc
                currentDialog();
                hero->activateDialog(false,0);
            }
            else { //speaker -> Hero
                if(!isInitialState()){
                    hero->activateDialog(true,0);
                    hero->setDialog(stateMachine.getCurrentState(),0);
                }
                else{
                    hero->activateDialog(false,0);
                }
            }
            gameState.controller->setState(false,cACTION);

            if(finishSpeak){
                // deactivation speak mode
                gameState.camera->setSpeakMode(false);
            }
        }
        else { //Else Check if hero will start a new conversation.
            if((distance.x>-1 && distance.x<1)&&(distance.y>-2 && distance.y<2)&&(distance.z>-1 && distance.z<1)){
                activateNpc(true);
                hero->activateDialog(false,1);

                //Check the speaker
                if(stateMachine.getCurrentSpeaker()==NPC_DIALOG){ //speaker -> Npc
                    currentDialog();
                    hero->activateDialog(false,0);
                }
                else {//speaker -> Hero
                    hero->activateDialog(true,0);
                    hero->setDialog(stateMachine.getCurrentState(),0);
                }
                gameState.controller->setState(false,cACTION);

                // Activation speak mode
                gameState.camera->setSpeakMode(true);
            }
        }
        dialogTime=time;
    }

    animation.updateState(time-currentTime);
    moveMatrix[0]->product(animation.readMatrix(0).getMatrix());

    currentTime+=time-currentTime;
}

//**********************************************************************//

void Npc::activateNpc(bool value){
    npcActivate=value;
    if(value==false)
        stateMachine.firstState();
}

//**********************************************************************//

bool Npc::getActivate(){
    return npcActivate;
}

//**********************************************************************//

vec3f Npc::getPosition(){
    return vec3f(position.x,position.y,position.z);
}

//**********************************************************************//

bool Npc::isInitialState(){
    return stateMachine.isFirstState();
}

//**********************************************************************//
void Npc::initAnimation(){
    LinearMovement * transBody=new LinearMovement(vec3f(0.0,0.2,0));
    LinearMovement * transBodySecond=new LinearMovement(vec3f(0.0,-0.2,0));

    //Movement to the first arm
    MatrixScript * bodyScript=new MatrixScript();

    bodyScript->add(0.5,transBody);
    bodyScript->add(0.5,transBodySecond);

    animation.add(bodyScript);


}
