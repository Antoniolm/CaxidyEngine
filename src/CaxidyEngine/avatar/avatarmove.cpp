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

#include "avatarmove.h"
#include "CaxidyEngine/rootmap.h"

namespace CaxidyEngine {
    
AvatarMove::~AvatarMove(){
}

//**********************************************************************//

bool AvatarMove::moveBody(vec3f aMove,avatarDirection aDir){
    ObjectScene * hasCollision=0;
    bool result=false;
    float tenthValue,tenthValue2;
    vec3f posHero=vec3f(position.x,position.y,position.z);
    //posHero.y+=1.0;
    //Check the collision first

    switch(aDir){
        case FORWARD:
            tenthValue=posHero.x-(int)posHero.x;
            hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.5));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y+1.0,posHero.z+0.5));

            if(tenthValue<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.5));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y+1.0,posHero.z+0.5));
            }
            else if(tenthValue>0.6 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.5));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y+1.0,posHero.z+0.5));
            }
        break;
        case BACKWARD:
            tenthValue=posHero.x-(int)posHero.x;
            hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.5));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y+1.0,posHero.z-0.5));

            if(tenthValue<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.5));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y+1.0,posHero.z-0.5));
            }
            else if(tenthValue>0.6 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.5));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y+1.0,posHero.z-0.5));
            }
        break;
        case LEFTWARD:
            tenthValue=(int)posHero.z-posHero.z;
            hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z));

            if(tenthValue<0.5 && hasCollision==0){                                        //+0.2
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z+0.05));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z+0.05));
            }
            else if(tenthValue>0.5 && hasCollision==0){                                  //+0.2
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z-0.05));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z-0.05));
            }
        break;
        case RIGHTWARD:
            tenthValue=(int)posHero.z-posHero.z;
            hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z));

            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z));

            if(tenthValue<0.5 && hasCollision==0){                                        //+0.2
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z+0.05));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z+0.05));
            }
            else if(tenthValue>0.5 && hasCollision==0){                                   //+0.2
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z-0.05));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z-0.05));
            }
        break;
        case FOR_LEFTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z+0.5));

            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z+0.5));

            if(tenthValue2<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.5));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y+1.0,posHero.z+0.5));
            }
            else if(tenthValue<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z));
            }
        break;
        case FOR_RIGHTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z+0.5));

            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z+0.5));

            if(tenthValue2<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.5));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y+1.0,posHero.z+0.5));
            }
            else if(tenthValue<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z));
            }
        break;
        case BACK_LEFTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z-0.5));

            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z-0.5));

            if(tenthValue2<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.5));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y+1.0,posHero.z-0.5));
            }
            else if(tenthValue<0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y,posHero.z));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.5,posHero.y+1.0,posHero.z));
            }
        break;
        case BACK_RIGHTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z-0.5));

            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z-0.5));


            if(tenthValue2>0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.5));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y+1.0,posHero.z-0.5));

            }
            else if(tenthValue>0.5 && hasCollision==0){
                hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y,posHero.z));

                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.5,posHero.y+1.0,posHero.z));
            }
        break;
    }
    float time=SDL_GetTicks();
    if(hasCollision==0){ //Case -> the hero can move = No collision
        if(direction!=aDir){
            vec4f position;
            position=moveAvatar->product(position);
            Matrix4f transHero;
            transHero.translation(position.x,position.y,position.z);
            LinearMovement lineMove(aMove);
            transHero.product(lineMove.updateState(time-currentTime).getMatrix());

            moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
            moveAvatar->product(transHero.getMatrix());

            direction=aDir;
        }
        else{
            LinearMovement lineMove(aMove);
            moveAvatar->product(lineMove.updateState(time-currentTime).getMatrix());
        }
        result=true;
        //isMoveCollision=false;
    }
    else{   //Case -> not Move for colission but the hero change the rotation in the Y-axis
        if(direction!=aDir){
            vec4f position;
            position=moveAvatar->product(position);
            Matrix4f transHero;
            transHero.translation(position.x,position.y,position.z);

            moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
            moveAvatar->product(transHero.getMatrix());

            direction=aDir;
        }
        //isMoveCollision=true;
    }

    isMoving=true;

    return result;
}

//**********************************************************************//

