#pragma once

#include "stdafx.h"

class CAnimationCtrl
{
public:
	CAnimationCtrl(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXANIMATIONCONTROLLER	pAniCtrl);
	~CAnimationCtrl();

public:
	HRESULT Init_AnimationCtrl(void);
	void Set_AnimationSet(const unsigned int& iIndex);
	void Play_AnimationSet(const float& fTimeDelta);
private:
	LPDIRECT3DDEVICE9			m_pGraphicDev = nullptr;
	LPD3DXANIMATIONCONTROLLER	m_pAniCtrl = nullptr;
private:
	unsigned int						m_iCurrentTrack = 0;
	unsigned int						m_iNewTrack = 1;
	unsigned int						m_iCurrentIdx = 0;
	double								m_TimeDeltaAcc = 0.0;
};

