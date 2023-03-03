//===================================
//
// ゲームモードの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "gamemode.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"
#include "bg.h"

//===========================
// コンストラクタ
//===========================
CGameMode::CGameMode() : CObject(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_mode = GAMEMODE_MAX;	//モード
	m_pBg = nullptr;
}

//===========================
// デストラクタ
//===========================
CGameMode::~CGameMode()
{

}

//===========================
// 初期化
//===========================
HRESULT CGameMode::Init(D3DXVECTOR3 pos)
{
	//------------------
	// 構造体の初期化
	//------------------
	m_pos = pos;
	m_fWidth = 500.0f;
	m_fHeight = 100.0f;

	if (m_pObject2D != nullptr)
	{
		switch (m_mode)
		{
		case GAMEMODE_TIME:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_TIME);
			break;

		case GAMEMODE_SCORE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_SCORE);
			break;

		case GAMEMODE_TUTORIAL:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TITLE_TUTORIAL);
			break;

		default:
			break;
		}

		m_pObject2D->Init(m_pos);

		m_pObject2D->SetSize(m_fWidth, m_fHeight);	//サイズの設定
	}

	//---------------------
	// 背景の生成
	//---------------------
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), CBg::BGTYPE_SELECTMODE);

	return S_OK;
}

//===========================
// 終了
//===========================
void CGameMode::Uninit()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}

//===========================
// 更新
//===========================
void CGameMode::Update()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Update();
	}
}

//===========================
// 描画
//===========================
void CGameMode::Draw()
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Draw();
	}
}

//===========================
// 生成
//===========================
CGameMode *CGameMode::Create(D3DXVECTOR3 pos, GAMEMODE mode)
{
	CGameMode *pGameMode = nullptr;

	//----------------------------------
	// ゲームモードの生成と初期化
	//----------------------------------
	pGameMode = new CGameMode;	//生成
	pGameMode->m_pObject2D = new CObject2D(1);

	if (pGameMode != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pGameMode->m_mode = mode;

		//初期化
		pGameMode->Init(pos);
		pGameMode->SetObjType(OBJTYPE_BG);
	}

	return pGameMode;
}

//===========================
// 位置の取得
//===========================
D3DXVECTOR3 CGameMode::GetPosition()
{
	return m_pos;
}

//===========================
// 幅の取得
//===========================
float CGameMode::GetWidth()
{
	return m_fWidth;
}

//===========================
// 高さの取得
//===========================
float CGameMode::GetHeight()
{
	return m_fHeight;
}

//===========================
// オブジェクトの取得
//===========================
CObject2D* CGameMode::GetObject2D()
{
	return m_pObject2D;
}