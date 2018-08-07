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

#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include <string>
#include "sound/sound.h"

using namespace std;
class Window
{
    public:


        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Window();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will set the initial parameters
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(const string & aTitle,int aHeight,int aWidth);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will create a SDL2 window
        *    \return true if the window was created and false if
        *    the window had an error
        */
        //////////////////////////////////////////////////////////////////////////
        bool createWindow();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will destroy a SDL2 window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void closeWindow();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will show the window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void showScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will hide the window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void hideScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will update the current screen in the window.
        */
        //////////////////////////////////////////////////////////////////////////
        void updateScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will clean the screen in the window.
        */
        //////////////////////////////////////////////////////////////////////////
        void cleanScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will resize our window
        *    @param windowH -> the new value of the width size
        *    @param windowW -> the new value of the width size
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void resizeWindow(int windowH,int windowW);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the width of our window
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getWidth();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the height of our window
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getHeight();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the title of the window
        *    @param title -> the new title of the window
        */
        //////////////////////////////////////////////////////////////////////////
        void setTitle(string aTitle);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the title of the window
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getTitle();

        static Window * getInstance(){
            if(instance == NULL)
                instance = new Window();

            return instance;
        }

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the mode of the window (full screen/ window mode)
        *    @param value -> the new value of the flag
        */
        //////////////////////////////////////////////////////////////////////////
        void fullScreen(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return is the window is in full screen
        *    \return bool true if the window is in full screen
        */
        //////////////////////////////////////////////////////////////////////////
        bool getIsFullScreen();

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Window();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the icon of the window
        */
        //////////////////////////////////////////////////////////////////////////
        void setIcon();

        static Window* instance;    // Instance of the window
        SDL_Window * window;        // Window of the object
        SDL_GLContext context;      // OpenGL context of the object
        bool fullScreenMode;        // Flag of window mode
        string title;               // Title of the window
        int height;                 // Height of the window
        int width;                  // Width of the window
};

#endif // WINDOW_H
