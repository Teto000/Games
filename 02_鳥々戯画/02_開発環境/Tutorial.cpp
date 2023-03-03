//===================================
//
// チュートリアルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "tutorial.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"
#include "sound.h"
#include "gamemode.h"
#include "game.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CBg	*CTutorial::m_pBG[MaxBg] = {};	//背景

//===========================
// コンストラクタ
//===========================
CTutorial::CTutorial()
{
	m_bPressEneter = false;
}

//===========================
// デストラクタ
//===========================
CTutorial::~CTutorial()
{

}

//===========================
// 初期化
//===========================
HRESULT CTutorial::Init()
{
	//背景の生成
	m_pBG[0]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, CBg::BGTYPE_TUTORIAL1);

	//サウンドの再生
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CTutorial::Uninit()
{
	//サウンドの停止
	CSound::StopSound(CSound::SOUND_LABEL_TITLE);
}

//===========================
// 更新
//===========================
void CTutorial::Update()
{
	if (!m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		m_pBG[1]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
			, CBg::BGTYPE_TUTORIAL2);

		m_bPressEneter = true;
	}
	else if(m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_TITLE);
	}
}