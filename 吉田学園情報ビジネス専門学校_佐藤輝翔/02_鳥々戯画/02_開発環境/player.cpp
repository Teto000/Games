//===================================
//
// プレイヤーの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "player.h"
#include "main.h"
#include "renderer.h"
#include "application.h"
#include "object2D.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "texture.h"
#include "sound.h"
#include "bullet.h"
#include "hp.h"
#include "mp.h"
#include "skill.h"
#include "level.h"
#include "hpfream.h"
#include "barrier.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CPlayer::fPlayerSpeed = 7.0f;
D3DXCOLOR CPlayer::m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

//===========================
// コンストラクタ
//===========================
CPlayer::CPlayer() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_nLife = 0;				//体力
	m_nMaxLife = 0;				//最大体力
	m_nRemLife = 0;				//残り体力
	m_nMagic = 0;				//MP
	m_nMaxMagic = 0;			//最大MP
	m_nRemMagic = 0;			//残りMP
	m_nAttack = 0;				//攻撃力
	m_nLevel = 0;				//レベル
	m_nShotTime = 0;			//弾の発射時間
	m_nCntShotTime = 0;			//弾の発射時間を数える
	m_nCntInvincible = 0;		//無敵時間を数える
	m_nCntSkill[nMaxSkill] = {};//スキルの使用可能時間を数える
	m_nCntTime = 0;				//テクスチャアニメーションカウント
	m_nSpeed = 0.0f;			//速度
	m_fWidth = 0.0f;			//幅
	m_fHeight = 0.0f;			//高さ
	m_bSlill[nMaxSkill] = {};	//スキル使用可能かどうか
	m_type = PLAYERSTATE_NORMAL;//状態
	m_Hp = nullptr;				//HPクラス
	m_Mp = nullptr;				//MPクラス
	m_Level = nullptr;			//レベルクラス
	m_Bullet = nullptr;			//弾クラス
	m_pHpFream = nullptr;		//HPフレームクラス
	m_pBarrier = nullptr;		//バリアクラス
}

//===========================
// デストラクタ
//===========================
CPlayer::~CPlayer()
{

}

//===========================
// 初期化
//===========================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;
	m_nLife = nPlayerLife;		//体力
	m_nMaxLife = nPlayerLife;	//最大体力
	m_nRemLife = nMaxLife;		//残り体力
	m_nMagic = 100;				//MP
	m_nMaxMagic = 100;			//最大MP
	m_nRemMagic = 100;			//残りMP
	m_fWidth = 70.0f;			//幅
	m_fHeight = 80.0f;			//高さ
	m_nAttack = 15;				//攻撃力
	m_nShotTime = 20;			//弾の発射時間
	m_nSpeed = fPlayerSpeed;	//速度

	for (int i = 0; i < nMaxSkill; i++)
	{
		m_nCntSkill[i] = 0;
		m_bSlill[i] = false;
	}

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);	//テクスチャの設定

	m_pos = CObject2D::GetPosition();

	//テクスチャ座標の設定
	CObject2D::SetTexCIE(0.0f, 0.5f);

	//--------------------------
	// HPの表示
	//--------------------------
	m_Hp = CHp::Create(D3DXVECTOR3(520.0f, 60.0f, 0.0f), 600.0f, 60.0f);
	m_Hp->SetLife(m_nLife, m_nRemLife);	//初期HPの設定

	//--------------------------
	// MPの表示
	//--------------------------
	m_Mp = CMp::Create(D3DXVECTOR3(520.0f, 110.0f, 0.0f), 600.0f, 20.0f);
	m_Mp->SetMP(m_nMagic, m_nRemMagic);	//初期HPの設定

	//--------------------------
	// レベルの生成
	//--------------------------
	m_Level = CLevel::Create();

	//--------------------------
	// フレームの生成
	//--------------------------
	m_pHpFream = CHpFream::Create(D3DXVECTOR3(520.0f, 60.0f, 0.0f), 600.0f, 60.0f);

	return S_OK;
}

