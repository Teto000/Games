//=====================================
//
// リザルトヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _RESULT_H_
#define _RESULT_H_	

//--------------------
// インクルード
//--------------------
#include <d3dx9.h>

//-----------------------
// 前方宣言
//-----------------------
class CBg;		//背景
class CScore;	//スコア
class CTimer;	//タイム

//-------------------------
// リザルトクラスの定義
//-------------------------
class CResult
{
public:
	CResult();	//コンストラクタ
	~CResult();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// 静的メンバ関数
	//------------------
	static CBg		*GetBG();		//背景の取得
	static CScore	*GetScore();	//スコアの取得
	static CTimer	*GetTimer();	//タイマーの取得

private:
	//------------------
	// 定数
	//------------------
	static const int MaxBg = 2;	//背景の最大数

	//------------------
	// 静的メンバ変数
	//------------------
	static CBg		*m_pBG[MaxBg];	//背景クラス
	static CScore	*m_pScore;		//スコアクラス
	static CTimer	*m_pTime;		//タイムクラス
};

#endif