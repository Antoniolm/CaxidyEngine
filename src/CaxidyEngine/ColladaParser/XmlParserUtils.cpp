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

#ifndef XMLPARSERUTILS_CPP
#define XMLPARSERUTILS_CPP

#include "XmlParserUtils.h"

namespace CaxidyEngine {

rapidxml::xml_node<> * XmlParserUtils::getChildWithAttribute(
    rapidxml::xml_node<> *parent, 
    const std::string & type, 
    const std::string & attribute, 
    const std::string & value)
{
    rapidxml::xml_node<> *node = parent->first_node( type.c_str());
    while (node)
    {
        rapidxml::xml_attribute<> *attr = node->first_attribute( attribute.c_str());
        if ( attr && value == attr->value()) return node;
        node = node->next_sibling( type.c_str());
    }
    return node;
}

std::vector<std::string> XmlParserUtils::extract(const std::string& stoextract) {
    std::vector<std::string> aListofWords;
    std::stringstream sstoext(stoextract);
    std::string sWordBuf;

    while (sstoext >> sWordBuf)
        aListofWords.push_back(sWordBuf);

    return aListofWords;
}

int XmlParserUtils::indexOf(const std::vector<std::string> & elements, const std::string & value)
{
    int index = -1;
    for(int i=0;i<elements.size();i++){
        if(elements[i] == value)
            index = i;
    }
    return index;
}

} // CaxidyEngine

#endif // XMLPARSERUTILS_CPP