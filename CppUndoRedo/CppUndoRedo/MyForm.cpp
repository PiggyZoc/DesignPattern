#include "MyForm.h"
using namespace Project1;
[STAThread]
int main(){
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
	return 0;
}
