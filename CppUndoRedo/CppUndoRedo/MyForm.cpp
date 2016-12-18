#include "MyForm.h"
using namespace Project;
[STAThread]
int main(){
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
	return 0;
}
