//===================================
//
// 弾の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "bullet.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "explosion.h"
#include "damage.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "barrier.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CBullet::fBulletSpeed = 10.0f;			//弾の速度
const float CBullet::fBulletSpeed_Homing = 1.05f;	//弾の速度(ホーミング)
const float CBullet::nDefaultSize = 30.0f;			//弾の基本の大きさ

int CBullet::m_nChageTime;	//弾のチャージ時間
int CBullet::m_nCntHorming;	

//===========================
// コンストラクタ
//===========================
CBullet::CBullet() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//位置
	m_Tirget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目標
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転
	m_nLife = 0;				//寿命
	m_nPlayerAttack = 0;		//プレイヤーの攻撃力
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_type = BULLETTYPE_MAX;	//種類
	pExplosion = nullptr;		//爆発
	pDamage = nullptr;			//ダメージ
}

//===========================
// デストラクタ
//===========================
CBullet::~CBullet()
{

}

//===========================
// 初期化
//===========================
HRESULT CBullet::Init(D3DXVECTOR3 pos)
{
	//----------------------------
	// メンバ変数の初期化
	//----------------------------
	m_pos = pos;
	m_nLife = nDefaultLife;
	m_fWidth = nDefaultSize;
	m_fHeight = nDefaultSize;

	CObject2D::Init(m_pos);

	//----------------------------
	// 種類別の情報の設定
	//----------------------------
	if (m_type == BULLETTYPE_CHARGE)
	{//チャージショットなら
		m_fWidth *= 3.0f;
		m_fHeight *= 3.0f;
	}
	else if (m_type == BULLETTYPE_HORMING)
	{//ホーミング弾なら
		m_nLife *= 2;
	}
	else if (m_type == BULLETTYPE_OPTION)
	{
		m_fWidth *= 0.7f;
		m_fHeight *= 0.7f;
	}

	CObject2D::SetSize(m_fWidth, m_fHeight);			//サイズの設定
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CBullet::Update()
{
	CObject2D::Update();

	switch (m_type)
	{
	//----------------------
	// ホーミング弾なら
	//----------------------
	case BULLETTYPE_HORMING:
		m_Tirget = CObject2D::GetTargetPos();	//敵の位置の取得

		if (m_Tirget.x == 0.0f, m_Tirget.y == 0.0f)
		{//ターゲットが消えたら
			//横に向かって飛ぶ
			m_Tirget = D3DXVECTOR3(1280.0f, m_pos.y, 0.0f);
		}
		
		if (m_nLife <= 150)
		{//ホーミング弾の寿命が150以下なら
			//敵に向かってホーミング
			D3DXVECTOR3 move = Homing(m_pos.x, m_pos.y, m_move.x, m_move.y);
			m_pos = CObject2D::AddMove(move);
		}
		else
		{
			//移動量の加算
			m_pos = CObject2D::AddMove(m_move);
		}
		break;
	default:
		//移動量の加算
		m_pos = CObject2D::AddMove(m_move);
		break;
	}

	//エフェクトの生成
	CEffect::Create(m_pos);

	//寿命の減少
	m_nLife--;

	//寿命が尽きた
	if (m_nLife <= 0.0f)
	{
		Uninit();
		return;
	}
	//画面外に出たら
	else if (CObject2D::OutScreen(m_pos))
	{
		Uninit();
		return;
	}

	//------------------------
	// 当たった処理
	//------------------------
	CollisionBullet(OBJTYPE_ENEMY);
	CollisionBullet(OBJTYPE_BARRIER);
}

//===========================
// 描画
//===========================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	CBullet *pBullet = nullptr;

	//----------------------------------
	// バレットの生成と初期化
	//----------------------------------
	pBullet = new CBullet;	//生成

	if (pBullet != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pBullet->m_move = move;		//移動量の代入
		pBullet->m_type = type;		//種類の代入

		//初期化
		pBullet->Init(pos);
		pBullet->SetObjType(OBJTYPE_BULLET);
	}

	return pBullet;
}

