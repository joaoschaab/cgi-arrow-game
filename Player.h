#pragma once
class Player
{
public:
	Player(void);
	~Player(void);

	float getX(void);
	float getY(void);
	float getW(void);
	float getH(void);
	
    void translate(float tx, float ty);
    void setWidth(float width);
    void setHeight(float height);

private: 
	float x, y, w, h;
};

