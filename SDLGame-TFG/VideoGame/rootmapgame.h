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

#ifndef ROOTMAPGAME_H
#define ROOTMAPGAME_H

#include "../GraphicEngine/rootmap.h"
#include "avatar/npc.h"
#include "avatar/enemy.h"
#include "projectilesystem.h"
#include "soul.h"
#include "soulcarrier.h"
#include "door.h"
#include "spiketrap.h"
#include "trapdoor.h"
#include "rottenvoxel.h"
#include "movablevoxel.h"
#include "respawnvoxel.h"
#include "slidetrap.h"
#include "jumpbutton.h"
#include "item.h"
#include "potion.h"
#include "coin.h"

class ObjectGroup;
class Npc;
class ProjectileSystem;
class Soul;
class SoulCarrier;
class Door;
class SpikeTrap;
class TrapDoor;
class RottenVoxel;
class MovableVoxel;
class RespawnVoxel;
class SlideTrap;
class JumpButton;
class Item;
class Potion;
class Coin;

class RootMapGame : public RootMap
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        RootMapGame();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        RootMapGame(string fileMap,bool flagThread=false);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RootMapGame();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize our rootMap
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        virtual void initialize(string fileMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the hero of our game
        *    \return hero *
        */
        //////////////////////////////////////////////////////////////////////////
        Hero * getHero();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the mate of our game
        *    \return hero *
        */
        //////////////////////////////////////////////////////////////////////////
        Mate * getMate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the enemyList of our map
        *    \return EnemyList *
        */
        //////////////////////////////////////////////////////////////////////////
        EnemyList * getEnemyList();


    protected:

    private:
};

#endif // ROOTMAPGAME_H