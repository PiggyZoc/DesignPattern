#pragma once
#include "UndoManager.h"
#include "UndoableEdit.h"
class UndoableEditSupport
{
public:
	UndoableEditSupport(){};
	~UndoableEditSupport();
	void postEdit(UndoableEdit* edit){
		this->undoMgr->undoableEditHappended(edit);
	}
	void addUndoManger(UndoManager* Mgr){
		this->undoMgr = Mgr;
	}
private:
	UndoManager*  undoMgr;

};

