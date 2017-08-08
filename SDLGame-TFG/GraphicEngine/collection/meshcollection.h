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

#ifndef MESHCOLLECTION_H
#define MESHCOLLECTION_H

#include "mesh/mesh.h"
#include "collection.h"
#include "collection.cpp"
class Mesh;

using namespace std;

enum MeshIndex{
    CUBE,       //0
    SPHERE,     //1
    BACKGROUND, //2
    KNEE,       //3
    KNEE2,      //4
    SWORD,      //5
    SHIELD,     //6
    HAND,       //7
    HANDS,      //8
    TOPARM,     //9
    CHEST,      //10
    HEAD,       //11
    TEXT,       //12
    COIN,       //13
    EHEAD,      //14
    ECHEST,     //15
    EHAND,      //16
    EFOOT,      //17
    RHEAD,      //18
    RCHEST,     //19
    RHAND,      //20
    RFOOT,      //21
    BUTLER,     //22
    BED,        //23
    CUPBOARD,   //24
    BEDSIDETABLE,//25
    ARROW,      //26
    BKSHELF,    //27
    SMALLTABLE, //29
    CHAIR,      //30
    RUG,        //31
    WINDOW,     //32
    PILLAR,     //33
    CBOW,       //34
    CLUB,       //35
    TORCH,      //36
    CHANDELIER, //37
    BARREL,     //38
    CHOLDER,    //39
    FLAG,       //40
    BENCH,      //41
    COLUMN,     //42
    POTION,     //43
    MATEHEAD,   //44
    MATEHAND,   //45
    BOOKS,      //46
    TRUNK,      //47
    LADDER,     //48
    SPIKE,      //49
    IWALLRIGHT, //50
    IWALLEFT,   //52
    POT,
    POT2,
    DOOR,
    GLYPH,
    SOUL,
    TRAPDOOR,
    BUTTONB,
    BUTTON
};

class MeshCollection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MeshCollection();

        static MeshCollection * getInstance(){
            if(instance == NULL)
                instance = new MeshCollection();

            return instance;
        }

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a mesh -> parameters MeshIndex
        *    \return Mesh *
        */
        //////////////////////////////////////////////////////////////////////////
        Mesh * getMesh(MeshIndex element);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a mesh -> parameters string
        *    \return Mesh *
        */
        //////////////////////////////////////////////////////////////////////////
        Mesh * getMesh(string element);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor  */
        //////////////////////////////////////////////////////////////////////////
        MeshCollection();

        static MeshCollection* instance;       // Instance of MeshCollection
        Collection<Mesh,MeshIndex> collection; // Collection object
};

#endif // MESHCOLLECTION_H
