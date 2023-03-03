//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		TEXTURE_PLAYER = 0,			//プレイヤー

		/* ↓　エネミー　↓　*/
		TEXTURE_ENEMY_BIRD,			//敵(鳥)
		TEXTURE_ENEMY_RED,			//敵(赤)
		TEXTURE_ENEMY_BLUE,			//敵(青)
		TEXTURE_ENEMY_GREEN,		//敵(緑)
		TEXTURE_ENEMY_PINK,			//敵(桃)
		TEXTURE_ENEMY_BIG,			//大きい敵

		/* ↓ ゲーム ↓*/
		TEXTURE_BULLET,				//弾
		TEXTURE_ENEMYBULLET,		//敵の弾
		TEXTURE_HEART,				//ハート
		TEXTURE_EFFECT,				//エフェクト
		TEXTURE_BARRIER,			//バリア

		/* ↓ BG ↓*/
		//ゲーム
		TEXTURE_BG_GAME,			//ゲーム画面の背景
		TEXTURE_BG_GAME_TIME,		//タイム
		TEXTURE_BG_GAME_SCORE,		//スコア
		//タイトル
		TEXTURE_BG_TITLE,			//タイトル画面の背景
		TEXTURE_BG_TITLE_LOGO,		//タイトルロゴ
		TEXTURE_BG_TITLE_PRESSENTER,//プレスエンター
		TEXTURE_BG_TITLE_TIME,		//タイムアタック
		TEXTURE_BG_TITLE_SCORE,		//スコアアタック
		TEXTURE_BG_TITLE_TUTORIAL,	//チュートリアル
		//リザルト
		TEXTURE_BG_RESULT,			//リザルト画面の背景
		TEXTURE_BG_RESULTTEXT,		//リザルト画面の文字
		//チュートリアル
		TEXTURE_BG_TUTORIAL1,		//チュートリアル1
		TEXTURE_BG_TUTORIAL2,		//チュートリアル2

		/* ↓ UI ↓*/
		TEXTURE_EXP,				//経験値
		TEXTURE_LEVEL,				//レベル
		TEXTURE_HPFREAM,			//HPバーのフレーム

		/* ↓ スキル ↓*/
		TEXTURE_SKILL_HPHEAL,		//スキル(体力回復)
		TEXTURE_SKILL_SPEEDUP_FIRE,	//スキル(弾速強化)
		TEXTURE_SKILL_ATTACKUP,		//スキル(攻撃力上昇)
		TEXTURE_SKILL_SPEEDUP,		//スキル(速度上昇)

		/* ↓ 共通 ↓*/
		TEXTURE_NUMBER,				//数字

		TEXTURE_MAX,
		TEXTURE_NONE,			//使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
