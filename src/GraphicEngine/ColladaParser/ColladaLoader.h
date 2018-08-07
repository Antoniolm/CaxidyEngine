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

#ifndef COLLADALOADER_H
#define COLLADALOADER_H

#include "GL/glew.h"
#include "matrix/matrix4f.h"
#include <string>
#include "rapidxml/rapidxml.hpp"
#include "SkinLoader.h"
#include "SkeletonLoader.h"
#include "GeometryLoader.h"
#include "AnimationLoader.h"
#include "ColladaData.h"

#include "XmlParserUtils.h"

using namespace rapidxml;
using namespace std;

class ColladaLoader
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ColladaLoader(std::string file_name);

    protected:

    private:
        AnimatedModelData model_data_;
        AnimationData animation_data_;

};

#endif // COLLADALOADER_H