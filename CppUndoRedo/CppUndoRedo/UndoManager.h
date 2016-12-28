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
	bool canUndo(){ return editToBeUndone()!=NULL; }
	bool canRedo(){ return editToBeRedone()!=NULL; }
	UndoableEdit* getEdit(){
		if (indexOfNextAdd < 1) return NULL;
		vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd - 1;
		return *ite;
	}
	
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
//	if (indexOfNextAdd > limit)return;
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd;
/*	for (; ite != edits.end(); ++ite)
	{
		delete (*ite);
	}*/
	edits.erase(edits.begin() + indexOfNextAdd, edits.end());
	edits.push_back(undoableEdit);
	indexOfNextAdd++;

}
inline void UndoManager::undo(){
	UndoableEdit* edit = editToBeUndone();
//	cout << indexOfNextAdd << endl;
	if (edit != NULL)
		this->undoTo(edit);
//	cout << edits.size() << endl;
}
inline void UndoManager::redo(){
	UndoableEdit* edit = editToBeRedone();
//	cout << 1 << endl;
	if (edit != NULL)
		this->redoTo(edit);
}
inline void UndoManager::undoTo(UndoableEdit* edit)
{
//	if (indexOfNextAdd <1)return;
//	cout << indexOfNextAdd << endl;
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd - 1;
	
	while (true){
		indexOfNextAdd--;
	
		(*ite)->undo();
//		cout << 1 << endl;
		if ((*ite) == edit) break;
		if (indexOfNextAdd < 1) break;
		ite--;
	}
}
inline void UndoManager::redoTo(UndoableEdit* edit)
{
	vector<UndoableEdit*>::iterator ite = edits.begin() + indexOfNextAdd ;
	while (true){
		indexOfNextAdd++;
		(*ite)->redo();
//		cout << 1 <<  endl;
		if ((*ite) == edit) break;
		ite++;
	}
}


inline UndoableEdit* UndoManager::editToBeUndone(){
	if (indexOfNextAdd<1)
	{
		return NULL;
	}
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
	//		cout << 2 << endl;
			return *ite;
		}
	}
	return NULL;
}
inline void UndoManager::discardAllEdits(){
	vector<UndoableEdit*>::iterator ite = edits.begin();
	for (;ite!=edits.end(); ++ite)
	{
		delete (*ite);
	}
	edits.clear();

	indexOfNextAdd = 0;
}