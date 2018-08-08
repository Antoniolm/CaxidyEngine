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

#include "text.h"

namespace CaxidyEngine {

Text::Text()
{
    //ctor
}

//**********************************************************************//

Text::Text(MaterialIndex material,TTF_Font * aFont,SDL_Color aColor,bool ahasDialog){
    font=aFont;
    hasDialog=ahasDialog;
    color=aColor;
    surface=0;
    textureText=0;

    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection *materialCollect=MaterialCollection::getInstance();

    positionText=new Matrix4f();
    positionText->identity();
    scaleText=new Matrix4f();
    scaleText->identity();

    textNode=new NodeSceneGraph(false,true);
    textNode->add(positionText);
    textNode->add(scaleText);
    textNode->add(meshCollect->getMesh(TEXT));

    if(hasDialog){ //if has a back texture our Text
        positionBack=new Matrix4f();
        positionBack->identity();
        scaleBack=new Matrix4f();
        scaleBack->identity();

        backNode=new NodeSceneGraph(false,true);
        backNode->add(positionBack);
        backNode->add(scaleBack);
        backNode->add(materialCollect->getMaterial(material));
        backNode->add(meshCollect->getMesh(TEXT));
    }

}

//**********************************************************************//

Text::~Text()
{
    if(textureText!=0)
        glDeleteTextures(1, &textureText);

    if(surface!=0)
      delete surface;

    delete textNode;

    if(hasDialog)
        delete backNode;
}

//**********************************************************************//

void Text::setParameters(MaterialIndex material,TTF_Font * aFont,SDL_Color aColor,bool ahasDialog){
    Text(material,aFont,aColor,ahasDialog);
}


//**********************************************************************//

void Text::setMessage(const std::string & aMessage){
    message=aMessage;
}

//**********************************************************************//
std::string Text::getMessage(){
    return message;
}

//**********************************************************************//

void Text::setPosition(vec3f position){
    positionText->translation(position.x,position.y,position.z);
    if(hasDialog)
        positionBack->translation(position.x,position.y-0.1,position.z-0.1);
}

//**********************************************************************//

void Text::init(float factorX, float factorY){
    glGenTextures(1, &textureText);
    glBindTexture(GL_TEXTURE_2D, textureText);

    if(surface!=0)
        delete surface;

    surface = TTF_RenderText_Blended(font, message.c_str(),color);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);

    //Adjust the size of dialog to our text
    float scaleX=surface->w/factorX,scaleY=surface->h/factorY;
    scaleText->scale(scaleX,scaleY*0.3,1.0);
    if(hasDialog)
        scaleBack->scale(scaleX+0.2,scaleY*1.1,1.0);

}

//**********************************************************************//

void Text::visualization(Context & vis){
    //Draw our texture of background
    if(hasDialog)
        backNode->visualization(vis);

    //Draw our text
    glBindTexture(GL_TEXTURE_2D, textureText);
    textNode->visualization(vis);

}

//**********************************************************************//

void Text::updateState(GameState & gameState){

}

//**********************************************************************//

void Text::setScaleDialog(vec3f value){
    scaleBack->scale(value.x,value.y,value.z);
}

//**********************************************************************//

void Text::setScaleText(vec3f value){
    scaleText->scale(value.x,value.y,value.z);
}

} // CaxidyEngine 
