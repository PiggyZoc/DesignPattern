#pragma once
#include "UndoableEdit.h"
 class AbstractUndoableEdit:public UndoableEdit
{
public:
	AbstractUndoableEdit(){};
	~AbstractUndoableEdit(){};
	virtual void undo() ;
	virtual void redo() ;
	virtual bool canUndo() ;
	virtual bool canRedo() ;
//	virtual void addEdit(UndoableEdit* anEdit) = 0;
//	virtual void die() = 0;
	string getPresentationName();
	string getUndoPresentationName();
	string getRedoPresentationName();
	
private:
	bool hasBeenDone = true;
	bool alive = true;
};

 inline void AbstractUndoableEdit::undo(){
	 hasBeenDone = false;
 }
 inline void AbstractUndoableEdit::redo(){
	 hasBeenDone = true;
 }
 inline bool AbstractUndoableEdit::canUndo(){
	 return hasBeenDone == true;
 };
 inline bool AbstractUndoableEdit::canRedo(){
	  return hasBeenDone == false;
 };