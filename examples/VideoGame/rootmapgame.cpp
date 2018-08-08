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

#include "rootmapgame.h"
#include "CaxidyEngine/mesh/objectgroup.h"
#include "enemylist.h"

RootMapGame::RootMapGame()
{
    //ctor
}

//**********************************************************************//

RootMapGame::RootMapGame(string fileMap,bool flagThread){
    loading=true;
    hero=0;
    if(flagThread){
        loader=new LoaderThread(this,fileMap);
        loader->run();
    }
    else initialize(fileMap);
}

//**********************************************************************//

RootMapGame::~RootMapGame()
{
    //dtor
}

//**********************************************************************//

void RootMapGame::initialize(string fileMap){
    cout<< "< Game is loading our current map >"<< endl;

    //Open file
    FILE * fp = fopen(fileMap.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);
    fclose(fp);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    //Take the file of our next map
    nextMapFile=document["nextMap"].GetString();

    /////////////////////////////////////////
    // Create hero and mate
    /////////////////////////////////////////
    vec3f positionHero=vec3f(document["heroPosition"][0].GetFloat(),document["heroPosition"][1].GetFloat(),document["heroPosition"][2].GetFloat());

    //Print a message for check
    cout<< "< Game is loading our hero >"<< endl;
    hero=new Hero(document["hero"]);
    elements.push_back(hero);

    /////////////////////////////////////////
    // Add Light to our map
    /////////////////////////////////////////
    //Print a message for check
    cout<< "< Game is loading light >"<< endl;
    const rapidjson::Value & lightFeature=document["light"];
    for(unsigned currentLight=0;currentLight<lightFeature.Size();currentLight++){
        //Create our light
        if(lightFeature[currentLight]["type"].GetFloat()==0)
            lights.push_back(new DirectionalLight(lightFeature[currentLight]));
        else
            lights.push_back(new PointLight(lightFeature[currentLight]));


    }

    /////////////////////////////////////////
    // Add movie to our map
    /////////////////////////////////////////
    cout<< "< Game is loading movie>"<< endl;
    const rapidjson::Value & movieFeature=document["movie"];
    movie=new MovieScreen(movieFeature);

    /////////////////////////////////////////
    // Add title to our map
    /////////////////////////////////////////
    cout<< "< Game is loading title >"<< endl;
    const rapidjson::Value & titleFeature=document["title"];
    title=new Notification(titleFeature);
    title->addLink();


    /////////////////////////////////////////
    // Add npcs of our map
    /////////////////////////////////////////
    cout<< "< Game is loading npcs >"<< endl;
    const rapidjson::Value & npcValue=document["npcs"];
    for(unsigned currentNpc=0;currentNpc<npcValue.Size();currentNpc++){
        elements.push_back(new Npc(npcValue[currentNpc]));
    }


    /////////////////////////////////////////
    // Add endMap region to our map
    /////////////////////////////////////////
    cout<< "< Game is loading end map region >"<< endl;
    const rapidjson::Value & endRegionFeature=document["endMapRegion"];
    endMapRegion=new EndMapRegion(endRegionFeature);

    /////////////////////////////////////////
    // Add particleSystems to our map
    /////////////////////////////////////////
    cout<< "< Game is loading particles system >"<< endl;
    const rapidjson::Value & particleFeature=document["particleSystem"];
    for(unsigned currentPSys=0;currentPSys<particleFeature.Size();currentPSys++){
        elements.push_back(new ParticleSystem(particleFeature[currentPSys]));
    }

    /////////////////////////////////////////
    // Add projectileSystem to our map
    /////////////////////////////////////////
    cout<< "< Game is loading proyectile system >"<< endl;
    const rapidjson::Value & projectileFeature=document["projectileSystem"];
    for(unsigned currentPSys=0;currentPSys<projectileFeature.Size();currentPSys++){
        elements.push_back(new ProjectileSystem(projectileFeature[currentPSys]));
    }

    /////////////////////////////////////////
    // Add text region to our map
    /////////////////////////////////////////
    cout<< "< Game is loading text region>"<< endl;
    const rapidjson::Value & regionFeature=document["textRegion"];
    for(unsigned currentRegion=0;currentRegion<regionFeature.Size();currentRegion++){
        regions.push_back(new TextRegion(regionFeature[currentRegion]));
    }

    /////////////////////////////////////////
    // Add soulCarriers to our map
    /////////////////////////////////////////
    cout<< "< Game is loading soul carriers >"<< endl;
    vector<SoulCarrier *> soulCarriers; // Vector of souls carriers
    const rapidjson::Value & soulCarrierFeature=document["soulCarrier"];
    for(unsigned currentSoulC=0;currentSoulC<soulCarrierFeature.Size();currentSoulC++){
        SoulCarrier * soulC=new SoulCarrier(soulCarrierFeature[currentSoulC]);
        soulCarriers.push_back(soulC);
        elements.push_back(soulC);
    }

    /////////////////////////////////////////
    // Add souls to our map
    /////////////////////////////////////////
    cout<< "< Game is loading souls >"<< endl;
    const rapidjson::Value & soulFeature=document["souls"];
    for(unsigned currentSoul=0;currentSoul<soulFeature.Size();currentSoul++){
        elements.push_back(new Soul(soulFeature[currentSoul]));
    }

    /////////////////////////////////////////
    // Add doors to our map
    /////////////////////////////////////////
    cout<< "< Game is loading doors >"<< endl;
    const rapidjson::Value & doorFeature=document["door"];
    for(unsigned currentDoor=0;currentDoor<doorFeature.Size();currentDoor++){
        Door * door=new Door(doorFeature[currentDoor],soulCarriers,currentDoor);
        door->addLink();door->addLink();door->addLink();
        elements.push_back(door);
        objs.push_back(door);
    }
    soulCarriers.clear();

    /////////////////////////////////////////
    // Add spikes to our map
    /////////////////////////////////////////
    cout<< "< Game is loading spike traps >"<< endl;
    const rapidjson::Value & spikeFeature=document["spikes"];
    for(unsigned currentSpike=0;currentSpike<spikeFeature.Size();currentSpike++){
        elements.push_back(new SpikeTrap(spikeFeature[currentSpike]));
    }

    /////////////////////////////////////////
    // Add traps door to our map
    /////////////////////////////////////////
    cout<< "< Game is loading traps door >"<< endl;
    const rapidjson::Value & trapFeature=document["trapDoor"];
    for(unsigned currentTrap=0;currentTrap<trapFeature.Size();currentTrap++){
        TrapDoor * trapDoor=new TrapDoor(trapFeature[currentTrap],objs.size());
        trapDoor->addLink();trapDoor->addLink();
        elements.push_back(trapDoor);
        objs.push_back(trapDoor);
    }

    /////////////////////////////////////////
    // Add rotten voxel to our map
    /////////////////////////////////////////
    cout<< "< Game is loading rotten voxel >"<< endl;
    const rapidjson::Value & rottenFeature=document["rottVoxel"];
    for(unsigned currentRot=0;currentRot<rottenFeature.Size();currentRot++){
        RottenVoxel * rotten=new RottenVoxel(rottenFeature[currentRot],objs.size());
        rotten->addLink();rotten->addLink();
        elements.push_back(rotten);
        objs.push_back(rotten);
    }

    /////////////////////////////////////////
    // Add respawn voxels to the map
    /////////////////////////////////////////
    cout<< "< Game is loading respawn voxels >"<< endl;
    vector<RespawnVoxel *> respawns; // Vector of respawn voxels
    const rapidjson::Value & resFeature=document["resVoxel"];
    for(unsigned currentRes=0;currentRes<resFeature.Size();currentRes++){
        RespawnVoxel * respVox=new RespawnVoxelGame(resFeature[currentRes]);
        respawns.push_back(respVox);
        elements.push_back(respVox);
    }

    /////////////////////////////////////////
    // Add movable voxels to our map
    /////////////////////////////////////////
    cout<< "< Game is loading movable voxels >"<< endl;
    const rapidjson::Value & movFeature=document["movVoxel"];
    for(unsigned currentMov=0;currentMov<movFeature.Size();currentMov++){
        MovableVoxel * movVox=new MovableVoxelGame(movFeature[currentMov],respawns,objs.size());
        movVox->addLink();movVox->addLink();
        elements.push_back(movVox);
        objs.push_back(movVox);
    }
    respawns.clear();

    /////////////////////////////////////////
    // Add slide traps to our map
    /////////////////////////////////////////
    cout<< "< Game is loading slide traps >"<< endl;
    const rapidjson::Value & slideFeature=document["slideTrap"];
    for(unsigned currentSlide=0;currentSlide<slideFeature.Size();currentSlide++){
        SlideTrap * slidTrap=new SlideTrap(slideFeature[currentSlide],objs.size());
        slidTrap->addLink();slidTrap->addLink();
        elements.push_back(slidTrap);
        objs.push_back(slidTrap);
    }

    /////////////////////////////////////////
    // Add jump button to our map
    /////////////////////////////////////////
    cout<< "< Game is loading jump button >"<< endl;
    const rapidjson::Value & jumpFeature=document["jumpButton"];
    for(unsigned currentButton=0;currentButton<jumpFeature.Size();currentButton++){
        elements.push_back(new JumpButtonGame(jumpFeature[currentButton]));
    }

    /////////////////////////////////////////
    // Add potion to our map
    /////////////////////////////////////////
    cout<< "< Game is loading potions >"<< endl;
    const rapidjson::Value & potionFeature=document["potion"];
    for(unsigned currentPotion=0;currentPotion<potionFeature.Size();currentPotion++){
        elements.push_back(new Potion(potionFeature[currentPotion]));
    }

    /////////////////////////////////////////
    // Add coin to our map
    /////////////////////////////////////////
    cout<< "< Game is loading coins >"<< endl;
    const rapidjson::Value & coinFeature=document["coin"];
    for(unsigned currentCoin=0;currentCoin<coinFeature.Size();currentCoin++){
        elements.push_back(new Coin(coinFeature[currentCoin]));
    }

    /////////////////////////////////////////
    // Add equipment to our map
    /////////////////////////////////////////
    cout<< "< Game is loading equipments >"<< endl;
    const rapidjson::Value & equipFeature=document["equip"];
    for(unsigned currentEquip=0;currentEquip<equipFeature.Size();currentEquip++){
        elements.push_back(new Equipment(equipFeature[currentEquip]));
    }

    /////////////////////////////////////////
    // Add voxelGroup to our map
    /////////////////////////////////////////
    cout<< "< Game is loading the scene >"<< endl;
    const rapidjson::Value & voxelGroup=document["voxelGroup"];

    for(unsigned currentGroup=0;currentGroup<voxelGroup.Size();currentGroup++){
        new VoxelGroup(voxelGroup[currentGroup],objs);
    }

    /////////////////////////////////////////
    // Add decorationObject to our map
    /////////////////////////////////////////
    cout<< "< Game is loading decoration objects >"<< endl;
    const rapidjson::Value & decoObject=document["decorationObject"];
    vec3f posDecoration;
    for(unsigned currentDeco=0;currentDeco<decoObject.Size();currentDeco++){

        for(unsigned i=0;i<decoObject[currentDeco]["position"].Size();i+=3){
            posDecoration=vec3f(decoObject[currentDeco]["position"][i].GetFloat(),
                                decoObject[currentDeco]["position"][i+1].GetFloat(),
                                decoObject[currentDeco]["position"][i+2].GetFloat());

            if(decoObject[currentDeco]["collision"].GetBool()) //If collision
                objs.push_back(new DecorationObject(decoObject[currentDeco],posDecoration));

            decorationObjs.push_back(new DecorationObject(decoObject[currentDeco],posDecoration));

        }
    }

    /////////////////////////////////////////
    // Add mate to our map
    /////////////////////////////////////////
    cout<< "< Game is loading our mate >"<< endl;
    mate=new Mate(document["mate"]);
    elements.push_back(mate);

    ////////////////////////////////////////////
    // Background
    Matrix4f * transObj=new Matrix4f();
    transObj->translation(document["bkgdPosition"][0].GetFloat(),document["bkgdPosition"][1].GetFloat(),document["bkgdPosition"][2].GetFloat());

    Matrix4f *scaleBack =new Matrix4f();
    scaleBack->scale(10.0,5.0,10.0);

    NodeSceneGraph * objNode=new NodeSceneGraph();
    objNode->add(transObj);
    objNode->add(scaleBack);
    objNode->add(materialCollect->getMaterial(document["bkgdMaterial"].GetString()));
    objNode->add(meshCollect->getMesh(BACKGROUND));
    background= new ObjectScene(objNode);

    /////////////////////////////////////////
    // Add enemy of our map
    cout<< "< Game is loading enemies >"<< endl;
    const rapidjson::Value & enemies=document["enemies"];

    enemyList=new EnemyList(enemies);
    elements.push_back(enemyList);

    ////////////////////////////////////////
    //Create the indexMap;
    Context cv;
    objectGroup.push_back(new ObjectGroup(mCUBE_DUNG));
    objectGroup.push_back(new ObjectGroup(mCUBE_WALL));
    objectGroup.push_back(new ObjectGroup(mCUBE_DUNGB));
    objectGroup.push_back(new ObjectGroup(mCUBE_TRAP));
    objectGroup.push_back(new ObjectGroup(mCUBE_SPIKE));

    for(unsigned i=0;i<objs.size();i++){
        objs[i]->obtainPosition(cv);
        switch(objs[i]->getMaterialIndex()){
            case mCUBE_DUNG:
                objectGroup[0]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_WALL:
                objectGroup[1]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_DUNGB:
                objectGroup[2]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_TRAP:
                objectGroup[3]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_SPIKE:
                objectGroup[4]->addObject(objs[i]->getPosition(),CUBE);
            break;
            default:
            break;
        }
    }

    for(unsigned i=0;i<decorationObjs.size();i++){
        decorationObjs[i]->obtainPosition(cv);
    }

    vec3f pos;
    BoundingBox bounding;

    //Create our indexMap for our collision system
    for(unsigned i=0;i<objs.size();i++){
        pos=objs[i]->getPosition();
        bounding=objs[i]->getBoundingBox();
        bounding.minValue.z+=0.1;
        bounding.minValue.x-=0.1;

        for(int x=bounding.minValue.x;x<bounding.maxValue.x;x++){
            for(int z=bounding.minValue.z;z<bounding.maxValue.z;z++){
                indexMap[(int)(pos.x+x)][(int)((pos.z+z)*(-1))].push_back(i);
            }
        }
    }
    /////////////////////////////////////////
    // Add sound of our map
    backSound=new Music(document["sound"].GetString(),document["volSound"].GetFloat());

    SDL_Delay(2000);

    currentTime=SDL_GetTicks();

    loading=false;
}

//**********************************************************************//

Hero * RootMapGame::getHero(){
    return hero;
}

//**********************************************************************//

Mate * RootMapGame::getMate(){
    return mate;
}
//**********************************************************************//

EnemyList * RootMapGame::getEnemyList(){
    return enemyList;
}

//**********************************************************************//

void RootMapGame::enableSound(bool value){
    if(value){
            backSound->play();
    }
    else{
        if(backSound->isPlaying())
            backSound->stop();
    }
    hero->enableSound(value);
}
