//=====================================
//
// ゲームモードヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_	

//--------------------
// インクルード
//--------------------
#include "object2D.h"

//--------------------
// 前方宣言
//--------------------
class CBg;	//背景

//----------------------------
// ゲームモードクラスの定義
//----------------------------
class CGameMode : public CObject
{
public:
	enum GAMEMODE
	{
		GAMEMODE_TIME = 0,	//タイムアタック
		GAMEMODE_SCORE,		//スコアアタック
		GAMEMODE_TUTORIAL,	//チュートリアル
		GAMEMODE_MAX
	};

	CGameMode();	//コンストラクタ
	~CGameMode();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//ゲッター
	D3DXVECTOR3 GetPosition() override;		//位置の取得
	float GetWidth() override;				//幅の取得
	float GetHeight() override;				//高さの取得
	CObject2D* GetObject2D();

	//------------------
	// 静的メンバ関数
	//------------------
	static CGameMode *Create(D3DXVECTOR3 pos, GAMEMODE mode);

private:
	//----------------
	// メンバ変数
	//----------------
	CObject2D *m_pObject2D;	//オブジェクト2D
	D3DXVECTOR3 m_pos;		//位置
	float m_fWidth;			//幅
	float m_fHeight;		//高さ
	GAMEMODE m_mode;		//モード
	CBg*	m_pBg;			//背景
};

#endif