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

#ifndef VOXELGROUP_H
#define VOXELGROUP_H

#include "objectscene.h"
#include "../../lib/rapidjson/document.h"
#include "nodescenegraph.h"
#include "object3d.h"
#include "matrix/matrix4f.h"
#include "collection/materialcollection.h"
#include "collection/meshcollection.h"

class VoxelGroup : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        VoxelGroup();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor json */
        //////////////////////////////////////////////////////////////////////////
        VoxelGroup(const rapidjson::Value & voxelGFeature,vector<ObjectScene *> & objs);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~VoxelGroup();

    protected:

    private:
};

#endif // VOXELGROUP_H
