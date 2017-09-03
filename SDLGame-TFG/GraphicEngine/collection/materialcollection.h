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

#ifndef MATERIALCOLLECTION_H
#define MATERIALCOLLECTION_H

#include <vector>
#include <map>
#include "collection.h"
#include "collection.cpp"
#include <string>

using namespace std;

enum MaterialIndex{
    mCUBE_DUNG,     //2
    mCUBE_DUNGB,    //3
    mCUBE_WALL,     //4
    mINVICUBE_WALL, //5
    mCUBE_TRAP,     //6
    mCUBE_SPIKE,    //7
    mCUBE_LAND,    //7
    mCUBE_STEEL,    //7
    mCUBE_ROCK,    //7
    mDWATER,        //8
    mVOID,          //9
    mCRYSTAL,       //10
    mHERO,          //11
    mSWORD,         //12
    mSHIELD,        //13
    mENEMY,         //14
    mARCHENEMY,     //15
    mDIALOG,        //16
    mBDIALOG,       //17
    mADIALOG,       //18
    mBUTLER,        //19
    mFURNITURE,     //20
    mRUG,           //22
    mFIRE,          //23
    mWINDOW,        //24
    mPILLAR,        //25
    mBED,           //26
    mTORCH,         //27
    mCHANDELIER,    //28
    mFLAG,          //29
    mCOLUMN,        //30
    mPOTION,        //31
    mMATE,          //32
    mCHAIR,         //33
    mWOOD,          //34
    mBOOKS,         //35
    mTRUNK,         //36
    mSPIKE,         //37
    mGMPADV,        //38
    mGMPADX,        //39
    mTITLE1,        //40
    mPOT,
    mDOOR,
    mGLYPH,
    mSOUL,
    mLIFEBAR,
    mLIFE,
    mEXP,
    mCRYSDRAW,
    mTRAPDOOR,
    mBUTTON,
    mSPEAK,
    mEQUIPPED
};

class Material;
class MaterialCollection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MaterialCollection();

        static MaterialCollection * getInstance(){
            if(instance == NULL)
                instance = new MaterialCollection();

            return instance;
        }

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a material -> parameters MaterialIndex
        *    \return Material *
        */
        //////////////////////////////////////////////////////////////////////////
        Material * getMaterial(MaterialIndex element);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a material -> parameters string
        *    \return Material *
        */
        //////////////////////////////////////////////////////////////////////////
        Material * getMaterial(string element);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MaterialCollection();

        static MaterialCollection* instance;           // Instance of MaterialCollection
        Collection<Material,MaterialIndex> collection; // Collection object
};

#endif // MATERIALCOLLECTION_H
