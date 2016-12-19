#pragma once
#include<string>
using namespace std;
class UndoableEdit
{
public:
	UndoableEdit(string editName = "Î´ÃüÃû"){
		this->presentationName = editName;
	};
	~UndoableEdit(){};
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual bool canUndo() = 0;
	virtual bool canRedo() = 0;
//	virtual void addEdit(UndoableEdit* anEdit) = 0;
//	virtual void die() = 0;
    string getPresentationName(){
		return this->presentationName;
	};
	string getUndoPresentationName();
	string getRedoPresentationName();
protected:
	string presentationName;

};

inline string UndoableEdit::getRedoPresentationName()
{
	return "Undo_" + this->presentationName;
}
inline string UndoableEdit::getUndoPresentationName()
{
	return "Redo_" + this->presentationName;
}

