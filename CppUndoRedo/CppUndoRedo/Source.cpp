#include<iostream>
#include<cstdlib>
#include<stack>
#include<string>
using namespace std;

static string editable;

class Command
{
public:
	bool hasBeenDone;
	Command(){
		this->previous_state = editable;
	}
	~Command(){}
	
	virtual void Execute(){}
    void Unexecute(){
		editable = this->previous_state;
		cout << "The current content is " << editable << endl;
	}
	string previous_state;
};

class InputCmd:public Command
{
private:
	string current_str;
	
public:
	InputCmd(string str) :current_str(str){
		previous_state = editable;
	}
	~InputCmd(){}
	void Execute(){
		editable = this->current_str;
		cout << "The current content is " << editable << endl;
	}
	
};
class AssignCmd :public Command
{
private:
	string assigned_str;
public:
	AssignCmd(string str) :assigned_str(str){}
	~AssignCmd(){}
	void Execute(){
		editable = editable + this->assigned_str;
		cout << "The current content is " << editable << endl;
	}
};

class ModifyCmd :public Command{
private:
	int pos;
	char c;
public:
	ModifyCmd(int pos, char c) :pos(pos), c(c){}
	~ModifyCmd(){}
	void Execute(){
		editable[pos] = c;
		cout << "The current content is " << editable << endl;
	}
};
class DeleteCmd :public Command{
public:
	DeleteCmd(){}
	void Execute(){
		int length = editable.size();
		editable = editable.erase(length - 1);
		cout << "The current content is " << editable << endl;
	}
};
class Manager
{
public:
	Manager(Command* cmd){
		this->index++;
		this->cmds[NumOfCmds] = cmd;
		this->NumOfCmds++;
		this->cmds[index]->Execute();
		
	}
	Manager(){}
	~Manager(){}
	bool addCmd(Command* cmd){
		if (!inProgress)
		{
			cout << "Cannot add a cmd！" << endl;
			return false;
		}
		else
		{
			for (int i = index + 1; i < NumOfCmds; i++)
				delete(this->cmds[i]);
			this->index++;
			this->cmds[index] = cmd;
			this->cmds[index]->Execute();
			this->NumOfCmds = index + 1;
			return true;
		}
		

	}
	bool Undo(){
		if (!inProgress)
		{
			cout << "Undo Failed!" << endl;
			return false;
		}
		else{
			if (this->NumOfCmds < 2 || this->index < 1)
			{
				cout << "Undo Failed!" << endl;
				return false;
			}

			this->cmds[index]->Unexecute();
			this->index--;
			
			cout << "Undo Successful!" << endl;
			return true;
		}
	}
	bool Redo(){
		if (!inProgress)
		{
			cout << "Redo Failed!" << endl;
			return false;
		}
		else
		{
			if (this->index == this->NumOfCmds - 1)
			{
				cout << "Redo Failed!" << endl;
				return false;
			}

			this->index++;
			this->cmds[index]->Execute();
			cout << "Redo Successful!" << endl;
			return true;
		}
		
	}
	bool end(){
		if (inProgress){
			for (int i = index + 1; i < NumOfCmds; i++)
				delete(this->cmds[i]);
			this->inProgress = false;
			return true;
		}
		return true;
	}
	int getIndex(){
		return this->index;
	}
	int getNumOfCmds(){
		return this->NumOfCmds;
	}
private:
	Command* cmds[1024];
	int index = -1;
	int NumOfCmds = 0;
	bool inProgress=true;
	
};

int main()
{

	cout << "##           电网造价模拟系统           ##" << endl;
	cout << "==========================================" << endl;
	cout << "##           A.Input/Revise           ##" << endl;
	cout << "##           B.Assign                 ##" << endl;
	cout << "##           C.Modify                 ##" << endl;
	cout << "##           D.Undo                   ##" << endl;
	cout << "##           E.Redo                   ##" << endl;
	cout << "##           F.Exit                   ##" << endl;
	cout << "==========================================" << endl;

	//Graph<char,int> MIN;

	
	Manager* mgr = new Manager();


	char in;
	cout << "选择您要进行的操作：";
	while (cin >> in)
	{
		if (in == 'F') {

			cout << "谢谢使用！！\n" << endl;
			break;
		}

		switch (in)
		{
		case 'A':
		{
			string s;
			cout << "请输入要内容：" << endl;
			
			cin >> s;
			mgr->addCmd(new InputCmd(s));

			break;

		};
		case 'B':
		{
			string s;
			cout << "请输入要追加的内容：" << endl;
			cin >> s;
			mgr->addCmd(new AssignCmd(s));
			break;

		};
		case 'C':
		{
			char c;
			int pos;
			cout << "请输入要替换的位置：" << endl;
			cin >> pos;
			cout << "请输入要替换的字符：" << endl;
			cin >> c;
			mgr->addCmd(new ModifyCmd(pos - 1, c));
			
			break;
		};
		case 'D':
		{
			mgr->Undo();		
			break;

		};
		case 'E':
		{
			mgr->Redo();
			break;
		}
		case 'Q':
		{
			mgr->addCmd(new DeleteCmd());
			break;
		}
		default:
		{
			cout << "PLEASE INPUT AGAIN!!" << endl;
			break;
		};


		}

		cout << "选择您要进行的操作：";
	}
	system("pause");
	return 0;
}