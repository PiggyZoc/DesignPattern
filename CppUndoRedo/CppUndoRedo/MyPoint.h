#pragma once
#include <math.h>
using namespace System::Drawing;
class MyPoint
{
public:
	MyPoint(int x, int y) :x(x), y(y){};
	~MyPoint();
	int getX(){
		return this->x;
	}
	int getY(){
		return this->y;
	}
private:
	int x;
	int y;

};
class MyGraphic{
public:
	MyGraphic(){};
	~MyGraphic(){};
	int getID(){
		return this->ID;
	}
protected:
	int ID;
	int Ridus;
	MyPoint* Pos;
};
class MySquare:public MyGraphic{
public:
	MySquare(Point pos, int R){
		sideLen = R;
		Pos = new MyPoint(pos.X, pos.Y);
		this->ID = 1;
	};
	MySquare(int R) :sideLen(R){};
	~MySquare();
	int getsideLen(){
		return this->sideLen;
	}
	MyPoint* getPos(){
		return this->Pos;
	}
    
private:
	int sideLen;
	MyPoint* Pos;
};
class MyTriangle:public MyGraphic
{
public:
	MyTriangle(Point pos, int R){
		sideLen = R;
		Pos = new MyPoint(pos.X, pos.Y);
		this->ID = 2;
	};
	~MyTriangle();
	int getsideLen(){
		return this->sideLen;
	}
	MyPoint* getPos(){
		return this->Pos;
	}
private:
	int sideLen;
	MyPoint* Pos;
};