//===========================
// 終了
//===========================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CPlayer::Update()
{
	CObject2D::Update();

	//--------------------
	// プレイヤーの操作
	//--------------------
	D3DXVECTOR3 move = OperationPlayer();
	//D3DXVECTOR3 move = MoveJoypad();

	//---------------------------
	// テクスチャアニメーション
	//---------------------------
	Animation();

	//--------------------
	// 移動量を更新(減衰)
	//--------------------
	m_move.x += (0.0f - move.x) * 0.4f;
	m_move.y += (0.0f - move.y) * 0.4f;

	//--------------------
	// 位置に移動量を加算
	//--------------------
	m_pos = CObject2D::AddMove(m_move);

	//--------------------
	// 画面端の設定
	//--------------------
	CObject2D::SetScreenX(m_pos.x, 0.0f + m_fWidth / 2, SCREEN_WIDTH - m_fWidth / 2);
	CObject2D::SetScreenY(m_pos.y, 0.0f + 200.0f, SCREEN_HEIGHT - 140.0f);
	
	//--------------------
	// レベルによる変化
	//--------------------
	m_nLevel = m_Level->GetLevel();	//レベルの取得
	//m_nAttack += (10 * (m_nLevel -1));

	//--------------------------
	// 弾の発射
	//--------------------------
	if (!CObject2D::GetCollision(OBJTYPE_BARRIER))
	{//バリアの範囲外なら
		m_nCntShotTime++;
		m_nCntShotTime %= m_nShotTime;	//発射時間をリセット

		m_Bullet->ShotBullet(m_pos, m_nLevel, m_nCntShotTime);	//弾の発射
	}

	//--------------------------
	// スキルの発動
	//--------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (!m_bSlill[i] && m_nMagic >= 10)
		{//スキルを使用していない & MPが10以上なら
			SetSkill();
		}
	}

	//--------------------------
	// スキルの効果が切れる
	//--------------------------
	for (int i = 0; i < nMaxSkill; i++)
	{
		if (m_bSlill[i])
		{//スキル使用状態なら
			m_nCntSkill[i]++;

			if (m_nCntSkill[i] >= 600)
			{
				m_bSlill[i] = false;
				m_nCntSkill[i] = 0;
			}
			else if (m_nCntSkill[i] >= 300)
			{//5秒経過したら
				m_nAttack = 10;				//攻撃力
				m_nShotTime = 20;			//弾の発射時間
				m_nSpeed = fPlayerSpeed;	//速度
			}
		}
	}

	//------------------------
	// 敵との当たり判定
	//------------------------
	if (m_type != PLAYERSTATE_INVINCIBLE && CObject2D::GetCollision(OBJTYPE_ENEMY))
	{//無敵でない状態 かつ 敵と当たったら
		m_nLife -= 20;	//プレイヤーの体力の減少

		//残り体力を計算
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP減少時の処理
		m_Hp->SetLife(m_nLife, m_nRemLife);

		m_type = PLAYERSTATE_INVINCIBLE;
	}

	//----------------------------
	// 無敵時間
	//----------------------------
	if (m_type == PLAYERSTATE_INVINCIBLE)
	{
		InvincibleTime();
	}

	//--------------------------
	// 体力が尽きた
	//--------------------------
	if (m_nLife <= 0)
	{
		//敵の消滅
		Uninit();

		Sleep(300);

		//リザルト画面に移行
		CApplication::SetMode(CApplication::MODE_RESULT);
		return;
	}

	CObject2D::SetColor(m_col);
}

//===========================
// 描画
//===========================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CPlayer *CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pPlayer = new CPlayer;	//生成

	if (pPlayer != nullptr)
	{//NULLチェック
		//初期化
		pPlayer->Init(D3DXVECTOR3(400.0f, SCREEN_HEIGHT / 2, 0.0f));
		pPlayer->SetObjType(OBJTYPE_PLAYER);
	}

	return pPlayer;
}