ObjectScene * AvatarMove::gravity(float time){
    ObjectScene * hasCollision=0;
    float tenthValueX,tenthValueZ;

    if(time-currentTime>35){
        currentTime=time-35;
    }

    vec3f posHero=getPosition();
    posHero.y-=limitBottom;

    if(!isJumping){
        GLfloat * moveGravity=acceleratedMove->updateState(time-currentTime).getMatrix();
        if(moveGravity[13]<-0.5)
            moveGravity[13]=-0.5;
    //Get the tenth of our position
    tenthValueX=posHero.x-(int)posHero.x;
    tenthValueZ=(int)posHero.z-posHero.z;

    //Check the collision in the center
    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z));

    //Check the collision in the area
    if(tenthValueX>0.5 && hasCollision==0){ //Case tenth in x >0.5
        if( tenthValueZ<0.5){ //case Tenth in x >0.5 and tenth in z <0.5
            hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.2));
        }else{  //case Tenth in x >0.5 and tenth in z >= 0.5
            hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.2));
        }
    }
    else if(tenthValueX<0.5 && hasCollision==0){ //Case tenth in x <0.5
        if( tenthValueZ<0.5){ //case Tenth in x <0.5 and tenth in z <0.5
            hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.2));
        }else{ //case Tenth in x <0.5 and tenth in z >= 0.5
            hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
            if(hasCollision==0)
            hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.2));
        }
    }

    if(hasCollision==0){ //if not collision
        moveAvatar->product(moveGravity);
        isFalling=true;
    }
    else {
        if(isFalling){
            vec3f positionObs=hasCollision->getPosition();
            BoundingBox box=hasCollision->getBoundingBox();
            if((positionObs.y+box.maxValue.y)-(posHero.y)>0.1 && (positionObs.y+box.maxValue.y)-(posHero.y)<0.5){
                Matrix4f trans;
                trans.translation(0.0,(positionObs.y+box.maxValue.y)-(posHero.y),0.0);
                moveAvatar->product(trans.getMatrix());
            }
        }
        isFalling=false;
        acceleratedMove->resetState();

        }
    }

    return hasCollision;
}


//**********************************************************************//

void AvatarMove::activeJump(vec3f velocity,vec3f acceleration){
    acceleratedMove=new AcceleratedMovement(velocity.x,velocity.y,velocity.z,acceleration.x,acceleration.y-9.8,acceleration.z);
    isJumping=true;
}

//**********************************************************************//

bool AvatarMove::jump(float time){
    ObjectScene * hasCollision;
    bool result=true;
    float tenthValueX,tenthValueZ;

    GLfloat * moveGravity=acceleratedMove->updateState(time-currentTime).getMatrix();
    vec3f posHero=getPosition();
    posHero.y+=0.5;

    if(moveGravity[13]>0){
        //Get the tenth of our position
        tenthValueX=posHero.x-(int)posHero.x;
        tenthValueZ=(int)posHero.z-posHero.z;

        //Check the collision in the center
        hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z));

        //Check the collision in the area
        if(tenthValueX>0.5 && hasCollision==0){ //Case tenth in x >0.5
            if( tenthValueZ<0.5){ //case Tenth in x >0.5 and tenth in z <0.5
                hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.2));
            }else{  //case Tenth in x >0.5 and tenth in z >= 0.5
                hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.2));
            }
        }
        else if(tenthValueX<0.5 && hasCollision==0){ //Case tenth in x <0.5
            if( tenthValueZ<0.5){ //case Tenth in x <0.5 and tenth in z <0.5
                hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.2));
            }else{ //case Tenth in x <0.5 and tenth in z >= 0.5
                hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=currentMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
                if(hasCollision==0)
                hasCollision=currentMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.2));
            }
        }

        if(hasCollision==0){ //if not collision
            moveAvatar->product(moveGravity);
            isJumping=true;
        }
        else {
            isJumping=false;
            isFalling=true;
            acceleratedMove->resetState();
            result=false;
        }
    }else{
        isJumping=false;
        isFalling=true;
        acceleratedMove->resetState();
        result=false;
    }

    return result;
}

//**********************************************************************//

