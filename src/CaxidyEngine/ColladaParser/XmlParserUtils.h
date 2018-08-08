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

#ifndef XMLPARSERUTILS_H
#define XMLPARSERUTILS_H

#include "rapidxml/rapidxml.hpp"
#include <string.h>
#include <sstream>
#include <vector>

namespace CaxidyEngine {

class XmlParserUtils{

public: 

rapidxml::xml_node<> * getChildWithAttribute(
    rapidxml::xml_node<> *parent, 
    const std::string & type, 
    const std::string & attribute, 
    const std::string & value);

std::vector<std::string> extract(const std::string& stoextract);

int indexOf(const std::vector<std::string> & elements, const std::string & value);

};

} // CaxidyEngine

#endif // XMLPARSERUTILS_H