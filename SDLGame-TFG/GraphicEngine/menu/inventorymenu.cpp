// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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

#include "inventorymenu.h"
#include "../VideoGame/inventory.h"
#include "../text.h"
#include "collection/meshcollection.h"



InventoryMenu::InventoryMenu(){

}

//**********************************************************************//

InventoryMenu::~InventoryMenu(){
    delete root;

    delete currentMaterial;
    delete materialBack;
    delete confirmMaterial;
    delete materialEquipped;

    delete damageItemText;
    delete armourItemText;
    delete lifeItemText;
    delete nameItemText;

    delete levelText;
    delete lifeText;
    delete damageText;
    delete armourText;

    delete inventory;
}

//**********************************************************************//

void InventoryMenu::visualization(Context & cv){

}

//**********************************************************************//

void InventoryMenu::updateState(GameState & gameState){

}

//**********************************************************************//

void InventoryMenu::setInventory(const vector<Equipment*> & equipVec, const vector<vec2f> & posVec){
    //Clean the current state of the inventory
    clearInventory();

    for(int i=0;i<equipVec.size();i++){
        inventory->addItem(posVec[i].x,posVec[i].y,equipVec[i]);

        //Change texture
        itemView[(int)posVec[i].y][(int)posVec[i].x]->setMaterial(*materialCollect->getMaterial(equipVec[i]->getImageProfile()));

        //If is equipped changes the mesh of equippedItem
        if(equipVec[i]->isEquipped())
            equippedItem[equipVec[i]->getEquipType()]->translation(-0.273+((int)posVec[i].x*distItem.x),0.455-((int)posVec[i].y*distItem.y),0.9f);
    }
}

//**********************************************************************//

bool InventoryMenu::addEquip(Equipment * aEquip){
    bool result=false;

    pair<int,int> positionSlot = inventory->emptySlot();
    if( positionSlot.first!=-1){ //If the inventory is not full
        result=true;
        inventory->addItem(positionSlot.first,positionSlot.second,aEquip);

        //Change texture
        itemView[positionSlot.second][positionSlot.first]->setMaterial(*materialCollect->getMaterial(aEquip->getImageProfile()));
    }

    return result;
}

//**********************************************************************//

Inventory * InventoryMenu::getInventory(){
    return inventory;
}

//**********************************************************************//

void InventoryMenu::clearInventory(){

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            if(inventory->removeItem(j,i))
                itemView[i][j]->setMaterial(*materialCollect->getMaterial(mVOID));
        }
    }

    //Clear equippedItem
    equippedItem[0]->translation(-0.273,0.455,0.9f);
    equippedItem[1]->translation(-0.273+distItem.x,0.455,0.9f);
    equippedItem[2]->translation(-0.273+(2*distItem.x),0.455,0.9f);
}

//**********************************************************************//

Equipment * InventoryMenu::getEquippetItem(int aType){
    Equipment * result=0;

    for(int i=0;i<inventory->getSizeY() && result==0 ;i++){
        for(int j=0;j<inventory->getSizeX() && result==0 ;j++){
            Equipment * auxEquip=inventory->getItem(j,i);
            if(auxEquip!=0 && auxEquip->getEquipType()==(EquipmentType)aType && auxEquip->isEquipped())
                result=inventory->getItem(j,i);
        }
    }

    return result;
}

//**********************************************************************//

void InventoryMenu::initInfoItem(){

    nameItemText->setMessage("--");
    lifeItemText->setMessage("--");
    damageItemText->setMessage("--");
    armourItemText->setMessage("--");

    materialCurrentMaterial->setMaterial((*materialCollect->getMaterial("mVOID")));

    nameItemText->init(1250.0,80.0);
    lifeItemText->init(750.0,60.0);
    damageItemText->init(750.0,60.0);
    armourItemText->init(750.0,60.0);

}

//**********************************************************************//

void InventoryMenu::changeSelectedItems(){
    std::stringstream lifeText,armourText,damageText,nameText;

    if(!inventory->isEmpty(currentItemX,currentItemY)){

        Equipment * equip=inventory->getItem(currentItemX,currentItemY);

        lifeText<< equip->getLife();
        lifeItemText->setMessage(lifeText.str());
        lifeItemText->init(750.0,60.0);

        armourText<< equip->getArmour();
        armourItemText->setMessage(armourText.str());
        armourItemText->init(750.0,60.0);

        damageText<< equip->getDamage();
        damageItemText->setMessage(damageText.str());
        damageItemText->init(750.0,60.0);

        nameText<< equip->getName();
        nameItemText->setMessage(nameText.str());
        nameItemText->init(1250.0,80.0);

        materialCurrentMaterial->setMaterial((*materialCollect->getMaterial(equip->getImageProfile())));
        lastSelection=equip;

    }
    else {
        if(lastSelection!=0){
            initInfoItem();
        }
        lastSelection=0;
    }

}

//**********************************************************************//

