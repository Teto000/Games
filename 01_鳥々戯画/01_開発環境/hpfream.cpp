//===================================
//
// HPフレームの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "hpfream.h"
#include "main.h"
#include "object2D.h"
#include "application.h"

//===========================
// コンストラクタ
//===========================
CHpFream::CHpFream() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
}

//===========================
// デストラクタ
//===========================
CHpFream::~CHpFream()
{
}

//===========================
// 初期化
//===========================
HRESULT CHpFream::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_HPFREAM);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CHpFream::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CHpFream::Update()
{
	CObject2D::Update();

	//-------------------
	// 移動
	//-------------------
	m_pos = CObject2D::AddMove(m_move);
}

//===========================
// 描画
//===========================
void CHpFream::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CHpFream *CHpFream::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CHpFream *pHpFream = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pHpFream = new CHpFream;	//生成

	if (pHpFream != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pHpFream->m_fWidth = fWidth;
		pHpFream->m_fHeight = fHeight;

		//初期化
		pHpFream->Init(pos);
		pHpFream->SetObjType(OBJTYPE_HP);
	}

	return pHpFream;
}

//===========================
// 移動量の設定
//===========================
void CHpFream::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}