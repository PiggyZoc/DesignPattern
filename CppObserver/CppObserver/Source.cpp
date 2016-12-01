
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
		this->Machine = obs;
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
	void NotifyToBuyers()
	{
		
			list<Observer*>::iterator ite;
			for (ite = List_Buyers.begin(); ite != List_Buyers.end();)
			{

				(*ite)->update();
				List_Buyers.erase(ite++);
				cout << endl;
				
			}

		}
	
	void NotifyToMachine(){
		if (this->GetNum() > 0)
			return;
		this->Machine->update();
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
		if (this->GetNum() > 0)
			this->num_ticket--;
		else
		{
			this->NotifyToMachine();
			this->num_ticket--;
		}
	}

private:
	list<Observer*> List_Buyers;

	
	Observer* Machine;
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

			ticket->SellATicket();

	}
	void update(){
		int get_ticket_num = ticket->GetNum();
		cout << "<<<<<<  " << "当前余票为： " << get_ticket_num << "  >>>>>>"<<endl;
		this->BuyATicket();
		cout << this->buyer_name << "已获得  1  张票" << endl;
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
		cout << "机器正在为您取票，请耐心等待。。。\n" << endl;
		Sleep(2000);
		this->ticket->AddATicket();
		cout << "机器已为您产生  1  张票" << endl;

	}

};

int main()
{
	Buyer *Buyers[10];
	
	Ticket* sh_ticket = new Ticket(4);
	for (int i = 0; i < 10; i++)
	{
		string s = "Waiter";
		Buyers[i] = new Buyer(s.append(to_string(i+1)), sh_ticket);
		sh_ticket->add_Buyer(Buyers[i]);
	}
//	sh_ticket->NotifyToBuyers();
	
	Machine machine_one("001", sh_ticket);

	sh_ticket->add_Machine(&machine_one);
	sh_ticket->NotifyToBuyers();

	
	system("PAUSE");
	return 0;
}