//=======================
// 弾の発射
//=======================
void CBullet::ShotBullet(D3DXVECTOR3 pos, int nLevel, int nShotTime)
{
	pos.x += 30.0f;	//発射位置の調整

	//---------------------------
	// レベルごとの弾
	//---------------------------
	if (!CInputKeyboard::Press(DIK_SPACE) && nShotTime == 0)
	{//チャージしていない時 かつ 弾の発射時間が0なら
		if (nLevel == 1)
		{//レベル2以下なら
			//右側に弾を発射する
			Create(pos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETTYPE_NORMAL);
		}

		if (nLevel == 2)
		{//レベル2なら
			D3DXVECTOR3 firstPos(pos.x, pos.y - 20.0f, pos.z);
			D3DXVECTOR3 secondPos(pos.x, pos.y + 20.0f, pos.z);

			//弾を2発に増やす
			Create(firstPos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETTYPE_NORMAL);
			Create(secondPos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETTYPE_NORMAL);
		}
		else if (nLevel >= 3)
		{//レベル3なら
			D3DXVECTOR3 firstPos(pos.x, pos.y - 20.0f, pos.z);
			D3DXVECTOR3 secondPos(pos.x, pos.y + 20.0f, pos.z);

			//右側に弾を発射する
			Create(pos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETTYPE_NORMAL);

			//小さい弾を左右に発射する
			Create(firstPos, D3DXVECTOR3(fBulletSpeed / 2, -1.0f, 0.0f), BULLETTYPE_OPTION);
			Create(secondPos, D3DXVECTOR3(fBulletSpeed / 2, 1.0f, 0.0f), BULLETTYPE_OPTION);
		}

		if (nLevel >= 4 && m_nCntHorming >= 3)
		{//レベル4なら
			D3DXVECTOR3 Pos(pos.x - 40.0f, pos.y - 40.0f, pos.z);
			Create(Pos, D3DXVECTOR3(-2.0f , -2.0f, 0.0f), BULLETTYPE_HORMING);
			m_nCntHorming = 0;
		}

		m_nCntHorming++;
	}

	//---------------------------
	// チャージショット
	//---------------------------
	/*if (CInputKeyboard::Press(DIK_SPACE))
	{//SPACEキーが押されている間
		m_nChageTime++;		//チャージ時間を加算
		
		if (m_nChageTime >= 40)
		{//チャージ時間が10以上なら
			CPlayer::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));	//プレイヤーの色を変更
		}
	}

	if (CInputKeyboard::Release(DIK_SPACE) && m_nChageTime >= 40)
	{//SPACEキーを離したとき かつ チャージ状態なら
		Create(pos, D3DXVECTOR3(fBulletSpeed, 0.0f, 0.0f), BULLETTYPE_CHARGE);
		
		for (int i = 0; i < nMaxHoming; i++)
		{
			Create(pos, D3DXVECTOR3(-5.0f, (float)(nMaxHoming - (i * nMaxHoming)), 0.0f), BULLETTYPE_HORMING);
		}

		m_nChageTime = 0;	//チャージ時間をリセット
		CPlayer::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//プレイヤーの色を変更
	}
	else if (CInputKeyboard::Release(DIK_SPACE) && m_nChageTime < 40)
	{
		m_nChageTime = 0;	//チャージ時間をリセット
	}*/
}

