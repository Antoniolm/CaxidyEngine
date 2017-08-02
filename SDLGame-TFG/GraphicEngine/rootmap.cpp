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

#include "rootmap.h"
#include "../VideoGame/enemylist.h"
#include "../VideoGame/itemlist.h"
#include "mesh/objectgroup.h"
#include <stdlib.h>     /* srand, rand */

RootMap::RootMap(){
}

//**********************************************************************//

RootMap::RootMap(string fileMap,bool flagThread){
    RootMap::loading=true;
    hero=0;
    if(flagThread){
        loader=new LoaderThread(this,fileMap);
        loader->run();
    }
    else initialize(fileMap);
}

//**********************************************************************//

RootMap::~RootMap()
{
    delete loader;
    delete backSound;
    delete enemyList;
    delete itemList;
    delete hero;
    delete mate;
    delete title;
    delete endMapRegion;
    delete movie;

    for(unsigned i=doors.size()+traps.size()+rottens.size();i<objs.size();i++)
        deleteObject3d(objs[i]);

    for(unsigned i=0;i<decorationObjs.size();i++)
        delete decorationObjs[i];

    for(unsigned i=0;i<objectGroup.size();i++)
        delete objectGroup[i];

    for(unsigned i=0;i<npcList.size();i++)
        delete npcList[i];

    for(unsigned i=0;i<particleSystem.size();i++)
        delete particleSystem[i];

    for(unsigned i=0;i<projectileSystem.size();i++)
        delete projectileSystem[i];

   for(unsigned i=0;i<regions.size();i++)
        delete regions[i];

    for(unsigned i=0;i<spikes.size();i++)
        delete spikes[i];

    for(unsigned i=0;i<souls.size();i++)
        delete souls[i];

    for(unsigned i=0;i<soulCarriers.size();i++)
        delete soulCarriers[i];

    for(unsigned i=0;i<doors.size();i++)
        deleteObject3d(doors[i]);

    for(unsigned i=0;i<traps.size();i++)
        deleteObject3d(traps[i]);

    for(unsigned i=0;i<rottens.size();i++)
        deleteObject3d(rottens[i]);

    for(unsigned i=0;i<lights.size();i++)
        delete lights[i];

}

//**********************************************************************//

