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

using namespace std;

class XmlParserUtils{

public: 

rapidxml::xml_node<> * getChildWithAttribute(
    rapidxml::xml_node<> *parent, 
    const string & type, 
    const string & attribute, 
    const string & value);

vector<string> extract(const string& stoextract);

int indexOf(const vector<string> & elements, const string & value);

};

#endif // XMLPARSERUTILS_H