#include "PVector.h"       
#include <math.h>
PVector::PVector(float posx, float posy){
    sizex = posx;
    sizey = posy;
	auxx  = posx;
	auxy  = posy;
    x = 0;
    y = 0;
}

PVector::~PVector(void)
{
}

float PVector::getX() { return x; }
float PVector::getY() { return y; }

float PVector::getSizeX() { return sizex; }
float PVector::getSizeY() { return sizey; }

float PVector::getAuxx() { return auxx; }
float PVector::getAuxy() { return auxy; }

float PVector::getAngle(float vx, float vy){
    // cross product
    double ny = (sizex * vy) - (vx * sizey);
    // dot product
    double nx = (sizex * vx) + (sizey * vy);
    return atan2(ny, nx);
}
void PVector::addSum(float tx, float ty){
    x += tx;
    y += ty;
}
void PVector::addSum2(float tx, float ty){
    sizex+= tx;
    sizey+= ty;
}


void PVector::setXY(float nx, float ny){
    x = nx;
    y = ny;
}

void PVector::setSizeY(float ny){
    sizey = ny;
}
void PVector::setSizeX(float nx){
    sizex = nx;
}

void PVector::setSizeXY(float nx, float ny){
    sizex = nx;
    sizey = ny;
	auxx = nx;
	auxy = ny;
}
float PVector::getNorma(){
    return sqrt((sizex * sizex) + (sizey * sizey));
}

float PVector::getUnitarioX(){
    return sizex / getNorma();
}

float PVector::getUnitarioY(){
    return sizey / getNorma();
}

void PVector::rotate(float angle){
	//angle = angle * (3.14159265358979/180);
    float newx = sizex * cos(angle) - sizey * sin(angle);
    float newy = sizex * sin(angle) + sizey * cos(angle);
    sizex = newx;
    sizey = newy;
}
