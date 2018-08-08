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


#include "nodescenegraph.h"

namespace CaxidyEngine {
    
NodeSceneGraph::NodeSceneGraph(bool aInvert,bool nolight)
{
    invert=aInvert;
    noLight=nolight;
    currentTime=SDL_GetTicks();
    boundingBox.maxValue=vec3f(2.5,2.5,2.5);
    boundingBox.minValue=vec3f(-2.5,-2.5,-2.5);
}

//**********************************************************************//

NodeSceneGraph::NodeSceneGraph(const NodeSceneGraph & aNode){
    entrance=aNode.entrance;
    boundingBox.maxValue=vec3f(0.5,0.5,0.5);
    boundingBox.minValue=vec3f(-0.5,-0.5,-0.5);
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

NodeSceneGraph::~NodeSceneGraph()
{
    std::vector<EntryNGE>::iterator it;
    for(it=entrance.begin();it!=entrance.end();it++){
        switch((*it).type){
            case 0: //Object3d
                (*it).obj->removeLink();
                if((*it).obj->getCountLink()==0){
                    delete (*it).obj; //testing
                }
                break;
            case 1: //Matrix4f
                delete (*it).matrix;
                break;
        }
    }
}

//**********************************************************************//

void NodeSceneGraph::visualization(Context & cv){
    //if invert
    if(invert) glUniform1i(glGetUniformLocation(cv.currentShader->getProgram(),"invertNormal"), 1);
    else glUniform1i(glGetUniformLocation(cv.currentShader->getProgram(),"invertNormal"), 0);

    //if noLight -> is a menu
    if(noLight) glUniform1i(glGetUniformLocation(cv.currentShader->getProgram(),"noLight"), 1);
    else glUniform1i(glGetUniformLocation(cv.currentShader->getProgram(),"noLight"), 0);

    int contMatrix=1;
    int contMaterial=0;
    vec4f pos;
    cv.matrixStack.push();
    std::vector<EntryNGE>::iterator it;
    for(it=entrance.begin();it!=entrance.end();it++){
            switch((*it).type){
            case 0: //Object3d
                cv.matrixStack.activate(cv.currentShader->getProgram());
                (*it).obj->visualization(cv);
                break;
            case 1: //Matrix4f
                cv.matrixStack.cMatrix((*(*it).matrix));
                contMatrix++;
                break;
            case 2: //Material
                cv.materialStack.push((*it).material);
                (*it).material->activate(cv.currentShader->getProgram());
                contMaterial++;
                break;
            }

    }
    cv.currentMaterialIndex=(cv.materialStack.getMaterial()->getIndex());
    cv.materialStack.pop(contMaterial);
    cv.materialStack.getMaterial()->activate(cv.currentShader->getProgram());

    cv.currentTransf.setMatrix(cv.matrixStack.getMatrix().getMatrix());
    cv.matrixStack.pop(contMatrix);
    cv.matrixStack.activate(cv.currentShader->getProgram());
}

//**********************************************************************//

void NodeSceneGraph::updateState(GameState & gameState){
    for(unsigned i=0;i<entrance.size();i++){
        if(entrance[i].type==0)
            entrance[i].obj->updateState(gameState);
    }

}

//**********************************************************************//

void NodeSceneGraph::add(EntryNGE * anEntry){
    entrance.push_back(*anEntry);
}

//**********************************************************************//

void NodeSceneGraph::add(Object3D * anObject){
    EntryNGE newEntrance(anObject);
    entrance.push_back(newEntrance);
}

//**********************************************************************//

void NodeSceneGraph::add(Matrix4f * aMatrix){
    EntryNGE newEntrance(aMatrix);
    entrance.push_back(newEntrance);

}

//**********************************************************************//

void NodeSceneGraph::add(Material * aMaterial){
    EntryNGE newEntrance(aMaterial);
    entrance.push_back(newEntrance);
}

//**********************************************************************//

BoundingBox NodeSceneGraph::getBoundingBox(){
    std::vector<EntryNGE>::iterator it;
    BoundingBox auxBox;
    for(it=entrance.begin();it!=entrance.end();it++){
            switch((*it).type){
            case 0: //Object3d
                auxBox=(*it).obj->getBoundingBox();
                if(auxBox<boundingBox)
                    boundingBox=auxBox;
                break;
            }

    }


    return boundingBox;
}

//**********************************************************************//

void NodeSceneGraph::obtainPosition(Context & cv){
    int contMatrix=1;
    int contMaterial=0;
    vec4f pos;
    cv.matrixStack.push();
    std::vector<EntryNGE>::iterator it;
    for(it=entrance.begin();it!=entrance.end();it++){
            switch((*it).type){
            case 0: //Object3d
                (*it).obj->obtainPosition(cv);
                break;
            case 1: //Matrix4f
                cv.matrixStack.cMatrix((*(*it).matrix));
                contMatrix++;
                break;
            case 2: //Material
                cv.materialStack.push((*it).material);
                contMaterial++;
                break;
            }

    }
    cv.currentMaterialIndex=(cv.materialStack.getMaterial()->getIndex());
    cv.materialStack.pop(contMaterial);

    cv.currentTransf.setMatrix(cv.matrixStack.getMatrix().getMatrix());
    cv.matrixStack.pop(contMatrix);
}

} // CaxidyEngine 

