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

#include "profile.h"

namespace CaxidyEngine {
    
Profile* Profile::instance = NULL;

Profile::Profile()
{
    totalVisualTime=0;
    totalUpdateTime=0;
    nFrame=0;
    fps=0;
}

//**********************************************************************//

Profile::~Profile()
{
    //dtor
}

//**********************************************************************//

void Profile::addVisualTime(float currentVisualTime){
    totalVisualTime+=currentVisualTime;
}

//**********************************************************************//

void Profile::addUpdateTime(float currentUpdateTime){
    totalUpdateTime+=currentUpdateTime;
}

//**********************************************************************//

void Profile::incrementFrames(){
    if(nFrame==0) initialTime=SDL_GetTicks();

    nFrame++;
}

//**********************************************************************//

void Profile::showResult(){
    float totalTime=SDL_GetTicks()-initialTime;
    totalTime=totalTime/1000; // second
    std::cout<< std::endl<<"-------PROFILE-------"<<std::endl;
    std::cout<< "Average update time-> "<< totalUpdateTime/nFrame<< " miliseconds"<<std::endl;
    std::cout<< "Average visualization time-> "<< totalVisualTime/nFrame<< " miliseconds"<<std::endl;
    std::cout<< "Average fps-> "<< nFrame/totalTime<< " fps"<<std::endl;
    std::cout<< "Total time-> "<< totalTime<< " seconds"<<std::endl;
    std::cout<< "-----END_PROFILE-----"<<std::endl;
}

} // CaxidyEngine 
