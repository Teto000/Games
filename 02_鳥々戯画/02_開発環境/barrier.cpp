//===================================
//
// バリアの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "barrier.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "game.h"
#include "bullet.h"
#include "player.h"

//===========================
// コンストラクタ
//===========================
CBarrier::CBarrier() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_playermove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//プレイヤーの移動量
	m_nLife = 0;		//体力
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//===========================
// デストラクタ
//===========================
CBarrier::~CBarrier()
{

}

//===========================
// 初期化
//===========================
HRESULT CBarrier::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;	//位置
	m_nLife = 100;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色の設定

	CObject2D::SetTexture(CTexture::TEXTURE_BARRIER);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CBarrier::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CBarrier::Update()
{
	CObject2D::Update();

	switch (m_type)
	{
	case BARRIERTYPE_PLAYER:
		//プレイヤーの速度を取得
		m_playermove = CGame::GetPlayer()->GetMove();
		m_pos = CObject2D::AddMove(m_playermove);
		break;

	case BARRIERTYPE_ENEMY:
		m_pos = CObject2D::AddMove(m_move);
		break;
	}

	//体力が尽きた
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//===========================
// 描画
//===========================
void CBarrier::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CBarrier *CBarrier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
							float fWidth, float fHeight, BARRIERTYPE type)
{
	CBarrier *pBarrier = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pBarrier = new CBarrier;	//生成

	if (pBarrier != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pBarrier->m_move = move;				//移動量
		pBarrier->m_fWidth = fWidth + 30.0f;	//幅
		pBarrier->m_fHeight = fHeight + 30.0f;	//高さ
		pBarrier->m_type = type;				//種類

		//初期化
		pBarrier->Init(pos);
		pBarrier->SetObjType(OBJTYPE_BARRIER);
	}

	return pBarrier;
}

//===========================
// 体力の減少
//===========================
void CBarrier::SubLife(CBullet::BULLETTYPE type)
{
	switch (type)
	{
	//チャージショット
	case CBullet::BULLETTYPE_HORMING:
		m_nLife = 0;
		break;

	default:
		m_nLife -= 10;
		break;
	}
}

//===========================
// 種類の取得
//===========================
CBarrier::BARRIERTYPE CBarrier::GetType()
{
	return m_type;
}