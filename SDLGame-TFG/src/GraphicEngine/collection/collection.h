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

#ifndef COLLECTION_H
#define COLLECTION_H

#include <map>
#include <vector>
#include <string>

using namespace std;

template <class T,class T2>
class Collection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Collection();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Collection();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will add a new element of our collection
        *   @param element -> the new element of our collection
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addElement(T * element);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will add a new index in our enumMap
        *   @param index -> the new index of our enum
        *   @param value -> the value of our new index
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addIndex(string index,T2 value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return a T -> parameters a enum element
        *   @param value -> the "index" of the element that will be returned
        *   \return T*
        */
        //////////////////////////////////////////////////////////////////////////
        T * getElement(T2 value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a T -> parameters a string
        *    @param index -> the index of the element that will be returned
        *    \return T *
        */
        //////////////////////////////////////////////////////////////////////////
        T * getElement(string index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the size of our collection
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getSize();

    protected:

    private:
        vector<T *> collection; // Vector of elements
        map<string,T2> enumMap; // Map of elements

};

#endif // COLLECTION_H
