#include "stdafx.h"
#include "Input.h"


Input::Input()
{
	ZeroMemory(m_PrevKeyState, sizeof(m_PrevKeyState));
	ZeroMemory(m_NowKeyState, sizeof(m_NowKeyState));

	m_bRButtonDown = false;
}

Input::~Input()
{
}

void Input::ButtonDown(bool down)
{
	m_bRButtonDown = down;
}

void Input::Update()
{
	m_vDeltaMove = D3DXVECTOR2(0.f, 0.f);

	UpdateKeyState();
	UpdateMouseState();
}

KeyState Input::GetKeyState(int key)
{
	m_bPrevState = m_PrevKeyState[key];
	m_bNowState = m_NowKeyState[key];

	if (m_bPrevState == false && m_bNowState == true)
	{
		return KeyState::Down;
	}

	else if (m_bPrevState == true && m_bNowState == true)
	{
		return KeyState::Pressed;
	}

	else if (m_bPrevState == true && m_bNowState == false)
	{
		return KeyState::Up;
	}

	return KeyState::None;
}

KeyState Input::GetMouseState(int button)
{
	return GetKeyState(button);
}

void Input::UpdateKeyState()
{
	for (int i = 0; i < 256; i++)
	{
		m_PrevKeyState[i] = m_NowKeyState[i];
		m_NowKeyState[i] = static_cast<bool>(::GetKeyState(i) & 0x8000);
	}
}

void Input::UpdateMouseState()
{
	POINT point;
	GetCursorPos(&point); // 마우스 위치 가져옴

	m_vDeltaMove.x = m_vMousePosition.x - (float)(point.x);
	m_vDeltaMove.y = m_vMousePosition.y - (float)(point.y);

	m_vMousePosition = { (float)(point.x), (float)(point.y) };
}