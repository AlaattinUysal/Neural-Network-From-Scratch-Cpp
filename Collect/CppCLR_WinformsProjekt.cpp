#include "pch.h"

using namespace System;

//int main(array<System::String ^> ^args)
//{
//    return 0;
//}

#include "Form1.h"
#include "Form_SingleLayer.h"
#include "Form_MultiLayer.h"
#include "Form_MultiLayerMomentum.h"
#include "Form_MNIST.h"
#include "Form_AutoEncoder.h"

using namespace System::Windows::Forms;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsProjekt::Form_MNIST());
	return 0;
}