NodeSceneGraph * InventoryMenu::createMatrixItems(){
    //////////////////////////////////
    //Shape for every item of the inventory
    MeshCollection * meshCollect=MeshCollection::getInstance();

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            itemView[i][j]=new Material((*materialCollect->getMaterial("mVOID")));
        }
    }

    Matrix4f * selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.272,0.439,0.8);

    Matrix4f * scaleItem=new Matrix4f();
    scaleItem->scale(0.078,0.5,0.1);

    NodeSceneGraph * items0x0=new NodeSceneGraph(false,true);
    items0x0->add(selectedPositionItem);
    items0x0->add(scaleItem);
    items0x0->add(itemView[0][0]);
    items0x0->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][1]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.062,0.439,0.8);

    NodeSceneGraph * items0x1=new NodeSceneGraph(false,true);
    items0x1->add(selectedPositionItem);
    items0x1->add(scaleItem);
    items0x1->add(itemView[0][1]);
    items0x1->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][2]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.142,0.439,0.8);

    NodeSceneGraph * items0x2=new NodeSceneGraph(false,true);
    items0x2->add(selectedPositionItem);
    items0x2->add(scaleItem);
    items0x2->add(itemView[0][2]);
    items0x2->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][3]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.345,0.439,0.8);

    NodeSceneGraph * items0x3=new NodeSceneGraph(false,true);
    items0x3->add(selectedPositionItem);
    items0x3->add(scaleItem);
    items0x3->add(itemView[0][3]);
    items0x3->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][4]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.555,0.439,0.8);

    NodeSceneGraph * items0x4=new NodeSceneGraph(false,true);
    items0x4->add(selectedPositionItem);
    items0x4->add(scaleItem);
    items0x4->add(itemView[0][4]);
    items0x4->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][5]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.757,0.439,0.8);

    NodeSceneGraph * items0x5=new NodeSceneGraph(false,true);
    items0x5->add(selectedPositionItem);
    items0x5->add(scaleItem);
    items0x5->add(itemView[0][5]);
    items0x5->add(meshCollect->getMesh(TEXT));


    ///////////////////////////////////////////////////////////////////
    // Row 2

    /////////////////////////
    // Item[1][0]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.272,0.15,0.8);

    NodeSceneGraph * items1x0=new NodeSceneGraph(false,true);
    items1x0->add(selectedPositionItem);
    items1x0->add(scaleItem);
    items1x0->add(itemView[1][0]);
    items1x0->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][1]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.062,0.15,0.8);

    NodeSceneGraph * items1x1=new NodeSceneGraph(false,true);
    items1x1->add(selectedPositionItem);
    items1x1->add(scaleItem);
    items1x1->add(itemView[1][1]);
    items1x1->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][2]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.142,0.15,0.8);

    NodeSceneGraph * items1x2=new NodeSceneGraph(false,true);
    items1x2->add(selectedPositionItem);
    items1x2->add(scaleItem);
    items1x2->add(itemView[1][2]);
    items1x2->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][3]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.345,0.15,0.8);

    NodeSceneGraph * items1x3=new NodeSceneGraph(false,true);
    items1x3->add(selectedPositionItem);
    items1x3->add(scaleItem);
    items1x3->add(itemView[1][3]);
    items1x3->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][4]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.555,0.15,0.8);

    NodeSceneGraph * items1x4=new NodeSceneGraph(false,true);
    items1x4->add(selectedPositionItem);
    items1x4->add(scaleItem);
    items1x4->add(itemView[1][4]);
    items1x4->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][5]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.757,0.15,0.8);

    NodeSceneGraph * items1x5=new NodeSceneGraph(false,true);
    items1x5->add(selectedPositionItem);
    items1x5->add(scaleItem);
    items1x5->add(itemView[1][5]);
    items1x5->add(meshCollect->getMesh(TEXT));

    ///////////////////////////////////////////////////////////////////
    // Row 3

    /////////////////////////
    // Item[2][0]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.272,-0.139,0.8);

    NodeSceneGraph * items2x0=new NodeSceneGraph(false,true);
    items2x0->add(selectedPositionItem);
    items2x0->add(scaleItem);
    items2x0->add(itemView[2][0]);
    items2x0->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][1]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.062,-0.139,0.8);

    NodeSceneGraph * items2x1=new NodeSceneGraph(false,true);
    items2x1->add(selectedPositionItem);
    items2x1->add(scaleItem);
    items2x1->add(itemView[2][1]);
    items2x1->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][2]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.142,-0.139,0.8);

    NodeSceneGraph * items2x2=new NodeSceneGraph(false,true);
    items2x2->add(selectedPositionItem);
    items2x2->add(scaleItem);
    items2x2->add(itemView[2][2]);
    items2x2->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][3]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.345,-0.139,0.8);

    NodeSceneGraph * items2x3=new NodeSceneGraph(false,true);
    items2x3->add(selectedPositionItem);
    items2x3->add(scaleItem);
    items2x3->add(itemView[2][3]);
    items2x3->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][4]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.555,-0.139,0.8);

    NodeSceneGraph * items2x4=new NodeSceneGraph(false,true);
    items2x4->add(selectedPositionItem);
    items2x4->add(scaleItem);
    items2x4->add(itemView[2][4]);
    items2x4->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][5]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.757,-0.139,0.8);

    NodeSceneGraph * items2x5=new NodeSceneGraph(false,true);
    items2x5->add(selectedPositionItem);
    items2x5->add(scaleItem);
    items2x5->add(itemView[2][5]);
    items2x5->add(meshCollect->getMesh(TEXT));


    //Create matrix

    NodeSceneGraph * matrixItems=new NodeSceneGraph(false,true);
    matrixItems->add(items0x0);
    matrixItems->add(items0x1);
    matrixItems->add(items0x2);
    matrixItems->add(items0x3);
    matrixItems->add(items0x4);
    matrixItems->add(items0x5);

    matrixItems->add(items1x0);
    matrixItems->add(items1x1);
    matrixItems->add(items1x2);
    matrixItems->add(items1x3);
    matrixItems->add(items1x4);
    matrixItems->add(items1x5);

    matrixItems->add(items2x0);
    matrixItems->add(items2x1);
    matrixItems->add(items2x2);
    matrixItems->add(items2x3);
    matrixItems->add(items2x4);
    matrixItems->add(items2x5);


    return matrixItems;
}

