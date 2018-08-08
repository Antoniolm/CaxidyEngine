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

#include "animationlist.h"

namespace CaxidyEngine {

AnimationList::AnimationList()
{
  currentAnimation=0;
}

//**********************************************************************//

AnimationList::~AnimationList()
{
    for(unsigned i=0;i<animations.size();i++)
        delete animations[i];
}

//**********************************************************************//

void AnimationList::add(ScriptLMD * animation){
    animations.push_back(animation);
}

//**********************************************************************//

void AnimationList::activate(int index){
    currentAnimation=index;
}

//**********************************************************************//

void AnimationList::update(float time){
    animations[currentAnimation]->updateState(time);
}

//**********************************************************************//

void AnimationList::resetAnimation(int index){
    animations[index]->resetState();
}

//**********************************************************************//

int AnimationList::getState(){
    return currentAnimation;
}

//**********************************************************************//

ScriptLMD * AnimationList::getAnimation(){
    return animations[currentAnimation];
}

//**********************************************************************//

int AnimationList::getNumAnimation(){
    return animations.size();
}

} // CaxidyEngine
