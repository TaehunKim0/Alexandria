#include "stdafx.h"
#include "Application.h"


Application::Application() :
	m_bWindowed(0)
	, m_fDeltaTime(0.f)
	, m_fNowTime(0.f)
	, m_fPrevTime(0.f)
	, m_hWnd(nullptr)
	, m_iWindowHeight(0)
	, m_iWindowWidth(0)
{
}


Application::~Application()
{
}

bool Application::Init(wchar_t * title, int width, int height, bool windowed)
{
	m_Title = title;
	m_iWindowWidth = width;
	m_iWindowHeight = height;
	m_bWindowed = windowed;


	if (_CreateWindow(title, width, height, windowed) == false)
		return false;

	if (_CreateRenderer() == false)
		return false;

	srand(time(NULL));

	return true;
}

bool Application::Release()
{
	return false;
}

bool Application::Run()
{
	return false;
}

bool Application::_CreateWindow(wchar_t * title, int width, int height, bool windowed)
{
	return false;
}

bool Application::_CreateRenderer()
{
	return false;
}

LRESULT Application::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
