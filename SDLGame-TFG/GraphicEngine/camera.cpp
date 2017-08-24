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

#include "camera.h"
#include "rootmap.h"

Camera::Camera(){
    viewMode=false;
    speakMode=false;
    factorZoomY=0.0;
    factorZoomZ=0.0;
    currentTime=SDL_GetTicks();
    viewDelay=currentTime;
}

//**********************************************************************//

Camera::Camera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    initialPosition=eye;
    target=aTarget;
    up=aUp;
    viewMode=false;
    speakMode=false;

    factorZoomY=0.0;
    factorZoomZ=0.0;

    createCamera();
    currentTime=SDL_GetTicks();
    viewDelay=currentTime;
}

//**********************************************************************//

Camera::~Camera()
{
    //dtor
}

//**********************************************************************//

void Camera::setCamera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    initialPosition=eye;
    target=aTarget;
    up=aUp;
}

//**********************************************************************//

void Camera::setPerspectiveProjection(float fov, float aspect, float nearPro, float farPro){
    float f=(float) 1/tan((fov * 3.1416) / 360.0);

    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=f/(aspect);  projec[1]=0;        projec[2]=0;                          projec[3]=0;
	projec[4]=0;                projec[5]=f;   projec[6]=0;                          projec[7]=0;
	projec[8]=0;                projec[9]=0;   projec[10]=(farPro+nearPro)/(nearPro-farPro);    projec[11]=-1.0f;
	projec[12]=0;               projec[13]=0;  projec[14]=(2.0f*farPro*nearPro)/(nearPro-farPro); projec[15]=0;

    perspecProjection.setMatrix(projec);
}

//**********************************************************************//

void Camera::setOrthographicProjection(float left,float right,float bottom,float top,float nearPro,float farPro){

    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=2.0f/(right-left);        projec[1]=0;                        projec[2]=0;                 projec[3]=((right+left)/(right-left));
	projec[4]=0;                        projec[5]=2.0f/(top-bottom);        projec[6]=0;                 projec[7]=((top+bottom)/(top-bottom));
	projec[8]=0;                        projec[9]=0;                        projec[10]=-2.0f/(farPro-nearPro); projec[11]=0.0;
	projec[12]=0;                       projec[13]=0;                       projec[14]=-(farPro+nearPro)/(farPro-nearPro); projec[15]=1;

	orthoProjection.setMatrix(projec);
}

//**********************************************************************//

void Camera::createCamera(){
    vec3f zCamera;
    vec3f yCamera;
    vec3f xCamera;

    //Calculate the z-Axis
    zCamera=position-target;
    zCamera.normalize();

    //Calculate the x-Axis
    xCamera=up.cross(zCamera);
    xCamera.normalize();

    //Calculate the y-Axis
    yCamera=zCamera.cross(xCamera);

    //Create the camera
    GLfloat * matrix=new GLfloat[16];
    matrix[0]=xCamera.x;  matrix[1]=yCamera.x;  matrix[2]=zCamera.x;  matrix[3]=0;
	matrix[4]=xCamera.y;  matrix[5]=yCamera.y;  matrix[6]=zCamera.y;  matrix[7]=0;
	matrix[8]=xCamera.z;  matrix[9]=yCamera.z;  matrix[10]=zCamera.z; matrix[11]=0;
	matrix[12]=-(xCamera.dot(position)); matrix[13]=-(yCamera.dot(position)); matrix[14]=-(zCamera.dot(position)); matrix[15]=1;

	camera.setMatrix(matrix);
}

//**********************************************************************//

void Camera::activateCamera(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,camera.getMatrix());
    glUniform3f(glGetUniformLocation(shaderID, "viewPos"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shaderID, "viewPosVertex"), position.x, position.y, position.z);
}

//**********************************************************************//

void Camera::activateOrthoProjection(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projection"),1,GL_FALSE,orthoProjection.getMatrix());
}

//**********************************************************************//

void Camera::activatePerspecProjection(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projection"),1,GL_FALSE,perspecProjection.getMatrix());
}

//**********************************************************************//

void Camera::update(GameState & gameState,GLuint shaderID,bool activateMenu){
    vec3f posHero=gameState.rootMap->getHero()->getPosition();
    ControllerManager * controller=gameState.controller;

    float time=gameState.time;
    if(time-currentTime>200)
        currentTime=time-50;

    if(controller->checkButton(cVIEW) && !activateMenu && viewDelay<(time-600)){
        viewMode=!viewMode;
        viewDelay=time;
        controller->setState(false,cVIEW);
    }

    target=posHero;

    //////////////////////
    // View mode activated
    if(viewMode){
        if(position.z<posHero.z+35){ //if is not in the max position
            position.y+=0.25*((time-currentTime)/10);
            position.z+=0.5*((time-currentTime)/10);
        }
        else if(controller->checkButton(cVIEW)){ //if is in the max position
                viewMode=!viewMode;              //the user want to quit viewMode
                viewDelay=time;
                controller->setState(false,cVIEW);
        }
    }
    else { //else normal mode
        if(!speakMode)
            position=vec3f(posHero.x+initialPosition.x,posHero.y+initialPosition.y,posHero.z+initialPosition.z);
    }

    /////////////////////
    // Speak mode activated
    if(speakMode){
        if(position.z>posHero.z+10){ //if is not in the max position
            factorZoomY-=0.8*((time-currentTime)/20);
            factorZoomZ-=1.3*((time-currentTime)/20);

            position.y-=0.8*((time-currentTime)/20);
            position.z-=1.3*((time-currentTime)/20);
        }
        else {
            position.y=posHero.y+initialPosition.y+factorZoomY;
            position.z=posHero.z+initialPosition.z+factorZoomZ;
        }

        position.x=posHero.x+initialPosition.x;
    }
    else { //else normal mode
        position=vec3f(posHero.x+initialPosition.x,posHero.y+initialPosition.y,posHero.z+initialPosition.z);
        factorZoomY=0.0;
        factorZoomZ=0.0;
    }

    //Assign parameters of the shader
    createCamera();//Create camera

    glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,camera.getMatrix());
    glUniform3f(glGetUniformLocation(shaderID, "viewPos"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shaderID, "viewPosVertex"), position.x, position.y, position.z);

    currentTime+=time-currentTime;
}

//**********************************************************************//

void Camera::setSpeakMode(bool value){
    speakMode=value;
}

//**********************************************************************//

Matrix4f & Camera::getCamera(){
    return camera;
}

//**********************************************************************//

GLfloat * Camera::getView(){
    return camera.getMatrix();
}

//**********************************************************************//

Matrix4f & Camera::getOrthoProyection(){
    return orthoProjection;
}

//**********************************************************************//

Matrix4f & Camera::getPersProyection(){
    return perspecProjection;
}

//**********************************************************************//

vec3f Camera::getPosition(){
    return position;
}

//**********************************************************************//

vec3f Camera::getTarget(){
    return target;
}

//**********************************************************************//

vec3f Camera::getUp(){
    return up;
}

//**********************************************************************//

bool Camera::isViewMode(){
    return viewMode;
}

//**********************************************************************//

void Camera::setPosition(vec3f aPosition,GLuint shaderID){

    position=vec3f(aPosition.x+initialPosition.x,aPosition.y+initialPosition.y,aPosition.z+initialPosition.z); //test camera
    target=aPosition;

    createCamera();//Create camera

    glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,camera.getMatrix());
    glUniform3f(glGetUniformLocation(shaderID, "viewPos"), position.x, position.y, position.z);
}
