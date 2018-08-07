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

#include "projectile.h"
#include "rootmapgame.h"

Projectile::Projectile(vec3f aPosition,vec3f aVelocity,avatarDirection aDir,float aDamage,string mesh,string material)
{
    direction=aDir;
    velocity=aVelocity;
    damage=aDamage;
    live=true;

    MeshCollection * meshCollect = MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    soundHit=soundCollect->getSound(sARROW);

    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);

    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);
    //Update direction
    changeDirection(direction);

    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(200,0.0,0.0,1.0);

    root=new NodeSceneGraph();
    root->add(moveAvatar);
    root->add(animationMatrix);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(mesh));

    calculateHead();

    currentTime=SDL_GetTicks();

}

//**********************************************************************//

Projectile::~Projectile()
{
    delete rotation;
    delete root;
}

//**********************************************************************//

void Projectile::visualization(Context & vis){
    if(live && position.x>vis.minVisualPosition.x && position.x<vis.maxVisualPosition.x
       && position.y>vis.minVisualPosition.y && position.y<vis.maxVisualPosition.y)
        root->visualization(vis);
}

//**********************************************************************//

void Projectile::updateState(GameState & gameState){
    float time=gameState.time;
    if(time-currentTime>200)
        currentTime=time-50;

    //Checking the hero
    currentMap=gameState.rootMap;
    Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();
    vec3f posHero=hero->getPosition();
    vec3f posHead=vec3f(vec3f(position)+projectileHead);
    float distance=sqrt(pow(posHead.x-posHero.x,2.0)+pow(posHead.z-posHero.z,2.0));

    //Check if the projectile has hit with our hero
    if(distance<=0.4 && live && (position.y>posHero.y-1 && position.y<posHero.y+1)){
        hero->takeDamage(position,direction,damage);
        live=false;
    }

    if(live) //if not collision with something
        live=moveBody(velocity,direction);

    root->updateState(gameState);
    position=moveAvatar->product(vec4f());
    if(position.z>0.0 || position.x<0.0)
        live=false;


    //Check if is not live
    if(!live){
        soundHit->play(distance);
    }

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());
    currentTime+=(time-currentTime);
}

//**********************************************************************//

bool Projectile::isLive(){
    return live;
}

//**********************************************************************//

void Projectile::setLive(bool value){
    live=value;
}

//**********************************************************************//

void Projectile::setDamage(float value){
    damage=value;
}

//**********************************************************************//

void Projectile::setVelocity(vec3f value){
    velocity=value;
}

//**********************************************************************//

vec3f Projectile::getVelocity(){
    return velocity;
}

//**********************************************************************//

float Projectile::getDamage(){
    return damage;
}

//**********************************************************************//

void Projectile::calculateHead(){
    switch(direction){
            case FORWARD:
                projectileHead=vec3f(0.0,0.0,0.5);
            break;
            case BACKWARD:
                projectileHead=vec3f(0.0,0.0,-0.5);
            break;
            case LEFTWARD:
                projectileHead=vec3f(-0.5,0.0,0.0);
            break;
            case RIGHTWARD:
                projectileHead=vec3f(0.5,0.0,0.0);
            break;
            case FOR_LEFTWARD:
                projectileHead=vec3f(-0.4,0.0,0.4);
            break;
            case FOR_RIGHTWARD:
                projectileHead=vec3f(0.4,0.0,0.4);
            break;
            case BACK_LEFTWARD:
                projectileHead=vec3f(-0.4,0.0,-0.4);
            break;
            case BACK_RIGHTWARD:
                projectileHead=vec3f(0.4,0.0,-0.4);
            break;
        }

}
