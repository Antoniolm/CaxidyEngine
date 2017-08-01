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

#include "mate.h"

Mate::Mate(vec3f aPosition)
{
    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    //Dialog for speak
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 20);
    currentText=new Text(mBDIALOG,font);


    //Node for animation
    Matrix4f * moveHand=new Matrix4f();
    moveHand->identity();
    moveMatrix.push_back(moveHand);

    position=vec4f(aPosition.x,aPosition.y+1.0,aPosition.z-2.0,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    moveAvatar=new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);

    Matrix4f * transHand=new Matrix4f();
    transHand->translation(0.4,0.0,0.0);

    Matrix4f * transOtherHand=new Matrix4f();
    transOtherHand->translation(-0.2,-0.3,0.0);

    root=new NodeSceneGraph();
    root->add(moveAvatar);
    root->add(materialCollect->getMaterial(mMATE));
    root->add(meshCollect->getMesh(MATEHEAD));
    root->add(transOtherHand);
    root->add(moveHand); // node for animation
    root->add(meshCollect->getMesh(MATEHAND));
    root->add(transHand);
    root->add(meshCollect->getMesh(MATEHAND));
    currentTime=SDL_GetTicks();

    initAnimation();

    textActivated=false;

}

//**********************************************************************//

Mate::~Mate()
{
    delete root;
    delete animation;
    delete currentText;

}

//**********************************************************************//

void Mate::visualization(Context & cv){
    root->visualization(cv);

    if(textActivated)
        currentText->visualization(cv);
}

//**********************************************************************//

void Mate::updateState(GameState & gameState){
    Hero * hero=gameState.rootMap->getHero();
    vec3f posHero=hero->getPosition();
    vec3f newMovement;

    float time=gameState.time;
    if(time-currentTime>200)
        currentTime=time-50;

    //Take our new position
    currentMove=nextPosition(posHero);

    //Check Y position
    posHero.y+=1.0;

    if(position.y>posHero.y+0.1){
        currentMove.second.y=-2.0;
    }
    else if(position.y<posHero.y){
        currentMove.second.y=+2.0;
    }

    moveMate(time,currentMove.second,currentMove.first);
    position=moveAvatar->product(vec4f());

    ////////////////////////////
    //UPDATE ANIMATION
    ////////////////////////////
    if(currentMove.second.x!=0.0 || currentMove.second.y!=0.0 || currentMove.second.z!=0.0){ //if is in movement
        animation->updateState(time-currentTime);

        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->setMatrix(animation->readMatrix(i).getMatrix());
    }
    else{ //if is not in movement
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();

    }

    ////////////////////////////
    //UPDATE TEXT
    ////////////////////////////
    if(textActivated)
        currentText->setPosition(vec3f(position.x,position.y+1.0f,position.z));

    currentTime+=time-currentTime;
}

//**********************************************************************//

void Mate::setDialog(string message){
    currentText->setPosition(vec3f(position.x,position.y+1.0f,position.z));
    currentText->setMessage(message);
    currentText->init();
}

//**********************************************************************//

void Mate::activateDialog(bool value){
    textActivated=value;
}
//**********************************************************************//

void Mate::moveMate(float time,vec3f aMove,avatarDirection aDir){
    if(direction!=aDir){
        Matrix4f transHero;
        transHero.translation(position.x,position.y,position.z);
        LinearMovement lineMove(aMove);
        transHero.product(lineMove.updateState(time-currentTime).getMatrix());

        moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
        moveAvatar->product(transHero.getMatrix());

        direction=aDir;
    }
    else{
        LinearMovement lineMove(aMove);
        moveAvatar->product(lineMove.updateState(time-currentTime).getMatrix());
    }
}

//**********************************************************************//

pair<avatarDirection,vec3f> Mate::nextPosition(vec3f posHero){

    vec3f newMovement;
    float distance,minDistance;
    pair<avatarDirection,vec3f> result;

    if(sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0))<0.8){
        result.first=currentMove.first;
        result.second=vec3f(0.0f,0.0f,0.0f);
        return result;
    }

    //Case -> Default
    newMovement.x=position.x;newMovement.y=position.y;newMovement.z=position.z;
    result.first=FORWARD;
    result.second=vec3f(0.0f,0.0f,0.0f);
    minDistance=1000.0;

    //Case -> Leftward
    newMovement.x=position.x-2.0;newMovement.y=position.y;newMovement.z=position.z;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance ){ //If Rightward will be our move -> The distance is smallest between them
        result.first=LEFTWARD;
        result.second=vec3f(-2.75f,0.0f,0.0f);
        minDistance=distance;
    }


    //Case -> Rightward
    newMovement.x=position.x+2.0;newMovement.z=position.z;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Rightward will be our move -> The distance is smallest between them
        result.first=RIGHTWARD;
        result.second=vec3f(2.75f,0.0f,0.0f);
        minDistance=distance;
    }

    //Case -> Backward
    newMovement.x=position.x;newMovement.z=position.z-2.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Backward will be our move -> The distance is smallest between them
        result.first=BACKWARD;
        result.second=vec3f(0.0f,0.0f,-2.75f);
        minDistance=distance;
    }

    //Case -> Forward
    newMovement.x=position.x;newMovement.z=position.z+2.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Forward will be our move -> The distance is smallest between them
        result.first=FORWARD;
        result.second=vec3f(0.0f,0.0f,2.75f);
        minDistance=distance;
    }

    //Case -> Left-forward
    newMovement.x=position.x-1.0;newMovement.z=position.z+1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Left-forward will be our move -> The distance is smallest between them
        result.first=FOR_LEFTWARD;
        result.second=vec3f(-1.75f,0.0f,1.75f);
        minDistance=distance;
    }

    //Case -> Right-forward
    newMovement.x=position.x+1.0;newMovement.z=position.z+1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Right-forward will be our move -> The distance is smallest between them
        result.first=FOR_RIGHTWARD;
        result.second=vec3f(+1.75f,0.0f,+1.75f);
        minDistance=distance;
    }

    //Case -> Left-backward
    newMovement.x=position.x-1.0;newMovement.z=position.z-1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Left-backward will be our move -> The distance is smallest between them
        result.first=BACK_LEFTWARD;
        result.second=vec3f(-1.75f,0.0f,-1.75f);
        minDistance=distance;
    }

    //Case -> Right-backward
    newMovement.x=position.x+1.0;newMovement.z=position.z-1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Right-backward will be our move -> The distance is smallest between them
        result.first=BACK_RIGHTWARD;
        result.second=vec3f(1.75f,0.0f,-1.75f);
        minDistance=distance;
    }

    return result;
}

//**********************************************************************//

void Mate::initAnimation(){
    animation=new ScriptLMD();

    Matrix4f * rotateHand=new Matrix4f();
    rotateHand->rotation(-60,1.0,0.0,0.0);

    MatrixStatic * staticRotate=new MatrixStatic(*rotateHand);

    //Movement to the second leg
    MatrixScript * handScript=new MatrixScript();
    handScript->add(0.5,staticRotate);

    animation->add(handScript);

}
