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

#include "endmapregion.h"

EndMapRegion::EndMapRegion(const Value & regionFeatures){

    position=vec3f(regionFeatures["position"][0].GetFloat(),regionFeatures["position"][1].GetFloat(),regionFeatures["position"][2].GetFloat());
    radioActivity=vec3f(regionFeatures["radioActivity"][0].GetFloat(),regionFeatures["radioActivity"][1].GetFloat(),regionFeatures["radioActivity"][2].GetFloat());

    activated=false;
}

//**********************************************************************//

EndMapRegion::~EndMapRegion()
{
    //dtor
}

//**********************************************************************//

void EndMapRegion::updateState(GameState & gameState){

    vec3f distance=vec3f(position.x,position.y,position.z)-gameState.refPoint;

    //check if the region will be activated in this frame
    if((distance.x>-radioActivity.x && distance.x<radioActivity.x)&&
       (distance.y>-radioActivity.y && distance.y<radioActivity.y)&&
       (distance.z>-radioActivity.z && distance.z<radioActivity.z)){
        activated=true;
    }

}
