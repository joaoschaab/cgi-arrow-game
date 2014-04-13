#pragma once
class PVector{
public:
	PVector(float posx, float posy);
	~PVector(void);

	float getX(void);
	float getY(void);

    void addSum(float tx, float ty);

private: 
	float x, y;
};

