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

#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include "matrix/matrix4f.h"
#include <string>
#include "ColladaData.h"
#include "rapidxml/rapidxml.hpp"

#include "XmlParserUtils.h"

using namespace rapidxml;
using namespace std;

class AnimationLoader
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        AnimationLoader(xml_node<> & animation_node, xml_node<> & joint_node);

    protected:

    private:
        xml_node<> *  meshData;

        Matrix4f current_matrix_; // Matrix 4x4
        XmlParserUtils xml_parser;

        vector<VertexSkinData> vertex_weights_;
};

#endif // ANIMATIONLOADER_H