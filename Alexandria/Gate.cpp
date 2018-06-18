#include"stdafx.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
#ifdef _DEBUG
	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "wt", stdout);
#endif 


#ifdef _DEBUG
	FreeConsole();

#endif 
	return 0;
}