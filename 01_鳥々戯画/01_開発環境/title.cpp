//===================================
//
// タイトルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "title.h"
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
CBg		  *CTitle::m_pBG[MaxBg] = {};			//背景
CGameMode *CTitle::m_pGameMode[MaxMode] = {};	//ゲームモード

//===========================
// コンストラクタ
//===========================
CTitle::CTitle()
{
	nCntTime = 0;	//アニメーションカウント
	nNumber = 0;	//選択中の番号
	m_bPressEneter = false;	//エンターキーが押されたか
}

//===========================
// デストラクタ
//===========================
CTitle::~CTitle()
{

}

//===========================
// 初期化
//===========================
HRESULT CTitle::Init()
{
	//背景の生成
	m_pBG[0]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)
					, CBg::BGTYPE_TITLE);

	m_pBG[1]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f)
					, CBg::BGTYPE_TITLE_LOGO);

	m_pBG[2]->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f)
					, CBg::BGTYPE_TITLE_ENTER);

	//サウンドの再生
	CSound::PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CTitle::Uninit()
{
	//サウンドの停止
	CSound::StopSound(CSound::SOUND_LABEL_TITLE);
}

//===========================
// 更新
//===========================
void CTitle::Update()
{
	if (!m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SEの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		{
			D3DXVECTOR3 timePos(SCREEN_WIDTH / 2, 250.0f, 0.0f);
			D3DXVECTOR3 scorePos(SCREEN_WIDTH / 2, 400.0f, 0.0f);
			D3DXVECTOR3 tutorialPos(SCREEN_WIDTH / 2, 550.0f, 0.0f);

			m_pGameMode[0] = CGameMode::Create(timePos, CGameMode::GAMEMODE_TIME);
			m_pGameMode[1] = CGameMode::Create(scorePos, CGameMode::GAMEMODE_SCORE);
			m_pGameMode[2] = CGameMode::Create(tutorialPos, CGameMode::GAMEMODE_TUTORIAL);
		}

		m_bPressEneter = true;
	}
	//ゲーム画面に移行
	else if (m_bPressEneter && CInputKeyboard::Trigger(DIK_RETURN))
	{
		//SEの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_BUTTOM);

		if (nNumber == 0)
		{
			CGame::SetMode(CGame::MODE_TIME);
			CApplication::SetMode(CApplication::MODE_GAME);
			return;
		}
		else if (nNumber == 1)
		{
			CGame::SetMode(CGame::MODE_SCORE);
			CApplication::SetMode(CApplication::MODE_GAME);
			return;
		}
		else if (nNumber == 2)
		{
			CApplication::SetMode(CApplication::MODE_TUTORIAL);
			return;
		}
	}

	//モード選択処理
	if (m_bPressEneter)
	{
		SelectMode();
	}
}

//===========================
// モード選択処理
//===========================
void CTitle::SelectMode()
{
	if (m_pGameMode[nNumber])
	{
		nCntTime++;
		nCntTime %= AnimationTime;

		if (nCntTime < 40)
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		}
	}

	//選択番号切り替え処理
	ChangeNumber();
}

//===========================
// 選択番号切り替え処理
//===========================
void CTitle::ChangeNumber()
{
	if (nNumber == 0)
	{
		if (CInputKeyboard::Trigger(DIK_W))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			nNumber = 2;
		}
		else if (CInputKeyboard::Trigger(DIK_S))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber++;
		}
	}
	else if (nNumber == 1)
	{
		if (CInputKeyboard::Trigger(DIK_W))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber--;
		}
		else if (CInputKeyboard::Trigger(DIK_S))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber++;
		}
	}
	else if (nNumber == 2)
	{
		if (CInputKeyboard::Trigger(DIK_W))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber--;
		}
		else if (CInputKeyboard::Trigger(DIK_S))
		{
			m_pGameMode[nNumber]->GetObject2D()->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			nNumber = 0;
		}
	}
}

//===========================
// 背景の取得
//===========================
CBg *CTitle::GetBG()
{
	return m_pBG[0];
}