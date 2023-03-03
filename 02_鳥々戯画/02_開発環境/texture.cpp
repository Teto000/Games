//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "texture.h"
#include "renderer.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::s_FileName[] =
{// テクスチャのパス
	"data/TEXTURE/Player.png",		//プレイヤー

	/* ↓　エネミー　↓　*/
	"data/TEXTURE/Enemy/Bird.png",		//敵(鳥)
	"data/TEXTURE/Enemy/Red.png",		//敵(赤)
	"data/TEXTURE/Enemy/Blue.png",		//敵(青)
	"data/TEXTURE/Enemy/Green.png",		//敵(緑)
	"data/TEXTURE/Enemy/Pink.png",		//敵(桃)
	"data/TEXTURE/Enemy/Big2.png",		//大きい敵

	/* ↓ ゲーム ↓　*/
	"data/TEXTURE/Game/Bullet.png",		//弾
	"data/TEXTURE/Game/EnemyBullet.png",//敵の弾
	"data/TEXTURE/Game/HitEffect.png",	//ハート
	"data/TEXTURE/Game/Effect.jpg",		//エフェクト
	"data/TEXTURE/Game/Barrier.png",	//バリア

	/* ↓ BG ↓　*/
	//ゲーム
	"data/TEXTURE/BG/Game.png",			//背景
	"data/TEXTURE/BG/Time.png",			//タイム
	"data/TEXTURE/BG/Score.png",		//スコア
	//タイトル
	"data/TEXTURE/BG/Title.png",		//タイトル画面の背景
	"data/TEXTURE/BG/TitleLogo.png",	//タイトルロゴ
	"data/TEXTURE/BG/PressEnter.png",	//プレスエンター
	"data/TEXTURE/BG/TimeAttack.png",	//タイムアタック
	"data/TEXTURE/BG/ScoreAttack.png",	//スコアアタック
	"data/TEXTURE/BG/GoTutorial.png",	//チュートリアル
	//リザルト
	"data/TEXTURE/BG/Result.png",		//リザルト画面の背景
	"data/TEXTURE/BG/ResultText.png",	//リザルト画面の文字
	//チュートリアル
	"data/TEXTURE/BG/Tutorial1.png",	//チュートリアル1
	"data/TEXTURE/BG/Tutorial2.png",	//チュートリアル2

	/* ↓ UI ↓　*/
	"data/TEXTURE/UI/Exp.png",			//経験値
	"data/TEXTURE/UI/Level.png",		//レベル
	"data/TEXTURE/UI/HPFream.png",		//HPバーのフレーム

	/* ↓ スキル ↓　*/
	"data/TEXTURE/Skill/HPheal.png",		//スキル(体力回復)
	"data/TEXTURE/Skill/SpeedUp_Fire.png",	//スキル(弾速強化)
	"data/TEXTURE/Skill/AttackUp.png",		//スキル(攻撃力上昇)
	"data/TEXTURE/Skill/SpeedUp.png",		//スキル(速度上昇)

	/* ↓ 共通 ↓　*/
	"data/TEXTURE/Number.png",		//数字
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの解放
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// 読み込み
	Load(inTexture);

	return s_pTexture[inTexture];
}
