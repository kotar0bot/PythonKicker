#include "MyForm.h"

using namespace PythonKicker;

[STAThreadAttribute]
int main() {
	Application::Run(gcnew MyForm());
	return 0;
}
