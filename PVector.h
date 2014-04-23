#pragma once
class PVector{
public:
	PVector(float sizex, float sizey);
	~PVector(void);

	void setXY(float nx, float ny);
	void setSizeXY(float nx, float ny);

	void setSizeY(float ny);
	void setSizeX(float nx);

	float getX(void);
	float getY(void);

	float getSizeX(void);
	float getSizeY(void);

	float getAuxx(void);
	float getAuxy(void);
	
    void addSum(float tx, float ty);
    void addSum2(float tx, float ty);

    void rotate(float angle);

    float getAngle(float vx, float vy);

    float getNorma(void);

    float getUnitarioX(void);
    float getUnitarioY(void);
private: 
	float x, y;
	float auxx;
	float auxy;
    float sizex;
    float sizey;
};

