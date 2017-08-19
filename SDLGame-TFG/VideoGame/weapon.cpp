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

#include "weapon.h"

Weapon::Weapon(const Value & weaponFeatures){
    position=vec4f(weaponFeatures["position"][0].GetFloat(),weaponFeatures["position"][1].GetFloat(),weaponFeatures["position"][2].GetFloat(),1.0f);
    damage=weaponFeatures["value"].GetInt();
    typeWeapon=(WeaponType)weaponFeatures["type"].GetInt();

    notTake=true;
    type=iWEAPON;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect = SoundCollection::getInstance();

    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(100,0.0,1.0,0.0);

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(animationMatrix);
    root->add(materialCollect->getMaterial(weaponFeatures["material"].GetString()));
    root->add(meshCollect->getMesh(weaponFeatures["geometry"].GetString()));
    currentTime=SDL_GetTicks();

    soundTake=soundCollect->getSound(sCoin);
}

//**********************************************************************//

Weapon::Weapon(vec3f aPos,WeaponType atype,float aDamage,string mesh,string material)
{
    damage=aDamage;
    typeWeapon=atype;
    type=iWEAPON;
    position=vec4f(aPos.x,aPos.y,aPos.z,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(mesh));

    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Weapon::~Weapon()
{
    delete root;
}
//**********************************************************************//

void Weapon::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Weapon::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();
    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.y-posHero.y,2.0)+pow(position.z-posHero.z,2.0));

    if(distance<=0.4){
        if(gameState.inventoryMenu->addEquip(this)){
            notTake=false;
            soundTake->play();
        }
    }

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());
    currentTime+=time-currentTime;
}

//**********************************************************************//

void Weapon::setDamage(float value){
    damage=value;
}

//**********************************************************************//

float Weapon::getDamage(){
    return damage;
}

//**********************************************************************//

WeaponType Weapon::getWeaponType(){
    return typeWeapon;
}

//**********************************************************************//

void Weapon::setWeapon(const Weapon & weapon){
    damage=weapon.damage;
    typeWeapon=weapon.typeWeapon;
    root=weapon.root;
}

