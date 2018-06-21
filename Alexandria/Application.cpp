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
	Release();
}

bool Application::Init(std::wstring title, int width, int height, bool windowed)
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
	Renderer::GetInstance()->Release();
	ObjectManager::GetInstance()->Release();

	printf("¸±¸®Áî µÊ");
	return true;
}

#include"ForestScene.h"
bool Application::Run()
{
	auto scene = new ForestScene();
	scene->Init();
	SceneManager::GetInstance()->SetScene(scene);

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

			Input::GetInstance()->Update();

			Renderer::GetInstance()->Begin();

			SceneManager::GetInstance()->Update(m_fDeltaTime);
			SceneManager::GetInstance()->Render();

			Renderer::GetInstance()->End();
		}
	}

	return true;
}

bool Application::_CreateWindow(std::wstring title, int width, int height, bool windowed)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = title.c_str();
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	
	if (RegisterClass(&wc) == false)
		return false;
	
	DWORD Style;
	if (windowed)
		Style = WS_POPUP;
	else
		Style = WS_POPUP | WS_EX_TOPMOST;

	m_hWnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, NULL, NULL);

	if (m_hWnd == nullptr)
		return false;


	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

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
		PostQuitMessage(0);
		Application::GetInstance()->Release();
		FreeConsole();
		break;

	case WM_RBUTTONDOWN:
		Input::GetInstance()->ButtonDown(true);
		break;

	case WM_RBUTTONUP:
		Input::GetInstance()->ButtonDown(false);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
