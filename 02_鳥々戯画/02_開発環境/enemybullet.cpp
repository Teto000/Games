//===================================
//
// 弾の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "enemybullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "application.h"
#include "damage.h"
#include "enemy.h"
#include "player.h"
#include "game.h"

//===========================
// コンストラクタ
//===========================
CEnemyBullet::CEnemyBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転
	m_nEnemyAttack = 0;			//敵の攻撃力
	m_nLife = 0;				//寿命
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
}

//===========================
// デストラクタ
//===========================
CEnemyBullet::~CEnemyBullet()
{

}

//===========================
// 初期化
//===========================
HRESULT CEnemyBullet::Init(D3DXVECTOR3 pos)
{
	//----------------------------
	// メンバ変数の初期化
	//----------------------------
	m_pos = pos;
	m_fWidth = 60.0f;
	m_fHeight = 20.0f;
	m_nLife = 300;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);			//サイズの設定
	CObject2D::SetTexture(CTexture::TEXTURE_ENEMYBULLET);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CEnemyBullet::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CEnemyBullet::Update()
{
	CObject2D::Update();

	m_nLife--;

	//移動量の加算
	m_pos = CObject2D::AddMove(m_move);

	//画面外に出たら
	if (CObject2D::OutScreen(m_pos))
	{
		Uninit();
		return;
	}

	if (CGame::GetPlayer()->GetState() != CPlayer::PLAYERSTATE_INVINCIBLE)
	{//プレイヤーが無敵状態じゃないなら
		//当たった処理
		CollisionEnemyBullet();
	}
}

//===========================
// 描画
//===========================
void CEnemyBullet::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CEnemyBullet *CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nAttack)
{
	CEnemyBullet *pBullet = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBullet = new CEnemyBullet;	//生成

	if (pBullet != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pBullet->m_move = move;				//移動量の代入
		pBullet->m_nEnemyAttack = nAttack;	//攻撃力の代入

		//初期化
		pBullet->Init(pos);
		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//===========================
// 当たった処理
//===========================
void CEnemyBullet::CollisionEnemyBullet()
{
	CObject* pHitObject = CObject2D::GetCollision(OBJTYPE_PLAYER);

	if (pHitObject != nullptr)
	{//プレイヤーと当たった

		//pObjectをCPlayer型にダウンキャスト
		CPlayer* pPlayer = (CPlayer*)pHitObject;

		pPlayer->AddLife(-m_nEnemyAttack);	//敵の体力の減少

		//弾の消滅
		Uninit();
		return;
	}
}