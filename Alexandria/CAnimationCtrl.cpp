#include "stdafx.h"
#include "CAnimationCtrl.h"


CAnimationCtrl::CAnimationCtrl(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pGraphicDev(pGraphicDev)
	, m_pAniCtrl(pAniCtrl)
	, m_iCurrentTrack(0)
	, m_iNewTrack(1)
{
	m_pAniCtrl->AddRef();
	m_pGraphicDev->AddRef();
}

CAnimationCtrl::~CAnimationCtrl()
{
}

HRESULT CAnimationCtrl::Init_AnimationCtrl(void)
{
	return E_NOTIMPL;
}

void CAnimationCtrl::Set_AnimationSet(const unsigned int & iIndex)
{
	if (m_iCurrentIdx == iIndex)
		return;

	if (nullptr == m_pAniCtrl)
		return;

	LPD3DXANIMATIONSET			pAniSet = nullptr;

	if (FAILED(m_pAniCtrl->GetAnimationSet(iIndex, &pAniSet)))
		return;

	double Period = pAniSet->GetPeriod();

	D3DXTRACK_DESC			Track_Desc;
	m_pAniCtrl->GetTrackDesc(m_iCurrentTrack, &Track_Desc);


	D3DXTRACK_DESC		TrackDesc;

	m_iNewTrack = m_iCurrentTrack == 0 ? 1 : 0;

	m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAniSet);

	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	m_pAniCtrl->KeyTrackEnable(m_iCurrentTrack, FALSE, m_TimeDeltaAcc + 0.25);
	m_pAniCtrl->KeyTrackSpeed(m_iCurrentTrack, 1.0f, m_TimeDeltaAcc, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_TimeDeltaAcc, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.0f, m_TimeDeltaAcc, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_TimeDeltaAcc, 0.25, D3DXTRANSITION_LINEAR);

	m_iCurrentTrack = m_iNewTrack;

	m_pAniCtrl->SetTrackPosition(m_iCurrentTrack, 0.0);

	m_pAniCtrl->ResetTime();

	m_TimeDeltaAcc = 0.f;

	m_iCurrentIdx = iIndex;
}

void CAnimationCtrl::Play_AnimationSet(const float & fTimeDelta)
{
	if (nullptr == m_pAniCtrl)
		return;

	m_TimeDeltaAcc += fTimeDelta;

	m_pAniCtrl->AdvanceTime(fTimeDelta, nullptr);
}
