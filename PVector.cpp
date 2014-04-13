#include "PVector.h"       

PVector::PVector(float posx, float posy){
    x = posx;
    y = posy;
}

PVector::~PVector(void)
{
}

float PVector::getX() { return x; }
float PVector::getY() { return y; }

void PVector::addSum(float tx, float ty){
    x += tx;
    y += ty;
}
