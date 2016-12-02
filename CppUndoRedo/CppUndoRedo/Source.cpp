#include<iostream>
#include<cstdlib>
#include<stack>
#include<string>
using namespace std;

class Command
{
public:
	Command(){}
	~Command(){}
	virtual void execute(){}

};

class InputCmd:public Command
{
private:
	string current_str;
	
public:
	InputCmd(string str) :current_str(str){}
	~InputCmd(){}
	void execute(){
		cout << "The current content is " << this->current_str << endl;
	}
};
class Manager
{
public:
	Manager(Command* cmd){
		this->index++;
		this->cmds[NumOfCmds] = cmd;
		this->NumOfCmds++;
		this->cmds[index]->execute();
	}
	Manager(){}
	~Manager(){}
	void addCmd(Command* cmd){
		this->index++;
		this->cmds[NumOfCmds] = cmd;
		this->NumOfCmds++;
		this->cmds[index]->execute();
	}
	void Undo(){
		if (this->NumOfCmds < 2||this->index<1)
		{
			cout << "Undo Failed!" << endl;
		    return;
		}

		this->index--;
		this->cmds[index]->execute();
		cout << "Undo Successful!" << endl;
	}
	void Redo(){
		if (this->index==this->NumOfCmds-1)
		{
			cout << "Redo Failed!" << endl;
			return;
		}

		this->index++;
		this->cmds[index]->execute();
		cout << "Redo Successful!" << endl;
	}
private:
	Command* cmds[1024];
	int index = -1;
	int NumOfCmds = 0;
	
};

int main()
{
//	InputCmd* input = new InputCmd("ggg");
//	input->execute();
	Manager* mgr = new Manager(new InputCmd("ggg"));
	mgr->addCmd(new InputCmd("hhh"));
	mgr->addCmd(new InputCmd("iii"));
	mgr->addCmd(new InputCmd("jjj"));
	mgr->addCmd(new InputCmd("kkk"));
	mgr->addCmd(new InputCmd("mmm"));
	cout << endl;
	mgr->Undo();
	mgr->Redo();
	mgr->Redo();



	
	system("PAUSE");
	return 0;
}