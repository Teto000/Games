//===================================
//
// アイテムの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "item.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//===========================
// コンストラクタ
//===========================
CItem::CItem() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	m_nLife = 0;			//体力
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_type = ITEMTYPE_MAX;	//種類
}

//===========================
// デストラクタ
//===========================
CItem::~CItem()
{

}

//===========================
// 初期化
//===========================
HRESULT CItem::Init(D3DXVECTOR3 pos)
{
	//初期値の設定
	m_pos = pos;		//位置
	m_nLife = 150;		//寿命
	m_fWidth = 50.0f;	//幅
	m_fHeight = 50.0f;	//高さ

	CObject2D::Init(m_pos);

	//------------------
	// 設定
	//------------------
	CObject2D::SetSize(m_fWidth, m_fHeight);			//大きさ
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//テクスチャ

	return S_OK;
}

//===========================
// 終了
//===========================
void CItem::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CItem::Update()
{
	CObject2D::Update();

	//-------------------------------
	// 寿命の減少処理
	//-------------------------------
	//寿命の減少
	m_nLife--;

	if (m_nLife <= 0)
	{//寿命が尽きたら
		Uninit();
		return;
	}

	//-------------------------------
	// プレイヤーとの当たり判定
	//-------------------------------
	if (CObject2D::GetCollision(OBJTYPE_PLAYER))
	{
		switch (m_type)
		{
		case ITEMTYPE_HPHEAL:
			//プレイヤーのMPを回復
			CGame::GetPlayer()->AddLife(30);
			Uninit();
			return;
			break;

		case ITEMTYPE_MPHEAL:
			//プレイヤーのMPを回復
			CGame::GetPlayer()->AddMagic(30);
			Uninit();
			return;
			break;

		default:
			break;
		}
	}
}

//===========================
// 描画
//===========================
void CItem::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CItem *CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CItem *pItem = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pItem = new CItem;	//生成

	if (pItem != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pItem->m_type = type;

		//初期化
		pItem->Init(pos);
		pItem->SetObjType(OBJTYPE_ITEM);
	}

	return pItem;
}