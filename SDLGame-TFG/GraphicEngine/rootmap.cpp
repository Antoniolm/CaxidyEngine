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

#include "rootmap.h"
#include "mesh/objectgroup.h"
#include <stdlib.h>

RootMap::RootMap(){
}

//**********************************************************************//

RootMap::~RootMap()
{
    delete loader;
    delete backSound;
    delete title;
    delete endMapRegion;
    delete movie;

    for(unsigned i=0;i<objs.size();i++)
        deleteObject3d(objs[i]);

    for(unsigned i=0;i<elements.size();i++)
        delete elements[i];

    for(unsigned i=0;i<decorationObjs.size();i++)
        delete decorationObjs[i];

    for(unsigned i=0;i<objectGroup.size();i++)
        delete objectGroup[i];

    for(unsigned i=0;i<regions.size();i++)
        delete regions[i];

    for(unsigned i=0;i<lights.size();i++)
        delete lights[i];
}

//**********************************************************************//

void RootMap::initialize(string fileMap){

}

//**********************************************************************//

Hero * RootMap::getHero(){
    return hero;
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    //Draw background
    background->visualization(cv);

    //Draw object groups
    for(unsigned i=0;i<objectGroup.size();i++){
        objectGroup[i]->visualization(cv);
    }

    //Draw elements of the scene
    for(unsigned i=0;i<elements.size();i++){
        elements[i]->visualization(cv);
    }

    //Draw decoration object
    for(unsigned i=0;i<decorationObjs.size();i++){
        decorationObjs[i]->visualization(cv);
    }

    //Draw title
    title->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    if(!gameState.movie->isActivated() && !gameState.mainMenu->isActivate() && !gameState.pauseMenu->isActivate()
       && !gameState.deadMenu->isActivate() && !gameState.inventoryMenu->isActivate() && !gameState.camera->isViewMode()){

        vector<Object3D * >::iterator it=elements.begin();

        while(it!=elements.end()){
            (*it)->updateState(gameState);
            if((*it)->isDeleting()){
                delete (*it);
                it = elements.erase(it);
            }
            else
                it++;
        }

        //Update the Scene
        for(unsigned i=0;i<objectGroup.size();i++)
            objectGroup[i]->updateState(gameState);

        //Update textregions
        for(unsigned i=0;i<regions.size();i++){
            regions[i]->updateState(gameState);
        }

        //Update title
        title->updateState(gameState);

        //Update endMapRegion
        endMapRegion->updateState(gameState);

        currentTime+=time-currentTime;
        gameState.rootMap->enableSound(true);
    }
    else{
        if(gameState.pauseMenu->isActivate() || gameState.deadMenu->isActivate() || gameState.inventoryMenu->isActivate())
            gameState.rootMap->enableSound(false);
    }
}

//**********************************************************************//

void RootMap::enableSound(bool value){
    if(value){
            backSound->play();
    }
    else{
        if(backSound->isPlaying())
            backSound->stop();
    }
}

//**********************************************************************//

ObjectScene * RootMap::collision(const vec3f & indexObj){
    bool hasCollision=false;
    ObjectScene * result=0;
    vec3f pos;
    BoundingBox box;
    int tam=indexMap[(int)indexObj.x][(int)indexObj.z*-1].size();

    vector<int>::iterator it=indexMap[(int)indexObj.x][(int)indexObj.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)indexObj.x][(int)indexObj.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt && !hasCollision;it++){ //if There are object in that position (x,z)
            pos=objs[(*it)]->getPosition();
            box=objs[(*it)]->getBoundingBox();
            if((indexObj.y >= (pos.y)+box.minValue.y && indexObj.y <= (pos.y)+box.maxValue.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;
}

//**********************************************************************//

ObjectScene * RootMap::collision(const vec3f & posFirst, const vec3f & posSecond){
    bool hasCollision=false;
    ObjectScene * result=0;
    vec3f pos;
    BoundingBox box;
    int tam=indexMap[(int)posFirst.x][(int)posFirst.z*-1].size();

    vector<int>::iterator it=indexMap[(int)posFirst.x][(int)posFirst.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)posFirst.x][(int)posFirst.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt && !hasCollision;it++){ //if There are object in that position (x,z)
            pos=objs[(*it)]->getPosition();
            box=objs[(*it)]->getBoundingBox();
            if((posFirst.y <= pos.y && posSecond.y >= pos.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;

}

//**********************************************************************//

void RootMap::addCollision(vec2f voxelPosition,int objID){

    //Create our indexMap for our collision system
    vec3f pos=objs[objID]->getPosition();
    BoundingBox bounding=objs[objID]->getBoundingBox();
    bounding.minValue.z+=0.1;
    bounding.minValue.x-=0.1;

    for(int x=bounding.minValue.x;x<bounding.maxValue.x;x++){
        for(int z=bounding.minValue.z;z<bounding.maxValue.z;z++){
            indexMap[(int)(pos.x+x)][(int)((pos.z+z)*(-1))].push_back(objID);
        }
    }
}

//**********************************************************************//

void RootMap::removeCollision(vec2f voxelPosition,int objID){
    int tam=indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].size();
    bool deleted=false;

    vector<int>::iterator it=indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].end();

    if(tam!=0 ){
        while(it!=endIt && !deleted){ //if There are object in that position (x,z)
            if((*it)==objID){
                indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].erase(it);
                deleted=true;
            }
            else
                it++;
        }
    }
}

//**********************************************************************//

bool RootMap::isLoading(){
    return loading;
}

//**********************************************************************//

bool RootMap::isFinished(){
    bool result=endMapRegion->isActivated();
    if(result){
        enableSound(false);
    }

    return result;
}

//**********************************************************************//

string RootMap::getNextMap(){
    return nextMapFile;
}

//**********************************************************************//

MovieScreen * RootMap::getMovie(){
    return movie;
}

//**********************************************************************//

void RootMap::activatedLight(GLuint shaderID){
    glUniform1i(glGetUniformLocation(shaderID, "numActivateLight"), lights.size()-1);
    for(unsigned i=0;i<lights.size();i++)
        lights[i]->activate(shaderID);
}

//**********************************************************************//

void RootMap::activatedObjectGroup(){
    for(unsigned i=0;i<objectGroup.size();i++)
        objectGroup[i]->init();
}

//**********************************************************************//

void RootMap::deleteObject3d(Object3D * obj){
    obj->removeLink();
    if(obj->getCountLink()==0){
        delete obj;
    }
}
