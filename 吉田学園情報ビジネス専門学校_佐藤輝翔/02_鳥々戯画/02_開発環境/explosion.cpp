//===================================
//
// 爆発の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "explosion.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "application.h"

//------------------------
// マクロ定義
//------------------------
#define TEX_DIVISION	(8)	//テクスチャの分割数

//------------------------
//静的メンバ変数
//------------------------


//===========================
// コンストラクタ
//===========================
CExplosion::CExplosion() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
	m_nLife = 0;		//寿命
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//===========================
// デストラクタ
//===========================
CExplosion::~CExplosion()
{

}

//===========================
// 初期化
//===========================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	//------------------
	// 構造体の初期化
	//------------------
	m_nLife = 100;
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fWidth = 80.0f;
	m_fHeight = 80.0f;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_HEART);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CExplosion::Update()
{
	CObject2D::Update();

	//--------------------
	// 徐々に透過
	//--------------------
	m_col.a -= 0.05f;
	SetColor(m_col);
	
	//--------------------
	// 寿命
	//--------------------
	//寿命の減少
	m_nLife--;

	//寿命が尽きた
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//===========================
// 描画
//===========================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CExplosion *pExplosion = nullptr;

	//----------------------------------
	// エクスプロージョンの生成と初期化
	//----------------------------------
	pExplosion = new CExplosion;	//生成

	if (pExplosion != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pExplosion->m_fWidth = fWidth;
		pExplosion->m_fHeight = fHeight;

		//初期化
		pExplosion->Init(pos);
		pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	}

	return pExplosion;
}