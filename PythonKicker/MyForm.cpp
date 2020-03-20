#include "MyForm.h"

using namespace PythonKicker;

[STAThreadAttribute]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application::Run(gcnew MyForm());
	return 0;
}

