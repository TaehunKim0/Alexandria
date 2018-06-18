#pragma once
class Application : public Singleton<Application>
{
private:
	HWND m_hWnd;

	std::wstring m_Title;

	int m_iWindowWidth;
	int m_iWindowHeight;

	bool m_bWindowed;

private:
	float m_fPrevTime;
	float m_fNowTime;

	float m_fDeltaTime;

public:
	Application();
	virtual ~Application();

public:
	bool Init(std::wstring title, int width, int height, bool windowed);
	bool Release();
	bool Run();

private:
	bool _CreateWindow(std::wstring title, int width, int height, bool windowed);
	bool _CreateRenderer();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

public:
	inline int GetWindowWidth() {
		return m_iWindowWidth;
	}
	inline int GetWindowHeight() {
		return m_iWindowHeight;
	}
	inline float GetDeltaTime() {
		return m_fDeltaTime;
	}
	inline HWND GetHandle() {
		return m_hWnd;
	}
	inline std::wstring GetTile() {
		return m_Title;
	}
	inline bool GetWindowed() {
		return m_bWindowed;
	}

};

