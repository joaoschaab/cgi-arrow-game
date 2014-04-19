#pragma once
class PVector{
public:
	PVector(float sizex, float sizey);
	~PVector(void);

	void setXY(float nx, float ny);
	void setSizeXY(float nx, float ny);

	float getX(void);
	float getY(void);

	float getSizeX(void);
	float getSizeY(void);

    void addSum(float tx, float ty);

    float getAngle(float vx, float vy);

    float getNorma(void);

    float getUnitarioX(void);
    float getUnitarioY(void);
private: 
	float x, y;
    float sizex;
    float sizey;
};