bool AvatarMove::detectHit(vec3f posAvatar,avatarDirection dirAvatar){
    bool result=false;

    switch(dirAvatar){
        case FORWARD:
            if(position.z>posAvatar.z && (position.x>=posAvatar.x-0.4 && position.x<=posAvatar.x+0.4))
                result=true;
            break;
        case BACKWARD:
            if(position.z<posAvatar.z && (position.x>=posAvatar.x-0.4 && position.x<=posAvatar.x+0.4))
                result=true;
            break;
        case LEFTWARD:
            if(position.x<posAvatar.x && (position.z>=posAvatar.z-0.4 && position.z<=posAvatar.z+0.4))
                result=true;
            break;
        case RIGHTWARD:
            if(position.x>posAvatar.x && (position.z>=posAvatar.z-0.4 && position.z<=posAvatar.z+0.4))
                result=true;
            break;
        case FOR_LEFTWARD:
            if(position.x<posAvatar.x && position.z>posAvatar.z)
                result=true;
            break;
        case FOR_RIGHTWARD:
            if(position.x>posAvatar.x && position.z>posAvatar.z)
                result=true;
            break;
        case BACK_LEFTWARD:
            if(position.x<posAvatar.x && position.z<posAvatar.z)
                result=true;
            break;
        case BACK_RIGHTWARD:
            if(position.x>posAvatar.x && position.z<posAvatar.z)
                result=true;
            break;
    }

    return result;
}

//**********************************************************************//

bool AvatarMove::detectShield(vec3f posAvatar,avatarDirection dirAvatar){
    bool result=false;

    switch(dirAvatar){
        case FORWARD:
            if(position.z<posAvatar.z && (position.x>=posAvatar.x-0.4 && position.x<=posAvatar.x+0.4))
                result=true;
            break;
        case BACKWARD:
            if(position.z>posAvatar.z && (position.x>=posAvatar.x-0.4 && position.x<=posAvatar.x+0.4))
                result=true;
            break;
        case LEFTWARD:
            if(position.x>posAvatar.x && (position.z>=posAvatar.z-0.4 && position.z<=posAvatar.z+0.4))
                result=true;
            break;
        case RIGHTWARD:
            if(position.x<posAvatar.x && (position.z>=posAvatar.z-0.4 && position.z<=posAvatar.z+0.4))
                result=true;
            break;
        case FOR_LEFTWARD:
            if(position.x>posAvatar.x && position.z<posAvatar.z)
                result=true;
            break;
        case FOR_RIGHTWARD:
            if(position.x<posAvatar.x && position.z<posAvatar.z)
                result=true;
            break;
        case BACK_LEFTWARD:
            if(position.x>posAvatar.x && position.z>posAvatar.z)
                result=true;
            break;
        case BACK_RIGHTWARD:
            if(position.x<posAvatar.x && position.z>posAvatar.z)
                result=true;
            break;
    }

    return result;
}
//**********************************************************************//

void AvatarMove::activeImpact(avatarDirection dirAvatar){
    impactTime=currentTime;
    switch(dirAvatar){
        case FORWARD:
            impactMovement=vec3f(0.0,0.0,3.0);
            break;
        case BACKWARD:
            impactMovement=vec3f(0.0,0.0,-3.0);
            break;
        case LEFTWARD:
            impactMovement=vec3f(-3.0,0.0,0.0);
            break;
        case RIGHTWARD:
             impactMovement=vec3f(3.0,0.0,0.0);
            break;
        case FOR_LEFTWARD:
            impactMovement=vec3f(-2.0,0.0,2.0);
            break;
        case FOR_RIGHTWARD:
            impactMovement=vec3f(2.0,0.0,2.0);

            break;
        case BACK_LEFTWARD:
            impactMovement=vec3f(-2.0,0.0,-2.0);
            break;
        case BACK_RIGHTWARD:
            impactMovement=vec3f(2.0,0.0,-2.0);
            break;
    }

    isImpacted=true;
}

//**********************************************************************//

void AvatarMove::impactMove(float time){
    if(impactTime>(time-150)){
        moveBody(impactMovement,direction);
    }
    else{
        isImpacted=false;
    }

}

//**********************************************************************//

vec3f AvatarMove::getPosition(){
    return vec3f(position.x,position.y,position.z);
}

//**********************************************************************//

avatarDirection AvatarMove::getDirection(){
    return direction;
}

//**********************************************************************//

void AvatarMove::changeDirection(avatarDirection aDir){
    direction=aDir;
    vec4f myPos;
    myPos=moveAvatar->product(myPos);
    Matrix4f transHero;
    transHero.translation(myPos.x,myPos.y,myPos.z);

    moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
    moveAvatar->product(transHero.getMatrix());

    direction=aDir;
}

//**********************************************************************//

void AvatarMove::visualization(Context & cv){
}

//**********************************************************************//

void AvatarMove::updateState(GameState & gameState){}

} // CaxidyEngine
