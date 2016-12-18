#pragma once
#include "MyPoint.h"
#include "AbstractUndoableEdit.h"
#include<vector>
using namespace std;
class DrawingSquareEdit:public AbstractUndoableEdit
{
public:
	DrawingSquareEdit(vector<MySquare*>sqr, MySquare* newSqr){
		this->squares = sqr;
		this->NewAddedOne = newSqr;
		this->squares.push_back(newSqr);
	};
	virtual void undo();
	virtual void redo();

private:
	vector<MySquare*> squares;
	MySquare* NewAddedOne;
};
void DrawingSquareEdit::undo(){
	AbstractUndoableEdit::undo();
	vector<MySquare*>::iterator iter = this->squares.begin();
	for (; iter != squares.end(); iter++)
	{
		if ((*iter) == this->NewAddedOne)
		{
			squares.erase(iter, iter + 1);
			return;
		}
	}
}

void DrawingSquareEdit::redo(){
	AbstractUndoableEdit::redo();
	this->squares.push_back(this->NewAddedOne);
}
