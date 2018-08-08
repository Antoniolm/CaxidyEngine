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

#include "materialcollection.h"
#include "material/material.h"

MaterialCollection* MaterialCollection::instance = NULL;

MaterialCollection::MaterialCollection()
{
    cout<< "Game is loading -> materials"<< endl;
    collection.addElement(new Material(vec3f(1.5f, 1.5f, 1.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeDungeon.png","resources/textures/cubeDungeonBump.png","",mCUBE_DUNG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeDungeonB.png","","",mCUBE_DUNGB));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/toy_box_diff.png","resources/textures/toy_box_normal.png","resources/textures/toy_box_disp.png",mCUBE_WALL));

    collection.addElement(new Material(vec3f(0.7f, 0.7f, 0.7f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/invisiblecubeWall.png","","",mINVICUBE_WALL));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeTrap.png","resources/textures/cubeTrapBump.png","",mCUBE_TRAP));

    collection.addElement(new Material(vec3f(1.5f, 1.5f, 1.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeDungeonTrap.png","resources/textures/cubeDungeonTrapBump.png","",mCUBE_SPIKE));

    collection.addElement(new Material(vec3f(4.0f, 4.0f, 4.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeLand.png","","",mCUBE_LAND));

    collection.addElement(new Material(vec3f(4.0f, 4.0f, 4.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeSteel.png","","",mCUBE_STEEL));

    collection.addElement(new Material(vec3f(3.0f, 3.0f, 3.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/cubeRock.png","","",mCUBE_ROCK));

    collection.addElement(new Material(vec3f(0.5f, 1.0f, 0.5f),vec3f(0.5f, 1.0f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/water.png","","",mDWATER));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/void.png","","",mVOID));

    collection.addElement(new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/TEX_crystal.png","","",mCRYSTAL));

    //Hero material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),16.0f,"resources/textures/heroTexture.jpg","resources/textures/heroTextureBump.jpg","",mHERO));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/swordTexture.png","","",mSWORD));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/shieldTexture.png","","",mSHIELD));

    //Enemy material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/enemyTexture.png","resources/textures/enemyTextureBump.png","",mENEMY));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/archerTexture.png","resources/textures/archerTextureBump.png","",mARCHENEMY));

    //Text Material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/dialog.png","","",mDIALOG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/dialogN.png","","",mBDIALOG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/actionDialog.png","","",mADIALOG));

    //NPC
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/butlerTexture.png","","",mBUTLER));

    //Scene Material
    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/furnitureText.png","","",mFURNITURE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/rugTexture.png","","",mRUG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/fireTexture.png","","",mFIRE));

    collection.addElement(new Material(vec3f(0.8f, 0.8f, 0.8f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"resources/textures/windowTex.png","","",mWINDOW));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"resources/textures/pillar.png","","",mPILLAR));

    collection.addElement(new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"resources/textures/bedTexture.png","","",mBED));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/torch.png","","",mTORCH));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/chandelier.png","","",mCHANDELIER));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/flag.png","","",mFLAG));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/column.png","resources/textures/columnBump.png","",mCOLUMN));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/potionTexture.png","","",mPOTION));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/mateTexture.png","","",mMATE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/chairTexture.png","","",mCHAIR));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/tableTexture.png","resources/textures/tableTextureBump.png","",mWOOD));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/bookTexture.png","","",mBOOKS));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/trunkTexture.png","","",mTRUNK));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/spikeTexture.png","","",mSPIKE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/gamepadV.png","","",mGMPADV));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/gamepadX.png","","",mGMPADX));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/title1.png","","",mTITLE1));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/potTexture.png","","",mPOT));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/doorTexture.png","","",mDOOR));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/glyphTexture.png","","",mGLYPH));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/soulTexture.png","","",mSOUL));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/lifeBar.png","","",mLIFEBAR));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/lifeBarBlack.png","","",mLIFE));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/barExp.png","","",mEXP));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/crystal.png","","",mCRYSDRAW));

    collection.addElement(new Material(vec3f(8.0f, 8.0f, 8.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/textureTrap.png","","",mTRAPDOOR));

    collection.addElement(new Material(vec3f(8.0f, 8.0f, 8.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/jumpTexture.png","","",mJUMP));

    collection.addElement(new Material(vec3f(8.0f, 8.0f, 8.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/buttonTexture.png","","",mBUTTON));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/speakModeTexture.png","","",mSPEAK));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/equipItem.png","","",mEQUIPPED));

    collection.addElement(new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"resources/textures/shieldProfile.png","","",mSHIELDPR));

    //Create our map
    collection.addIndex("mCUBE_DUNG",mCUBE_DUNG);
    collection.addIndex("mCUBE_DUNGB",mCUBE_DUNGB);
    collection.addIndex("mCUBE_WALL",mCUBE_WALL);
    collection.addIndex("mINVICUBE_WALL",mINVICUBE_WALL);
    collection.addIndex("mCUBE_TRAP",mCUBE_TRAP);
    collection.addIndex("mCUBE_SPIKE",mCUBE_SPIKE);
    collection.addIndex("mCUBE_LAND",mCUBE_LAND);
    collection.addIndex("mCUBE_STEEL",mCUBE_STEEL);
    collection.addIndex("mCUBE_ROCK",mCUBE_ROCK);
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
    collection.addIndex("mLIFEBAR",mLIFEBAR);
    collection.addIndex("mLIFE",mLIFE);
    collection.addIndex("mEXP,",mEXP);
    collection.addIndex("mCRYSDRAW",mCRYSDRAW);
    collection.addIndex("mTRAPDOOR",mTRAPDOOR);
    collection.addIndex("mJUMP",mJUMP);
    collection.addIndex("mBUTTON",mBUTTON);
    collection.addIndex("mSPEAK",mSPEAK);
    collection.addIndex("mEQUIPPED",mEQUIPPED);
    collection.addIndex("mSHIELDPR",mSHIELDPR);
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
