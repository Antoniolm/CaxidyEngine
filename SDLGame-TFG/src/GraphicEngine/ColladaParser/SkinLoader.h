// *********************************************************************
// **
// ** Copyright (C) 2016-2018 Antonio David L�pez Machado
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

#ifndef SKINLOADER_H
#define SKINLOADER_H

#include "ColladaData.h"
#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class SkinLoader
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        SkinLoader(xml_node<> &library_controllers_node);

        SkinningData & extractSkinData();

    protected:

    private:
        SkinningData skinning_data_;
	    int maxWeights;
};

#endif // SKINLOADER_H
