#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
using namespace std;

class Entry
{
public:
	Entry(){};
	~Entry(){};
	 string getName(){
		 return this->s_name;
	};
	virtual int getSize(){
		return NULL;
	};
	virtual void add(Entry* entry){
	}
	virtual void remove_child(Entry* entry){
	}
	virtual Entry* get_Child_At(int index){
		return NULL;
	}
	virtual void printList(){
		cout << "" << endl;
	}
	virtual void delete_Entry(){}
	void printSize(){
		cout << "The size of " << this->getName() << " is " << this->getSize() << endl;
	}
	string s_name;
	
};

class File :public Entry{
private:
	string name;
	int size;
public:
	File(string name, int size) :name(name), size(size){
		s_name = this->name;
	}
	~File(){
	}
	int getSize(){
		return this->size;
	}
	void printList(){
		cout << this->getName() << endl;
	}
	
};
class Directory :public Entry{
private:
	string name;
	vector<Entry*> vec_entry;
public:
	Directory(string name) :name(name){
		s_name = this->name;
		}
	~Directory(){}
	
	 void add(Entry* entry){
		vec_entry.push_back(entry);
		cout << entry->getName() << " has been added into " << this->getName() << endl;
		
	}
	 Entry* get_Child_At(int index){
		 if (index < 0 || index >= vec_entry.size())
			 return NULL;
		 vector<Entry*>::iterator ite;
		 ite = this->vec_entry.begin() + index;
		 return *ite;
	 }
	 void remove_child(Entry* entry){
		 vector<Entry*>::iterator ite;
		 for (ite = vec_entry.begin(); ite != vec_entry.end();ite++)
		 {
			 if ((*ite) == entry){
				// cout << entry->getName() << " has been removed from " << this->getName() << endl;
				 string name = (*ite)->getName();
			//	 ite = vec_entry.erase(ite);
				 vec_entry.erase(ite, ite + 1);
				 cout << name << " has been removed from " << this->getName() << endl;
				// (*ite)->delete_Entry();
				// delete(entry);
				 return;
			 }
		 }
	 }

	int getSize(){
		int size = 0;
		vector<Entry*>::iterator ite;
		ite = this->vec_entry.begin();
		while (ite != this->vec_entry.end()){
			Entry* entry = *ite;
			size += entry->getSize();
			ite++;
		}
		return size;
	}
	void printList(){
		cout << this->getName()<< endl;
		
		vector<Entry*>::iterator ite;
		ite = this->vec_entry.begin();
		while (ite != this->vec_entry.end()){
			Entry* entry = *ite;
			
			entry->printList();
		   	ite++;
		}
	}

};

int main()
{
	Directory* root = new Directory("ROOT");
	Directory* sub0 = new Directory("SUB0");
	Directory* sub1 = new Directory("SUB1");
	Directory* sub2 = new Directory("SUB2");
	File* file0 = new File("FILE0", 10);
	File* file1 = new File("FILE1", 12);
	File* file2 = new File("FILE2", 12);
	
	sub0->add(file0);
	sub0->add(file2);
	sub0->add(file1);
	sub1->add(file1);
	sub1->add(file2);
	sub1->add(file2);
	sub2->add(file1);
	sub2->add(file2);
	sub2->add(file2);
	root->add(sub0);
	root->add(sub1);
	root->add(sub2);
//	sub0->remove_child(file1);
//	cout << root->getSize() << endl;
//	cout << sub0->getSize() << endl;
	root->printSize();
	sub0->printSize();
	root->remove_child(sub0);
	root->printSize();
//	cout << root->getSize() << endl;
//	root->printList();
	cout << endl;
	cout << endl;
	cout << endl;
//	cout << root->get_Child_At(3)->getName() << endl;
	//cout << sub2->getName() << endl;
	
	//cout << file0->getName() << endl;
	system("PAUSE");
	return 0;
}