//===========================
// プレイヤーの操作
//===========================
D3DXVECTOR3 CPlayer::OperationPlayer()
{
	if (CInputKeyboard::Press(DIK_A) == true)
	{//Aキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;		//上左移動
			m_move.x += sinf(-D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;		//下左移動
			m_move.x += sinf(-D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * m_nSpeed;		//左移動
		}
	}
	else if (CInputKeyboard::Press(DIK_D) == true)
	{//Dキーが押された
		if (CInputKeyboard::Press(DIK_W) == true)
		{//Wキーが押された
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;		//上右移動
			m_move.x += sinf(D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (CInputKeyboard::Press(DIK_S) == true)
		{//Sキーが押された
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;		//下右移動
			m_move.x += sinf(D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * m_nSpeed;		//右移動
		}
	}
	else if (CInputKeyboard::Press(DIK_W) == true)
	{//Wキーが押された
		m_move.y += cosf(-D3DX_PI * 1.0f) * m_nSpeed;			//上移動
	}
	else if (CInputKeyboard::Press(DIK_S) == true)
	{//Sキーが押された
		m_move.y += cosf(D3DX_PI * 0.0f) * m_nSpeed;			//下移動
	}

	return m_move;
}

//===========================
// ジョイパッドを使った移動
//===========================
D3DXVECTOR3 CPlayer::MoveJoypad()
{
	// ジョイパッドでの操作
	CInputJoypad* joypad = CApplication::GetJoypad();
	D3DXVECTOR3 stick = joypad->Stick(CInputJoypad::JOYKEY_LEFT_STICK, 0);

	//if (joypad->IsJoyPadUse(0) == false)
	//{//ジョイパッドが使われていないなら
	//	return ;
	//}

	//スティックを動かす値の設定
	float fMoveValue = 0.5f;

	//-----------------------------------
	// 右移動
	//-----------------------------------
	if (stick.x >= fMoveValue)
	{
		if (stick.y <= -fMoveValue)
		{//奥移動
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;
			m_move.x += sinf(D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (stick.y >= fMoveValue)
		{//前移動
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;
			m_move.x += sinf(D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(D3DX_PI * 0.5f) * m_nSpeed;
		}
	}
	//-----------------------------------
	// 左移動
	//-----------------------------------
	else if (stick.x <= -fMoveValue)
	{
		// スティックを倒した方向へ移動する
		if (stick.y <= -fMoveValue)
		{//奥移動
			m_move.y += cosf(-D3DX_PI * 0.75f) * m_nSpeed;
			m_move.x += sinf(-D3DX_PI * 0.75f) * m_nSpeed;
		}
		else if (stick.y >= fMoveValue)
		{//前移動
			m_move.y += cosf(D3DX_PI * 0.25f) * m_nSpeed;
			m_move.x += sinf(-D3DX_PI * 0.25f) * m_nSpeed;
		}
		else
		{
			m_move.x += sinf(-D3DX_PI * 0.5f) * m_nSpeed;
		}
	}
	//-----------------------------------
	// 奥移動
	//-----------------------------------
	else if (stick.y <= -fMoveValue)
	{
		m_move.y += cosf(-D3DX_PI * 1.0f) * m_nSpeed;
	}
	//-----------------------------------
	// 前移動
	//-----------------------------------
	else if (stick.y >= fMoveValue)
	{
		m_move.y += cosf(D3DX_PI * 0.0f) * m_nSpeed;
	}

	return m_move;
}

//===========================
// スキルの発動
//===========================
void CPlayer::SetSkill()
{
	//-----------------------
	// 体力の回復
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_U) && !m_bSlill[0])
	{//1キーが押されたら
		if (m_nLife + 50 >= m_nMaxLife)
		{//回復して上限なら
			m_nLife = m_nMaxLife;	//体力を最大にする
		}
		else
		{//それ以外なら
			m_nLife += 50;	//体力を回復
		}

		//残り体力を計算
		m_nRemLife = m_nLife * 100 / m_nMaxLife;

		//HP減少時の処理
		m_Hp->SetLife(m_nLife, m_nRemLife);

		//MPの減少
		AddMagic(-10);

		m_bSlill[0] = true;

		//サウンドの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}

	//-----------------------
	// 弾速の強化
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_I) && !m_bSlill[1])
	{//2キーが押されたら
		//発射間隔の減少
		m_nShotTime = 10;

		//MPの減少
		AddMagic(-10);

		m_bSlill[1]= true;

		//サウンドの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}

	//-----------------------
	// 攻撃力上昇
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_O) && !m_bSlill[2])
	{
		//攻撃力の上昇
		m_nAttack = 30;

		//MPの減少
		AddMagic(-10);

		m_bSlill[2] = true;

		//サウンドの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}

	//-----------------------
	// 速度上昇
	//-----------------------
	if (CInputKeyboard::Trigger(DIK_P) && !m_bSlill[3])
	{
		//速度の上昇
		m_nSpeed = 10.0f;

		//MPの減少
		AddMagic(-10);

		m_bSlill[3] = true;

		//サウンドの再生
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SKILL);
	}
}

//===========================
// 無敵時間
//===========================
void CPlayer::InvincibleTime()
{
	m_nCntInvincible++;

	//色の変更
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	if (m_nCntInvincible >= 120)
	{//無敵時間が終わったら
		m_type = PLAYERSTATE_NORMAL;	//通常の状態に戻す
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_nCntInvincible = 0;
	}
}

//============================
// テクスチャアニメーション
//============================
void CPlayer::Animation()
{
	m_nCntTime++;
	m_nCntTime %= 80;	//リセット

	if (m_nCntTime >= 40)
	{
		CObject2D::SetTexCIE(0.0f, 0.5f);	//テクスチャ座標の設定
	}
	else
	{
		CObject2D::SetTexCIE(0.5f, 1.0f);
	}
}

//===========================
// HPの加算
//===========================
void CPlayer::AddLife(int nValue)
{
	if (m_nLife + nValue < m_nMaxLife)
	{
		m_nLife += nValue;	//プレイヤーの体力の加算
	}
	else
	{
		m_nLife = m_nMaxLife;
	}

	//残り体力を計算
	m_nRemLife = m_nLife * 100 / m_nMaxLife;

	//HP減少時の処理
	m_Hp->SetLife(m_nLife, m_nRemLife);
}

//===========================
// MPの加算
//===========================
void CPlayer::AddMagic(int nValue)
{
	if (m_nMagic + nValue < m_nMaxMagic)
	{//最大MPを超えないなら
		m_nMagic += nValue;	//プレイヤーのMPの加算
	}
	else 
	{
		//MPを最大にする
		m_nMagic = m_nMaxMagic;
	}

	//残りMPを計算
	m_nRemMagic = m_nMagic * 100 / m_nMaxMagic;

	//MP減少時の処理
	m_Mp->SetMP(m_nMagic, m_nRemMagic);
}

//===========================
// 色の設定
//===========================
void CPlayer::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//===========================
// 移動量の取得
//===========================
D3DXVECTOR3 CPlayer::GetMove()
{
	return m_move;
}

//===========================
// 体力の取得
//===========================
int CPlayer::GetLife()
{
	return m_nLife;
}

//===========================
// 残り体力の取得
//===========================
int CPlayer::GetRemLife()
{
	return m_nRemLife;
}

//===========================
// 攻撃力の取得
//===========================
int CPlayer::GetAttack()
{
	return m_nAttack;
}

//===========================
// プレイヤーの状態の取得
//===========================
CPlayer::PLAYERSTATE CPlayer::GetState()
{
	return m_type;
}