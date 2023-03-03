//=====================================
//
// ゲームヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _GAME_H_
#define _GAME_H_	

//--------------------
// インクルード
//--------------------
#include <d3dx9.h>
#include "application.h"

//-----------------------
// 前方宣言
//-----------------------
class CPlayer;	//プレイヤー
class CEnemy;	//敵
class CScore;	//スコア
class CBg;		//背景
class CSkill;	//スキル
class CTimer;	//タイム

//-------------------------
// ゲームクラスの定義
//-------------------------
class CGame
{
public:
	enum MODE
	{
		MODE_TIME = 0,	//タイムアタック
		MODE_SCORE,		//スコアアタック
		MODE_MAX
	};

	enum EnemyName
	{
		NORMAL = 0,	//通常敵
		HORMING,	//ホーミング
		HPITEM,		//HPアイテム
		MPITEM,		//MPアイテム
		BIG,		//大きい敵
		MAX
	};

	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	void SetMode(CApplication::GAMEMODE mode);

	//------------------
	// 静的メンバ関数
	//------------------
	static CPlayer	*GetPlayer();	//プレイヤーの取得
	static CScore	*GetScore();	//スコアの取得
	static CBg		*GetBG();		//背景の取得
	static CTimer	*GetTimer();	//時間の取得

	static void SetMode(MODE mode);

private:
	void AppearEnemy();
	void SetEnemy(float X, float Y, EnemyName type);

private:
	//------------------
	// 定数
	//------------------
	static const int nOneSecond = 60;	//一秒
	static const int nMaxBg = 3;		//背景の最大数
	static const int nMaxSkill = 4;		//スキルの最大数

	//------------------
	// メンバ変数
	//------------------
	int m_EnemyCnt;
	int m_nTime;
	int m_nSkillTime[nMaxSkill];
	bool m_bSkill[nMaxSkill];
	EnemyName m_type;

	//------------------
	// 静的メンバ変数
	//------------------
	static CPlayer	*m_pPlayer;				//プレイヤークラス
	static CEnemy	*m_pEnemy;				//敵クラス
	static CScore	*m_pScore;				//スコアクラス
	static CBg		*m_pBG[nMaxBg];			//背景クラス
	static CSkill	*m_pSkill[nMaxSkill];	//スキルクラス
	static CTimer	*m_pTimer;				//タイマークラス

	static MODE m_mode;
};

#endif