//=====================================
//
// タイトルヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _TITLE_H_
#define _TITLE_H_	

//--------------------
// インクルード
//--------------------
#include <d3dx9.h>

//-----------------------
// 前方宣言
//-----------------------
class CBg;			//背景
class CGameMode;	//ゲームモード

//-------------------------
// タイトルクラスの定義
//-------------------------
class CTitle
{
public:
	CTitle();	//コンストラクタ
	~CTitle();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// 静的メンバ関数
	//------------------
	static CBg	*GetBG();	//背景の取得

private:
	void SelectMode();
	void ChangeNumber();

private:
	//------------------
	// 定数
	//------------------
	static const int MaxBg = 3;		//背景の最大数
	static const int MaxMode = 3;	//モードの最大数
	static const int AnimationTime = 80;

	//------------------
	// メンバ変数
	//------------------
	int nCntTime;			//アニメーションカウント
	int nNumber;			//選択中の番号
	bool m_bPressEneter;	//エンターキーが押されたか

	//------------------
	// 静的メンバ変数
	//------------------
	static CBg		 *m_pBG[MaxBg];			//背景クラス
	static CGameMode *m_pGameMode[MaxMode];	//ゲームモードクラス
};

#endif