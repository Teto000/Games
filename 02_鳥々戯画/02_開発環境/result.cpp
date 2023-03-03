//===================================
//
// リザルトの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "result.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"
#include "sound.h"
#include "score.h"
#include "timer.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CBg		*CResult::m_pBG[MaxBg] = {};	//背景
CScore	*CResult::m_pScore = nullptr;	//スコア
CTimer	*CResult::m_pTime = nullptr;	//タイム

//===========================
// コンストラクタ
//===========================
CResult::CResult()
{

}

//===========================
// デストラクタ
//===========================
CResult::~CResult()
{

}

//===========================
// 初期化
//===========================
HRESULT CResult::Init()
{
	//背景の生成
	m_pBG[0]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
						, CBg::BGTYPE_RESULT);

	m_pBG[1]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
						, CBg::BGTYPE_RESULTTEXT);

	//スコアの生成
	m_pScore->Create(CScore::MODE_RESULT);

	//タイムの生成
	m_pTime->Create(CTimer::MODE_RESULT);

	//サウンドの再生
	CSound::PlaySound(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//===========================
// 終了
//===========================
void CResult::Uninit()
{
	//サウンドの停止
	CSound::StopSound(CSound::SOUND_LABEL_RESULT);
}

//===========================
// 更新
//===========================
void CResult::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SEの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		CApplication::SetMode(CApplication::MODE_TITLE);
	}
}

//===========================
// 背景の取得
//===========================
CBg *CResult::GetBG()
{
	return m_pBG[0];
}

//===========================
// スコアの取得
//===========================
CScore *CResult::GetScore()
{
	return m_pScore;
}

//===========================
// タイマーの取得
//===========================
CTimer	*CResult::GetTimer()
{
	return m_pTime;
}