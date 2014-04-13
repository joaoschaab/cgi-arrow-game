#pragma once
#include "PVector.h"
class Player
{
public:
	Player(float posx, float posy);
	~Player(void);

	float getX(void);
	float getY(void);
	float getW(void);
	float getH(void);

    void translate(float tx, float ty);

    void setWidth(float width);
    void setHeight(float height);

private:
    PVector *p;
	float w, h;
};

