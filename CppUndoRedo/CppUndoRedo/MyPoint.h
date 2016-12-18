#pragma once
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
class MySquare{
public:
	MySquare(Point pos, int R){
		sideLen = R;
		Pos = new MyPoint(pos.X, pos.Y);
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
