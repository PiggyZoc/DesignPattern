#include<iostream>
#include<cstdlib>
#include<stack>
#include<string>
using namespace std;

class Command
{
public:
	
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
	Manager(InputCmd* inputcmd){
		undo_stack.push(inputcmd);
	}

private:
	stack<Command*> undo_stack;
	stack<Command*> redo_stack;
	
};
int main()
{
	InputCmd* in = new InputCmd("ggg");
	in->execute();
	system("PAUSE");
	return 0;
}