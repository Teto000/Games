//===================================
//
// ゲームの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <time.h>
#include "game.h"
#include "renderer.h"
#include "application.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "bg.h"
#include "skill.h"
#include "timer.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CPlayer	  *CGame::m_pPlayer = nullptr;		//プレイヤー
CEnemy	  *CGame::m_pEnemy = nullptr;		//敵
CScore	  *CGame::m_pScore = nullptr;		//スコア
CBg		  *CGame::m_pBG[nMaxBg] = {};		//背景
CSkill	  *CGame::m_pSkill[nMaxSkill] = {};	//スキル
CTimer	  *CGame::m_pTimer;					//タイマー
CGame::MODE CGame::m_mode = MODE_MAX;		//モード

//===========================
// コンストラクタ
//===========================
CGame::CGame()
{
	m_EnemyCnt = 0;
	m_nTime = 0;
	m_nSkillTime[nMaxSkill] = {};
	m_bSkill[nMaxSkill] = {};
}

//===========================
// デストラクタ
//===========================
CGame::~CGame()
{

}

//===========================
// 初期化
//===========================
HRESULT CGame::Init()
{
	//時刻をもとにしたランダムな値を生成
	srand((unsigned int)time(NULL));

	//メンバ変数の初期化
	for (int i = 0; i < nMaxSkill; i++)
	{
		m_bSkill[i] = false;
		m_nSkillTime[i] = 0;
	}

	//背景の生成
	{
		D3DXVECTOR3 bgPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		D3DXVECTOR3 timePos(950.0f, 70.0f, 0.0f);
		D3DXVECTOR3 scorePos(1170.0f, 70.0f, 0.0f);

		m_pBG[0] = CBg::Create(bgPos, CBg::BGTYPE_GAME);
		m_pBG[1] = CBg::Create(timePos, CBg::BGTYPE_GAME_TIME);
		m_pBG[2] = CBg::Create(scorePos, CBg::BGTYPE_GAME_SCORE);
	}

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	//スコアの生成
	m_pScore = CScore::Create(CScore::MODE_GAME);

	//タイマーの生成
	m_pTimer = CTimer::Create(CTimer::MODE_GAME);

	m_pSkill[0] = CSkill::Create(CSkill::SKILLTYPE_HEAL);
	m_pSkill[1] = CSkill::Create(CSkill::SKILLTYPE_SPEEDUP_FIRE);
	m_pSkill[2] = CSkill::Create(CSkill::SKILLTYPE_ATTACKUP);
	m_pSkill[3] = CSkill::Create(CSkill::SKILLTYPE_SPEEDUP);

	//サウンドの再生
	CSound::PlaySound(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//===========================
// 終了
//===========================
void CGame::Uninit()
{
	//サウンドの停止
	CSound::StopSound(CSound::SOUND_LABEL_GAME);
}

//===========================
// 更新
//===========================
void CGame::Update()
{
	//敵の出現
	AppearEnemy();

	//------------------------
	// スキルの色変更
	//------------------------
	if (m_pPlayer->GetMagic() >= 10)
	{//プレイヤーのMPが10以上なら
		if (CInputKeyboard::Trigger(DIK_U) && !m_bSkill[0])
		{
			m_pSkill[0]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
			m_bSkill[0] = true;
		}
		else if (CInputKeyboard::Trigger(DIK_I) && !m_bSkill[1])
		{
			m_pSkill[1]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
			m_bSkill[1] = true;
		}
		else if (CInputKeyboard::Trigger(DIK_O) && !m_bSkill[2])
		{
			m_pSkill[2]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
			m_bSkill[2] = true;
		}
		else if (CInputKeyboard::Trigger(DIK_P) && !m_bSkill[3])
		{
			m_pSkill[3]->CObject2D::SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
			m_bSkill[3] = true;
		}
	}

	//-------------------------
	// スキル時間のカウント
	//-------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (m_bSkill[i])
		{
			m_nSkillTime[i]++;
		}

		if (m_nSkillTime[i] >= 600)
		{
			//スキルの色を戻す
			m_bSkill[i] = false;
			m_pSkill[i]->CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nSkillTime[i] = 0;
		}
	}

	//-------------------------
	// 時間で終了する処理
	//-------------------------
	if (m_mode == MODE_TIME)
	{//タイムアタックモードなら
		int nTime = m_pTimer->GetTime();

		if (nTime >= 270)
		{//1分が経過したら
			Sleep(300);

			//リザルト画面へ移動
			CApplication::SetMode(CApplication::MODE_RESULT);
		}
	}
}

//===========================
// 敵の出現
//===========================
void CGame::AppearEnemy()
{
	m_nTime++;

	if (m_nTime == nOneSecond * 1)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 4)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 5)
	{
		SetEnemy(1300.0f, 600.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 7)
	{
		SetEnemy(1300.0f, 450.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 10)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 300.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 13)
	{
		SetEnemy(1300.0f, 200.0f, HORMING);
	}
	else if (m_nTime == nOneSecond * 18)
	{
		SetEnemy(1300.0f, 300.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 23)
	{
		SetEnemy(1300.0f, 400.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 28)
	{
		SetEnemy(1300.0f, 300.0f, NORMAL);
		SetEnemy(1300.0f, 500.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 31)
	{
		SetEnemy(1300.0f, 500.0f, BIG);
		SetEnemy(1300.0f, 250.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 36)
	{
		SetEnemy(1300.0f, 250.0f, HPITEM);
	}
	else if (m_nTime == nOneSecond * 41)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 300.0f, NORMAL);
		SetEnemy(1300.0f, 500.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 43)
	{
		SetEnemy(1300.0f, 250.0f, HORMING);
	}
	else if (m_nTime == nOneSecond * 44)
	{
		SetEnemy(1300.0f, 250.0f, MPITEM);
	}
	else if (m_nTime == nOneSecond * 48)
	{
		SetEnemy(1300.0f, 400.0f, BIG);
	}
	else if (m_nTime == nOneSecond * 50)
	{
		SetEnemy(1300.0f, 200.0f, NORMAL);
		SetEnemy(1300.0f, 600.0f, NORMAL);
	}
	else if (m_nTime == nOneSecond * 52)
	{
		SetEnemy(1300.0f, 300.0f, HORMING);
		SetEnemy(1300.0f, 500.0f, HORMING);
	}

	else if (m_nTime == nOneSecond * 55)
	{
		m_nTime = 0;
		CEnemy::AddLevel();
	}
}

//===========================
// 敵の生成
//===========================
void CGame::SetEnemy(float X, float Y, EnemyName type)
{
	switch (type)
	{
	case NORMAL:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_NORMAL);
		break;

	case HORMING:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_HORMING);
		break;

	case HPITEM:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_HPITEM);
		break;

	case MPITEM:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_MPITEM);
		break;

	case BIG:
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(X, Y, 0.0f), CEnemy::ENEMYTYPE_BIG);
		break;

	default:
		break;
	}
}

//===========================
// モード設定
//===========================
void CGame::SetMode(CApplication::GAMEMODE mode)
{
	switch (mode)
	{
	case CApplication::GAMEMODE_TIME:
		m_mode = CGame::MODE_TIME;
		break;

	case CApplication::GAMEMODE_SCORE:
		m_mode = CGame::MODE_SCORE;
		break;

	case CApplication::GAMEMODE_MAX:
		break;

	default:
		break;
	}
}

//===========================
// モードの設定
//===========================
void CGame::SetMode(CGame::MODE mode)
{
	m_mode = mode;
}

//===========================
// プレイヤーの取得
//===========================
CPlayer *CGame::GetPlayer()
{
	return m_pPlayer;
}

//===========================
// スコアの取得
//===========================
CScore *CGame::GetScore()
{
	return m_pScore;
}

//===========================
// 背景の取得
//===========================
CBg *CGame::GetBG()
{
	return m_pBG[0];
}

//===========================
// タイマーの取得
//===========================
CTimer *CGame::GetTimer()
{
	return m_pTimer;
}