
#include <cstdio>
#include <string>  
#include <iostream>
#include <list>

#include <windows.h>
using namespace std;

class Observer
{
public:
	Observer(){}
	 ~Observer(){}
	virtual void update(){};
};

class Observable
{
public:
	Observable(){}
	~Observable(){}
	list<Observer*> List_Obs;
	bool addObserver(Observer* obs){
		list<Observer*>::iterator ite;
		for (ite = List_Obs.begin(); ite != List_Obs.end(); ite++)
		{
			if ((*ite) == obs){
				return false;
			}
		}
		this->List_Obs.push_back(obs);
		return true;
	}
	bool deleteObserver(Observer* obs){
		list<Observer*>::iterator ite;
		for (ite = List_Obs.begin(); ite != List_Obs.end(); ite++)
		{
			if ((*ite) == obs){
				ite = List_Obs.erase(ite);
				ite--;
				return true;
			}
		}
		return false;
	}
	virtual void Notify(){}


};

class NoticeBoard :public Observable
{
public:
	NoticeBoard(){
		contents[0] = "Undetermined";
		contents[1] = "Have Ship!";
		contents[2] = "No ship,sorry!";
	}
	~NoticeBoard(){}
	void SetStatus(int i){
		if (!(i == 1 || i == 2 || i == 3)) return;
		this->current_status = i;
		this->SetContent();
	}
	int GetStatus(){
		return this->current_status;
	}
	void SetContent(){
		int temp = this->current_status;
		string temp_s;
		if (temp == 1)
			temp_s = this->contents[0];
		if (temp == 2)
	    	temp_s = this->contents[1];
		if (temp == 3)
			temp_s = this->contents[2];
		this->current_content = temp_s;
	}
	string GetContent(){
		return this->current_content;
	}
	bool hasChanged(){
		if (this->previous_status != this->current_status){
			this->previous_status = this->current_status;
			return true;
		}
		else
			return false;
	}
	void Notify(){
		if (!hasChanged()) return;
		list<Observer*>::iterator ite;
		for (ite = List_Obs.begin(); ite != List_Obs.end(); ite++){
			(*ite)->update();
		}

	}
private:
	int previous_status=-1;
	int current_status=-1;
	string current_content;
	string contents[10];
};
class Passenger :public Observer
{
public:
	Passenger(string name, NoticeBoard*noticeboard) :name(name), noticeboard(noticeboard){
		moods[0] = "Anxious";
		moods[1] = "Happy";
		moods[2] = "Upset";
		
	}
	~Passenger(){}
	
	string GetMood(){
		return this->current_mood;
	}
	void update(){
		int t = this->noticeboard->GetStatus();
		this->SetMood(t);
		cout<<this->name<<"--------------" << GetMood() << endl;
	}
private:
	string name;
	NoticeBoard* noticeboard;
	string moods[10];
	string current_mood;
	void SetMood(int t){
		int temp = t;
		string temp_s;
		if (temp == 1)
			temp_s = this->moods[0];
		if (temp == 2)
			temp_s = this->moods[1];
		if (temp == 3)
			temp_s = this->moods[2];

		this->current_mood = temp_s;
	}
};
void Print(string s)
{
	cout << "##           Ship Schedule:           ##" << endl;
	cout << endl;
	cout << "##        From Shanghai To Taibei     ##" << endl;
	cout << endl;
	cout << "==========================================" << endl;
	cout << endl;
	cout << "           " << s << "                  " << endl;
	cout << endl;
	cout << "==========================================" << endl;
	cout << endl;
	cout << "Choose one of the following options to update status£º" << endl;
	cout << endl;
	cout << "A. Undetermined  B.Have Ship  C.No Ship   E.Exit" << endl;
	cout << endl;
}
int main()
{

	NoticeBoard* noticeboard = new NoticeBoard();
	Passenger* passenger1 = new Passenger("Wang Ming", noticeboard);
	Passenger* passenger2 = new Passenger("Zhang Qiang", noticeboard);
	Passenger* passenger3 = new Passenger("Li Xiang", noticeboard);
	noticeboard->addObserver(passenger1);
	noticeboard->addObserver(passenger2);
	noticeboard->addObserver(passenger3);

	noticeboard->deleteObserver(passenger2);

	string s = "Welcome!";
	Print(s);

	//Graph<char,int> MIN;


	

	char in;
	cout << "\nPlease choose your option£º";
	while (cin >> in)
	{
		if (in == 'E') {

			cout << "\nThanks£¡£¡\n" << endl;
			break;
		}

		switch (in)
		{
		case 'A':
		{
			system("cls");
			noticeboard->SetStatus(1);
			s = noticeboard->GetContent();
			Print(s);
			noticeboard->Notify();
			break;

		};
		case 'B':
		{
			system("cls");
			noticeboard->SetStatus(2);
			s = noticeboard->GetContent();
			Print(s);
			noticeboard->Notify();
			break;

		};
		case 'C':
		{
			system("cls");
			noticeboard->SetStatus(3);
			s = noticeboard->GetContent();
			Print(s);
			noticeboard->Notify();
			break;

		};
		
		default:
		{
			cout << "PLEASE INPUT AGAIN!!" << endl;
			break;
		};


		}

		Sleep(3000);
		cout << "\nPlease choose your option£º";
	}
	

	system("PAUSE");
	return 0;
}