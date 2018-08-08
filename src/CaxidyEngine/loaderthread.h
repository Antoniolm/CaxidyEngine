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

#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <thread>
#include "rootmap.h"
#include "context/shader.h"
#include <string>

namespace CaxidyEngine {

class LoaderThread
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        LoaderThread(RootMap * aRootMap, std::string aFileMap);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~LoaderThread();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create and run our thread
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void run();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will create a new rootMap instance( inside our thread )
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initialize();

    protected:

    private:
        std::thread * loader;       // Thread that will load the map
        static RootMap * rootMap;   // Object where the map will be load
        static std::string fileMap;      // File that contains the map to load
};

} // CaxidyEngine 

#endif // LOADERTHREAD_H
