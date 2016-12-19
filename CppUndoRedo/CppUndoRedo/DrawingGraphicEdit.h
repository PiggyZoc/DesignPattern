#pragma once
#include "MyPoint.h"
#include "AbstractUndoableEdit.h"
#include<vector>
using namespace std;
class DrawingSquareEdit:public AbstractUndoableEdit
{
public:
  /*	DrawingSquareEdit(vector<MySquare*>sqr, MySquare* newSqr){
		this->squares = sqr;
		this->NewAddedOne = newSqr;
		this->squares.push_back(newSqr);
		this->presentationName = "Draw A Square";
	};*/
	DrawingSquareEdit(vector<MyGraphic*>gra, MySquare* newSqr){
		this->graphics = gra;
		this->NewAddedOne = newSqr;
		this->graphics.push_back(newSqr);
		this->presentationName = "Draw A Square";
	};
	virtual void undo();
	virtual void redo();
/*	vector<MySquare*> getSquares(){
		return this->squares;
	*/
	vector<MyGraphic*> getGraphics(){
		return this->graphics;
	}
private:
	
	vector<MyGraphic*> graphics;
	MySquare* NewAddedOne;
};
inline void DrawingSquareEdit::undo(){
	AbstractUndoableEdit::undo();
	vector<MyGraphic*>::iterator iter = this->graphics.begin();
	for (; iter != graphics.end(); iter++)
	{
		if ((*iter) == this->NewAddedOne)
		{
			graphics.erase(iter, iter + 1);
		//	cout << squares.size() << endl;
		//	cout << this->gethas() << endl;
		//	cout << this->canRedo() << endl;
		//	AbstractUndoableEdit::canRedo();
		//	cout << this->canRedo() << endl;
			return;
		}
	}
	
}

inline void DrawingSquareEdit::redo(){
	AbstractUndoableEdit::redo();
	this->graphics.push_back(this->NewAddedOne);
}

class DrawingTriangleEdit :public AbstractUndoableEdit
{
public:
	
	DrawingTriangleEdit(vector<MyGraphic*>gra, MyTriangle* newSqr){
		this->graphics = gra;
		this->NewAddedOne = newSqr;
		this->graphics.push_back(newSqr);
		this->presentationName = "Draw A Triangle";
	};
	virtual void undo();
	virtual void redo();
	/*	vector<MySquare*> getSquares(){
	return this->squares;
	*/
	vector<MyGraphic*> getGraphics(){
		return this->graphics;
	}
private:

	vector<MyGraphic*> graphics;
	MyTriangle* NewAddedOne;
};
inline void DrawingTriangleEdit::undo(){
	AbstractUndoableEdit::undo();
	vector<MyGraphic*>::iterator iter = this->graphics.begin();
	for (; iter != graphics.end(); iter++)
	{
		if ((*iter) == this->NewAddedOne)
		{
			graphics.erase(iter, iter + 1);
			return;
		}
	}

}

inline void DrawingTriangleEdit::redo(){
	AbstractUndoableEdit::redo();
	this->graphics.push_back(this->NewAddedOne);
}



