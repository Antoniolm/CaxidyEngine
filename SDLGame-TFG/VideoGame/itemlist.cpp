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

#include "itemlist.h"

ItemList::ItemList()
{
    //ctor
}

//**********************************************************************//

ItemList::ItemList(const Value & coinFeatures){
    for(unsigned i=0;i<coinFeatures.Size();i++){
        items.push_back(new Item(vec3f(coinFeatures[i]["position"][0].GetFloat(),coinFeatures[i]["position"][1].GetFloat(),coinFeatures[i]["position"][2].GetFloat()),
                                 coinFeatures[i]["value"].GetInt(),(ItemIndex)coinFeatures[i]["type"].GetInt() ) );
    }
}

//**********************************************************************//

ItemList::~ItemList()
{
    for(unsigned i=0;i<items.size();i++)
        delete items[i];
}

//**********************************************************************//

void ItemList::add(Item * coin){
    items.push_back(coin);
}

//**********************************************************************//

void ItemList::visualization(Context & cv){
    for(unsigned i=0;i<items.size();i++)
        items[i]->visualization(cv);
}

//**********************************************************************//

void ItemList::updateState(GameState & gameState ){
    vector<Item*>::iterator it=items.begin();
    while(it!=items.end()){ //loop items
        (*it)->updateState(gameState);
        if((*it)->isTake()){
            delete (*it);
            items.erase(it);
        }
        else
            it++;
    }
}

//**********************************************************************//

const vector<Item *> & ItemList::getItems(){
    return items;
}

//**********************************************************************//

Item * ItemList::getItem(int index){
    return items[index];
}

//**********************************************************************//

int ItemList::getNumItem(){
    return items.size();
}
