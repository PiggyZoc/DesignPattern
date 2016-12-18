#pragma once
#include "MyPoint.h"
#include<vector>
using namespace std;
class DrawingSquareEdit
{
public:
	DrawingSquareEdit(vector<MySquare*>sqr, MySquare* newSqr){
		this->squares = sqr;
		this->squares.push_back(newSqr);
	};
private:
	vector<MySquare*> squares;
};

