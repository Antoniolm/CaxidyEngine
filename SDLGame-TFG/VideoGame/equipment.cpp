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

Equipment::Equipment(){
    notTake=true;
    type=iWEAPON;
    equipped=false;
    rotation=0;
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Equipment::Equipment(const Value & equipFeatures){

    position=vec4f(equipFeatures["posInScene"][0].GetFloat(),equipFeatures["posInScene"][1].GetFloat(),equipFeatures["posInScene"][2].GetFloat(),1.0f);
    posInAvatar=vec3f(equipFeatures["posInAvatar"][0].GetFloat(),equipFeatures["posInAvatar"][1].GetFloat(),equipFeatures["posInAvatar"][2].GetFloat());

    equipType=(EquipmentType)equipFeatures["type"].GetInt();

    imageProfile=equipFeatures["imgProfile"].GetString();
    material=equipFeatures["material"].GetString();
    mesh=equipFeatures["geometry"].GetString();
    name=equipFeatures["name"].GetString();

    damage=equipFeatures["damage"].GetInt();
    life=equipFeatures["life"].GetInt();
    armour=equipFeatures["armour"].GetInt();

    notTake=true;
    equipped=equipFeatures["equipped"].GetBool();
    type=iWEAPON;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect = SoundCollection::getInstance();

    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(100,0.0,1.0,0.0);

    transObject=new Matrix4f();
    if(position.x==0 && position.y==0 && position.z==0)
        transObject->translation(posInAvatar.x,posInAvatar.y,posInAvatar.z);
    else
        transObject->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(animationMatrix);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(mesh));
    currentTime=SDL_GetTicks();

    soundTake=soundCollect->getSound(sCoin);
}

//**********************************************************************//

Equipment::Equipment(vec3f aPos,EquipmentType atype, bool aEquipped,int aDmg,int aLife, int aArmour,string aImg,string aMesh,string aMaterial,string aName)
{
    position=vec4f(aPos.x,aPos.y,aPos.z,1.0);
    posInAvatar=aPos;

    equipType=atype;

    imageProfile=aImg;
    material=aMaterial;
    mesh=aMesh;
    name=aName;

    damage=aDmg;
    life=aLife;
    armour=aArmour;

    notTake=false;
    type=iWEAPON;
    equipped=aEquipped;
    rotation=0;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(mesh));

    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Equipment::~Equipment(){

    root->removeLink();
    if(root->getCountLink()==0){
        delete root;
    }

    if(rotation!=0)
        delete rotation;
}

//**********************************************************************//

void Equipment::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Equipment::updateState(GameState & gameState){
    float time=gameState.time;
    vec3f posRefPoint=gameState.refPoint;
    float distance=sqrt(pow(position.x-posRefPoint.x,2.0)+pow(position.y-posRefPoint.y,2.0)+pow(position.z-posRefPoint.z,2.0));

    if(distance<=0.4){ //Catch the new equipement

        Equipment * newEquip=new Equipment();
        newEquip->setEquip((*this));
        root->addLink();
        root->addLink();

        if(gameState.inventoryMenu->addEquip(newEquip)){
            notTake=false;
            transObject->translation(posInAvatar.x,posInAvatar.y,posInAvatar.z);
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

void Equipment::setMesh(const string & aMesh){
    mesh=aMesh;
}

//**********************************************************************//

void Equipment::setMaterial(const string & aMaterial){
    material=aMaterial;
}

//**********************************************************************//

void Equipment::setName(const string & aName){
    name=aName;
}

//**********************************************************************//

void Equipment::setArmour(int anArmour){
    armour=anArmour;
}

//**********************************************************************//

void Equipment::setLife(int aLife){
    life=aLife;
}

//**********************************************************************//

void Equipment::setEquipType(EquipmentType aTypeEquip){
    equipType=aTypeEquip;
}

//**********************************************************************//

void Equipment::setEquipped(bool isEquip){
    equipped=isEquip;
}

//**********************************************************************//

void Equipment::setEquip(const Equipment & equip){
    position=equip.position;
    posInAvatar=equip.posInAvatar;

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

vec3f Equipment::getPosInAvatar(){
    return posInAvatar;
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

string Equipment::getName(){
    return name;
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

//**********************************************************************//

EquipmentType Equipment::getEquipType(){
    return equipType;
}

//**********************************************************************//

bool Equipment::isEquipped(){
    return equipped;
}
