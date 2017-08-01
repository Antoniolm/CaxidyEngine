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

#include "window.h"
#include "mesh/file_obj.h"

Window* Window::instance = NULL;

//**********************************************************************//

Window::Window(){
    title="Test";
    height=800;
    width=600;
    fullScreenMode=false;

}

//**********************************************************************//

Window::~Window(){
    SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
}

//**********************************************************************//

void Window::setParameters(const string & aTitle,int aHeight,int aWidth){
    title=aTitle;
    height=aHeight;
    width=aWidth;
}

//**********************************************************************//

bool Window::createWindow(){
    bool salida=true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Error: %s\n", SDL_GetError());
		salida=false;
	}
	else {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

        window = SDL_CreateWindow(title.c_str() , 20, 30, height, width, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

		if (window == NULL) {
			printf("SDL_Error: %s\n", SDL_GetError());
			salida=false;
		}
		else {
            //Initialize SDL_mixer
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 512 ) == -1 ){
                    cout<< "SDL_mixer could not initialize!"<<endl;
                    salida = false;
            }
			context = SDL_GL_CreateContext(window);
		}
	}

    if ( TTF_Init( )== -1 ){
        cout << "SDL_ttf could not initialize! SDL_ttf Error:"<< endl;
        salida=false;
    }

    /////////////////////////////////////////////////////////////

    glewInit();

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    Mix_AllocateChannels(16);

    setIcon();
    return salida;
}

//**********************************************************************//

void Window::showScreen(){
    SDL_ShowWindow(window);
}

//**********************************************************************//

void Window::hideScreen(){
    SDL_HideWindow(window);
}

//**********************************************************************//

void Window::setIcon(){
    #include "icon.c"

    Uint32 rmask, gmask, bmask, amask;
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = (my_icon.bytes_per_pixel == 3) ? 0 : 0xff000000;

    SDL_Surface* icon = SDL_CreateRGBSurfaceFrom((void*)my_icon.pixel_data, my_icon.width,my_icon.height,
                                                 my_icon.bytes_per_pixel*8, my_icon.bytes_per_pixel*my_icon.width,
                                                 rmask, gmask, bmask, amask);
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

//**********************************************************************//

void Window::updateScreen(){
    SDL_GL_SwapWindow(window);
}

//**********************************************************************//

void Window::cleanScreen(){
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**********************************************************************//

void Window::resizeWindow(int windowH,int windowW){
    height =windowH;
    width = windowW;

    SDL_SetWindowSize(window,width,height);
    glViewport(0,0,width,height);
}

//**********************************************************************//

int Window::getWidth(){
    return width;
}

//**********************************************************************//

int Window::getHeight(){
    return height;
}

//**********************************************************************//

void Window::setTitle(string aTitle){
    title=aTitle;
    SDL_SetWindowTitle(window,title.c_str());
}

//**********************************************************************//

string Window::getTitle(){
    return title;
}

//**********************************************************************//

void Window::fullScreen(bool value){
    fullScreenMode=value;
    if(fullScreenMode)
        SDL_SetWindowFullscreen(window,SDL_TRUE);
    else
        SDL_SetWindowFullscreen(window,SDL_FALSE);
}

//**********************************************************************//

bool Window::getIsFullScreen(){
    return fullScreenMode;
}
