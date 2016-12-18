#pragma once
#define LIMIT 10
#include "UndoableEdit.h"
#include <vector>
using namespace std;
class UndoManager
{

public:
	UndoManager(){};
	~UndoManager(){};
	int getLimit() { return limit; }
	void setLimit(int l) { this->limit = l; }
	void discardAllEdits();

	virtual void undo();
	virtual void redo();
	virtual void addEdit(UndoableEdit* undoableEdit);
	void undoableEditHappended(UndoableEdit* undoableEdit) { 
		this->addEdit(undoableEdit);
		
	};
	virtual bool canUndo(){ return false; }
	virtual bool canRedo(){ return false; }
	
private:
	int limit = LIMIT;
	int indexOfNextAdd = 0;//类似于指针，指向容器当前的位置
	vector<UndoableEdit*> edits;
protected:
	UndoableEdit* editToBeUndone();
	UndoableEdit* editToBeRedone();
	void undoTo(UndoableEdit* edit);
	void redoTo(UndoableEdit* edit);

};
inline void UndoManager::addEdit(UndoableEdit* undoableEdit){
	if (indexOfNextAdd > limit)return;
	edits.erase(edits.begin() + indexOfNextAdd, edits.end());
	edits.push_back(undoableEdit);
	indexOfNextAdd++;

}
inline void UndoManager::undo(){
	UndoableEdit* edit = editToBeUndone();
	if (edit != NULL)
		this->undoTo(edit);
	cout << edits.size() << endl;
}
inline void UndoManager::redo(){
	UndoableEdit* edit = editToBeRedone();
	if (edit != NULL)
		this->redoTo(edit);
}
inline void UndoManager::undoTo(UndoableEdit* edit)
{
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd - 1;
	while (true){
		indexOfNextAdd--;
		(*ite)->undo();
		if ((*ite) == edit) break;
		ite--;
	}
}
inline void UndoManager::redoTo(UndoableEdit* edit)
{
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd ;
	while (true){
		indexOfNextAdd++;
		(*ite)->redo();
		if ((*ite) == edit) break;
		ite++;
	}
}

inline UndoableEdit* UndoManager::editToBeUndone(){
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd-1;
	for (; ite >= edits.begin(); ite--)
	{
		if ((*ite)->canUndo()){
			
			return *ite;
		}
	}
	return NULL;
}

inline UndoableEdit* UndoManager::editToBeRedone(){
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd ;
	for (; ite!= edits.end(); ite++)
	{
		if ((*ite)->canRedo()){
			return *ite;
		}
	}
	return NULL;
}
