#include "PVector.h"       
#include <math.h>
PVector::PVector(float posx, float posy){
    sizex = posx;
    sizey = posy;
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

void PVector::setSizeXY(float nx, float ny){
    sizex = nx;
    sizey = ny;
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
    float newx = ((sizex - x) * cos(angle)) - ((y - sizey) * sin(angle));
    float newy = ((y - sizey) * cos(angle)) - ((sizex - x) * sin(angle));
    sizex = newx;
    sizey = newy;
}