//=======================
// 当たった時の処理
//=======================
void CBullet::CollisionBullet(CObject::EObjType ObjType)
{
	CObject* pHitObject = CObject2D::GetCollision(ObjType);
	m_nPlayerAttack = CGame::GetPlayer()->GetAttack();

	if (pHitObject != nullptr)
	{//敵と当たった
		if (ObjType == OBJTYPE_ENEMY)
		{
			//pObjectをCEnemy型にダウンキャスト
			CEnemy* pEnemy = (CEnemy*)pHitObject;

			if (m_type == BULLETTYPE_CHARGE)
			{//チャージショットなら
				//ダメージ上昇
				pEnemy->SubLife(m_nPlayerAttack * 3);	//敵の体力の減少
			}
			else
			{//それ以外なら
				pEnemy->SubLife(m_nPlayerAttack);	//敵の体力の減少
			}

			pExplosion->Create(m_pos, (float)m_nPlayerAttack, (float)m_nPlayerAttack);//爆発の生成
			//pDamage->Create(m_pos, 20.0f, 30.0f, 20.0f, 2, m_nPlayerAttack);	//ダメージの表示

			//サウンドの再生
			CSound::PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

			//弾の消滅
			Uninit();
			return;
		}

		else if (ObjType == OBJTYPE_BARRIER)
		{
			//pObjectをCBarrier型にダウンキャスト
			CBarrier* pBarrier = (CBarrier*)pHitObject;

			//バリアの耐久を削る
			pBarrier->SubLife(m_type);

			//弾の消滅
			Uninit();
			return;
		}
	}
}

//=======================
// ホーミング弾
//=======================
D3DXVECTOR3 CBullet::Homing(float& posX, float& posY, float& moveX, float& moveY)
{
	//弾の元の速度
	float vx0 = moveX, vy0 = moveY;

	//自機方向の速度ベクトル(vx1,vy1)を求める
	float vx1, vy1;

	//目標までの距離dを求める
	float d = sqrtf((m_Tirget.x - posX) * (m_Tirget.x - posX)
		+ (m_Tirget.y - posY) * (m_Tirget.y - posY));

	if (d)
	{
		vx1 = (m_Tirget.x - posX) / d * fBulletSpeed_Homing;
		vy1 = (m_Tirget.y - posY) / d * fBulletSpeed_Homing;
	}
	else
	{
		vx1 = 0;
		vy1 = fBulletSpeed_Homing;
	}

	//右回り旋回角度上限の速度ベクトル(vx2,vy2)を求める
	float rad = (D3DX_PI / 180) * 5.0f; //旋回角度上限
	float vx2 = cosf(rad) * vx0 - sinf(rad) * vy0;
	float vy2 = sinf(rad) * vx0 + cosf(rad) * vy0;

	//自機方向と旋回角度上限のどちらに曲がるかを決める
	if (vx0 * vx1 + vy0 * vy1 >= vx0 * vx2 + vy0 * vy2)
	{//自機方向が旋回可能範囲内の場合
	 //自機方向に曲がる
		moveX = vx1;
		moveY = vy1;
	}
	else
	{
		//自機方向が旋回可能範囲外の場合
		//左回り旋回角度上限の速度ベクトル(vx3,vy3)を求める
		float vx3 = cosf(rad) * vx0 + sinf(rad) * vy0;
		float vy3 = -sinf(rad) * vx0 + cosf(rad) * vy0;

		//弾から自機への相対位置ベクトル(px,py)を求める
		float px = m_Tirget.x - posX, py = m_Tirget.y - posY;

		//右回りか左回りかを決める
		if (px * vx2 + py * vy2 >= px * vx3 + py * vy3)
		{//右回りの場合
			moveX = vx2;
			moveY = vy2;
		}
		else
		{//左回りの場合
			moveX = vx3;
			moveY = vy3;
		}
	}

	moveX *= fBulletSpeed_Homing;
	moveY *= fBulletSpeed_Homing;

	return D3DXVECTOR3(moveX, moveY, 0.0f);
}

//=======================
// 弾の大きさの設定
//=======================
void CBullet::SetBulletSize(float fLength)
{
	m_fWidth = fLength;
	m_fHeight = fLength;
}

//=======================
// 弾の種類を取得
//=======================
CBullet::BULLETTYPE CBullet::GetType()
{
	return m_type;
}