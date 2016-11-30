




#include <cstdio>
#include <string>  
#include <iostream>
#include<list>
#include <windows.h>
using namespace std;

class Observer
{
public:
	Observer(){}
	virtual ~Observer(){}
	virtual void update(){};
};

class Ticket{
public:
	Ticket(int num) :num_ticket(num){}
	virtual ~Ticket(){}
	void add_Buyer(Observer* obs){
		this->List_Buyers.push_back(obs);
	}
	void add_Machine(Observer* obs){
		this->List_Machines.push_back(obs);
	}
	void remove_obs(Observer* obs){
		list<Observer*>::iterator ite;
		for (ite = List_Buyers.begin(); ite != List_Buyers.end(); ite++)
		{
			if ((*ite) == obs){
				ite = List_Buyers.erase(ite);
				ite--;
				break;
			}
		}
	}
	void NotifyToBuyers(){
		list<Observer*>::iterator ite;
		for (ite = List_Buyers.begin(); ite != List_Buyers.end(); ite++)
		{

			(*ite)->update();
		}
	}

	void NotifyToMachines(){
		if (this->GetNum() > 0)
			return;
		list<Observer*>::iterator ite;
		for (ite = List_Machines.begin(); ite != List_Machines.end(); ite++)
		{
			//cout << "aaaaaa" << endl;
			(*ite)->update();
			//	cout << "bbbbb" << endl;

		}

	}

	int GetNum(){
		return this->num_ticket;
	}
	void SetNum(int num){
		this->num_ticket = num;
	}
	void AddATicket(){
		this->num_ticket++;
	}
	void SellATicket(){

		this->num_ticket--;

	}

private:
	list<Observer*> List_Buyers;
	list<Observer*>List_Machines;
	int num_ticket;

};

class Buyer :public Observer{
private:
	string buyer_name;
	Ticket* ticket;

public:

	Buyer(string m_name, Ticket* m_ticket) :buyer_name(m_name), ticket(m_ticket){}
	~Buyer(){};
	void BuyATicket(){
		if (ticket->GetNum() != 0)
		{
			ticket->SellATicket();

			//ticket->remove_obs(this);
		}
		else
			cout << "当前余票为零，无法购买" << endl;

	}
	void update(){
		int get_ticket_num = ticket->GetNum();
		cout << this->buyer_name << "-------" << "当前余票为：" << get_ticket_num << endl;
	}
};
class Machine :public Observer
{
private:
	string machine_id;
	Ticket* ticket;
public:
	Machine(string m_id, Ticket* ticket) :machine_id(m_id), ticket(ticket){}
	~Machine(){}
	void update(){
		Sleep(2000);
		this->ticket->AddATicket();
		//cout << this->ticket->GetNum() << endl;

	}

};

int main()
{
	Ticket* sh_ticket = new Ticket(5);
	Buyer* buyer_one = new Buyer("Tom", sh_ticket);
	Buyer* buyer_two = new Buyer("Json", sh_ticket);
	Buyer* buyer_three = new Buyer("Amy", sh_ticket);
	Machine machine_one("001", sh_ticket);
	sh_ticket->add_Machine(&machine_one);
	//machine_one.update();

	sh_ticket->NotifyToMachines();

	sh_ticket->add_Buyer(buyer_one);
	sh_ticket->add_Buyer(buyer_two);
	sh_ticket->add_Buyer(buyer_three);

	//buyer_one->BuyATicket();

	//sh_ticket->remove_obs(buyer_two);
	//	Sleep(2000);
	sh_ticket->NotifyToBuyers();

	system("PAUSE");
	return 0;
}