void RootMap::initialize(string fileMap){
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
    hero=new Hero(positionHero);

    //Print a message for check
    cout<< "< Game is loading our mate >"<< endl;
    mate=new Mate(positionHero);

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
        particleSystem.push_back(new ParticleSystem(particleFeature[currentPSys]));
    }

    /////////////////////////////////////////
    // Add projectileSystem to our map
    /////////////////////////////////////////
    cout<< "< Game is loading proyectile system >"<< endl;
    const rapidjson::Value & projectileFeature=document["projectileSystem"];
    for(unsigned currentPSys=0;currentPSys<projectileFeature.Size();currentPSys++){
        projectileSystem.push_back(new ProjectileSystem(projectileFeature[currentPSys]));
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
    // Add souls to our map
    /////////////////////////////////////////
    cout<< "< Game is loading souls >"<< endl;
    const rapidjson::Value & soulFeature=document["souls"];
    for(unsigned currentSoul=0;currentSoul<soulFeature.Size();currentSoul++){
        souls.push_back(new Soul(soulFeature[currentSoul]));
    }

    /////////////////////////////////////////
    // Add soulCarriers to our map
    /////////////////////////////////////////
    cout<< "< Game is loading soul carriers >"<< endl;
    const rapidjson::Value & soulCarrierFeature=document["soulCarrier"];
    for(unsigned currentSoulC=0;currentSoulC<soulCarrierFeature.Size();currentSoulC++){
        soulCarriers.push_back(new SoulCarrier(soulCarrierFeature[currentSoulC]));
    }

    /////////////////////////////////////////
    // Add doors to our map
    /////////////////////////////////////////
    cout<< "< Game is loading doors >"<< endl;
    const rapidjson::Value & doorFeature=document["door"];
    for(unsigned currentDoor=0;currentDoor<doorFeature.Size();currentDoor++){
        Door * door=new Door(doorFeature[currentDoor],soulCarriers,currentDoor);
        door->addLink();door->addLink();
        doors.push_back(door);
        objs.push_back(door);
    }

    /////////////////////////////////////////
    // Add spikes to our map
    /////////////////////////////////////////
    cout<< "< Game is loading spike traps >"<< endl;
    const rapidjson::Value & spikeFeature=document["spikes"];
    for(unsigned currentSpike=0;currentSpike<spikeFeature.Size();currentSpike++){
        spikes.push_back(new SpikeTrap(spikeFeature[currentSpike]));
    }

    /////////////////////////////////////////
    // Add traps door to our map
    /////////////////////////////////////////
    cout<< "< Game is loading traps door >"<< endl;
    const rapidjson::Value & trapFeature=document["trapDoor"];
    for(unsigned currentTrap=0;currentTrap<trapFeature.Size();currentTrap++){
        TrapDoor * trapDoor=new TrapDoor(trapFeature[currentTrap],objs.size()+currentTrap);
        trapDoor->addLink();trapDoor->addLink();
        traps.push_back(trapDoor);
        objs.push_back(trapDoor);
    }

    /////////////////////////////////////////
    // Add rotten voxel to our map
    /////////////////////////////////////////
    cout<< "< Game is loading rotten voxel >"<< endl;
    const rapidjson::Value & rottenFeature=document["rottVoxel"];
    for(unsigned currentRot=0;currentRot<rottenFeature.Size();currentRot++){
        RottenVoxel * rotten=new RottenVoxel(rottenFeature[currentRot],objs.size()+traps.size()+currentRot);
        rotten->addLink();rotten->addLink();
        rottens.push_back(rotten);
        objs.push_back(rotten);
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
    // Add coins to our map
    /////////////////////////////////////////
    cout<< "< Game is loading items>"<< endl;
    const rapidjson::Value & coinValue=document["items"];
    itemList=new ItemList(coinValue);


    /////////////////////////////////////////
    // Add npcs of our map
    /////////////////////////////////////////
    cout<< "< Game is loading npcs >"<< endl;
    const rapidjson::Value & npcValue=document["npcs"];
    for(unsigned currentNpc=0;currentNpc<npcValue.Size();currentNpc++){
        npcList.push_back(new Npc(npcValue[currentNpc]));
    }

    /////////////////////////////////////////
    // Add enemy of our map
    cout<< "< Game is loading enemies >"<< endl;
    const rapidjson::Value & enemies=document["enemies"];

    enemyList=new EnemyList(enemies);

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

void RootMap::setHero(Hero * theHero){
    hero=theHero;
}

//**********************************************************************//

Hero * RootMap::getHero(){
    return hero;
}

//**********************************************************************//

Mate * RootMap::getMate(){
    return mate;
}
//**********************************************************************//

EnemyList * RootMap::getEnemyList(){
    return enemyList;
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    vec3f position,posHero=hero->getPosition();
    //Draw background
    background->visualization(cv);

    //Draw object groups
    for(unsigned i=0;i<objectGroup.size();i++){
        objectGroup[i]->visualization(cv);
    }

    //Draw hero
    hero->visualization(cv);

    //Draw ncps
    for(unsigned i=0;i<npcList.size();i++)
        npcList[i]->visualization(cv);

    //Draw enemies
    enemyList->visualization(cv);

    //Draw items
    itemList->visualization(cv);

    //Draw particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        position=vec3f(particleSystem[i]->getPosition());
        if(position.x>posHero.x-8 && position.x<posHero.x+8)
            particleSystem[i]->visualization(cv);
    }

    //Draw projectile system
    for(unsigned i=0;i<projectileSystem.size();i++){
        projectileSystem[i]->visualization(cv);
    }

    //Draw souls
    for(unsigned i=0;i<souls.size();i++){
        souls[i]->visualization(cv);
    }

    //Draw soulCarriers
    for(unsigned i=0;i<soulCarriers.size();i++){
        soulCarriers[i]->visualization(cv);
    }

    //Draw doors
    for(unsigned i=0;i<doors.size();i++){
        doors[i]->visualization(cv);
    }

    //Draw spiketrap
    for(unsigned i=0;i<spikes.size();i++){
        spikes[i]->visualization(cv);
    }

    //Draw traps
    for(unsigned i=0;i<traps.size();i++){
        traps[i]->visualization(cv);
    }

    //Draw rotten
    for(unsigned i=0;i<rottens.size();i++){
        rottens[i]->visualization(cv);
    }

    //Draw decoration object
    for(unsigned i=0;i<decorationObjs.size();i++){
        position=decorationObjs[i]->getPosition();
        if(position.x>posHero.x-11 && position.x<posHero.x+11)
            decorationObjs[i]->visualization(cv);
    }

    //Draw mate
    mate->visualization(cv);

    //Draw title
    title->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    if(!gameState.movie->isActivated() && !gameState.mainMenu->isActivate() && !gameState.pauseMenu->isActivate()
       && !gameState.deadMenu->isActivate() && !gameState.camera->isViewMode()){
        //Update the hero
        hero->updateState(gameState);

        //Update the mate
        mate->updateState(gameState);

        //Update the Scene
        for(unsigned i=0;i<objectGroup.size();i++)
            objectGroup[i]->updateState(gameState);
        //Update the Scene
        itemList->updateState(gameState);

        //Update particles system
        for(unsigned i=0;i<particleSystem.size();i++){
            particleSystem[i]->updateState(gameState);
        }

        //Update projectile system
        for(unsigned i=0;i<projectileSystem.size();i++){
            projectileSystem[i]->updateState(gameState);
        }

        //Update textregions
        for(unsigned i=0;i<regions.size();i++){
            regions[i]->updateState(gameState);
        }

        //Update soulCarriers
        for(unsigned i=0;i<soulCarriers.size();i++){
            soulCarriers[i]->updateState(gameState);
        }

        //Update doors
        for(unsigned i=0;i<doors.size();i++){
            doors[i]->updateState(gameState);
        }

        //Update souls
        for(unsigned i=0;i<souls.size();i++){
            souls[i]->updateState(gameState);
        }

        //Update spikeTraps
        for(unsigned i=0;i<spikes.size();i++){
            spikes[i]->updateState(gameState);
        }

        //Update spikeTraps
        for(unsigned i=0;i<traps.size();i++){
            traps[i]->updateState(gameState);
        }

        //Update rotten voxel
        for(unsigned i=0;i<rottens.size();i++){
            rottens[i]->updateState(gameState);
        }

        //Update title
        title->updateState(gameState);

        //Update npcs
        for(unsigned i=0;i<npcList.size();i++){
            npcList[i]->updateState(gameState);
        }

        //Update enemies
        enemyList->updateState(gameState);

        //Update endMapRegion
        endMapRegion->updateState(gameState);

        currentTime+=time-currentTime;
        gameState.rootMap->enableSound(true);
    }
    else{
        if(gameState.pauseMenu->isActivate() || gameState.deadMenu->isActivate())
            gameState.rootMap->enableSound(false);
    }
}

//**********************************************************************//

void RootMap::enableSound(bool value){
    if(value){
            backSound->play();
    }
    else{
        if(backSound->isPlaying())
            backSound->stop();
    }
    hero->enableSound(value);
}

//**********************************************************************//

ObjectScene * RootMap::collision(const vec3f & indexObj){
    bool hasCollision=false;
    ObjectScene * result=0;
    vec3f pos;
    BoundingBox box;
    int tam=indexMap[(int)indexObj.x][(int)indexObj.z*-1].size();

    vector<int>::iterator it=indexMap[(int)indexObj.x][(int)indexObj.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)indexObj.x][(int)indexObj.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt && !hasCollision;it++){ //if There are object in that position (x,z)
            pos=objs[(*it)]->getPosition();
            box=objs[(*it)]->getBoundingBox();
            if((indexObj.y >= (pos.y)+box.minValue.y && indexObj.y <= (pos.y)+box.maxValue.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;
}

//**********************************************************************//

ObjectScene * RootMap::collision(const vec3f & posFirst, const vec3f & posSecond){
    bool hasCollision=false;
    ObjectScene * result=0;
    vec3f pos;
    BoundingBox box;
    int tam=indexMap[(int)posFirst.x][(int)posFirst.z*-1].size();

    vector<int>::iterator it=indexMap[(int)posFirst.x][(int)posFirst.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)posFirst.x][(int)posFirst.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt && !hasCollision;it++){ //if There are object in that position (x,z)
            pos=objs[(*it)]->getPosition();
            box=objs[(*it)]->getBoundingBox();
            if((posFirst.y <= pos.y && posSecond.y >= pos.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;

}

//**********************************************************************//

void RootMap::addCollision(vec2f voxelPosition,int objID){

    //Create our indexMap for our collision system
    vec3f pos=objs[objID]->getPosition();
    BoundingBox bounding=objs[objID]->getBoundingBox();
    bounding.minValue.z+=0.1;
    bounding.minValue.x-=0.1;

    for(int x=bounding.minValue.x;x<bounding.maxValue.x;x++){
        for(int z=bounding.minValue.z;z<bounding.maxValue.z;z++){
            indexMap[(int)(pos.x+x)][(int)((pos.z+z)*(-1))].push_back(objID);
        }
    }
}

//**********************************************************************//

void RootMap::removeCollision(vec2f voxelPosition,int objID){
    int tam=indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].size();
    bool deleted=false;

    vector<int>::iterator it=indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].end();

    if(tam!=0 ){
        while(it!=endIt && !deleted){ //if There are object in that position (x,z)
            if((*it)==objID){
                indexMap[(int)voxelPosition.x][(int)voxelPosition.y*-1].erase(it);
                deleted=true;
            }
            else
                it++;
        }
    }
}

//**********************************************************************//

bool RootMap::isLoading(){
    return loading;
}

//**********************************************************************//

bool RootMap::isFinished(){
    bool result=endMapRegion->isActivated();
    if(result){
        enableSound(false);
    }

    return result;
}

//**********************************************************************//

string RootMap::getNextMap(){
    return nextMapFile;
}

//**********************************************************************//

MovieScreen * RootMap::getMovie(){
    return movie;
}

//**********************************************************************//

void RootMap::activatedLight(GLuint shaderID){
    glUniform1i(glGetUniformLocation(shaderID, "numActivateLight"), lights.size()-1);
    for(unsigned i=0;i<lights.size();i++)
        lights[i]->activate(shaderID);
}

//**********************************************************************//

void RootMap::activatedObjectGroup(){
    for(unsigned i=0;i<objectGroup.size();i++)
        objectGroup[i]->init();
}

//**********************************************************************//

void RootMap::deleteObject3d(Object3D * obj){
    obj->removeLink();
    if(obj->getCountLink()==0){
        delete obj; //testing
    }
}
