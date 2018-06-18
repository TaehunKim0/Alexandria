#include"stdafx.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
#ifdef _DEBUG
	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "wt", stdout);
#endif 
	Application* App = Application::GetInstance();
	App->Init(L"Alexandria", 1280, 720, 1);
	App->Run();

	App->Release();
#ifdef _DEBUG
	FreeConsole();

#endif 
	return 0;
}