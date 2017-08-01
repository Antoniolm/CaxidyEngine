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

#include "materialcollection.h"
#include "material/material.h"

MaterialCollection* MaterialCollection::instance = NULL;

MaterialCollection::MaterialCollection()
{
    cout<< "Game is loading -> materials"<< endl;
    collection.addElement(new Material(vec3f(1.5f, 1.5f, 1.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeDungeon.png","./textures/cubeDungeonBump.png",mCUBE_DUNG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeDungeonB.png","",mCUBE_DUNGB));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeWall.png","./textures/cubeWallBump.png",mCUBE_WALL));

    collection.addElement(new Material(vec3f(0.7f, 0.7f, 0.7f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/invisiblecubeWall.png","",mINVICUBE_WALL));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeTrap.png","./textures/cubeTrapBump.png",mCUBE_TRAP));

    collection.addElement(new Material(vec3f(1.5f, 1.5f, 1.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeDungeonTrap.png","./textures/cubeDungeonTrapBump.png",mCUBE_SPIKE));

    collection.addElement(new Material(vec3f(0.5f, 1.0f, 0.5f),vec3f(0.5f, 1.0f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/water.png","",mDWATER));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/void.png","",mVOID));

    collection.addElement(new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/TEX_crystal.png","",mCRYSTAL));

    //Hero material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),16.0f,"./textures/heroTexture.jpg","./textures/heroTextureBump.jpg",mHERO));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/swordTexture.png","",mSWORD));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/shieldTexture.png","",mSHIELD));

    //Enemy material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/enemyTexture.png","./textures/enemyTextureBump.png",mENEMY));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/archerTexture.png","./textures/archerTextureBump.png",mARCHENEMY));

    //Text Material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/dialog.png","",mDIALOG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/dialogN.png","",mBDIALOG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/actionDialog.png","",mADIALOG));

    //NPC
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/butlerTexture.png","",mBUTLER));

    //Scene Material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/furnitureText.png","",mFURNITURE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/rugTexture.png","",mRUG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/fireTexture.png","",mFIRE));

    collection.addElement(new Material(vec3f(0.8f, 0.8f, 0.8f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"textures/windowTex.png","",mWINDOW));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"textures/pillar.png","",mPILLAR));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"textures/bedTexture.png","",mBED));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/torch.png","",mTORCH));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/chandelier.png","",mCHANDELIER));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/flag.png","",mFLAG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/column.png","textures/columnBump.png",mCOLUMN));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/potionTexture.png","",mPOTION));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/mateTexture.png","",mMATE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/chairTexture.png","",mCHAIR));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/tableTexture.png","./textures/tableTextureBump.png",mWOOD));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/bookTexture.png","",mBOOKS));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/trunkTexture.png","",mTRUNK));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/spikeTexture.png","",mSPIKE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/gamepadV.png","",mGMPADV));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/gamepadX.png","",mGMPADX));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/title1.png","",mTITLE1));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/potTexture.png","",mPOT));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/doorTexture.png","",mDOOR));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/glyphTexture.png","",mGLYPH));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/soulTexture.png","",mSOUL));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/lifeBar0.png","",mLIFE0));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/lifeBar25.png","",mLIFE25));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/lifeBar50.png","",mLIFE50));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/lifeBar75.png","",mLIFE75));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/lifeBar100.png","",mLIFE100));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/crystal.png","",mCRYSDRAW));

    //Create our map
    collection.addIndex("mCUBE_DUNG",mCUBE_DUNG);
    collection.addIndex("mCUBE_DUNGB",mCUBE_DUNGB);
    collection.addIndex("mCUBE_WALL",mCUBE_WALL);
    collection.addIndex("mINVICUBE_WALL",mINVICUBE_WALL);
    collection.addIndex("mCUBE_TRAP",mCUBE_TRAP);
    collection.addIndex("mCUBE_SPIKE",mCUBE_SPIKE);
    collection.addIndex("mDWATER",mDWATER);
    collection.addIndex("mVOID",mVOID);
    collection.addIndex("mCRYSTAL",mCRYSTAL);
    collection.addIndex("mHERO",mHERO);
    collection.addIndex("mSWORD",mSWORD);
    collection.addIndex("mSHIELD",mSHIELD);
    collection.addIndex("mENEMY",mENEMY);
    collection.addIndex("mARCHENEMY",mARCHENEMY);
    collection.addIndex("mDIALOG",mDIALOG);
    collection.addIndex("mBDIALOG",mBDIALOG);
    collection.addIndex("mADIALOG",mADIALOG);
    collection.addIndex("mBUTLER",mBUTLER);
    collection.addIndex("mFURNITURE",mFURNITURE);
    collection.addIndex("mRUG",mRUG);
    collection.addIndex("mFIRE",mFIRE);
    collection.addIndex("mWINDOW",mWINDOW);
    collection.addIndex("mPILLAR",mPILLAR);
    collection.addIndex("mBED",mBED);
    collection.addIndex("mTORCH",mTORCH);
    collection.addIndex("mCHANDELIER",mCHANDELIER);
    collection.addIndex("mFLAG",mFLAG);
    collection.addIndex("mCOLUMN",mCOLUMN);
    collection.addIndex("mPOTION",mPOTION);
    collection.addIndex("mMATE",mMATE);
    collection.addIndex("mCHAIR",mCHAIR);
    collection.addIndex("mWOOD",mWOOD);
    collection.addIndex("mBOOKS",mBOOKS);
    collection.addIndex("mTRUNK",mTRUNK);
    collection.addIndex("mSPIKE",mSPIKE);
    collection.addIndex("mGMPADV",mGMPADV);
    collection.addIndex("mGMPADX",mGMPADX);
    collection.addIndex("mTITLE1",mTITLE1);
    collection.addIndex("mPOT",mPOT);
    collection.addIndex("mDOOR",mDOOR);
    collection.addIndex("mGLYPH",mGLYPH);
    collection.addIndex("mSOUL",mSOUL);
    collection.addIndex("mLIFE0",mLIFE0);
    collection.addIndex("mLIFE25",mLIFE25);
    collection.addIndex("mLIFE50",mLIFE50);
    collection.addIndex("mLIFE75",mLIFE75);
    collection.addIndex("mLIFE100",mLIFE100);
    collection.addIndex("mCRYSDRAW",mCRYSDRAW);

}

//**********************************************************************//

MaterialCollection::~MaterialCollection()
{
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(MaterialIndex element){
    return collection.getElement(element);
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(string element){
    return collection.getElement(element);
}
