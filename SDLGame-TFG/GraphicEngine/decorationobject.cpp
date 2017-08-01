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

#include "decorationobject.h"

DecorationObject::DecorationObject()
{
    //ctor
}

//**********************************************************************//

DecorationObject::DecorationObject(const rapidjson::Value & DOFeature,vec3f posDecoration){
    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    NodeSceneGraph * objNode=new NodeSceneGraph();

    Matrix4f * transformation=new Matrix4f();
    transformation->translation(posDecoration.x,posDecoration.y,posDecoration.z);

    objNode->add(transformation);
    for(unsigned currentTrans=0; currentTrans<DOFeature["transforms"].Size(); currentTrans++)
    {
        transformation=new Matrix4f();
        if(strcmp(DOFeature["transforms"][currentTrans]["type"].GetString(),"translation")==0)  //If is a translation
        {

            transformation->translation(DOFeature["transforms"][currentTrans]["values"][0].GetFloat(),
            DOFeature["transforms"][currentTrans]["values"][1].GetFloat(),
            DOFeature["transforms"][currentTrans]["values"][2].GetFloat());

        }
        else if(strcmp(DOFeature["transforms"][currentTrans]["type"].GetString(),"scale")==0)  //If is a scale
        {

            transformation->scale(DOFeature["transforms"][currentTrans]["values"][0].GetFloat(),
                                  DOFeature["transforms"][currentTrans]["values"][1].GetFloat(),
                                  DOFeature["transforms"][currentTrans]["values"][2].GetFloat());

        }
        else if(strcmp(DOFeature["transforms"][currentTrans]["type"].GetString(),"rotation")==0)  //If is a rotation
        {

            transformation->rotation(DOFeature["transforms"][currentTrans]["values"][0].GetFloat(),
                                     DOFeature["transforms"][currentTrans]["values"][1].GetFloat(),
                                     DOFeature["transforms"][currentTrans]["values"][2].GetFloat(),
                                     DOFeature["transforms"][currentTrans]["values"][3].GetFloat());

        }
        objNode->add(transformation);

    }


    objNode->add(materialCollect->getMaterial(DOFeature["material"].GetString()));
    objNode->add(meshCollect->getMesh(DOFeature["mesh"].GetString()));

    object=objNode;
    damage=0.0;
    hasShadow=DOFeature["shadow"].GetBool();

}

//**********************************************************************//

DecorationObject::~DecorationObject()
{
    //dtor
}
