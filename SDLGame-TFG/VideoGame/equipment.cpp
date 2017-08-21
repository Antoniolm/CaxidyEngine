// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David López Machado
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


#include "equipment.h"

Equipment::Equipment(const Value & equipFeatures){
    position=vec4f(equipFeatures["position"][0].GetFloat(),equipFeatures["position"][1].GetFloat(),equipFeatures["position"][2].GetFloat(),1.0f);
    damage=equipFeatures["value"].GetInt();
    equipType=(EquipmentType)equipFeatures["type"].GetInt();
    imageProfile=equipFeatures["imgProfile"].GetString();

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
    root->add(materialCollect->getMaterial(equipFeatures["material"].GetString()));
    root->add(meshCollect->getMesh(equipFeatures["geometry"].GetString()));
    currentTime=SDL_GetTicks();

    soundTake=soundCollect->getSound(sCoin);
}

//**********************************************************************//

Equipment::Equipment(vec3f aPos,EquipmentType atype,float aDamage,string mesh,string material)
{
    damage=aDamage;
    equipType=atype;
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

Equipment::~Equipment(){
    delete root;
}

//**********************************************************************//

void Equipment::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Equipment::updateState(GameState & gameState){
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

void Equipment::setImageProfile(const string & imageFile){
    imageProfile=imageFile;
}


//**********************************************************************//

void Equipment::setDamage(int dmg){
    damage=dmg;
}

//**********************************************************************//

float Equipment::getDamage(){
    return damage;
}

//**********************************************************************//

EquipmentType Equipment::getEquipType(){
    return equipType;
}

//**********************************************************************//

void Equipment::setEquip(const Equipment & equip){
    name=equip.name;
    imageProfile=equip.imageProfile;
    mesh=equip.mesh;
    material=equip.material;
    equipType=equip.equipType;

    damage=equip.damage;
    armour=equip.armour;
    life=equip.life;
    root=equip.root;
}

//**********************************************************************//

string Equipment::getImageProfile(){
    return imageProfile;
}

//**********************************************************************//

string Equipment::getMesh(){
    return mesh;
}

//**********************************************************************//

string Equipment::getMaterial(){
    return material;
}

//**********************************************************************//

int Equipment::getDamage(){
    return damage;
}

//**********************************************************************//

int Equipment::getArmour(){
    return armour;
}

//**********************************************************************//

int Equipment::getLife(){
    return life;
}
