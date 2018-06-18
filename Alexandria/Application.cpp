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
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_fNowTime = GetTickCount();
			m_fDeltaTime = (m_fNowTime - m_fPrevTime) / 1000.f;

			m_fPrevTime = m_fNowTime;
		}
	}

	return true;
}

bool Application::_CreateWindow(wchar_t * title, int width, int height, bool windowed)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = title;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	
	if (RegisterClass(&wc) == false)
		return false;
	
	DWORD Style;
	if (windowed)
		Style = WS_POPUP;
	else
		Style = WS_POPUP | WS_EX_TOPMOST;

	m_hWnd = CreateWindow(title, title, Style, 0, 0, width, height, NULL, NULL, NULL, NULL);

	if (m_hWnd == nullptr)
		return false;

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);

	return true;
}

bool Application::_CreateRenderer()
{
	if (Renderer::GetInstance()->Init() == false)
		return false;

	return true;
}

LRESULT Application::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}