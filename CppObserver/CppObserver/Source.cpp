#include <cstdio>
#include <string>  
#include <iostream>
#include<list>
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
	Ticket(int num):num_ticket(num){}
	virtual ~Ticket(){}
	void add_obs(Observer* obs){
		List_Obs.push_back(obs);
	}
	void remove_obs(Observer* obs){
		list<Observer*>::iterator ite;
		for (ite = List_Obs.begin(); ite != List_Obs.end(); ite++)
		{
			if ((*ite) == obs){
				ite=List_Obs.erase(ite);
				ite--;
				break;
			}
		}
	}
	void Notify(){
		list<Observer*>::iterator ite;
		for (ite = List_Obs.begin(); ite != List_Obs.end(); ite++)
		{
						
			(*ite)->update();
		}
		

	}
	int GetNum(){
		return this->num_ticket;
	}
	void SetNum(int num){
		this->num_ticket = num;
	}
	void SellATicket(){
   
		this->num_ticket--;
			  
	}
	
private:
	list<Observer*> List_Obs;
	int num_ticket;

};

class Buyer :public Observer{
private:
	string buyer_name;
	Ticket* ticket;
	
public:

	Buyer(string m_name, Ticket* m_ticket):buyer_name(m_name), ticket(m_ticket){}
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
		cout<<this->buyer_name<<"-------" << "当前余票为：" << get_ticket_num << endl;
	}
};


int main()
{
	Ticket* sh_ticket = new Ticket(5);
	Buyer* buyer_one = new Buyer("Tom", sh_ticket);
	Buyer* buyer_two = new Buyer("Json", sh_ticket);
	Buyer* buyer_three = new Buyer("Amy", sh_ticket);
	sh_ticket->add_obs(buyer_one);
	sh_ticket->add_obs(buyer_two);
	sh_ticket->add_obs(buyer_three);
	buyer_one->BuyATicket();
	
	sh_ticket->remove_obs(buyer_two);
	
	sh_ticket->Notify();
	
	system("PAUSE");
	return 0;
}